<?php
/**
 *
 */
?>
define service {
    service_description <?php print $host . "\n"; ?>
    host <?php print $server . "\n"; ?>
    check_command check_site!<?php print $host; ?>!<?php print $ssl_arg . "\n"?>
    use generic-service
}
