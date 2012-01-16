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
                'EditUserForm' => array(
                    'action' => './users/editUserProcess/'.$id,
                    )
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
            header('location: ' . $this->getUrlPrefix() . 'users');
        }
	}
	
	public function add() {
		echo $this->t()->render('user/add_user.html', array(
			'pageTitle' => 'We R Asia | Add User',
            'AddUserForm' => array(
					'action' => './users/addUserProcess/',
            )
		));
	}
    
    public function editUserProcess($id = false){
        if($id)
		{
			$userMapper = $this->mapper('user');
			$user = $userMapper->find($id);
			$user->setUsername($_POST['username']);
            $user->setName($_POST['name']);
            $user->setEmail($_POST['email']);
            $user->setAddress($_POST['address']);
            $user->setResidence($_POST['residence']);
			$user->save();
            exit;
			header('location: ' . $this->getUrlPrefix() . 'users/edit/'.$id);
		} else {
			//leeg
		}
    }
    
    public function addUserProcess(){
        $userMapper = $this->mapper('user');
        $user = new User_Model($userMapper);
        $user->setUsername($_POST['username']);
        $user->setName($_POST['name']);
        $user->setEmail($_POST['email']);
        $user->setAddress($_POST['address']);
        $user->setResidence($_POST['residence']);
        $user->setRights($this->mapper('right')->find($_POST['type']));
        $user->setCompany($_POST['company']);
        $user->setSalt(hash('sha256',dechex(sin(rand(0,100000))*100000)));
        $user->setPassword(hash('sha256',hash('sha256',$_POST['password']).$user->getSalt()));
        $user->save();
        header('location: ' . $this->getUrlPrefix() . 'users');
    }
}
?>