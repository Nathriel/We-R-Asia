<?php
class Projects extends System_Controller {
    
    public function init(){
        $user = $this->mapper('user')->getLoggedinUser();
        if(!$user){
            header("Location: ./");
        }
    }
    
	public function index() {
		$user = $this->mapper('user')->getLoggedinUser();
		if ($user) {
			$projects = $user->getProjects();
		} else {
			$projects = $this->mapper('project')->findAll();
		}
		
		$tplProjects = array();
		foreach ($projects as $project) {
			$tplProjects[] = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'status' => 'moet nog',
			);
		}
		
		echo $this->t()->render('projects.html', array(
			'pageTitle' => 'We R Asia | Projects',
			'projects' => $tplProjects,
		));
	}
	
	public function add_project() {
		echo $this->t()->render('add_project.html', array(
			'pageTitle' => 'We R Asia | Add Project',
			'AddProjectForm' => array(
    				'action' => './projects/processAddProject/',
    			),
		));
	}
	public function processAddProject() {
		$projectMapper = $this->mapper('project');
		$project = new Project_Model($projectMapper);
		$project->setName($_POST['name']);
		$project->setCode($_POST['code']);
		$project->setFinished(0);
		$project->setStatusId(1);
		$project->save();
		header('location: ../../');
	}
	
	public function project($id = false) {
		if($id)
		{
			
			$project = $this->mapper('project')->find($id);
			
			$CurProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
			);
			/*
			$products = $this->mapper('product')->findAll();
			
			$tplProducts = array();
			foreach ($products as $product) {
				$tplProducts[] = array(
					'id' => $product->getId(),
					'name' => $product->getName(),
				);
			}
			*/
			
			echo $this->t()->render('project.html', array(
				'pageTitle' => 'We R Asia | Project',
				'project' => $CurProject,
				//'product' => $tplProducts,
			));
		} else {
			//leeg
		}
	}
	
	public function edit_project() {
		echo $this->t()->render('edit_project.html', array(
			'pageTitle' => 'We R Asia | Edit Project',
		));
	}
	
	public function product() {
		echo $this->t()->render('product.html', array(
			'pageTitle' => 'We R Asia | Product',
		));
	}
	
	public function add_product() {
		echo $this->t()->render('add_product.html', array(
			'pageTitle' => 'We R Asia | Add Product',
		));
	}
	
	public function edit_product() {
		echo $this->t()->render('edit_product.html', array(
			'pageTitle' => 'We R Asia | Edit Product',
		));
	}
	
	public function archive() {
		echo $this->t()->render('archive.html', array(
			'pageTitle' => 'We R Asia | Archive',
		));
	}
	
	public function upload() {
		echo $this->t()->render('doc_upload.html', array(
			'pageTitle' => 'We R Asia | Upload Document',
		));
	}
}
?>