<?php
//Should contain a basic database interface that can be applied to any kind of database
class System_Database_Database extends PDO {
	public function __construct(array $config) {
		$dsn = 'mysql:host='.$config['host'].';dbname='.$config['database'];
		if ($config['port']) {
			$dsn .= ';port='.$config['port'];
		}
		parent::__construct($dsn, $config['username'], $config['password']);
	}
}
?>
