<?php
class Welcome extends System_Controller {	
	public function index() {
		$userMapper = $this->mapper('user');
		var_dump($userMapper->find(1));
		var_dump($userMapper->findByUsername('testpersoon'));
		echo $this->t()->render('test.html', array(
			'pageTitle' => 'Titeltje!',
			'username' => 'GLaDOS 123',
		));
	}
}
?>