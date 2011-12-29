<?php
class Error extends System_Controller {	
	public function index() {
		echo $this->t()->render('error.html', array(
			'pageTitle' => 'We R Asia | Error',
		));
	}
}
?>