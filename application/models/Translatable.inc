<?php
class Translatable_Mapper extends System_Mapper {
	private $sentenceCache;
	
	protected function init() {
		$this->sentenceCache = array();
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findTranslatable',
				'SELECT id,sentence
				FROM translatable
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$translatable = new Translatable_Model($this);
		$translatable
			->setId($row['id'])
			->setSentence($row['sentence']);
		return $translatable;
	}
	
	public function findBySentence($sentence) {
		if (!isset($this->sentenceCache[$sentence])) {
			$query = $this->db->prepareCached('findTranslatableBySentence',
					'SELECT id
					FROM translatable
					WHERE sentence = ?');
			$query->execute(array($sentence));
			$row = $query->fetch(PDO::FETCH_ASSOC);
			$this->sentenceCache[$sentence] = $this->find($row['id']);
		}
		return $this->sentenceCache[$sentence];
	}
	
	protected function doDelete($id) {
		return null;
	}
	
	protected function doSave(System_Model $model) {
		return null;
	}
}

class Translatable_Model extends System_Model {
	private $id;
	private $sentence;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getSentence() {
		return $this->sentence;
	}
	
	public function setSentence($sentence) {
		$this->sentence = $sentence;
		return $this;
	}
	
	public function getTranslationForLanguage($language) {
		return $this->mapper->mapper('translation')->findByLanguageAndTranslatable($language, $this);
	}
}
?>