<?php
session_start();
class Logout extends System_Controller {	
	public function index() {
	   session_unset();
       session_destroy();
       header("Location: ./");
	}
 }