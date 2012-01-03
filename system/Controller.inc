<?php
abstract class System_Controller {
	private $system;
	
	public function __construct(System $system) {
		$this->system = $system;
		$this->init();
	}
	
	public function init() {
		// design-technically this should be an abstract function, but it would be annoying.
	}
	
	/**
	 * @see System::getMapper()
	 */
	protected function mapper($name) {
		return $this->system->getMapper($name);
	}
	
	/**
	 * short syntax version of System_Controller::templateEngine()
	 * @see System_Controller::templateEngine()
	 */
	protected function t() {
		return $this->templateEngine();
	}
	
	/**
	 * @see System::getTemplateEngineInstance()
	 */
	protected function templateEngine() {
		return $this->system->getTemplateEngineInstance();
	}
	
	/**
	 * Gets called when a method that is called isn't found in this class
	 */
	public function notFound() {
		//TODO: Redirect to the standard 404 if the controller doesn't override this
	}
	
	protected function multiLanguage() {
		return $this->system->getMultiLanguage();
	}
	
	protected function m() {
		return $this->multiLanguage();
	}
}
?>