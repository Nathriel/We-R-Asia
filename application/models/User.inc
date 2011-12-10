<?php
class User_Mapper extends System_Mapper {
	
	protected function init() {
		
	}
	
	public function doFind($id) {
		return null;
	}
	
	public function doDelete($id) {
		return null;
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