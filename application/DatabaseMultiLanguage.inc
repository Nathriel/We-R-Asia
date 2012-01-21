<?php
class DatabaseMultiLanguage extends System_MultiLanguage {
	protected function getCurrentLanguage() {
		if (isset($_SESSION['languageId'])) {
			return $this->mapper('language')->find($_SESSION['languageId']);
		} elseif (isset($_SESSION['userId'])) {
			$_SESSION['languageId'] = $this->mapper('user')->find($_SESSION['userId'])->getLanguageId();
			return $this->getCurrentLanguage(); // sorry for the weird code oO
		} else {
			return $this->mapper('language')->findByCode('nl');
		}
	}
	
	public function translate($string, $language) {
		$translatable = $this->mapper('translatable')->findBySentence($string);
		if ($translatable && $translation = $translatable->getTranslationForLanguage($language)) {
			return $translation->getTranslation();
		} else {
			return 'couldn\'t translate ['.$string.']';
		}
	}
}
?>