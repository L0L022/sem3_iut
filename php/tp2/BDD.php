<?php
  require_once("configBDD.inc.php");

  function connectBDD() {
    return new PDO('mysql:host='.$settings["dbserver"].';dbname='.$settings["dbname"], $settings["dbusername"], $settings["dbpassword"]);
  }
?>
