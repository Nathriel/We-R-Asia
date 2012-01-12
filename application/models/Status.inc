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
	
	protected function doDelete($id) {
		return null;
	}
	
	protected function doSave(System_Model $status) {
		return null;
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