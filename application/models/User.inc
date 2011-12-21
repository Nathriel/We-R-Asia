<?php
class User_Mapper extends System_Mapper {
	
	protected function init() {
		
	}
	
	public function doFind($id) {
		$query = $this->db->prepareCached('findUser',
			'SELECT id,username,name,address,residence,email,company,language_id
			FROM user
			WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$user = new User_Model($this);
		$user
			->setId($row['id'])
			->setUsername($row['username']);
		return $user;
	}
	
	public function doDelete($id) {
		return null;
	}
	
	public function findByUsername($username) {
		$query = $this->db->prepareCached('findUsername',
			'SELECT id
			FROM user
			WHERE username = ?');
		$query->execute(array($username));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		return $this->find($row['id']);
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