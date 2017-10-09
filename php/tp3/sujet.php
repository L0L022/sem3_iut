<?php
  require_once("BDD.php");

  if (isset($_POST['open'])) {
    $BDD = new BDD();

    $sujets = $BDD->getSujets($_POST['open']);
  } else {
    header('location: forms.php');
  }
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
  <title>Formulaires</title>
</head>
<body>
  <div class="w3-container w3-teal">
    <h2>Formulaires</h2>
  </div>
  <form class="w3-container" action="" method="post">
    <ul class="w3-ul w3-card-4">
    <?php
      foreach ($sujets as $sujet) {
        $id = $sujet['id_sujet'];
        $nb_question = $sujet['nb_question'];
          echo <<<EOS
          <li class="w3-bar">
            <div class="w3-bar-item">
              <span class="w3-large">Sujet n°$id</span><br>
              <span>Nombre de questions répondus : $nb_question</span>
            </div>
            <button type="submit" class="w3-bar-item w3-button w3-xlarge w3-right" name="remove" value="$id">
              <i class="fa fa-remove"></i>
            </button>
            <button type="submit" class="w3-bar-item w3-button w3-xlarge w3-right" name="edit" value="$id" formaction="edit_form.php">
              <i class="fa fa-edit"></i>
            </button>
          </li>
EOS;
      }
    ?>
  </ul>
</form>
</body>
</html>
</DOCTYPE>
