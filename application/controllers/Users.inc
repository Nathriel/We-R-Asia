<?php
class Users extends System_Controller {	
	public function index() {
		echo $this->t()->render('users.html', array(
			'pageTitle' => 'We R Asia | User',
		));
	}
	
	public function edit($id = false) {
		if ($id) {
			echo $this->t()->render('edit_user.html', array(
				'pageTitle' => 'We R Asia | Edit User',
			));
		} else {
			// /edit/ zonder id erachter
		}
	}
	
	public function add() {
		echo $this->t()->render('add_user.html', array(
			'pageTitle' => 'We R Asia | Add User',
		));
	}
}
?>