<?php
class Document_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findDocument',
				'SELECT id,file_location
				FROM document
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$document = new Document_Model($this);
		$document
			->setId($row['id'])
			->setFileLocation($row['file_location']);
		return $document;
	}
	
	public function findByProject(Project_Model $project) {
		$query = $this->db->prepareCached('findDocumentByProject',
				'SELECT document_id
				FROM project_has_document
				WHERE project_id = ?');
		$query->execute(array($project->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['document_id']);
		}
		return $result;
	}
	
	public function findByProduct(Product_Model $product) {
		$query = $this->db->prepareCached('findDocumentByProduct',
				'SELECT document_id
				FROM product_has_document
				WHERE product_id = ?');
		$query->execute(array($product->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['document_id']);
		}
		return $result;
	}
	
	public function findAll() {
		$query = $this->db->prepareCached('findAllDocuments',
						'SELECT id
						FROM document');
		$query->execute(array());
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	protected function doDelete($id) {
		
		$query = $this->db->prepareCached('deleteDocumentRights', 'DELETE FROM document_rights WHERE document_id = ?');
		$query->execute(array($id));
		$query = $this->db->prepareCached('deleteDocument',
			'DELETE FROM document WHERE id = ?'
		);
        $query->execute(array($id));
	}
	
    public function getProject($id = false){
        if($id)
        {
            $query = $this->db->prepareCached('findProjectId',
						'SELECT project_id
						FROM project_has_document WHERE document_id=?');
    		$query->execute(array($id));
    		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
    			$result = $this->mapper('project')->find($row['project_id']);
    		}
    		return $result;
        }
    }
    
    public function getProduct($id = false){
        if($id)
        {
            $query = $this->db->prepareCached('findProjectId',
						'SELECT product_id
						FROM product_has_document WHERE document_id=?');
    		$query->execute(array($id));
    		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
    			$result = $this->mapper('product')->find($row['product_id']);
    		}
    		return $result;
        }
    }
    
	protected function doSave(System_Model $document) {
		$args = array();
		if ($document->getId()) {
			$args[] = $document->getId();
			$query = $this->db->prepareCached('updateDocument',
				'UPDATE document
				SET file_location=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertDocument',
				'INSERT INTO document
				SET file_location=?');
		}
		$args = array_merge(array(
			$document->getFileLocation(),
		), $args);
		$query->execute($args);
		if (!$document->getId()) {
			$document->setId($this->db->lastInsertId());
		}
		
		$query = $this->db->prepareCached('deleteDocumentRights', 'DELETE FROM document_rights WHERE document_id = ?');
		$query->execute(array($document->getId()));
		$addedRights = array();
		foreach ($document->getRights() as $right) {
			if (!in_array($right->getId(), $addedRights)) {
				$addedRights[] = $right->getId();
				$query = $this->db->prepareCached('addDocumentRights', 'INSERT INTO document_rights SET document_id = ?, right_id = ?');
				$query->execute(array($document->getId(), $right->getId()));
			}
		}
	}
}

class Document_Model extends System_Model {
	private $id;
	private $fileLocation;
	private $rights;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getFileLocation() {
		return $this->fileLocation;
	}
	
	public function setFileLocation($fileLocation) {
		$this->fileLocation = $fileLocation;
		return $this;
	}
	
	public function createFromUser(User_Model $user) {
		if ($user->hasRight('europe')) {
			$rights = $this->mapper->mapper('right')->findAll();
		} else {
			$rights = $user->getRights();
		}
		foreach ($rights as $right) {
			$this->addRight($right);
		}
		return $this;
	}
	
	public function getRights() {
		if ($this->rights == null) {
			$this->rights = $this->mapper->mapper('right')->findByDocument($this);
		}
		return $this->rights;
	}
	
	public function addRight(Right_Model $right) {
		$rights = $this->getRights();
		$rights[] = $right;
		$this->rights = $rights;
		return $this;
	}
	
	public function hasRight(Right_Model $right) {
		$rights = $this->getRights();
		foreach ($rights as $yeahRight) {
			if ($yeahRight->getId() == $right->getId()) {
				return true;
			}
		}
		return false;
	}
}
?>