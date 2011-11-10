<?php
class System {
	private $baseConfig;

	public function __construct(array $config) {
		ini_set('unserialize_callback_func', 'spl_autoload_call');
        spl_autoload_register(array($this, 'autoload'));
		
		//initialize stuff
		$this->baseConfig = $config;
	}
	
	public function run() {
		//run it!
		$requestedPage = $_SERVER['PATH_INFO'];
		$pathInfo = explode('/', $requestedPage);
		array_shift($pathInfo);
		
		if (isset($pathInfo[0])) {
			$controllerName = $pathInfo[0];
			if (is_file($controllerFile = './'.$this->baseConfig['applicationPath'].'controllers/'.ucfirst($controllerName).'.inc')) {
				if (isset($pathInfo[1])) {
					$function = $pathInfo[1];
				} else {
					$function = 'index';
				}
				require($controllerFile);
				
				$controller = new $controllerName($this);
				$controller->$function();
			}
		}
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