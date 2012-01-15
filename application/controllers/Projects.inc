<?php
class Projects extends System_Controller {
    
    public function init(){
        $user = $this->mapper('user')->getLoggedinUser();
        if(!$user){
            header('Location: ./');
        }
    }
    
	public function index() {
		$user = $this->mapper('user')->getLoggedinUser();
		$languageModel = $user->getLanguage();
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
				'status' => $project->getStatus()->getTextForLanguage($languageModel),
			);
		}
		
		echo $this->t()->render('project/projects.html', array(
			'pageTitle' => 'We R Asia | Projects',
			'projects' => $tplProjects,
			'productsCount' => count($tplProjects),
		));
	}
	
	public function addProject() {
		echo $this->t()->render('project/add_project.html', array(
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
		header('location: ' . $this->getUrlPrefix() . 'projects');
	}
	
	public function project($id = false) {
		if($id)
		{
			$user = $this->mapper('user')->getLoggedinUser();
			$languageModel = $user->getLanguage();
			$project = $this->mapper('project')->find($id);
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
				'status' => $project->getStatus()->getTextForLanguage($languageModel),
			);
			
			$products = $this->mapper('product')->findByProject($project);
			$tplProducts = array();
			foreach ($products as $product) {
				$tplProducts[] = array(
					'id' => $product->getId(),
					'name' => $product->getName(),
					'status' => $product->getStatus()->getTextForLanguage($languageModel),
				);
			}
			
			echo $this->t()->render('project/project.html', array(
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
			
			echo $this->t()->render('project/edit_project.html', array(
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
			$project->save();
			header('location: ' . $this->getUrlPrefix() . 'projects');
		} else {
			//leeg
		}
	}
	
	public function product($id = false) {
		if($id)
		{
			$user = $this->mapper('user')->getLoggedinUser();
			$languageModel = $user->getLanguage();
			$product = $this->mapper('product')->find($id);
			
			$tplLogItems = array();
			$logItems = $product->getLogItems();
			foreach ($logItems as $logItem) {
				$tplLogItems[] = array(
					'date' => $logItem->getDate(),
					'text' => $logItem->getTextForLanguage($languageModel),
				);
			}
			
			$curProduct = array(
				'id' => $product->getId(),
				'name' => $product->getName(),
				'status' => $product->getStatus()->getTextForLanguage($languageModel),
				'logItems' => $tplLogItems,
			);
			
			
			$project = $this->mapper('project')->find($product->getProjectId());
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
			);
			
			echo $this->t()->render('project/product/product.html', array(
				'pageTitle' => 'We R Asia | Product',
				'product' => $curProduct,
				'project' => $curProject,
				'productsCount' => count($tplLogItems),
			));
		} else {
			//leeg
		}
	}
	
	public function addProduct($id = false) {
		if($id)
		{
			$project = $this->mapper('project')->find($id);
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
			);
			echo $this->t()->render('project/product/add_product.html', array(
				'pageTitle' => 'We R Asia | Add Product',
				'project' => $curProject,
				'AddProductForm' => array(
					'action' => './projects/addProductProcess/' . $id,
				),
			));
		} else {
			//leeg
		};
	}
	public function addProductProcess($id = false) {
		if($id)
		{
			$productMapper = $this->mapper('product');
			$product = new Product_Model($productMapper);
			$product->setName($_POST['name']);
			$product->setProjectId($id);
			$product->setStatusId(1);
			$product->save();
			header('location: ' . $this->getUrlPrefix() . 'projects/project/1');
		} else {
			//leeg
		};
	}
	
	public function editProduct($id = false) {
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
			);
			
			echo $this->t()->render('project/product/edit_product.html', array(
				'pageTitle' => 'We R Asia | Edit Product',
				'product' => $curProduct,
				'project' => $curProject,
				'EditProductForm' => array(
					'action' => './projects/editProductProcess/' . $product->getId(),
				),
			));
		} else {
			//leeg
		};
	}
	public function editProductProcess($id = false) {
		if($id)
		{
			$productMapper = $this->mapper('product');
			$product = $productMapper->find($id);
			$product->setName($_POST['name']);
			$product->save();
			header('location: ' . $this->getUrlPrefix() . 'projects/project/1');
		} else {
			//leeg
		}
	}
	
	public function addStatusToProject($id = false) {
		if($id)
		{
			$project = $this->mapper('project')->find($id);
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
			);
			
			echo $this->t()->render('project/update_status.html', array(
				'pageTitle' => 'We R Asia | Update Status',
				'project' => $curProject,
			));
		} else {
			//leeg
		}
	}
	
	public function addStatusToProduct($id = false) {
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
			);
			
			echo $this->t()->render('project/product/update_status.html', array(
				'pageTitle' => 'We R Asia | Update Status',
				'project' => $curProject,
				'product' => $curProduct,
			));
		} else {
			//leeg
		}
	}
	
	public function invoice() {
		echo $this->t()->render('project/invoices.html', array(
			'pageTitle' => 'We R Asia | Invoices',
		));
	}
	
	public function uploadInvoice() {
		echo $this->t()->render('project/invoice_upload.html', array(
			'pageTitle' => 'We R Asia | Upload Invoice',
		));
	}
	
	public function uploadDocument() {
		echo $this->t()->render('project/doc_upload.html', array(
			'pageTitle' => 'We R Asia | Upload Document',
		));
	}
}
?>