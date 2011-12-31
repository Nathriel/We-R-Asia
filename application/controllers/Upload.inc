<?php
class Upload extends System_Controller {	
	public function index() {
		echo $this->t()->render('upload.html', array(
			'pageTitle' => 'We R Asia | Upload',
		));
	}
}
?>