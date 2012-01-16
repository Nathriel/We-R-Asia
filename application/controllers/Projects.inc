<?php
class Projects extends System_Controller {
    
    public function init(){
        $user = $this->mapper('user')->getLoggedinUser();
        if(!$user){
            header('Location: ./');
        }
    }
    
    public function moveToArchive($id = false){
        if($id){
            $project = $this->mapper('project')->find($id);
            if($project){
                $project->setFinished(1);
                $project->save();
                header('location: ' . $this->getUrlPrefix() . 'archive');
            }
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
			
			echo $this->t()->render('project/project.html', array(
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
	
	public function archiveProjectProcess($id = false) {
		if($id)
		{
			$project = $this->mapper('project')->find($id);
			$project->setFinished(1);
			$project->save();
			header('location: ' . $this->getUrlPrefix() . 'projects');
		} else {
			//leeg
		}
	}
	
	public function deleteProjectProcess($id = false) {
		if($id)
		{
			$this->mapper('project')->delete($id);
			header('location: ' . $this->getUrlPrefix() . 'projects');
		} else {
			//leeg
		}
	}
	
	public function addProject() {
		$users = $this->mapper('user')->findAll();
		$tplUsers = array();
		foreach ($users as $user) {
			if (!$user->hasRight('europe')) {
				$tplUsers[] = array(
					'id' => $user->getId(),
					'name' => $user->getName(),
				);
			}
		}
		
		echo $this->t()->render('project/add_project.html', array(
			'pageTitle' => 'We R Asia | Add Project',
			'users' => $tplUsers,
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
		$project->setUsersAsIdArray($_POST['permissions']);
		$project->save();
		header('location: ' . $this->getUrlPrefix() . 'projects');
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
			
			$users = $this->mapper('user')->findAll();
			$tplUsers = array();
			foreach ($users as $user) {
				if (!$user->hasRight('europe')) {
					$tplUsers[] = array(
						'id' => $user->getId(),
						'name' => $user->getName(),
						'permission' => $user->canViewProject($project),
					);
				}
			}
			
			echo $this->t()->render('project/edit_project.html', array(
				'pageTitle' => 'We R Asia | Edit Project',
				'project' => $curProject,
				'users' => $tplUsers,
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
			$project->setUsersAsIdArray($_POST['permissions']);
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
			
			echo $this->t()->render('project/product/product.html', array(
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
	
	public function deleteProductProcess($id = false) {
		if($id)
		{
			$product = $this->mapper('product')->find($id);
			$project = $this->mapper('project')->find($product->getProjectId());
			$this->mapper('product')->delete($id);
			header('location: ' . $this->getUrlPrefix() . 'projects/project/' . $project->getId());
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
			header('location: ' . $this->getUrlPrefix() . 'projects/project/'.$id);
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
			$statuses = $this->mapper('status')->findAll();
			$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
			);
			
			$tplStatuses = array();
			foreach ($statuses as $status) {
				$tplStatuses[] = array(
					'name' => $status->getTextForLanguage($this->mapper('user')->getLoggedInUser()->getLanguage()),
					'id' => $status->getId(),
				);
			}
			
			echo $this->t()->render('project/update_status.html', array(
				'pageTitle' => 'We R Asia | Update Status',
				'project' => $curProject,
				'statuses' => $tplStatuses,
				'relevantId' => $curProject['id'],
				'type' => 'Project',
			));
		} else {
			//leeg
		}
	}
	
	public function processAddExistingStatusToProject($id = false) {
		if (!$id) {
			return;
		}
		$status = $this->mapper('status')->find($_POST['status']);
		$project = $this->mapper('project')->find($id);
		$logItemMapper = $this->mapper('logItem');
		$logItem = new LogItem_Model($logItemMapper);
		$logItem
			->setDate(time())
			->setTranslatableId($this->mapper('translatable')->findBySentence('statusChange')->getId())
			->setData(
				array(
					'fromStatus' => array(
						'find', 'Status', $project->getStatus()->getId(), 'TextForLanguage', 'currentLanguage'
					),
					'toStatus' => array(
						'find', 'Status', $_POST['status'], 'TextForLanguage', 'currentLanguage'
					),
				)
			)
			->save();
		$project->addLogItem($logItem);
		$project->setStatus($status);
		$project->save();
		header('location: ' . $this->getUrlPrefix() . 'projects/project/'.$id);
	}
	
	public function processAddNewStatusToProject($id = false) {
		if (!$id) {
			return;
		}
		$nlStatus = $_POST['nl_status'];
		$enStatus = $_POST['en_status'];
		$translatableMapper = $this->mapper('translatable');
		$translatable = new Translatable_Model($translatableMapper);
		$translatable->setSentence($enStatus);
		$translatable->save();
		
		$translationMapper = $this->mapper('translation');
		$translation = new Translation_Model($translationMapper);
		$translation->setTranslatableId($translatable->getId());
		$translation->setLanguage($this->mapper('language')->findByCode('en'));
		$translation->setTranslation($enStatus);
		$translation->save();
		
		$translation = new Translation_Model($translationMapper);
		$translation->setTranslatableId($translatable->getId());
		$translation->setLanguage($this->mapper('language')->findByCode('nl'));
		$translation->setTranslation($nlStatus);
		$translation->save();
		
		$statusMapper = $this->mapper('status');
		$status = new Status_Model($statusMapper);
		$status->setTranslatableId($translatable->getId());
		$status->save();
		$project = $this->mapper('project')->find($id);
		$logItemMapper = $this->mapper('logItem');
		$logItem = new LogItem_Model($logItemMapper);
		$logItem
			->setDate(time())
			->setTranslatableId($this->mapper('translatable')->findBySentence('statusChange')->getId())
			->setData(
					array(
							'fromStatus' => array(
									'find', 'Status', $project->getStatus()->getId(), 'TextForLanguage', 'currentLanguage'
							),
							'toStatus' => array(
									'find', 'Status', $status->getId(), 'TextForLanguage', 'currentLanguage'
							),
					)
			)
		->save();
		$project->addLogItem($logItem);
		$project->setStatus($status);
		$project->save();
		header('location: ' . $this->getUrlPrefix() . 'projects/project/'.$id);
	}
	
	public function processAddExistingStatusToProduct($id = false) {
		if (!$id) {
			return;
		}
		$status = $this->mapper('status')->find($_POST['status']);
		$product = $this->mapper('product')->find($id);
		$logItemMapper = $this->mapper('logItem');
		$logItem = new LogItem_Model($logItemMapper);
		$logItem
		->setDate(time())
		->setTranslatableId($this->mapper('translatable')->findBySentence('statusChange')->getId())
		->setData(
				array(
					'fromStatus' => array(
						'find', 'Status', $product->getStatus()->getId(), 'TextForLanguage', 'currentLanguage'
					),
					'toStatus' => array(
						'find', 'Status', $_POST['status'], 'TextForLanguage', 'currentLanguage'
					),
				)
		)
		->save();
		$product->addLogItem($logItem);
		$product->setStatus($status);
		$product->save();
		header('location: ' . $this->getUrlPrefix() . 'projects/product/'.$id);
	}
	
	public function processAddNewStatusToProduct($id = false) {
		if (!$id) {
			return;
		}
		$nlStatus = $_POST['nl_status'];
		$enStatus = $_POST['en_status'];
		$translatableMapper = $this->mapper('translatable');
		$translatable = new Translatable_Model($translatableMapper);
		$translatable->setSentence($enStatus);
		$translatable->save();
	
		$translationMapper = $this->mapper('translation');
		$translation = new Translation_Model($translationMapper);
		$translation->setTranslatableId($translatable->getId());
		$translation->setLanguage($this->mapper('language')->findByCode('en'));
		$translation->setTranslation($enStatus);
		$translation->save();
	
		$translation = new Translation_Model($translationMapper);
		$translation->setTranslatableId($translatable->getId());
		$translation->setLanguage($this->mapper('language')->findByCode('nl'));
		$translation->setTranslation($nlStatus);
		$translation->save();
	
		$statusMapper = $this->mapper('status');
		$status = new Status_Model($statusMapper);
		$status->setTranslatableId($translatable->getId());
		$status->save();
		$product = $this->mapper('product')->find($id);
		$logItemMapper = $this->mapper('logItem');
		$logItem = new LogItem_Model($logItemMapper);
		$logItem
		->setDate(time())
		->setTranslatableId($this->mapper('translatable')->findBySentence('statusChange')->getId())
		->setData(
				array(
						'fromStatus' => array(
								'find', 'Status', $product->getStatus()->getId(), 'TextForLanguage', 'currentLanguage'
						),
						'toStatus' => array(
								'find', 'Status', $status->getId(), 'TextForLanguage', 'currentLanguage'
						),
				)
		)
		->save();
		$product->addLogItem($logItem);
		$product->setStatus($status);
		$product->save();
		header('location: ' . $this->getUrlPrefix() . 'projects/product/'.$id);
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
			
			$statuses = $this->mapper('status')->findAll();
			$tplStatuses = array();
			foreach ($statuses as $status) {
				$tplStatuses[] = array(
						'name' => $status->getTextForLanguage($this->mapper('user')->getLoggedInUser()->getLanguage()),
						'id' => $status->getId(),
				);
			}
			
			echo $this->t()->render('project/product/update_status.html', array(
				'pageTitle' => 'We R Asia | Update Status',
				'project' => $curProject,
				'product' => $curProduct,
				'type' => 'Product',
				'relevantId' => $curProduct['id'],
				'statuses' => $tplStatuses,
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
		echo $this->t()->render('project/invoices.html', array(
			'pageTitle' => 'We R Asia | Invoices',
			'project' => $curProject,
		));
	}
	
	public function uploadInvoice($id = false) {
		if (!$id) {
			return;
		}
		$project = $this->mapper('project')->find($id);
		$curProject = array(
			'id' => $project->getId(),
			'name' => $project->getName(),
			'code' => $project->getCode(),
		);
		echo $this->t()->render('project/invoice_upload.html', array(
				'pageTitle' => 'We R Asia | Upload Invoice',
				'project' => $curProject,
		));
	}
	
	public function uploadInvoiceProcess($id = false) {
		if (!$id) {
			return;
		}
		$newName = './content/uploads/'.(microtime(true)*1000).'_'.$_FILES['file_input']['name'];
		move_uploaded_file($_FILES['file_input']['tmp_name'], $newName);
		$project = $this->mapper('project')->find($id);
		$invoiceMapper = $this->mapper('invoice');
		$invoice = new Invoice_Model($invoiceMapper);
		$invoice->setFileLocation($newName)->setProjectId($id)->save();
	
		$project->addInvoice($invoice);
		$project->save();
		header('location: ' . $this->getUrlPrefix() . 'projects/invoice/'.$id);
	}
	
	public function uploadDocumentToProject($id = false) {
		if (!$id) {
			return;
		}
		$project = $this->mapper('project')->find($id);
		$curProject = array(
			'id' => $project->getId(),
			'name' => $project->getName(),
			'code' => $project->getCode(),
		);
		echo $this->t()->render('project/doc_upload.html', array(
			'pageTitle' => 'We R Asia | Upload Document',
			'project' => $curProject,
		));
	}
	
	public function uploadDocumentToProjectProcess($id = false) {
		if (!$id) {
			return;
		}
		$newName = './content/uploads/'.(microtime(true)*1000).'_'.$_FILES['file_input']['name'];
		move_uploaded_file($_FILES['file_input']['tmp_name'], $newName);
		$project = $this->mapper('project')->find($id);
		$documentMapper = $this->mapper('document');
		$document = new Document_Model($documentMapper);
		$document->setFileLocation($newName)->save();
		
		$project->addDocument($document);
		$project->save();
		header('location: ' . $this->getUrlPrefix() . 'projects/project/'.$id);
	}
	
	public function uploadDocumentToProduct($id = false) {
		if (!$id) {
			return;
		}
		$product = $this->mapper('product')->find($id);
		$curProduct = array(
			'id' => $product->getId(),
			'name' => $product->getName(),
		);
		
		$project = $product->getProject();
		$curProject = array(
				'id' => $project->getId(),
				'name' => $project->getName(),
				'code' => $project->getCode(),
		);
		echo $this->t()->render('project/product/doc_upload.html', array(
				'pageTitle' => 'We R Asia | Upload Document',
				'project' => $curProject,
				'product' => $curProduct,
		));
	}
	
	public function uploadDocumentToProductProcess($id = false) {
		if (!$id) {
			return;
		}
		$newName = './content/uploads/'.(microtime(true)*1000).'_'.$_FILES['file_input']['name'];
		move_uploaded_file($_FILES['file_input']['tmp_name'], $newName);
		$product = $this->mapper('product')->find($id);
		$documentMapper = $this->mapper('document');
		$document = new Document_Model($documentMapper);
		$document->setFileLocation($newName)->save();
	
		$product->addDocument($document);
		$product->save();
		header('location: ' . $this->getUrlPrefix() . 'projects/product/'.$id);
	}
}
?>