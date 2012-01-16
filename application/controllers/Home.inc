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
        header('Location: ../');
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
		$decodedReturnUrl = str_replace('|','/',$returnUrl);
		$language = $this->mapper('language')->findByCode($languageCode);
		/* @var $user User_Model */
		$user = $this->mapper('user')->getLoggedinUser();
		if ($user) {
			$user->setLanguage($language);
			$user->save();
		}
		$_SESSION['languageId'] = $language->getId();
		header('Location: '.$this->getUrlPrefix().$decodedReturnUrl);
		
	}
	
	private function generatePassword($length=9, $strength=0) {
		$vowels = 'aeuy';
		$consonants = 'bdghjmnpqrstvz';
		if ($strength & 1) {
			$consonants .= 'BDGHJLMNPQRSTVWXZ';
		}
		if ($strength & 2) {
			$vowels .= "AEUY";
		}
		if ($strength & 4) {
			$consonants .= '23456789';
		}
		if ($strength & 8) {
			$consonants .= '@#$%';
		}
		
		$password = '';
		$alt = time() % 2;
		for ($i = 0; $i < $length; $i++) {
			if ($alt == 1) {
				$password .= $consonants[(rand() % strlen($consonants))];
				$alt = 0;
			} else {
				$password .= $vowels[(rand() % strlen($vowels))];
				$alt = 1;
			}
		}
		return $password;
	}
	
	public function forgotPassword() {
		$user = $this->mapper('user')->findByEmail($_POST['recipient'];
		
		$newPass = generatePassword(9,8);
        $user->setSalt(hash('sha256',dechex(sin(rand(0,100000))*100000)));
        $user->setPassword(hash('sha256',hash('sha256',$newPass).$user->getSalt()));
		
		if(isset($user))) {
			if(isset($_SESSION['languageId'])) {
				if($_SESSION['languageId'] == 1) {
					$subject = "password forgotten";
					$headers = "From:" . "service@we-r-asia.com" . "\n";
					$body = "new password:" + $newPass;
				} else {
					$subject = "wachtwoord vergeten";
					$headers = "Van:" . "service@we-r-asia.com" . "\n";
					$body = "nieuwe wachtword:" + $newPass;
				}
			}
			$charset='UTF-8';
			$recipient = $_POST['recipient'];
			$headers += "Content-Type: text/html; charset=$charset; format=flowed\n"
			. "MIME-Version: 1.0\n"
			. "Content-Transfer-Encoding: 8bit\n"
			. "X-Mailer: PHP\n";
			mail($recipient, $subject, $body, $headers);
		} else {
			
		}
	}
}
?>