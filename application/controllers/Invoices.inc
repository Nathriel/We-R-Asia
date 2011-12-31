<?php
class Invoices extends System_Controller {	
	public function index() {
		echo $this->t()->render('invoices.html', array(
			'pageTitle' => 'We R Asia | Invoices',
		));
	}
}
?>