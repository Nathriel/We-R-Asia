<?php
class DatabaseMultiLanguage extends System_MultiLanguage {
	protected function getCurrentLanguage() {
		if (isset($_SESSION['userId'])) {
			return $this->mapper('user')->find($_SESSION['userId'])->getLanguage();
		} else {
			return $this->mapper('language')->find(1);
		}
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