<?php
class Welcome extends System_Controller {	
	public function index() {
		echo 'test';
		$this->system->getMapper('user');
	}
}
?>