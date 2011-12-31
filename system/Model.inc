<?php
abstract class System_Model {
	protected $mapper;
	
	public function __construct(System_Mapper $mapper) {
		$this->mapper = $mapper;
	}
	
	public function save() {
		if (method_exists($this->mapper, 'doSave')) {
			$this->mapper->doSave($this);
		}
	}
}
?>