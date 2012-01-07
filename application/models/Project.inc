<?php
class Project_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findProject',
				'SELECT id,name,code,finished,status_id
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
			->setCode($row['code'])
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
	
	public function findArchived() {
		$query = $this->db->prepareCached('findArchivedProjects',
			'SELECT id
			FROM projects
			WHERE finished = 0'
		);
		$query->execute(array());
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	protected function doDelete($id) {
		return null;
	}
	
	protected function doSave(System_Model $project) {
		$args = array();
		if ($project->getId()) {
			$args[] = $project->getId();
			$query = $this->db->prepareCached('updateProject',
				'UPDATE project
				SET id=?,name=?,code=?,finished=?,status_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertProject',
				'INSERT INTO project
				SET id=?,name=?,code=?,finished=?,status_id=?');
		}
		$args = array_merge(array(
			$project->getId(),
			$project->getName(),
			$project->getCode(),
			$project->getFinished(),
			$project->getStatusId(),
		), $args);
		$query->execute($args);
		if (!$project->getId()) {
			$project->setId($this->db->lastInsertId());
		}
	}
}

class Project_Model extends System_Model {
	private $id;
	private $name;
	private $projectCode;
	private $finished;
	private $statusId;
	private $status;
	
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
	
	public function getCode() {
		return $this->Code;
	}
	
	public function setCode($Code) {
		$this->Code = $Code;
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
		$this->status = null;
		return $this;
	}
	
	public function getStatus() {
		if ($this->status == null && $this->getStatusId()) {
			$this->status = $this->mapper->mapper('status')->find($this->getStatusId());
		}
		return $this->status;
	}
	
	public function setStatus($status) {
		$this->status = $status;
		$this->statusId = $status->getId();
		return $this;
	}
}
?>