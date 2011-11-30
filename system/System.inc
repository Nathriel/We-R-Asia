<?php
class System {
	private $baseConfig;
	private $mapperCache;
	private $db;
	private $templateEngine;

	public function __construct(array $config) {
		ini_set('unserialize_callback_func', 'spl_autoload_call');
        spl_autoload_register(array($this, 'autoload'));
		
		//initialize stuff
		$this->baseConfig = $config;
		$this->mapperCache = array();
		$this->db = new System_Database_Database(include './'.$this->baseConfig['applicationPath'].'config/db.inc');
	}
	
	public function run() {
		//run it!
		$requestedPage = (isset($_SERVER['PATH_INFO'])?$_SERVER['PATH_INFO']:null);
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
	
	public function getMapper($name) {
		$mapperClassName = ucfirst($name).'_Mapper';
		if (!isset($this->mapperCache[$mapperClassName])) {
			if (is_file($mapperFile = './'.$this->baseConfig['applicationPath'].'models/'.ucfirst($name).'.inc')) {
				require_once($mapperFile);
				$this->mapperCache[$mapperClassName] = new $mapperClassName($this->db);
			} else {
				return false;
			}
		}
		return $this->mapperCache[$mapperClassName];
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
	
	public function getTemplateEngineInstance() {
		if ($this->templateEngine == null) {
			require_once './'.$this->baseConfig['libraryPath'].'/Twig/Autoloader.php';
			Twig_Autoloader::register();
			
			$loader = new Twig_Loader_Filesystem('./'.$this->baseConfig['applicationPath'].'views/');
			$this->templateEngine = new Twig_Environment($loader, array(
				'cache' => './'.$this->baseConfig['contentPath'].'cache/twig/',
			));			
		}
		return $this->templateEngine;
	}
}
?>