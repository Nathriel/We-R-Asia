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
		$languageModel = $user->getLanguage();
		if ($user) {
			$projects = $user->getProjects(true);
		} else {
			$projects = $this->mapper('project')->findAll(true);
		}
        
        //var_dump($projects);
        //exit;
		
		$tplProjects = array();
		foreach ($projects as $project) {
			$tplProjects[] = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'status' => $project->getStatus()->getTextForLanguage($languageModel),
			);
		}
		
		echo $this->t()->render('archive/archive.html', array(
			'pageTitle' => 'We R Asia | Archive',
			'projects' => $tplProjects,
			'productsCount' => count($tplProjects),
		));
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
			
			$documents = $this->mapper('document')->findByProject($project);
			$tplDocuments = array();
			foreach ($documents as $document) {
				if ($document) {
					$splitFileLocation = explode('_', $document->getFileLocation());
					$tplDocuments[] = array(
						'id' => $document->getId(),
						'name' => (isset($splitFileLocation[1])?$splitFileLocation[1]:'Unknown'),
						'date' => date('d-m-Y H:i:s', filemtime($document->getFileLocation())),
						'fileUrl' => $document->getFileLocation(),
					);
				}
			}
			
			echo $this->t()->render('archive/project.html', array(
				'pageTitle' => 'We R Asia | Project',
				'project' => $curProject,
				'products' => $tplProducts,
				'documents' => $tplDocuments,
				'productsCount' => count($tplProducts),
				'documentsCount' => count($tplDocuments),
			));
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
			
			$documents = $this->mapper('document')->findByProduct($product);
			$tplDocuments = array();
			foreach ($documents as $document) {
				if ($document) {
					$splitFileLocation = explode('_', $document->getFileLocation());
					$tplDocuments[] = array(
						'id' => $document->getId(),
						'name' => (isset($splitFileLocation[1])?$splitFileLocation[1]:'Unknown'),
						'date' => date('d-m-Y H:i:s', filemtime($document->getFileLocation())),
						'fileUrl' => $document->getFileLocation(),
					);
				}
			}
			
			echo $this->t()->render('archive/product/product.html', array(
				'pageTitle' => 'We R Asia | Product',
				'product' => $curProduct,
				'project' => $curProject,
				'documents' => $tplDocuments,
				'productsCount' => count($tplLogItems),
				'documentsCount' => count($tplDocuments),
			));
		} else {
			//leeg
		}
	}
	
	public function invoice($id = false) {
		if (!$id) {
			return;
		}
		$project = $this->mapper('project')->find($id);
		$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
		);
		
		$invoices = $project->getInvoices();
		$tplInvoices = array();
		foreach ($invoices as $invoice) {
			if ($invoice) {
				$splitFileLocation = explode('_', $invoice->getFileLocation());
				$tplInvoices[] = array(
						'id' => $invoice->getId(),
						'name' => (isset($splitFileLocation[1])?$splitFileLocation[1]:'Unknown'),
						'date' => date('d-m-Y H:i:s', filemtime($invoice->getFileLocation())),
						'fileUrl' => $invoice->getFileLocation(),
				);
			}
		}
		
		echo $this->t()->render('archive/invoices.html', array(
			'pageTitle' => 'We R Asia | Invoices',
			'project' => $curProject,
			'invoices' => $tplInvoices,
		));
	}
}
?>