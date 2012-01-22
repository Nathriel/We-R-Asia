<?php
class Invoice_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findInvoice',
				'SELECT id,file_location,project_id
				FROM invoices
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$invoice = new Invoice_Model($this);
		$invoice
			->setId($row['id'])
			->setFileLocation($row['file_location'])
			->setProjectId($row['project_id']);
		return $invoice;
	}
	
	public function findByProject(Project_Model $project) {
		$query = $this->db->prepareCached('findInvoiceByProject',
				'SELECT id
				FROM invoices
				WHERE project_id = ?');
		$query->execute(array($project->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	public function findAll() {
		$query = $this->db->prepareCached('findAllInvoices',
						'SELECT id
						FROM invoices');
		$query->execute(array());
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['id']);
		}
		return $result;
	}
	
	protected function doDelete($id) {
		$query = $this->db->prepareCached('deleteInvoice',
			'DELETE FROM invoices WHERE id = ?'
		);
        $query->execute(array($id));
	}
	
	protected function doSave(System_Model $invoice) {
		$args = array();
		if ($invoice->getId()) {
			$args[] = $invoice->getId();
			$query = $this->db->prepareCached('updateInvoice',
				'UPDATE invoices
				SET file_location=?,project_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertInvoice',
				'INSERT INTO invoices
				SET file_location=?,project_id=?');
		}
		$args = array_merge(array(
			$invoice->getFileLocation(),
			$invoice->getProjectId(),
		), $args);
		$query->execute($args);
		if (!$invoice->getId()) {
			$invoice->setId($this->db->lastInsertId());
		}
	}
}

class Invoice_Model extends System_Model {
	private $id;
	private $fileLocation;
	private $projectId;
	
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
	
	public function getProjectId() {
		return $this->projectId;
	}
	
	public function setProjectId($projectId) {
		$this->projectId = $projectId;
		return $this;
	}
}
?>