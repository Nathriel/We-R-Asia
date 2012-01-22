<?php
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
            $mail->AddReplyTo($user->getEmail(), $user->getName());
            $mail->AddAddress('info@beyondquality.nl','WeAreAsia');
            $mail->SetFrom($user->getEmail(), $user->getName());
            $mail->AddReplyTo($user->getEmail(), $user->getName());
            $mail->Subject = $subject;
            $mail->AltBody = 'To view the message, please use an HTML compatible email viewer!'; // optional - MsgHTML will create an alternate automatically
            $mail->MsgHTML($message);
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
            $msg[] = $this->m()->translate('NewPasswordEmailSent', $user->getLanguage());
        }
        
        $this->index($msg);
    }
}

?>