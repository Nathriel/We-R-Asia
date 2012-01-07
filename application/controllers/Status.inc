<?php
class Status extends System_Controller {
	public function index() {
		echo $this->t()->render('status/add_status.html', array(
			'pageTitle' => 'We R Asia | New Status',
		));
	}
	
	public function add() {
		echo $this->t()->render('status/add_status.html', array(
			'pageTitle' => 'We R Asia | New Status',
		));
	}
	
	public function edit() {
		echo $this->t()->render('status/edit_status.html', array(
			'pageTitle' => 'We R Asia | Edit Status',
		));
	}
}
?>