<?php
class User_Mapper extends System_Mapper {
	public function __construct(System_Database_Database $db) {
		parent::__construct($db);
		echo 'User Mapper Loaded';
	}
}

class User_Model extends System_Model {
	private $id;
	private $username;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getUsername() {
		return $this->username;
	}
	
	public function setUsername($username) {
		$this->username = $username;
		return $this;
	}
}
?>