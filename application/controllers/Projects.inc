<?php
class Projects extends System_Controller {	
	public function index() {
		echo $this->t()->render('projects.html', array(
			'pageTitle' => 'We R Asia | Projects',
		));
	}
}
?>