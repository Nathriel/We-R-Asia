<?php
class Home extends System_controller{
    public function init(){
        
    }
    
    public function index() {
        $user = $this->mapper('user')->getLoggedinUser();
        if($user){
            header("location: projects");
        }
        else
        {
            echo $this->t()->render('login.html', array(
    			'pageTitle' => 'We R Asia | Login',
    			'loginForm' => array(
    				'action' => './login/processLogin/',
    			),
    		));
        }
    }
    
    public function logout(){
        session_unset();
        session_destroy();
        header("Location: ./");
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