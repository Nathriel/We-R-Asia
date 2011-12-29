<?php
class Login extends System_Controller {	
	public function index() {
		echo $this->t()->render('login.html', array(
			'pageTitle' => 'We R Asia | Login',
			'loginForm' => array(
				'action' => './login/processLogin/',
			),
		));
	}
	
	/**
	 * Called through ajax
	 */
	public function processLogin() {
		$username = $_POST['username'];
		$password = $_POST['password']; // sha256 encoded
		
		$userMapper = $this->mapper('user');
		if ($userMapper->tryLogin($username, $password)) {
			// succesful login
			echo 1;
		} else {
			// wrong username/password
			echo -1;
		}
	}
}
?>