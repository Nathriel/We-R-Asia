<?php
class System {
	private $baseConfig;
	private $applicationConfig;
	private $mapperCache;
	private $db;
	private $templateEngine;
	private $multiLanguage;

	/**
	 * @param $config array an array with the configuration of the System, only the info it needs to even run, the rest should be configured in the application itself
	 */
	public function __construct(array $config) {
		ini_set('unserialize_callback_func', 'spl_autoload_call');
        spl_autoload_register(array($this, 'autoload'));
		
		//initialize stuff
		$this->baseConfig = $config;
		$this->mapperCache = array();
		$this->db = new System_Database_Database(include './'.$this->baseConfig['applicationPath'].'config/db.inc');
		$this->applicationConfig = include './'.$this->baseConfig['applicationPath'].'config/config.inc';
	}
	
	/**
	 * This runs the page, easy as that
	 */
	public function run() {
		//run it!
		$requestedPage = (isset($_SERVER['PATH_INFO'])?$_SERVER['PATH_INFO']:null);
		$pathInfo = explode('/', $requestedPage);
		array_shift($pathInfo);
		
		if (isset($pathInfo[0])) {
			$controllerName = $pathInfo[0];
		} else {
			$controllerName = $this->applicationConfig['homeController'];
		}
		if (is_file($controllerFile = './'.$this->baseConfig['applicationPath'].'controllers/'.ucfirst($controllerName).'.inc')) {
			if (isset($pathInfo[1])) {
				$function = $pathInfo[1];
			} else {
				$function = 'index';
			}
			require($controllerFile);
			
			$controller = new $controllerName($this);
			if (method_exists($controller, $function)) {
				try {
					$controller->$function();
				} catch (Exception $e) {
					echo '<pre>';
					var_dump($e);
					header('HTTP/1.0 500 Internal Server Error');
				}
			} else {
				header('HTTP/1.0 404 Not Found');
				$controller->notFound();
			}			
		} else {
			header('HTTP/1.0 404 Not Found');
		}
	}
	
	/**
	 * This gives you a mapper class, when called 2 times on different places, it will still return the same instance of the mapper.
	 * @param $name string the name of the mapper you want to get(excluding the _Mapper part)
	 */
	public function getMapper($name) {
		$mapperClassName = ucfirst($name).'_Mapper';
		if (!isset($this->mapperCache[$mapperClassName])) {
			if (is_file($mapperFile = './'.$this->baseConfig['applicationPath'].'models/'.ucfirst($name).'.inc')) {
				require_once($mapperFile);
				$this->mapperCache[$mapperClassName] = new $mapperClassName($this->db, $this);
			} else {
				return false;
			}
		}
		return $this->mapperCache[$mapperClassName];
	}
	
	/**
	 * Should only be used to autoload the system classes.
	 */
	private function autoload($class)
    {
        if (0 !== strpos($class, 'System_')) {
            return;
        }

        if (is_file($file = dirname(__FILE__).'/../'.str_replace(array('_', "\0"), array('/', ''), $class).'.inc')) {
            require $file;
        }
    }
	
	/**
	 * Gives you an instance of the template engine
	 * TODO: Make the template engine you want to use configurable.
	 */
	public function getTemplateEngineInstance() {
		if ($this->templateEngine == null) {
			$tplDir = './'.$this->baseConfig['applicationPath'].'views';
			
			require_once './'.$this->baseConfig['libraryPath'].'/Twig/Autoloader.php';
			Twig_Autoloader::register();
			
			$loader = new Twig_Loader_Filesystem($tplDir);
			$this->templateEngine = new Twig_Environment($loader, array(
				'cache' => './'.$this->baseConfig['contentPath'].'cache/twig/',
			));	
			$this->templateEngine->addExtension(new System_Twig_SystemTwigExtension($this));
			
			foreach (new RecursiveIteratorIterator(new RecursiveDirectoryIterator($tplDir), RecursiveIteratorIterator::LEAVES_ONLY) as $file)
			{
				// force compilation
				$this->templateEngine->loadTemplate(str_replace($tplDir.'\\', '', $file));
			}
		}
		return $this->templateEngine;
	}
	
	public function getMultiLanguage() {
		if ($this->multiLanguage == null) {
			$className = $this->applicationConfig['multiLanguage'];
			require_once './'.$this->baseConfig['applicationPath'].$className.'.inc';
			$this->multiLanguage = new $className($this);
		}
		return $this->multiLanguage;
	}
}
?>