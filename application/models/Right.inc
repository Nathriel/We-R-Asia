<?php
class Right_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findRight',
				'SELECT id,name
				FROM `right`
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$right = new Right_Model($this);
		$right
			->setId($row['id'])
			->setName($row['name']);
		return $right;
	}
	
	public function findByUser(User_Model $user) {
		$query = $this->db->prepareCached('findRightByUser',
				'SELECT right_id
				FROM user_rights
				WHERE user_id = ?');
		$query->execute(array($user->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['right_id']);
		}
		return $result;
	}
	
	protected function doDelete($id) {
		return null;
	}
	
	protected function doSave(System_Model $right) {
		return null;
	}
}

class Right_Model extends System_Model {
	private $id;
	private $name;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getName() {
		return $this->name;
	}
	
	public function setName($name) {
		$this->name = $name;
		return $this;
	}
}
?>