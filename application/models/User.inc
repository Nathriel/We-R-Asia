<?php
/**
 * 
 * Easy testuser:
 * username: anything you want
 * password: eea24c37723ada81453c2038df4bef0725b3b9f28c926e597dc463b2a9252030
 * password_salt: 63479ad69a090b258277ec8fba6f99419a2ffb248981510657c944ccd1148e97
 * password is dan "test"
 * @author Teun
 *
 */
class User_Mapper extends System_Mapper {
	
	protected function init() {
		
	}
	
	public function doFind($id) {
		$query = $this->db->prepareCached('findUser',
			'SELECT id,username,password,password_salt,name,address,residence,email,company,language_id
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
			->setUsername($row['username'])
			->setPassword($row['password'])
			->setSalt($row['password_salt']);
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
	
	public function tryLogin($username, $password) {
		$user = $this->findByUsername($username);
		if (!$user) {
			return false;
		}
		
		$passwordDb = hash('sha256', $password.$user->getSalt());
		
		if ($passwordDb == $user->getPassword()) {
			return $user;
		} else {
			return false;
		}
	}
}

class User_Model extends System_Model {
	private $id;
	private $username;
	private $password;
	private $salt;
	
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
	
	public function getPassword() {
		return $this->password;
	}
	
	public function setPassword($password) {
		$this->password = $password;
		return $this;
	}
	
	public function getSalt() {
		return $this->salt;
	}
	
	public function setSalt($salt) {
		$this->salt = $salt;
		return $this;
	}
}
?>