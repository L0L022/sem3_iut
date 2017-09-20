<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">

</head>
<body>
<h1>Liste des fichiers de tp :</h1>
<table>
	<?php
		$files = scandir('.');
    foreach ($files as &$file) {
			if ($file != '.' and $file != '..')
      	echo '<tr><td><a href='.$file.' >'.$file.'</td></tr>';
    }
	?>
</table>
</body>
</html>
</DOCTYPE>
