<?php
class Projecten extends System_Controller {	
	public function index() {
		echo $this->t()->render('projecten.html', array(
			'pageTitle' => 'We R Asia | Projecten',
		));
	}
}
?>