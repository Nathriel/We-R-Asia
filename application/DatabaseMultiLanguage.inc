<?php
class DatabaseMultiLanguage extends System_MultiLanguage {
	protected function getCurrentLanguage() {
		echo 'it works!';
		return null;
	}
	
	protected function translate($string, $language) {
		return null;
	}
}
?>