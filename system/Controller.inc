<?php
class System_Controller {
	private $system;
	
	public function __construct(System $system) {
		$this->system = $system;
	}
	
	public function mapper($name) {
		return $this->system->getMapper($name);
	}
	
	public function t() {
		return $this->templateEngine();
	}
	
	public function templateEngine() {
		return $this->system->getTemplateEngineInstance();
	}
}
?>