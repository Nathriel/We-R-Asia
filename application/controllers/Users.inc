<?php
class Users extends System_Controller {	
	public function index() {
		$users = $this->mapper('user')->findAll();
		$tplUsers = array();
		foreach ($users as $user) {
			/* @var $user User_Model */
			$type = 'Customer';
			if ($user->hasRight('europe')) {
				$type = 'Europe';
			} elseif ($user->hasRight('china')) {
				$type = 'China';
			}
			
			$tplUsers[] = array(
				'id' => $user->getId(),
				'name' => $user->getName(),
				'company' => $user->getCompany(),
				'type' => $type, // TODO: multilanguage
			);
		}
		echo $this->t()->render('user/users.html', array(
			'pageTitle' => 'We R Asia | User',
			'users' => $tplUsers,
		));
	}
	
	public function edit($id = false) {
	   if($id)
       {
    	   $args = array(
    			'pageTitle' => 'We R Asia | Edit User',
	      );
           $user = $this->mapper('user')->find($id);
           $args += array(
    				'username' => $user->getUsername(),
    				'name' => $user->getName(),
    				'email' => $user->getEmail(),
    				'address' => $user->getAddress(),
    				'residence' => $user->getResidence(),
    				'company' => $user->getCompany(),
    			);
    		echo $this->t()->render('user/edit_user.html', $args);
        }else{
            //Wanneer edit leeg is
        }
	}
	
	public function add() {
		echo $this->t()->render('user/add_user.html', array(
			'pageTitle' => 'We R Asia | Add User',
		));
	}
}
?>