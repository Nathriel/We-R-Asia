<?php
class Welcome extends System_Controller {	
	public function index() {
		$userMapper = $this->mapper('user');
		$userMapper->find(3)->save();
		echo $this->t()->render('test.html', array(
			'pageTitle' => 'Titeltje!',
			'username' => 'GLaDOS 123',
		));
	}
}
?>