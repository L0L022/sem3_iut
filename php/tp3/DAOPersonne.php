<?php

interface DAOPersonne
{
  private $conn;
  
  public function __construct(&$conn)
  {
    $this->conn = & $conn;
  }

  public function find(Personne &$p);
  public function update(Personne &$p)
  {
    if ($p->id == 0)
      insert($p);
    else
      update($p);
  }
  public function delete($id);

  private function insert(Personne &$p);
  private function update(Personne &$p);
}

 ?>
