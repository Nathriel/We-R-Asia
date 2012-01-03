<?php
class Projects extends System_Controller {	
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
	
	public function project() {
		echo $this->t()->render('project.html', array(
			'pageTitle' => 'We R Asia | Project',
		));
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
	
	public function edit_product() {
		echo $this->t()->render('edit_product.html', array(
			'pageTitle' => 'We R Asia | Edit Product',
		));
	}
	
	public function upload() {
		echo $this->t()->render('doc_upload.html', array(
			'pageTitle' => 'We R Asia | Upload Document',
		));
	}
}
?>