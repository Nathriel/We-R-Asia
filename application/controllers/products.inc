<?php
class Products extends System_Controller {
    public function init(){
        $user = $this->mapper('user')->getLoggedinUser();
        if(!$user){
            header("Location: index.php");
        }
    }
    
	public function index() {
		echo $this->t()->render('product.html', array(
			'pageTitle' => 'We R Asia | product',
		));
	}
}
?>