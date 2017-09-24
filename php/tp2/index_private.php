<?php
  session_start();

  if (!isset($_SESSION['login']))
    header('location: authent.php');

  if ($_POST['logout']) {
    session_unset();
    session_destroy();
    header('location: authent.php');
  }

  require_once("BDD.php");

  $BDD = new BDD();

  $infos = $BDD->getInfos($_SESSION['login']);
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
  <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
  <title>Page perso</title>
</head>
<body>
  <div class="w3-container w3-teal">
    <h2>Page perso</h2>
  </div>
  <table class="w3-table w3-striped w3-hoverable">
  	<tr class="w3-teal">
  		<td>Variable</td>
  		<td>Valeur</td>
  	</tr>
  	<?php
      foreach ($infos as $name => $value) {
          echo '<tr><td>'.$name.'</td><td>'.$value.'</td></tr>';
      }
  	?>
  </table>
  <form class="" action="" method="post">
    <input class="w3-btn w3-blue-grey" type="submit" name="logout" value="Déconnexion">
  </form>
</body>
</html>
</DOCTYPE>
