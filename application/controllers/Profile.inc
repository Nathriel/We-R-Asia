<?php
class Profile extends System_Controller {	
	public function index() {
		$args = array(
			'pageTitle' => 'We R Asia | Profile',
			'profileForm' => array(
				'action' => './Profile/EditProcess',
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
		
	}
}
?>