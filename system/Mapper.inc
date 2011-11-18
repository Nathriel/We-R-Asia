<?php
class System_Mapper {
	protected $db;
	public function __construct(System_Database_Database $db) {
		$this->db = $db;
	}
}
?>