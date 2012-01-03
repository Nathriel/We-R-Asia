<?php
class Invoices extends System_Controller {
	public function index() {
		echo $this->t()->render('invoices.html', array(
			'pageTitle' => 'We R Asia | Invoices',
		));
	}
	public function overview() {
		echo $this->t()->render('invoices.html', array(
			'pageTitle' => 'We R Asia | Invoices',
		));
	}
	
	public function upload() {
		echo $this->t()->render('invoice_upload.html', array(
			'pageTitle' => 'We R Asia | Upload Invoice',
		));
	}
}
?>