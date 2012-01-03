<?php
class Users extends System_Controller {	
	public function index() {
		echo $this->t()->render('users.html', array(
			'pageTitle' => 'We R Asia | User',
		));
	}
	
	public function edit($id = false) {
	   $args = array(
			'pageTitle' => 'We R Asia | Edit User',
		);
       $user = $this->mapper('user')->find($id);
       $args += array(
				'username' => $user->getUsername(),
				'name' => $user->getName(),
				'email' => $user->getEmail(),
				'address' => $user->getAddress(),
				'residence' => $user->getResidence(),
				'company' => $user->getCompany(),
			);
		echo $this->t()->render('edit_user.html', $args);
	}
	
	public function add() {
		echo $this->t()->render('add_user.html', array(
			'pageTitle' => 'We R Asia | Add User',
		));
	}
}
?>