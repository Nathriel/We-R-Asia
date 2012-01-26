<?php
class Profile extends System_Controller {	
	public function index() {
		$args = array(
			'pageTitle' => 'We R Asia | Profile',
			'ProfileForm' => array(
				'action' => './Profile/editProcess',
			),
		);
		if (isset($_SESSION['userId'])) {
			/* @var $user User_Model */ // little trick for autocompletion
			$user = $this->mapper('user')->find($_SESSION['userId']);
			$args += array(
				'username' => $user->getUsername(),
				'name' => $user->getName(),
				'email' => $user->getEmail(),
				'address' => $user->getAddress(),
				'residence' => $user->getResidence(),
				'company' => $user->getCompany(),
			);
		}
		echo $this->t()->render('user/profile.html', $args);
	}
	
	public function editProcess() {
	   if (isset($_SESSION['userId'])) {
            $userMapper = $this->mapper('user');
			$user = $userMapper->find($_SESSION['userId']);
			$user->setUsername($_POST['username']);
            $user->setName($_POST['name']);
            $user->setEmail($_POST['email']);
            $user->setAddress($_POST['address']);
            $user->setResidence($_POST['residence']);
            $user->setCompany($_POST['company']);
            
            if($_POST['password'] && $_POST['password'] !="")
            {
                $user->setSalt(hash('sha256',dechex(sin(rand(0,100000))*100000)));
                $user->setPassword(hash('sha256',hash('sha256',$_POST['password']).$user->getSalt()));
            }
            
			$user->save();
			header('location: ' . $this->getUrlPrefix() . 'Profile');
        }
	}
}
?>