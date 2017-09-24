<?php
  if (isset($_POST['submit'])) {

    $requiredVars = array("login", "name", "firstname", "email", "password", "password2");
    foreach ($requiredVars as $varName)
      if (!isset($_POST[$varName]))
        die('Error : '.$varName.' note defined !');

    if ($_POST["password"] === $_POST["password2"]) {
      if (filter_var($_POST["email"], FILTER_VALIDATE_EMAIL)) {
        require_once("BDD.php");

        $BDD = new BDD();

        if ($BDD->isUniqueLogin($_POST["login"])) {
          $BDD->newUser($_POST["login"], $_POST["name"], $_POST["firstname"], $_POST["email"], $_POST["password"], $_POST["phone"]);
          header('location: authent.php');
        } else {
          $error_message = "Le login est déjà utilisé.";
        }
      } else {
        $error_message = "L'addresse email est invalide.";
      }
    } else {
      $error_message = "Les mots de passes sont différents.";
    }
  }
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
  <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
  <title>Inscription</title>
</head>
<body>
  <div class="w3-container w3-teal">
    <h2>Inscription</h2>
  </div>
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
	<form class="w3-container" action="" method="post">
      <label class="w3-text-teal" for="login">Identifiant* : </label>
  	  <input class="w3-input w3-border w3-light-grey" type="text" name="login" id="login" value="" required>
      <br>
      <label class="w3-text-teal" for="name">Nom* : </label>
      <input class="w3-input w3-border w3-light-grey" type="text" name="name" id="name" value="" required>
      <br>
      <label class="w3-text-teal" for="firstname">Prénom* : </label>
      <input class="w3-input w3-border w3-light-grey" type="text" name="firstname" id="firstname" value="" required>
      <br>
      <label class="w3-text-teal" for="email">Courriel* : </label>
      <input class="w3-input w3-border w3-light-grey" type="email" name="email" id="email" value="" required>
      <br>
      <label class="w3-text-teal" for="password">Mot de passe* : </label>
      <input class="w3-input w3-border w3-light-grey" type="password" name="password" id="password" value="" required>
      <br>
      <label class="w3-text-teal" for="password2">Confirmation du mot de passe* : </label>
      <input class="w3-input w3-border w3-light-grey" type="password" name="password2" id="password2" value="" required>
      <br>
      <label class="w3-text-teal" for="phone">Numéro de téléphone : </label>
      <input class="w3-input w3-border w3-light-grey" type="tel" name="phone" id="phone" value="">
      <br>
      <i>* champs obligatoire</i>
      <br>
      <input class="w3-btn w3-blue-grey" type="submit" name="submit" value="S'inscrire">
      <input class="w3-btn w3-blue-grey" type="reset" name="" value="Effacer">
      <br>
	</form>
</body>
</html>
</DOCTYPE>
