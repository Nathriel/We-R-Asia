<?php
abstract class System_Model {
	protected $mapper;
	
	public function __construct(System_Mapper $mapper) {
		$this->mapper = $mapper;
	}
	
	public function save() {
		$this->mapper->save($this);
	}
}
?>