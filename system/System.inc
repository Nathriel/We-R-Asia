<?php
class System {
	public function __construct() {
		ini_set('unserialize_callback_func', 'spl_autoload_call');
        spl_autoload_register(array($this, 'autoload'));
		
		//initialize stuff
	}
	
	public function run() {
		//run it!
		$requestedPage = $_SERVER['PATH_INFO'];
		$pathInfo = explode('/', $requestedPage);
		array_shift($pathInfo);
	}
	
	private function autoload($class)
    {
        if (0 !== strpos($class, 'System_')) {
            return;
        }

        if (is_file($file = dirname(__FILE__).'/../'.str_replace(array('_', "\0"), array('/', ''), $class).'.inc')) {
            require $file;
        }
    }
}
?>