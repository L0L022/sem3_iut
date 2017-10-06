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
  <title>Formulaires</title>
</head>
<body>
  <div class="w3-container w3-teal">
    <h2>Formulaires</h2>
  </div>
  <li class="w3-bar">
    <span onclick="this.parentElement.style.display='none'"
    class="w3-bar-item w3-button w3-xlarge w3-right">&times;</span>
    <?php
      foreach ($forms as $form) {
        $name = $form['name'];
        $description = $form['description'];
        $
          echo <<<EOS
          <div class="w3-bar-item">
            <span class="w3-large">$name</span><br>
            <span>Web Designer</span>
          </div>
EOS;
      }
    ?>
  </li>
</body>
</html>
</DOCTYPE>
