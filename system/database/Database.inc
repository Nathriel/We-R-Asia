<?php
//Should contain a basic database interface that can be applied to any kind of database
class System_Database_Database extends PDO {
	private $prepareCache;
	
	public function __construct(array $config) {
		$dsn = 'mysql:host='.$config['host'].';dbname='.$config['database'];
		if ($config['port']) {
			$dsn .= ';port='.$config['port'];
		}
		parent::__construct($dsn, $config['username'], $config['password']);
		$this->prepareCache = array();
	}
	
	public function prepareCached($name, $query) {
		if (!isset($this->prepareCache[$name])) {
			$this->prepareCache[$name] = $this->prepare($query);
		}
		return $this->prepareCache;
	}
}
?>
