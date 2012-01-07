<?php
class Product_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findProduct',
				'SELECT id,name,status_id
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
			->setStatusId($row['status_id']);
		return $product;
	}
	
	public function findByProject(Project_Model $project) {
		$query = $this->db->prepareCached('findProductByProject',
				'SELECT product_id
				FROM product
				WHERE project_id = ?');
		$query->execute(array($project->getId()));
		$result = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$result[] = $this->find($row['product_id']);
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
				SET id=?,name=?,status_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertProduct',
				'INSERT INTO product
				SET id=?,name=?,status_id=?');
		}
		$args = array_merge(array(
			$product->getId(),
			$product->getName(),
			$product->getStatusId(),
		), $args);
		$query->execute($args);
		if (!$product->getId()) {
			$product->setId($this->db->lastInsertId());
		}
	}
}

class Product_Model extends System_Model {
	private $id;
	private $name;
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