<?php
/**
 *
 */
?>
define service {
  use generic-service
  service_description <?php print $host . " - Google Safe Browsing check\n"; ?>
  host <?php print $server . "\n"; ?>
  check_command check_google_safebrowsing!<?php print $host . "\n"; ?>
  is_volatile 0
  check_period 24x7
  max_check_attempts 2
  normal_check_interval 3600
  retry_check_interval 30
}
