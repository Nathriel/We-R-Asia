<?php
class Status extends System_Controller {
	public function index() {
		echo $this->t()->render('add_status.html', array(
			'pageTitle' => 'We R Asia | New Status',
		));
	}
	
	public function add() {
		echo $this->t()->render('add_status.html', array(
			'pageTitle' => 'We R Asia | New Status',
		));
	}
	
	public function edit() {
		echo $this->t()->render('edit_status.html', array(
			'pageTitle' => 'We R Asia | Edit Status',
		));
	}
}
?>