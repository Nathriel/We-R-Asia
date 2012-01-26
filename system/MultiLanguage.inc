<?php
abstract class System_MultiLanguage {
	private $system;
	
	public function __construct($system) {
		$this->system = $system;
	}
	
	public function c($string) {
		return $this->convert($string);
	}
	
	public function convert($string) {
		return $this->translate($string, $this->getCurrentLanguage());
	}
	
	public abstract function getCurrentLanguage();
	protected abstract function translate($string, $language);
	
	protected function mapper($modelName) {
		return $this->system->getMapper($modelName);
	}
}
?>