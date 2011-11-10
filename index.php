<?php
//this should only call the system class, since we want to program Object-Oriented, just like Java :)
$config = array(
	'applicationPath' => 'application/',
	'systemPath' => 'system/',
);
require_once('./'.$config['systemPath'].'System.inc');
$system = new System($config);
$system->run();
?>