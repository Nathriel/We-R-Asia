<?php
class Products extends System_Controller {	
	public function index() {
		echo $this->t()->render('product.html', array(
			'pageTitle' => 'We R Asia | product',
		));
	}
}
?>