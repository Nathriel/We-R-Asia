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
			'pageTitle' => 'We R Asia | project',
		));
	}
}
?>