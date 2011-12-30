<?php
class Projects extends System_Controller {	
	public function index() {
		echo $this->t()->render('projects.html', array(
			'pageTitle' => 'We R Asia | Projecten',
		));
	}
	
	public function project() {
		echo $this->t()->render('project.html', array(
			'pageTitle' => 'We R Asia | project',
		));
	}
}
?>