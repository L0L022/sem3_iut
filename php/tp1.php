<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">

</head>
<body>
  <h1>TP 1</h1>
<?php
	echo '<h1>Exercice 1</h1>';
    echo 'Ceci est une ligne créée uniquement en PHP.<br/>';
    echo 'Ceci est la 2 éme phrase créée avec PHP.<br/>';
    echo '<a href="google.fr">iut</a><br/>';

    echo '<h1>Exercice 2</h1>';
    $nom="Deuf";
    $prenom="John";
    $age=14;

    echo 'Nom : '.$nom.' Prénom : '.$prenom.' Age : '.$age.'</br>';
    echo "Nom : $nom Prénom : $prenom Age : $age<br/>";

    echo '<h1>Exercice 3</h1>';
    echo '<h1>Calcul sur les variables</h1>';
    $remise=0.80;
    $prix=150;
    $prixAvecRemise=$prix*(1-$remise);
    echo 'Remise : '.($remise*100).' Prix : '.$prix.' Prix avec remise : '.$prixAvecRemise.'.</br>';
    echo 'Types : <br/><ul>';
    echo '<li>Prix : '.gettype($prix).'</li>';
    echo '<li>Remise : '.gettype($prix).'</li>';
    echo '<li>Prix avec remise : '.gettype($prixAvecRemise).'</li>';
    echo '</ul>';

    echo '<h1>Exercice 4</h1>';

    function prix_reduit($prix, $remise)
    {
		return $prix*(1-$remise);
	}

    $prix_table=150;
    $remise_table=0.70;
    $prix_armoire=120;
    $remise_armoire=0.90;

    $prix_reduit_table=prix_reduit($prix_table, $remise_table);
    $prix_reduit_armoire=prix_reduit($prix_armoire, $remise_armoire);

    if ($prix_armoire > $prix_table) {
		echo 'L\'armoire est plus chère.';
	} else if ($prix_armoire < $prix_table) {
		echo 'La table est ple chère.';
	} else {
		echo 'Les deux ont le même prix.';
	}

	echo '<h1>Exercice 5</h1>';
	$nombre=10;

	for ($i = 0; $i < $nombre; $i += 1) {
		echo $i;
	}
	echo '<br/>';
	$i = 0;
	while ($i < $nombre) {
		echo $i;
		$i += 1;
	}
	echo '<br/>';

	echo '<h1>Exercice 6</h1>';
	$nombres = array(1, 10, 100, 1000, 10000000000);
	$dernier_nombre = $nombres[count($nombres) - 1];
	$resultat = 0;
	echo 'Nombres : ';
	foreach ($nombres as &$nombre) {
		echo $nombre;
		if ($nombre !== $dernier_nombre)
			echo ' + ';
		$resultat += $nombre;
	}
	echo ' = '.$resultat.'<br/>';
?>
<h1>Exercice 7</h1>
<h1>Mes livres:</h1>
<table>
	<tr>
		<td>Auteur</td>
		<td>Titre</td>
	</tr>
	<?php
	    $auteurs = array("Laurent", "Loïc", "Killan");
	    $livres = array("Je me prends la tête", "Je suis fatigué", "DES GAUFRES");

	    for ($i = 0; $i < min(count($auteurs), count($livres)); $i += 1) {
	        echo '<tr ';
	        if ($i % 2 === 0) {
	            echo 'style="background-color:powderblue;"';
	        }
	        echo '><td>'.$auteurs[$i].'</td><td>'.$livres[$i].'</td></tr>';
	    }

	    $bouquins = array(
	        "Game Of Thrones" => "Alexandre",
	        "Sense 8" => "Loïc",
	        "You Me Her" => "Loïc",
	        "Sherlock" => "Loïc",
	        "Code Geass" => "Laurent",
	        "Murder" => "Killian",
	        "Death Note" => "Killian"
	    );

	    foreach ($bouquins as $titre => $auteur) {
	        echo '<tr><td>'.$auteur.'</td><td>'.$titre.'</td></tr>';
	    }
	?>

</table>
</body>
</html>
</DOCTYPE>
