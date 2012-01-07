<?php
class Archive extends System_Controller {
    
    public function init(){
        $user = $this->mapper('user')->getLoggedinUser();
        if(!$user){
            header('Location: ./');
        }
    }
    
	public function index() {
		$user = $this->mapper('user')->getLoggedinUser();
		if ($user) {
			$projects = $user->getProjects(true);
		} else {
			$projects = $this->mapper('project')->findAll(true);
		}
		
		$tplProjects = array();
		foreach ($projects as $project) {
			$tplProjects[] = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'status' => 'moet nog',
			);
		}
		
		echo $this->t()->render('archive/archive.html', array(
			'pageTitle' => 'We R Asia | Archive',
			'projects' => $tplProjects,
		));
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
			
			echo $this->t()->render('archive/project.html', array(
				'pageTitle' => 'We R Asia | Project',
				'project' => $curProject,
				'products' => $tplProducts,
				'productsCount' => count($tplProducts),
			));
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
			
			echo $this->t()->render('archive/product/product.html', array(
				'pageTitle' => 'We R Asia | Product',
				'product' => $curProduct,
				'project' => $curProject,
			));
		} else {
			//leeg
		}
	}
	
	public function invoice() {
		echo $this->t()->render('archive/invoices.html', array(
			'pageTitle' => 'We R Asia | Invoices',
		));
	}
}
?>