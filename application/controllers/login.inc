<?php
class Login extends System_Controller {	
	public function index() {
		echo $this->t()->render('login.html', array(
			'pageTitle' => 'We R Asia | Login',
		));
	}
	
	public function processLogin() {
		$username = $_POST['username'];
		$password = $_POST['password']; // sha256 encoded
		
		$userMapper = $this->mapper('user');
		if ($userMapper->tryLogin($username, $password)) {
			// succesful login
		} else {
			// wrong username/password
		}
	}
}
?>