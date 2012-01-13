<?php
class LogItem_Mapper extends System_Mapper {
	protected function init() {
	
	}
	
	protected function doFind($id) {
		$query = $this->db->prepareCached('findLogItem',
				'SELECT id,date,data,translatable_id
				FROM logitems
				WHERE id = ?');
		$query->execute(array($id));
		$row = $query->fetch(PDO::FETCH_ASSOC);
		if (!$row) {
			return null;
		}
		$logItem = new LogItem_Model($this);
		$logItem
			->setId($row['id'])
			->setDate($row['date'])
			->setData(unserialize($row['data']))
			->setTranslatableId($row['translatable_id']);
		return $logItem;
	}
	
	public function findByProject(Project_Model $project) {
		$query = $this->db->prepareCached('findLogItemByProjectId',
			'SELECT logitem_id
			FROM project_has_logitem
			WHERE project_id = ?');
		$query->execute(array($project->getId()));
		$results = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$results[] = $this->find($row['logitem_id']);
		}
		return $results;
	}
	
	public function findByProduct(Product_Model $product) {
		$query = $this->db->prepareCached('findLogItemByProductId',
				'SELECT logitem_id
				FROM product_has_logitem
				WHERE product_id = ?');
		$query->execute(array($product->getId()));
		$results = array();
		while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
			$results[] = $this->find($row['logitem_id']);
		}
		return $results;
	}
	
	protected function doDelete($id) {
		return null;
	}
	
	protected function doSave(System_Model $model) {
		return null;
	}
}

class LogItem_Model extends System_Model {
	private $id;
	private $date;
	private $data;
	private $translatableId;
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($id) {
		$this->id = $id;
		return $this;
	}
	
	public function getDate() {
		return $this->date;
	}
	
	public function setDate($date) {
		$this->date = $date;
		return $this;
	}
	
	public function getData() {
		return $this->data;
	}
	
	public function setData($data) {
		$this->data = $data;
		return $this;
	}
	
	public function getTranslatableId() {
		return $this->translatableId;
	}
	
	public function setTranslatableId($translatableId) {
		$this->translatableId = $translatableId;
		return $this;
	}
	
	private function getTranslationForLanguage($language) {
		return $this->mapper->mapper('translatable')->find($this->getTranslatableId())->getTranslationForLanguage($language);
	}
	
	public function getTextForLanguage($language) {
		$text = $this->getTranslationForLanguage($language)->getTranslation();
		foreach ($this->data as $key => $val) {
			if (is_array($val) && count($val) >= 4 && $val[0] == 'find') {
				$valCount = count($val);
				$mapper = $this->mapper->mapper($val[1]);
				$object = $mapper->find($val[2]);
				$args = array();
				for ($i = 4; $i < $valCount; ++$i) {
					if ($val[$i] == 'currentLanguage') {
						$args[] = $language;
					} else {
						$args[] = $val[$i];
					}
				}
				$val = call_user_func_array(array($object, 'get'.ucfirst($val[3])), $args);
			}
			$text = str_replace('{'.$key.'}', $val, $text);
		}
		return $text;
	}
}
?>