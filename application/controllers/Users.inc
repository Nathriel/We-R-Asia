<?php
class Users extends System_Controller {	
	public function index() {
        $user = $this->mapper('user')->find($_SESSION['userId']);
        if($user && $user->hasRight('europe'))
        {
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
    			if($user->getId() ==  $this->mapper('user')->getLoggedInUser()->getId())
                    $canDelete = false;
                else
                    $canDelete = true;
    			$tplUsers[] = array(
    				'id' => $user->getId(),
    				'name' => $user->getName(),
    				'company' => $user->getCompany(),
    				'type' => $type, // TODO: multilanguage
                    'candelete' => $canDelete,
    			);
    		}
    		echo $this->t()->render('user/users.html', array(
    			'pageTitle' => 'We R Asia | User',
    			'users' => $tplUsers,
    		));
        }
        else
        {
            header('location: ' . $this->getUrlPrefix() . 'Profile');
        }
	}
	
    public function delete($id = false){
        $user = $this->mapper('user')->find($_SESSION['userId']);
        if(!$user->hasRight('europe'))
        {
            echo "Restricted Area";
            exit;
        }
        
        if($id){
            if($id !=  $this->mapper('user')->getLoggedInUser()->getId())
            {
                $this->mapper('user')->doDelete($id);
            }
            header('location: ' . $this->getUrlPrefix() . 'users');
        }
    }
    
	public function edit($id = false) {
	   $user = $this->mapper('user')->find($_SESSION['userId']);
	   if(!$user->hasRight('europe'))
        {
            echo "Restricted Area";
            exit;
        }
        
	   if($id)
       {
    	   $args = array(
    			'pageTitle' => 'We R Asia | Edit User',
                'EditUserForm' => array(
                    'action' => './users/editUserProcess/'.$id,
                    )
	      );
           $user = $this->mapper('user')->find($id);
           $rightarray = $user->getRights();
           $permission = $rightarray[0]->getId();
           $args += array(
    				'username' => $user->getUsername(),
    				'name' => $user->getName(),
    				'email' => $user->getEmail(),
    				'address' => $user->getAddress(),
    				'residence' => $user->getResidence(),
    				'company' => $user->getCompany(),
                    'permission' => $permission,
    			);
    		echo $this->t()->render('user/edit_user.html', $args);
        }else{
            header('location: ' . $this->getUrlPrefix() . 'users');
        }
	}
	
	public function add() {
	   $user = $this->mapper('user')->find($_SESSION['userId']);
	   if(!$user->hasRight('europe'))
        {
            echo "Restricted Area";
            exit;
        }
		echo $this->t()->render('user/add_user.html', array(
			'pageTitle' => 'We R Asia | Add User',
            'AddUserForm' => array(
					'action' => './users/addUserProcess/',
            )
		));
	}
    
    public function editUserProcess($id = false){
        $user = $this->mapper('user')->find($_SESSION['userId']);
        if(!$user->hasRight('europe'))
        {
            echo "Restricted Area";
            exit;
        }
        if($id)
		{
			$userMapper = $this->mapper('user');
			$user = $userMapper->find($id);
			$user->setUsername($_POST['username']);
            $user->setName($_POST['name']);
            $user->setEmail($_POST['email']);
            $user->setAddress($_POST['address']);
            $user->setResidence($_POST['residence']);
            $user->setRights($this->mapper('right')->find($_POST['type']));
            if($_POST['password'])
            {
                $user->setSalt(hash('sha256',dechex(sin(rand(0,100000))*100000)));
                $user->setPassword(hash('sha256',hash('sha256',$_POST['password']).$user->getSalt()));
            }
            
			$user->save();
			header('location: ' . $this->getUrlPrefix() . 'users/edit/'.$id);
		} else {
			//leeg
		}
    }
    
    public function addUserProcess(){
        $user = $this->mapper('user')->find($_SESSION['userId']);
        if(!$user->hasRight('europe'))
        {
            echo "Restricted Area";
            exit;
        }
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