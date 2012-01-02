<?php
class Users extends System_Controller {	
	public function index() {
		echo $this->t()->render('users.html', array(
			'pageTitle' => 'We R Asia | users',
		));
	}
}
?>