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
	
	public function doDelete($id) {
	   
       $query = $this->db->prepareCached('deleteRightByUser',
				'DELETE FROM user_rights WHERE user_id = ?');
       $query->execute(array($id));
		$query = $this->db->prepareCached('deleteProjectByUser',
				'DELETE FROM user_has_project WHERE user_id = ?');
		$query->execute(array($id));
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
	
	public function findByEmail($email) {
		$query = $this->db->prepareCached('findUserByEmail',
			'SELECT id
			FROM user
			WHERE email = ?');
		$query->execute(array($email));
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
				SET username=?,password=?,password_salt=?,name=?,address=?,residence=?,email=?,company=?,language_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertUser',
				'INSERT INTO user
				SET username=?,password=?,password_salt=?,name=?,address=?,residence=?,email=?,company=?,language_id=?');
		}
        
        if(!$user->getLanguage()){
            $user->setLanguage($this->mapper('language')->find('1'));
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
            $query = $this->db->prepareCached('insertRight',
				'INSERT INTO `user_rights`
				SET user_id=?,right_id=?');
            $args = array(
                $user->getId(),
                $user->getRights()->getId(),
            );
            $query->execute($args);
		}
        else
        {
            if($user->getRights())
            {
                if(is_array($user->getRights()))
                {
                    $right = $user->getRights();
                    $right = $right[0];
                }
                else
                {
                    $right = $user->getRights();
                }
                $query = $this->db->prepareCached('updateRight',
    				'UPDATE `user_rights`
    				SET right_id=? WHERE user_id= ?');
                
                $args = array(
                    $right->getId(),
                    $user->getId()
                );
                $query->execute($args);
            }
        }

        //print_r($user);
        //print_r($this->mapper('right'));
        //var_dump($this->mapper->('right')->find(7));  
        //var_dump($this->mapper('right')->find(7));
        
	}
	
	public function getLoggedInUser() {
		if (isset($_SESSION['userId'])) {
			return $this->find($_SESSION['userId']);
		} else {
			return null;
		}
	}
	
	public function findAll() {
		$query = $this->db->prepareCached('findAllUsers',
				'SELECT id
				FROM user');
		$query->execute(array());
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	public function findByProject(Project_Model $project) {
		$query = $this->db->prepareCached('findUserByProject',
				'SELECT user_id
				FROM user_has_project
				WHERE project_id = ?');
		$query->execute(array($project->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['user_id']);
		}
		return $result;
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
	
	public function setLanguage(Language_Model $language) {
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
    
    public function setRights($rights){
        $this->rights = $rights;
    } 
	
	public function hasRight($name) {
		$rights = $this->getRights();
		foreach ($rights as $right) {
			if ($right && $right->getName() == $name) {
				return true;
			}
		}
		return false;
	}
	
	public function canViewProject(Project_Model $project) {
		return ($project->hasUser($this) || $this->hasRight('europe'));
	}
	
	public function canViewDocument(Document_Model $document) {
		foreach ($this->getRights() as $right) {
			if ($document->hasRight($right)) {
				return true;
			}
		}
		return $this->hasRight('europe');
	}
	
	public function canViewInvoice(Invoice_Model $invoice) {
		return ($invoice->getApproved() || ($this->hasRight('europe') || $this->hasRight('china')));
	}
}
?>