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
		if ($user = $userMapper->tryLogin($username, $password)) {
			// successful login
			$_SESSION['userId'] = $user->getId();
			echo 1;
		} else {
			// wrong username/password
			echo -1;
		}
	}
}
?>