<?php
class Translation_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findTranslation',
				'SELECT id,translation,translatable_id,language_id
				FROM translation
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$translation = new Translation_Model($this);
		$translation
			->setId($row['id'])
			->setTranslation($row['translation'])
			->setTranslatableId($row['translatable_id'])
			->setLanguageId($row['language_id']);
		return $translation;
	}
	
	public function findByLanguageAndTranslatable($language, $translatable) {
		$query = $this->db->prepareCached('findTranslationByLanguageIdAndTranslatableId',
			'SELECT id
			FROM translation
			WHERE language_id = ? AND translatable_id = ?');
		if (is_object($language) && is_object($translatable)) {
			$query->execute(array($language->getId(), $translatable->getId()));
		} elseif (is_int($language) && is_object($translatable)) {
			$query->execute(array($language, $translatable));
		} else {
			return null;
		}
		$row = $query->fetch(PDO::FETCH_ASSOC);
		return $this->find($row['id']);
	} 
	
	protected function doDelete($id) {
		return null;
	}
}

class Translation_Model extends System_Model {
	private $id;
	private $translation;
	private $translatableId;
	private $translatable;
	private $languageId;
	private $language;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getTranslation() {
		return $this->translation;
	}
	
	public function setTranslation($translation) {
		$this->translation = $translation;
		return $this;
	}
	
	public function getTranslatableId() {
		return $this->translatableId;
	}
	
	public function setTranslatableId($translatableId) {
		$this->translatableId = $translatableId;
		return $this;
	}
	
	public function getTranslatable() {
		if ($this->translatable == null && $this->getTranslatableId()) {
			$this->translatable = $this->mapper->mapper('translatable')->find($this->getTranslatableId());
		}
		return $this->translatable;
	}
	
	public function setTranslatable($translatable) {
		$this->translatable = $translatable;
		$this->translatableId = $this->translatable->getId();
		return $this;
	}
	
	public function getLanguageId() {
		return $this->languageId;
	}
	
	public function setLanguageId($languageId) {
		$this->languageId = $languageId;
		return $this;
	}
	
	public function getLanguage() {
		if ($this->language == null && $this->getLanguageId()) {
			$this->language = $this->mapper->mapper('language')->find($this->getLanguageId());
		}
		return $this->language;
	}
	
	public function setLanguage($language) {
		$this->language = $language;
		$this->languageId = $this->language->getId();
		return $this;
	}
}
?>