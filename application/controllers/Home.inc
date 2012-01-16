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
        require_once('/libraries/phpMailer/class.phpmailer.php');
        $mail = new PHPMailer(true);
        $mail->IsSMTP();

		$user = $this->mapper('user')->findByEmail($_POST['recipient']);
		$newPass = $this->generatePassword(9,8);
        $user->setSalt(hash('sha256',dechex(sin(rand(0,100000))*100000)));
        $user->setPassword(hash('sha256',hash('sha256',$newPass).$user->getSalt()));
		
		if(isset($user)) {
			if(isset($_SESSION['languageId'])) {
				if($_SESSION['languageId'] == 1) {
					$subject = "password forgotten";
					$headers = "From:" . "service@we-r-asia.com" . "\n";
					$body = "new password:" . $newPass;
				} else {
					$subject = "wachtwoord vergeten";
					$headers = "Van:" . "service@we-r-asia.com" . "\n";
					$body = "nieuwe wachtwoord:" . $newPass;
				}
			}else
            {
                $body = "new password:" . $newPass;
            }
            
            $mail->Host       = "mail.bequtest.nl"; // SMTP server                  
          $mail->SMTPAuth   = true;                  // enable SMTP authentication
          $mail->Host       = "mail.bequtest.nl"; // sets the SMTP server
          $mail->Port       = 26;                    // set the SMTP port for the GMAIL server
          $mail->Username   = "wra@bequtest.nl"; // SMTP account username
          $mail->Password   = "wra";        // SMTP account password
          $mail->AddReplyTo('wra@bequtest.nl', 'First Last');
          $mail->AddAddress($_POST['recipient'],$user->getUsername());
          $mail->SetFrom('wra@bequtest.nl', 'We Are Asia');
          $mail->AddReplyTo('wra@bequtest.nl', 'We Are Asia');
          $mail->Subject = $subject;
          $mail->AltBody = 'To view the message, please use an HTML compatible email viewer!'; // optional - MsgHTML will create an alternate automatically
          $mail->MsgHTML($body);
          try{
            $mail->Send();
            $user->save();
          } catch (phpmailerException $e) {
            //echo $e->errorMessage(); //Pretty error messages from PHPMailer
          } catch (Exception $e) {
            //echo $e->getMessage(); //Boring error messages from anything else!
          }
          header('Location: '.$this->getUrlPrefix());
		} else {
			
		}
	}
}
?>