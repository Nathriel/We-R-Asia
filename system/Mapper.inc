<?php
abstract class System_Mapper {
	protected $db;
	private $cache;
	private $system;
	
	public function __construct(System_Database_Database $db, System $system) {
		$this->db = $db;
		$this->cache = array();
		$this->system = $system;
	}
	
	/**
	* @see System::getMapper()
	*/
	public function mapper($name) {
		return $this->system->getMapper($name);
	}
	
	protected abstract function init();
	
	/**
	 * Finds an instance of the Model that matches the given id, this is cached
	 * @param $id int
	 */
	public function find($id) {
		if (!isset($this->cache[$id])) {
			$this->cache[$id] = $this->doFind($id);
		}
		return $this->cache[$id];
	}
	
	/**
	 * Implementation of find(), this should never be called directly
	 * @param $id int
	 */
	protected abstract function doFind($id);
	
	/**
	 * Deletes the Model that matches the given id and removes it from cache
	 * @param $id int
	 */
	public function delete($id) {
		unset($this->cache[$id]);
		$this->doDelete($id);
	}
	
	/**
	 * Implementation of delete(), this should never be called directly
	 * @param $id int
	 */
	public abstract function doDelete($id);
}
?>