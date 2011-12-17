<?php
class System_Twig_SystemTwigExtension extends Twig_Extension {
	private $system;
	
	public function __construct($system) {
		$this->system = $system;
	}
	
	public function getName() {
		return 'SystemTwig';
	}
	
	public function getFunctions() {
		return array(
			'trans' => new Twig_Function_Method($this, 'translate'),
		);
	}
	
	public function translate($string) {
		$realargs = func_get_args();
		array_shift($realargs);
		$args = array($this->system->getMultiLanguage()->c($string));
		$args = array_merge($args, $realargs);
		return call_user_func_array('sprintf', $args);
	}
}
?>