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
	
	protected function doFind($id) {
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
			->setSalt($row['password_salt'])
			->setName($row['name'])
			->setAddress($row['address'])
			->setResidence($row['residence'])
			->setEmail($row['email'])
			->setCompany($row['company'])
			->setLanguageId($row['language_id']);
		return $user;
	}
	
	protected function doDelete($id) {
		$query = $this->db->prepareCached('deleteUser',
			'DELETE FROM user WHERE id = ?');
		$query->execute(array($id));
	}
	
	public function findByUsername($username) {
		$query = $this->db->prepareCached('findUserByUsername',
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
	
	protected function doSave(System_Model $user) {
		$args = array();
		if ($user->getId()) {
			$args[] = $user->getId();
			$query = $this->db->prepareCached('updateUser',
				'UPDATE user
				SET username=?,password=?,salt=?,name=?,address=?,residence=?,email=?,company=?,language_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertUser',
				'INSERT INTO user
				SET username=?,password=?,salt=?,name=?,address=?,residence=?,email=?,company=?,language_id=?');
		}
		$args = array_merge(array(
			$user->getUsername(),
			$user->getPassword(),
			$user->getSalt(),
			$user->getName(),
			$user->getAddress(),
			$user->getResidence(),
			$user->getEmail(),
			$user->getCompany(),
			$user->getLanguage()->getId()
		), $args);
		$query->execute($args);
		if (!$user->getId()) {
			$user->setId($this->db->lastInsertId());
		}
	}
	
	public function getLoggedInUser() {
		if (isset($_SESSION['userId'])) {
			return $this->find($_SESSION['userId']);
		} else {
			return null;
		}
	}
}

class User_Model extends System_Model {
	private $id;
	private $username;
	private $password;
	private $salt;
	private $name;
	private $address;
	private $residence;
	private $email;
	private $company;
	private $languageId;
	private $language;
	private $rights;
	
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
	
	public function getName() {
		return $this->name;
	}
	
	public function setName($name) {
		$this->name = $name;
		return $this;
	}
	
	public function getAddress() {
		return $this->address;
	}
	
	public function setAddress($address) {
		$this->address = $address;
		return $this;
	}
	
	public function getResidence() {
		return $this->residence;
	}
	
	public function setResidence($residence) {
		$this->residence = $residence;
		return $this;
	}
	
	public function getEmail() {
		return $this->email;
	}
	
	public function setEmail($email) {
		$this->email = $email;
		return $this;
	}
	
	public function getCompany() {
		return $this->company;
	}
	
	public function setCompany($company) {
		$this->company = $company;
		return $this;
	}
	
	public function getLanguageId() {
		return $this->languageId;
	}
	
	public function setLanguageId($languageId) {
		$this->languageId = $languageId;
		$this->language = null;
		return $this;
	}
	
	public function getLanguage() {
		if ($this->language == null && $this->getLanguageId()) {
			$this->language = $this->mapper->mapper('language')->find($this->getLanguageId());
		}
		return $this->language;
	}
	
	public function setLanguage($language) {
		$this->language = $language;
		$this->languageId = $this->language->getId();
		return $this;
	}
	
	public function getProjects($finished = 0) {
		return $this->mapper->mapper('project')->findByUser($this, $finished);
	}
	
	public function getRights() {
		if ($this->rights == null && $this->getId()) {
			$this->rights = $this->mapper->mapper('right')->findByUser($this);
		}
		return $this->rights;
	}
	
	public function hasRight($name) {
		$rights = $this->getRights();
		foreach ($rights as $right) {
			if ($right->getName() == $name) {
				return true;
			}
		}
		return false;
	}
}
?>