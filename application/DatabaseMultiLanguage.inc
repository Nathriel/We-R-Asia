<?php
class DatabaseMultiLanguage extends System_MultiLanguage {
	protected function getCurrentLanguage() {
		if (isset($_SESSION['userId'])) {
			return $this->mapper('user')->find($_SESSION['userId'])->getLanguage();
		} else {
			return $this->mapper('language')->findByCode('nl');
		}
	}
	
	protected function translate($string, $language) {
		$translatable = $this->mapper('translatable')->findBySentence($string);
		if ($translatable && $translation = $translatable->getTranslationForLanguage($language)) {
			return $translation->getTranslation();
		} else {
			return 'couldn\'t translate ['.$string.']';
		}
	}
}
?>