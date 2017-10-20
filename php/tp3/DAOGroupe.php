<?php

interface DAOGroupe
{
  public function insert(Groupe $g);
  public function delete($id);
  public function find(Groupe $g);
  public function update(Groupe $g);
}

 ?>
