<?php
  require_once("BDD.php");

  $BDD = new BDD();
  $forms = $BDD->getForms();
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
      foreach ($forms as $form) {
        $id = $form['id_formulaire'];
        $name = $form['nom'];
        $description = $form['description'];
          echo <<<EOS
          <li class="w3-bar">
            <div class="w3-bar-item">
              <span class="w3-large">$name</span><br>
              <span>$description</span>
            </div>
            <input class="w3-bar-item w3-button w3-xlarge w3-right" type="submit" name="remove" value="×">
            <button type="submit" class="w3-bar-item w3-button w3-xlarge w3-right" name="edit">
              <i class="fa fa-edit"></i>
            </button>
            <button type="submit" class="w3-bar-item w3-button w3-xlarge w3-right" name="open" value="$id" formaction="question.php">
              <i class="fa fa-eye"></i>
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
