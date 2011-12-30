<?php
class Profile extends System_Controller {	
	public function index() {
		echo $this->t()->render('profile.html', array(
			'pageTitle' => 'We R Asia | Profile',
		));
	}
}
?>