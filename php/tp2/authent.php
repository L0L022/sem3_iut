<?php
  if (isset($_POST['submit'])) {

    $requiredVars = array("login", "password");
    foreach ($requiredVars as $varName)
      if (!isset($_POST[$varName]))
        die('Error : '.$varName.' note defined !');

    require_once("BDD.php");

    $BDD = new BDD();

    if ($BDD->validLogin($_POST['login'], $_POST['password'])) {
      session_start();
      $_SESSION['login'] = $_POST['login'];

      header('location: index_private.php');
    } else {
      $error_message = "Échec de l'authentification.";
    }
  }
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
  <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
  <title>Authentification</title>
</head>
<body>
  <div class="w3-container w3-teal">
    <h2>Authentification</h2>
  </div>
	<form class="w3-container" action="" method="post">
      <label class="w3-text-teal" for="login">Identifiant : </label>
  	  <input class="w3-input w3-border w3-light-grey" type="text" name="login" id="login" value="" required>
      <br>
      <label class="w3-text-teal" for="password">Mot de passe : </label>
      <input class="w3-input w3-border w3-light-grey" type="password" name="password" id="password" value="" required>
      <?php
        if (isset($error_message))
          echo <<<EOS
          <div class="w3-panel w3-red w3-display-container">
            <span onclick="this.parentElement.style.display='none'"
              class="w3-button w3-red w3-large w3-display-topright">&times;</span>
              <p>$error_message</p>
          </div>
EOS;
      ?>
      <br>
      <input class="w3-btn w3-blue-grey" type="submit" name="submit" value="S'identifier">
      <a class="w3-btn w3-teal" href="inscription.php">S'inscrire</a>
	</form>
</body>
</html>
</DOCTYPE>
