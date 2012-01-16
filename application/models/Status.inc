<?php
class Status_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findStatus',
				'SELECT id,translatable_id
				FROM status
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$status = new Status_Model($this);
		$status
			->setId($row['id'])
			->setTranslatableId($row['translatable_id']);
		return $status;
	}
	
	public function findAll() {
		$query = $this->db->prepareCached('findAllStatuses',
				'SELECT id
				FROM status');
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
	
	protected function doSave(System_Model $status) {
		$args = array();
		if ($status->getId()) {
			$args[] = $status->getId();
			$query = $this->db->prepareCached('updateStatus',
				'UPDATE status
				SET translatable_id=?
				WHERE id=?');
		} else {
			$query = $this->db->prepareCached('insertStatus',
				'INSERT INTO status
				SET translatable_id=?');
		}
		$args = array_merge(array(
			$status->getTranslatableId(),
		), $args);
		$query->execute($args);
		if (!$status->getId()) {
			$status->setId($this->db->lastInsertId());
		}
	}
}

class Status_Model extends System_Model {
	private $id;
	private $translatableId;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getTranslatableId() {
		return $this->translatableId;
	}
	
	public function setTranslatableId($translatableId) {
		$this->translatableId = $translatableId;
		return $this;
	}
	
	public function getTranslationForLanguage($language) {
		return $this->mapper->mapper('translatable')->find($this->getTranslatableId())->getTranslationForLanguage($language);
	}
	
	public function getTextForLanguage($language) {
		return $this->getTranslationForLanguage($language)->getTranslation();
	}
}
?>