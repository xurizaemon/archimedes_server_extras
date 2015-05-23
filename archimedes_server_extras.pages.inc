<?php

/**
 * Page callbacks.
 */

/**
 * Return a Nagios configuration snippet to check_site each hosted
 * site.
 */
function archimedes_server_extras_nagios_config_sites_page() {
  $output[] = '# Automated Nagios configuration sourced from Archimedes.';

  // Production sites only.
  $terms = taxonomy_get_term_by_name('Production');
  $term = reset($terms);

  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'website')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_webserver', 'value', 'NULL', '!=')
    ->fieldCondition('field_webserver', 'value', array('fuci.fuzion.co.nz', 'fudge.fuzion.co.nz'), 'NOT IN')
    ->fieldCondition('field_site_env', 'tid', $term->tid)
    ->propertyCondition('changed', strtotime('-1 week'), '>=');
  $result = $query->execute();

  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $websites = entity_load('node', $nids);
    foreach ($websites as $website) {
      // $node->title
      $server               = field_get_items('node', $website, 'field_webserver');
      $website->environment = field_get_items('node', $website, 'field_site_env');
      $website->site_data   = field_get_items('node', $website, 'field_sitedata');
      $website->site_size   = field_get_items('node', $website, 'field_sitesize');
      $website->db_size     = field_get_items('node', $website, 'field_db_size');
      $website->alias       = t('"@title"', array('@title' => $website->title));
      $website->url         = field_get_items('node', $website, 'field_servername');
      $website->webserver   = field_get_items('node', $website, 'field_webserver');
      $servers[$server[0]['value']][$website->nid] = $website;
    }
    $output[] = '';
    ksort($servers);
    foreach ($servers as $hostname => $sites) {
      $variables = array();

      // Hardcoding backup times here for now. Refs #7691.
      switch ($hostname) {
        case '':
          $variables['backups_timeperiod'] = '19:00-21:00';
          break;

        case 'aba.fuzion.co.nz':
          $variables['backups_timeperiod'] = '02:00-04:00';
          break;

        case 'euro.fuzion.co.nz':
          $variables['backups_timeperiod'] = '13:00-15:00';
          break;

        case 'fuci':
          $variables['backups_timeperiod'] = '18:00-20:00';
          break;

        case 'imba.fuzion.co.nz':

        case 'p3915893.pubip.serverbeach.com':
          $variables['backups_timeperiod'] = '01:00-03:00';
          break;

        case 'www.internetnz.net.nz':
          $variables['backups_timeperiod'] = '01:00-05:00';
          break;

        case 'fugu.fuzion.co.nz':
        case 'alfresco':
        case 'archer':
        case 'aba.fuzion.co.nz':
        default:
          $variables['backups_timeperiod'] = '01:00-02:00';
      }

      if (empty($hostname)) {
        $hostname = 'host_' . substr(md5(print_r($sites,1)), 0, 6);
      }


      $variables['server'] = $hostname;
      $variables['address'] = $hostname;
      $variables['use'] = 'generic-host';
      $variables['hostgroups'] = 'site-monitoring';

      $output[] = theme('nagios_host_template', $variables);

      foreach ($sites as $site) {
        $url = parse_url($site->url[0]['url']);
        $url['ssl_arg'] = $url['scheme'] == 'https' ? '--ssl' : '';
        $variables = array_merge($variables, $url);
        $output[] = theme('nagios_site_template', $variables);
        $output[] = theme('nagios_googlesafebrowsing', $variables);
      }

    }
  }

  // return '<pre>' . implode("\n", $output) . '</pre>';
  header('Content-type: text/plain');
  print implode("\n", $output);
  drupal_exit();
}

/**
 * Output Munin configuration for site data.
 */
