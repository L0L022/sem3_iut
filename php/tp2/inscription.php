<?php
  if (isset($_REQUEST['submit'])) {
    require_once("configBDD.inc.php");

    $requiredVars = array("login", "name", "firstname", "email", "password", "password2");
    foreach ($requiredVars as $varName)
      if (!isset($_REQUEST[$varName]))
        die('Error : '.$varName.' note defined !');

    if ($_REQUEST["password"] !== $_REQUEST["password2"])
      die('Error : passwords are differents !');

    if (!filter_var($_REQUEST["email"], FILTER_VALIDATE_EMAIL))
      die('Error : Invalid email : '.$_REQUEST["email"]);
  }
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
  <title>Inscription</title>
</head>
<body>
	<form class="" action="" method="post">
    <fieldset>
      <legend>Inscription</legend>
      <label for="login">Identifiant* : </label>
  	  <input type="text" name="login" id="login" value="" required>
      <br>
      <label for="name">Nom* : </label>
      <input type="text" name="name" id="name" value="">
      <br>
      <label for="firstname">Prénom* : </label>
      <input type="text" name="firstname" id="firstname" value="" required>
      <br>
      <label for="email">Courriel* : </label>
      <input type="email" name="email" id="email" value="" required>
      <br>
      <label for="password">Mot de passe* : </label>
      <input type="password" name="password" id="password" value="" required>
      <br>
      <label for="password2">Confirmation du mot de passe* : </label>
      <input type="password" name="password2" id="password2" value="" required>
      <br>
      <label for="phone">Numéro de téléphone : </label>
      <input type="text" name="phone" id="phone" value="">
      <br>
      <i>* champs obligatoire</i>
      <br>
      <input type="submit" name="submit" value="S'inscrire">
      <input type="reset" name="" value="Effacer">
      <br>
    </fieldset>
	</form>
</body>
</html>
</DOCTYPE>
