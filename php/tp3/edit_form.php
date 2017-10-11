<?php
  require_once("BDD.php");

  if (isset($_POST['edit'])) {
    $BDD = new BDD();

    if (isset($_POST['remove'])) {
      $BDD->removeQuestion($_POST['remove']);
    }

    $questions = $BDD->getQuestions($_POST['edit']);
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
  <title>Éditer le formulaire</title>
</head>
<body>
  <div class="w3-container w3-teal">
    <h2>Éditer le formulaire</h2>
  </div>
  <form class="w3-container" action="" method="post">
    <ul class="w3-ul w3-card-4">
    <?php
      $prevId = -1;
      foreach ($questions as $question) {
        $id = $question['id_question'];
        $buttons = <<<EOS
        <button type="submit" class="w3-bar-item w3-button w3-xlarge w3-right" name="remove" value="$id">
          <i class="fa fa-remove"></i>
        </button>
        <button type="submit" class="w3-bar-item w3-button w3-xlarge w3-right" name="edit" value="$id" formaction="edit_form.php">
          <i class="fa fa-edit"></i>
        </button>
EOS;
        if ($prevId !== $question['id_question'] && $prevId !== -1)
          echo $buttons.'</div></li>';
        if ($prevId !== $question['id_question'])
          echo '<li class="w3-bar"><div class="w3-bar-item"><label class="w3-text-teal"><b>'.$question['intitule'].'</b></label><br>';

        if ($question['type'] === 'unique') {
          echo '<p><input class="w3-radio" type="radio" name="'.$question['id_question'].'" value="'.$question['id_choix'].'"><label>'.$question['signification'].'</label></p>';
        } else if ($question['type'] === 'multiple') {
          echo '<p><input class="w3-check" type="checkbox" name="'.$question['id_question'].'" value="'.$question['id_choix'].'"><label>'.$question['signification'].'</label></p>';
        } else if ($question['type'] === 'ouverte') {
         echo '<p><input class="w3-input w3-border w3-light-grey" type="text"></p>';
        }

        $prevId = $question['id_question'];
      }
      if ($prevId !== -1)
        echo $buttons.'</div></li>';
    ?>
    </ul>
  </form>
</body>
</html>
</DOCTYPE>
