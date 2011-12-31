<?php
class Language_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	public function doFind($id) {
		$query = $this->db->prepareCached('findLanguage',
				'SELECT id,code
				FROM language
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$language = new Language_Model($this);
		$language
			->setId($row['id'])
			->setCode($row['code']);
		return $language;
	}
	
	public function findByCode($code) {
		$query = $this->db->prepareCached('findLanguageByCode',
					'SELECT id
					FROM language
					WHERE code = ?');
		$query->execute(array($code));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		return $this->find($row['id']);
	}
	
	public function doDelete($id) {
		return null;
	}
}

class Language_Model extends System_Model {
	private $id;
	private $code;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getCode() {
		return $this->code;
	}
	
	public function setCode($code) {
		$this->code = $code;
		return $this;
	}
}
?>