function archimedes_server_extras_munin_config_sites_page() {
  // Find all current websites.
  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'website')
    ->propertyCondition('status', NODE_PUBLISHED);
  // ->fieldCondition('field_webserver', 'value', 'NULL', 'NOT NULL');
  $result = $query->execute();
  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $websites = entity_load('node', $nids);
    foreach ($websites as $website) {
      // $node->title
      $server               = field_get_items('node', $website, 'field_webserver');
      $website->environment = field_get_items('node', $website, 'field_site_env');
      $website->site_data   = field_get_items('node', $website, 'field_sitedata');
      $website->site_size   = field_get_items('node', $website, 'field_sitesize');
      $website->db_size     = field_get_items('node', $website, 'field_db_size');
      $website->alias       = t('"@title"', array('@title' => $website->title));
      $website->servername  = field_get_items('node', $website, 'field_servername');
      $servers[$server[0]['value']][$website->nid] = $website;
    }
    $output[] = '[Hosting]';
    $output[] = '  update no';
    $graphs = array(
      'archimedes_website_size' => '@server - Website Codebase',
      'archimedes_website_data' => '@server - Website Media',
      'archimedes_website_db' => '@server - Website DB',
      'archimedes_website_total' => '@server - Website Total',
    );
    $output[] = '';
    foreach ($servers as $hostname => $sites) {
      foreach ($graphs as $id => $graph_title) {
        $short_hostname = preg_replace('/\..*/', '', $hostname);
        if (!empty($short_hostname)) {
          $graph_id = $short_hostname . '_' . $id;
          $targs = array(
            '@id'       => $id,
            '@graph_id' => $graph_id,
            '@server'   => $hostname,
          );
          $output[] = '';
          $targs['@title'] = t($graph_title, $targs);
          $output[] = t('  @graph_id.graph_title @title', $targs);
          $output[] = t('  @graph_id.graph_category hosting', $targs);
          $output[] = t('  @graph_id.graph_order \\', $targs);
          foreach ($sites as $nid => $site) {
            $targs['@title'] = $site->alias;
            $servername = reset($site->servername);
            $url = parse_url($servername['url']);
            $targs['@url'] = $url['host'];
            $targs['@value'] = _archimedes_munin_format($url['host']);
            // $targs['@environment'] = $site->environment;
            //$line =
            $output[] = t('    @value=fuzion.co.nz;archer.fuzion.co.nz:@id.@value \\', $targs);
          }
          $last_row_id = count($output)-1;
          $output[$last_row_id] = str_replace('\\', '', $output[$last_row_id]);
        }
      }
    }
  }
  // return t('<pre>!output</pre>', array('!output' => implode("\n",$output)));
  header('Content-type: text/plain');
  print implode("\n", $output);
  drupal_exit();
}

/**
 * Return a collection of Drush aliases.
 */
function archimedes_server_extras_drush_aliases_page($server = NULL) {
  if (empty($server)) {
    $query = db_select('field_data_field_webserver', 'w')
      ->fields('w', array('field_webserver_value'))
      ->distinct()
      ->execute();
    while ($result = $query->fetchAssoc()) {
      $items[] = l($result['field_webserver_value'], t('drush/aliases/@server', array('@server' => $result['field_webserver_value'])));
    }
    return theme('item_list', array('items' => $items));
  }

  $output[] = '<?php';
  $output[] = '// Automated Drush aliases sourced from Archimedes.';

  // Production sites only.
  $terms = taxonomy_get_term_by_name('Production');
  $term = reset($terms);

  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'website')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_webserver', 'value', 'NULL', '!=')
    ->fieldCondition('field_site_env', 'tid', $term->tid)
    ->propertyCondition('changed', strtotime('-1 week'), '>=')
    ->propertyOrderBy('changed');
  if (!empty($server)) {
    $query
      ->fieldCondition('field_webserver', 'value', $server);
  }
  $result = $query->execute();

  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $websites = entity_load('node', $nids);
    foreach ($websites as $website) {
      // $node->title
      $server               = field_get_items('node', $website, 'field_webserver');
      $website->environment = field_get_items('node', $website, 'field_site_env');
      $website->site_data   = field_get_items('node', $website, 'field_sitedata');
      $website->site_size   = field_get_items('node', $website, 'field_sitesize');
      $website->db_size     = field_get_items('node', $website, 'field_db_size');
      $website->alias       = t('"@title"', array('@title' => $website->title));
      $website->url         = field_get_items('node', $website, 'field_servername');
      $website->webserver   = field_get_items('node', $website, 'field_webserver');
      $website->wwwroot     = field_get_items('node', $website, 'field_webroot');
      $website->parsed_url  = parse_url($website->url[0]['url']);
      $website->uri         = preg_replace('/^www\./', '', $website->parsed_url['host']);
      $servers[$server[0]['value']][$website->uri] = $website;
    }
    $output[] = '';

    foreach ($servers as $hostname => $sites) {
      $variables = array(
        'remote_host' => $hostname,
      );

      $output[] = t('// Sites for @server', array('@server' => $hostname));

      // Sort found websites alphabetically.
      ksort($sites);

      foreach ($sites as $site) {
        $url = parse_url($site->url[0]['url']);
        $variables = array_merge($variables, $url);
        $variables['uri'] = $site->uri;
        $variables['root'] = $site->wwwroot[0]['value'];
        // $output[] = print_r($variables,1);
        $output[] = theme('drush_alias_entry', $variables);
      }
    }
  }

  // return '<pre>' . implode("\n", $output) . '</pre>';
  header('Content-type: text/plain');
  print implode("\n", $output);
  drupal_exit();
}
