<?php
/**
 * @file
 * archimedes_server_extras.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function archimedes_server_extras_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'fz_sites_using_module';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Fz Arch: Sites Using Module';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'views_access_callback';
  $handler->display->display_options['access']['views_access_callback'] = 'archimedes_munin_access_callback';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_drupal_mod_node']['id'] = 'reverse_field_drupal_mod_node';
  $handler->display->display_options['relationships']['reverse_field_drupal_mod_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_drupal_mod_node']['field'] = 'reverse_field_drupal_mod_node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'project';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Drupal compatibility */
  $handler->display->display_options['fields']['field_drupal_compat']['id'] = 'field_drupal_compat';
  $handler->display->display_options['fields']['field_drupal_compat']['table'] = 'field_data_field_drupal_compat';
  $handler->display->display_options['fields']['field_drupal_compat']['field'] = 'field_drupal_compat';
  $handler->display->display_options['fields']['field_drupal_compat']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_drupal_compat']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Major version */
  $handler->display->display_options['fields']['field_major_version']['id'] = 'field_major_version';
  $handler->display->display_options['fields']['field_major_version']['table'] = 'field_data_field_major_version';
  $handler->display->display_options['fields']['field_major_version']['field'] = 'field_major_version';
  $handler->display->display_options['fields']['field_major_version']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_major_version']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Version patch */
  $handler->display->display_options['fields']['field_version_patch']['id'] = 'field_version_patch';
  $handler->display->display_options['fields']['field_version_patch']['table'] = 'field_data_field_version_patch';
  $handler->display->display_options['fields']['field_version_patch']['field'] = 'field_version_patch';
  $handler->display->display_options['fields']['field_version_patch']['label'] = 'version';
  $handler->display->display_options['fields']['field_version_patch']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_version_patch']['alter']['text'] = '[field_drupal_compat]-[field_major_version].[field_version_patch]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'reverse_field_drupal_mod_node';
  $handler->display->display_options['fields']['title_1']['label'] = 'site_name';
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_servername']['id'] = 'field_servername';
  $handler->display->display_options['fields']['field_servername']['table'] = 'field_data_field_servername';
  $handler->display->display_options['fields']['field_servername']['field'] = 'field_servername';
  $handler->display->display_options['fields']['field_servername']['relationship'] = 'reverse_field_drupal_mod_node';
  $handler->display->display_options['fields']['field_servername']['label'] = 'url';
  $handler->display->display_options['fields']['field_servername']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_servername']['type'] = 'link_absolute';
  /* Contextual filter: Content: Drupal.org project name (field_dru_proj) */
  $handler->display->display_options['arguments']['field_dru_proj_value']['id'] = 'field_dru_proj_value';
  $handler->display->display_options['arguments']['field_dru_proj_value']['table'] = 'field_data_field_dru_proj';
  $handler->display->display_options['arguments']['field_dru_proj_value']['field'] = 'field_dru_proj_value';
  $handler->display->display_options['arguments']['field_dru_proj_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_dru_proj_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_dru_proj_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_dru_proj_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_dru_proj_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_dru_proj_value']['limit'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter criterion: Content: Environment (field_site_env) */
  $handler->display->display_options['filters']['field_site_env_tid']['id'] = 'field_site_env_tid';
  $handler->display->display_options['filters']['field_site_env_tid']['table'] = 'field_data_field_site_env';
  $handler->display->display_options['filters']['field_site_env_tid']['field'] = 'field_site_env_tid';
  $handler->display->display_options['filters']['field_site_env_tid']['relationship'] = 'reverse_field_drupal_mod_node';
  $handler->display->display_options['filters']['field_site_env_tid']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_site_env_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_site_env_tid']['vocabulary'] = 'environment';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'fz/module-site/';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_json';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'fnet/sites-using';
  $export['fz_sites_using_module'] = $view;

  $view = new view();
  $view->name = 'munin_website_size';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Munin Website Size';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Munin Website Size';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['format'] = 'full_html';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_servername']['id'] = 'field_servername';
  $handler->display->display_options['fields']['field_servername']['table'] = 'field_data_field_servername';
  $handler->display->display_options['fields']['field_servername']['field'] = 'field_servername';
  $handler->display->display_options['fields']['field_servername']['label'] = '';
  $handler->display->display_options['fields']['field_servername']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_servername']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_servername']['type'] = 'munin_label_formatter';
  /* Field: Content: Site Size */
  $handler->display->display_options['fields']['field_sitesize']['id'] = 'field_sitesize';
  $handler->display->display_options['fields']['field_sitesize']['table'] = 'field_data_field_sitesize';
  $handler->display->display_options['fields']['field_sitesize']['field'] = 'field_sitesize';
  $handler->display->display_options['fields']['field_sitesize']['label'] = '';
  $handler->display->display_options['fields']['field_sitesize']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sitesize']['empty'] = 'U';
  $handler->display->display_options['fields']['field_sitesize']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_sitesize']['settings'] = array(
    'trim_length' => '600',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'website' => 'website',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'munin/website-size';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['separator'] = ' ';
  $handler->display->display_options['style_options']['quote'] = 0;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 0;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['path'] = 'munin/website-size/data';
  $export['munin_website_size'] = $view;

  return $export;
}
