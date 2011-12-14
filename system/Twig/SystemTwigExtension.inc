<?php
class System_Twig_SystemTwigExtension extends Twig_Extension {
	private $system;
	
	public function __construct($system) {
		$this->system = $system;
	}
	
	public function getName() {
		return 'SystemTwig';
	}
	
	public function getTokenParsers() {
		return array(new System_Twig_TokenParserTrans());
	}
	
	public function getFilters() {
		return array(
			'trans' => new Twig_Filter_Function(array($this, 'translate')),
		);
	}
	
	public function translate($string) {
		return $this->system->getMultiLanguage()->c($string);
	}
}
?>