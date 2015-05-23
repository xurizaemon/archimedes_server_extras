<?php
/**
 *
 */
?>
define service {
  use generic-service
  service_description <?php print $host . "\n"; ?>
  host <?php print $server . "\n"; ?>
  check_command check_site!<?php print $host; ?>!<?php print $ssl_arg . "\n"?>
  notification_period <?php print $server ; ?>_notbackups
}
