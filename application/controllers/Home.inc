<?php
class Home extends System_controller{
    public function init(){
        
    }
    
    public function index() {
        $user = $this->mapper('user')->getLoggedinUser();
        if ($user) {
            header('location: ./Projects');
        } else {
            echo $this->t()->render('login.html', array(
    			'pageTitle' => 'We R Asia | Login',
    			'loginForm' => array(
    				'action' => './Home/processLogin/',
    			),
            	'languageSwitchReturnUrl' => urlencode(''),
    		));
        }
    }
    
    public function logout() {
    	unset($_SESSION['userId']);
        header('Location: ./');
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
			if (isset($_SESSION['languageId'])) {
				$user->setLanguage($this->mapper('language')->find($_SESSION['languageId']));
				$user->save();
			}
			echo 1;
		} else {
			// wrong username/password
			echo -1;
		}
	}
	
	public function language($languageCode, $returnUrl) {
		$decodedReturnUrl = urldecode($returnUrl);
		/* @var $user User_Model */
		$user = $this->mapper('user')->getLoggedinUser();
		if ($user) {
			$user->setLanguage($this->mapper('language')->findByCode($languageCode));
			$user->save();
		} else {
			$_SESSION['languageId'] = $this->mapper('language')->findByCode($languageCode)->getId();
		}
		header('Location: '.$this->getUrlPrefix().$decodedReturnUrl);
	}
}
?>