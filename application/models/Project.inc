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
	
	public function findByUser(User_Model $user, $finished = 0) {
		if ($finished === null) {
			$query = $this->db->prepareCached('findProjectByUser',
				'SELECT project_id
				FROM user_has_project
				WHERE user_id = ?');
			$query->execute(array($user->getId()));
		} else {
			$query = $this->db->prepareCached('findProjectByUserAndFinished',
				'SELECT user_has_project.project_id
				FROM user_has_project
				INNER JOIN project ON project.id = user_has_project.project_id
				WHERE user_has_project.user_id = ? AND project.finished = ?');
			$query->execute(array($user->getId(), $finished));
		}
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['project_id']);
		}
		return $result;
	}
	
	public function findAll($finished = 0) {
		if ($finished === null) {
			$query = $this->db->prepareCached('findAllProjects',
				'SELECT id
				FROM projects');
			$query->execute(array());
		} else {
			$query = $this->db->prepareCached('findAllProjectsByFinished',
				'SELECT id
				FROM projects
				WHERE finished=?');
			$query->execute(array($finished));
		}
		
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	protected function doDelete($id) {
		$query = $this->db->prepareCached('deleteProject',
			'DELETE FROM project WHERE id = ?'
		);
		$query->execute(array($id));
		var_dump($query->errorInfo());exit;
		return true;
	}
	
	protected function doSave(System_Model $project) {
		$args = array();
		if ($project->getId()) {
			$args[] = $project->getId();
			$query = $this->db->prepareCached('updateProject',
				'UPDATE project
				SET name=?,code=?,finished=?,status_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertProject',
				'INSERT INTO project
				SET name=?,code=?,finished=?,status_id=?');
		}
		$args = array_merge(array(
			$project->getName(),
			$project->getCode(),
			$project->getFinished(),
			$project->getStatusId(),
		), $args);
		$query->execute($args);
		if (!$project->getId()) {
			$project->setId($this->db->lastInsertId());
		}
		
		$logItems = $project->getLogItems();
		$deleteQuery = $this->db->prepareCached('deleteAllLogitemRelationsByProject', 'DELETE FROM project_has_logitem WHERE project_id = ?');
		$deleteQuery->execute(array($project->getId()));
		foreach ($logItems as $logItem) {
			if ($logItem) {
				$logItem->save();
				$insertQuery = $this->db->prepareCached('insertLogitemRelationByProject', 'INSERT INTO project_has_logitem SET project_id = ?, logitem_id = ?');
				$insertQuery->execute(array($project->getId(), $logItem->getId()));
			}
		}
		
		foreach ($project->getProducts() as $product) {
			$product->setProjectId($project->getId());
			$product->save();
		}
		
		$users = $project->getUsers();
		$deleteQuery = $this->db->prepareCached('deleteAllUsersFromProject', 'DELETE FROM user_has_project WHERE project_id = ?');
		$deleteQuery->execute(array($project->getId()));
		foreach ($users as $user) {
			$insertQuery = $this->db->prepareCached('insertUserByProject', 'INSERT INTO user_has_project SET project_id = ?, user_id = ?');
			$insertQuery->execute(array($project->getId(), $user->getId()));
		}
		
		$documents = $project->getDocuments();
		$deleteQuery = $this->db->prepareCached('deleteAllDocumentsFromProject', 'DELETE FROM project_has_document WHERE project_id = ?');
		$deleteQuery->execute(array($project->getId()));
		foreach ($documents as $document) {
			$insertQuery = $this->db->prepareCached('insertDocumentByProject', 'INSERT INTO project_has_document SET project_id = ?, document_id = ?');
			$insertQuery->execute(array($project->getId(), $document->getId()));
		}
		
		foreach ($project->getInvoices() as $invoice) {
			$invoice->setProjectId($project->getId());
			$invoice->save();
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
	private $logItems;
	private $users;
	private $products;
	private $documents;
	private $invoices;
	
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
	
	public function getLogItems() {
		if ($this->logItems == null) {
			$this->logItems = $this->mapper->mapper('logItem')->findByProject($this);
		}
		return $this->logItems;
	}
	
	public function addLogItem(LogItem_Model $logItem) {
		$logItems = $this->getLogItems();
		$logItems[] = $logItem;
		$this->logItems = $logItems;
		return $this;
	}
	
	public function getProducts() {
		if ($this->products == null) {
			$this->products = $this->mapper->mapper('product')->findByProject($this);
		}
		return $this->products;
	}
	
	public function addProduct(Product_Model $product) {
		$products = $this->getProducts();
		$products[] = $product;
		$this->products = $products;
		return $this;
	}
	
	public function getUsers() {
		if ($this->users == null && $this->getId()) {
			$this->users = $this->mapper->mapper('user')->findByProject($this);
		}
		return $this->users;
	}
	
	public function setUsersAsIdArray(array $userIds = array()) {
		$this->users = array();
		foreach ($userIds as $userId) {
			$this->users[] = $this->mapper->mapper('user')->find($userId);
		}
		return $this;
	}
	
	public function hasUser(User_Model $user) {
		$users = $this->getUsers();
		foreach ($users as $u) {
			if ($u->getId() == $user->getId()) {
				return true;
			}
		}
		return false;
	}
	
	public function getDocuments() {
		if ($this->documents == null && $this->getId()) {
			$this->documents = $this->mapper->mapper('document')->findByProject($this);
		}
		return $this->documents;
	}
	
	public function addDocument($document) {
		$documents = $this->getDocuments();
		$documents[] = $document;
		$this->documents = $documents;
		return $this;
	}
	
	public function getInvoices() {
		if ($this->invoices == null && $this->getId()) {
			$this->invoices = $this->mapper->mapper('invoice')->findByProject($this);
		}
		return $this->invoices;
	}
	
	public function addInvoice($invoice) {
		$invoices = $this->getInvoices();
		$invoices[] = $invoice;
		$this->invoices = $invoices;
		return $this;
	}
}
?>