<?php
class Project_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	public function doFind($id) {
		$query = $this->db->prepareCached('findProject',
				'SELECT id,name,finished,status_id
				FROM project
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$project = new Project_Model($this);
		$project
			->setId($row['id'])
			->setName($row['name'])
			->setFinished($row['finished'])
			->setStatusId($row['status_id']);
		return $project;
	}
	
	public function findByUser(User_Model $user) {
		$query = $this->db->prepareCached('findProjectByUser',
				'SELECT project_id
				FROM user_has_project
				WHERE user_id = ?');
		$query->execute(array($user->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['project_id']);
		}
		return $result;
	}
	
	public function findAll() {
		$query = $this->db->prepareCached('findAllProjects',
						'SELECT id
						FROM projects');
		$query->execute(array());
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	public function doDelete($id) {
		return null;
	}
}

class Project_Model extends System_Model {
	private $id;
	private $name;
	private $finished;
	private $statusId;
	
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
	
	public function getFinished() {
		return $this->finished;
	}
	
	public function setFinished($finished) {
		$this->finished = $finished;
		return $this;
	}
	
	public function getStatusId() {
		return $this->statusId;
	}
	
	public function setStatusId($statusId) {
		$this->statusId = $statusId;
		return $this;
	}
}
?>