<?php
class Welcome extends System_Controller {	
	public function index() {
		echo $this->t()->render('login.html', array(
			'pageTitle' => 'We R Asia &bull; Login',
		));
	}
}
?>