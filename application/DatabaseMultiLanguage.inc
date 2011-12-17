<?php
class DatabaseMultiLanguage extends System_MultiLanguage {
	protected function getCurrentLanguage() {
		return 'nl';
	}
	
	protected function translate($string, $language) {
		$temporaryTranslateArray = array(
			'hello' => array(
				'nl' => 'Hallo %1$s!',
				'en' => 'Hello %1$s',
			),
		);
		return $temporaryTranslateArray[$string][$language];
	}
}
?>