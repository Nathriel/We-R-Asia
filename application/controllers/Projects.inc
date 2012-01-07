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
	
	public function addProject() {
		echo $this->t()->render('add_project.html', array(
			'pageTitle' => 'We R Asia | Add Project',
			'AddProjectForm' => array(
				'action' => './projects/addProjectProcess/',
			),
		));
	}
	public function addProjectProcess() {
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
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
			);
			
			$products = $this->mapper('product')->findByProject($project);
			$tplProducts = array();
			foreach ($products as $product) {
				$tplProducts[] = array(
					'id' => $product->getId(),
					'name' => $product->getName(),
				);
			}
			
			echo $this->t()->render('project.html', array(
				'pageTitle' => 'We R Asia | Project',
				'project' => $curProject,
				'products' => $tplProducts,
				'productsCount' => count($tplProducts),
			));
		} else {
			//leeg
		}
	}
	
	public function editProject($id = false) {
		if($id)
		{
			$project = $this->mapper('project')->find($id);
			
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
				'done' => $project->getFinished(),
			);
			
			echo $this->t()->render('edit_project.html', array(
				'pageTitle' => 'We R Asia | Edit Project',
				'project' => $curProject,
				'EditProjectForm' => array(
					'action' => './projects/editProjectProcess/' . $project->getId(),
				),
			));
		} else {
			//leeg
		}
	}
	public function editProjectProcess($id = false) {
		if($id)
		{
			$projectMapper = $this->mapper('project');
			$project = $projectMapper->find($id);
			$project->setName($_POST['name']);
			$project->setCode($_POST['code']);
			if(isset($_POST['done'])) {
				$project->setFinished(1);
			} else {
				$project->setFinished(0);
			}
			$project->setStatusId(1);
			$project->save();
			header('location: ../../');
		} else {
			//leeg
		}
	}
	
	public function product($id = false) {
		if($id)
		{
			$product = $this->mapper('product')->find($id);
			$curProduct = array(
				'id' => $product->getId(),
				'name' => $product->getName(),
			);
			
			$project = $this->mapper('project')->find($product->getProjectId());
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
			);
			
			echo $this->t()->render('product.html', array(
				'pageTitle' => 'We R Asia | Product',
				'product' => $curProduct,
				'project' => $curProject,
			));
		} else {
			//leeg
		}
	}
	
	public function addProduct() {
		echo $this->t()->render('add_product.html', array(
			'pageTitle' => 'We R Asia | Add Product',
		));
	}
	
	public function editProduct() {
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