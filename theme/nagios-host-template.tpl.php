<?php
/**
 *
 */
?>
# <?php print $server; ?> --------------------------------------------------
define timeperiod {
    timeperiod_name <?php print $server ; ?>_backups
    alias "Backups for <?php print $server ; ?>"
    monday    <?php print $backups_timeperiod . "\n"; ?>
    tuesday   <?php print $backups_timeperiod . "\n"; ?>
    wednesday <?php print $backups_timeperiod . "\n"; ?>
    thursday  <?php print $backups_timeperiod . "\n"; ?>
    friday    <?php print $backups_timeperiod . "\n"; ?>
    saturday  <?php print $backups_timeperiod . "\n"; ?>
    sunday    <?php print $backups_timeperiod . "\n"; ?>
}

define timeperiod {
    timeperiod_name <?php print $server ; ?>_notbackups
    alias "24x7 except backups for <?php print $server ; ?>"
    monday          00:00-24:00
    tuesday         00:00-24:00
    wednesday       00:00-24:00
    thursday        00:00-24:00
    friday          00:00-24:00
    saturday        00:00-24:00
    sunday          00:00-24:00
    exclude <?php print $server ; ?>_backups
}

define host {
  use generic-host
  host_name <?php print $server . "\n"; ?>
  alias <?php print $server . "\n"; ?>
  address <?php print $address . "\n"; ?>
  hostgroups site-monitoring
  notification_period <?php print $server ; ?>_notbackups
}
