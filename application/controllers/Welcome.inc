<?php
class Welcome extends System_Controller {	
	public function index() {
		$this->mapper('user');
		echo $this->t()->render('test.html', array(
			'pageTitle' => 'Titeltje!',
			'hello' => 'GLaDOS 123',
		));
	}
}
?>