<?php
error_reporting(0);
class Contact extends System_Controller {	
	public function index($msg="") {
		echo $this->t()->render('contact.html', array(
			'pageTitle' => 'We R Asia | Contact',
            'contactForm' => array (
                'action' => './Contact/processContact'
            ),
            'messages' => $msg,
		));
	}
    
    public function processContact(){
        if($_POST)
        {
            $user = $this->mapper('user')->getLoggedInUser();
            
            $subject = $_POST['subject'];
            $message = $_POST['message'];
            
            $mail = $this->mailer();
            if(check_email_address($user->getEmail()))
            {
                $user_email = $user->getEmail();
            }
            else
            {
                $user_email = "not_valid_email@beyondquality.nl";
            }
            $mail->AddReplyTo($user_email, $user->getName());
            $mail->AddAddress('info@beyondquality.nl','WeAreAsia');
            $mail->SetFrom($user_email, $user->getName());
            $mail->AddReplyTo($user_email, $user->getName());
            $mail->Subject = $subject;
            $mail->AltBody = 'To view the message, please use an HTML compatible email viewer!'; // optional - MsgHTML will create an alternate automatically
            $mail->MsgHTML($message);
            $error=false;
            try{
                $mail->Send();
                $user->save();
            } catch (phpmailerException $e) {
                $msg[] = $this->m()->translate('emailNotSendError', $user->getLanguage());
                $msg[] = $e->errorMessage();
                $error = true;
            } catch (Exception $e) {
                $msg[] = $this->m()->translate('emailNotSendError', $user->getLanguage());
                $msg[] = $e->errorMessage();
                $error=true;
            }
            if(!$error)
            $msg[] = $this->m()->translate('EmailHasBeenSent', $user->getLanguage());
        }
        
        $this->index($msg);
    }
}

function check_email_address($email) {
  // First, we check that there's one @ symbol, 
  // and that the lengths are right.
  if (!ereg("^[^@]{1,64}@[^@]{1,255}$", $email)) {
    // Email invalid because wrong number of characters 
    // in one section or wrong number of @ symbols.
    return false;
  }
  // Split it into sections to make life easier
  $email_array = explode("@", $email);
  $local_array = explode(".", $email_array[0]);
  for ($i = 0; $i < sizeof($local_array); $i++) {
    if
(!ereg("^(([A-Za-z0-9!#$%&'*+/=?^_`{|}~-][A-Za-z0-9!#$%&
?'*+/=?^_`{|}~\.-]{0,63})|(\"[^(\\|\")]{0,62}\"))$",
$local_array[$i])) {
      return false;
    }
  }
  // Check if domain is IP. If not, 
  // it should be valid domain name
  if (!ereg("^\[?[0-9\.]+\]?$", $email_array[1])) {
    $domain_array = explode(".", $email_array[1]);
    if (sizeof($domain_array) < 2) {
        return false; // Not enough parts to domain
    }
    for ($i = 0; $i < sizeof($domain_array); $i++) {
      if
(!ereg("^(([A-Za-z0-9][A-Za-z0-9-]{0,61}[A-Za-z0-9])|
?([A-Za-z0-9]+))$",
$domain_array[$i])) {
        return false;
      }
    }
  }
  return true;
}
?>