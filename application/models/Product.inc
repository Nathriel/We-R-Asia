<?php
class Product_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findProduct',
				'SELECT id,name,project_id,status_id
				FROM product
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$product = new Product_Model($this);
		$product
			->setId($row['id'])
			->setName($row['name'])
			->setProjectId($row['project_id'])
			->setStatusId($row['status_id']);
		return $product;
	}
	
	public function findByProject(Project_Model $project) {
		$query = $this->db->prepareCached('findProductByProject',
				'SELECT id
				FROM product
				WHERE project_id = ?');
		$query->execute(array($project->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	public function findAll() {
		$query = $this->db->prepareCached('findAllProducts',
						'SELECT id
						FROM products');
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
	
	protected function doSave(System_Model $product) {
		$args = array();
		if ($product->getId()) {
			$args[] = $product->getId();
			$query = $this->db->prepareCached('updateProduct',
				'UPDATE product
				SET name=?,project_id=?,status_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertProduct',
				'INSERT INTO product
				SET name=?,project_id=?,status_id=?');
		}
		$args = array_merge(array(
			$product->getName(),
			$product->getProjectId(),
			$product->getStatusId(),
		), $args);
		$query->execute($args);
		if (!$product->getId()) {
			$product->setId($this->db->lastInsertId());
		}
		
		$logItems = $product->getLogItems();
		$deleteQuery = $this->db->prepareCached('deleteAllLogitemRelationsByProduct', 'DELETE FROM product_has_logitem WHERE product_id = ?');
		$deleteQuery->execute(array($product->getId()));
		foreach ($logItems as $logItem) {
			if ($logItem) {
				$logItem->save();
				$insertQuery = $this->db->prepareCached('insertLogitemRelationByProduct', 'INSERT INTO product_has_logitem SET product_id = ?, logitem_id = ?');
				$insertQuery->execute(array($product->getId(), $logItem->getId()));
			}
		}
		
		$documents = $product->getDocuments();
		$deleteQuery = $this->db->prepareCached('deleteAllDocumentsFromProduct', 'DELETE FROM product_has_document WHERE product_id = ?');
		$deleteQuery->execute(array($product->getId()));
		foreach ($documents as $document) {
			$insertQuery = $this->db->prepareCached('insertDocumentByProduct', 'INSERT INTO product_has_document SET product_id = ?, document_id = ?');
			$insertQuery->execute(array($product->getId(), $document->getId()));
		}
	}
}

class Product_Model extends System_Model {
	private $id;
	private $name;
	private $projectId;
	private $statusId;
	private $status;
	private $logItems = array();
	private $documents;
	
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
	
	public function getProjectId() {
		return $this->projectId;
	}
	
	public function setProjectId($projectId) {
		$this->projectId = $projectId;
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
		if ($this->logItems == null || !count($this->logItems)) {
			$this->logItems = $this->mapper->mapper('logItem')->findByProduct($this);
		}
		return $this->logItems;
	}
	
	public function addLogItem(LogItem_Model $logItem) {
		$logItems = $this->getLogItems();
		$logItems[] = $logItem;
		$this->logItems = $logItems;
		return $this;
	}
	
	public function getDocuments() {
		if ($this->documents == null && $this->getId()) {
			$this->documents = $this->mapper->mapper('document')->findByProduct($this);
		}
		return $this->documents;
	}
	
	public function addDocument($document) {
		$documents = $this->getDocuments();
		$documents[] = $document;
		$this->documents = $documents;
		return $this;
	}
}
?>