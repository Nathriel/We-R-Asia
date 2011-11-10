<?php
class System_Controller {
	protected $system;
	
	public function __construct(System $system) {
		$this->system = $system;
	}
}
?>