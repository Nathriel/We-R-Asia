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
	
    public function newPasswordRequest(){
        $user = $this->mapper('user')->getLoggedinUser();
        if ($user) {
            header('location: ./Projects');
        } else {
            echo $this->t()->render('forgotPassword.html', array(
    			'pageTitle' => 'We R Asia | Forgot Password',
    			'passwordForm' => array(
    				'action' => './home/sendPassword/',
    			),
            	'languageSwitchReturnUrl' => urlencode(''),
    		));
        }
    }
    
    public function sendPassword(){
        $this->forgotPassword();
    }
    
	public function forgotPassword() {
		$user = $this->mapper('user')->findByEmail($_POST['recipient']);
		$newPass = $this->generatePassword(9,8);
        $user->setSalt(hash('sha256',dechex(sin(rand(0,100000))*100000)));
        $user->setPassword(hash('sha256',hash('sha256',$newPass).$user->getSalt()));
		
        
        $mail_body = $this->m()->translate('newPasswordEmail', $user->getLanguage());
        $subject = $this->m()->translate('newPasswordSubjectEmail', $user->getLanguage());
        $mail_body = str_replace("{user}", $user->getUsername(), $mail_body);
        $mail_body = str_replace("{username}", $user->getUsername(), $mail_body);
        $mail_body = str_replace("{password}", $newPass, $mail_body);
        $mail_body = nl2br($mail_body);
        $messages = array();
		if(isset($user)) {
            $mail = $this->mailer();
            $mail->AddReplyTo('wra@bequtest.nl', 'WeAreAsia');
            $mail->AddAddress($_POST['recipient'],$user->getUsername());
            $mail->SetFrom('wra@bequtest.nl', 'WeAreAsia');
            $mail->AddReplyTo('wra@bequtest.nl', 'WeAreAsia');
            $mail->Subject = $subject;
            $mail->AltBody = 'To view the message, please use an HTML compatible email viewer!'; // optional - MsgHTML will create an alternate automatically
            $mail->MsgHTML($mail_body);
            try{
                $mail->Send();
                $user->save();
            } catch (phpmailerException $e) {
                $msg[] = $this->m()->translate('emailNotSendError', $user->getLanguage());
                $msg[] = $e->errorMessage();
            } catch (Exception $e) {
                $msg[] = $this->m()->translate('emailNotSendError', $user->getLanguage());
                $msg[] = $e->errorMessage();
            }
		} else {
			$msg[] = $this->m()->translate('userByEmailNotFound', $user->getLanguage());
            $msg[] = $e->errorMessage();
		}
        $msg[] = $this->m()->translate('NewPasswordEmailSent', $user->getLanguage());
        echo $this->t()->render('forgotPassword.html', array(
    			'pageTitle' => 'We R Asia | Forgot Password',
    			'passwordForm' => array(
    				'action' => './home/sendPassword/',
    			),
            	'languageSwitchReturnUrl' => urlencode(''),
                'messages' => $msg,
    		));
	}
}
?>