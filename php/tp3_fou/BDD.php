<?php
require_once("configBDD.inc.php");

class BDD
{
  private $PDO;

  public function __construct()
  {
    try {
      $this->PDO = new PDO(DB_TYPE.':host='.DB_HOST.';port='.DB_PORT.';dbname='.DB_NAME, DB_USER, DB_PASS);
      $this->PDO->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
      $this->PDO->exec("SET NAMES 'utf8'");
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  private function error(Exception $e)
  {
    echo 'Error: '.$e->getMessage().'<br>';
    echo 'N°: '.$e->getCode();
    exit();
  }

  public function getForms()
  {
    try {
      $query = $this->PDO->prepare("SELECT * FROM formulaire");
      $query->execute();
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res;
  }

  public function newForm($name, $description)
  {
    try {
      $query = $this->PDO->prepare("INSERT INTO formulaire (nom, description) values (?, ?)");
      $query->execute(array($name, $description));
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  public function removeForm($id)
  {
    try {
      $query = $this->PDO->prepare("DELETE FROM formulaire WHERE id_formulaire = ?");
      $query->execute(array($id));
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  public function getSujets($idForm)
  {
    try {
      $query = $this->PDO->prepare("SELECT * FROM view_sujet_nb_question WHERE id_formulaire = ?");
      $query->execute(array($idForm));
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res;
  }

  public function getQuestions($idForm)
  {
    try {
      $query = $this->PDO->prepare("SELECT * FROM view_question WHERE id_formulaire = ?");
      $query->execute(array($idForm));
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res;
  }

  private function newQuestion($idForm, $title)
  {
    try {
      $query = $this->PDO->prepare("INSERT INTO question (id_formulaire, intitule) values (?, ?)");
      $query->execute(array($idForm, $title));
    } catch (Exception $e) {
      $this->error($e);
    }

    return $this->PDO->lastInsertId();
  }

  private function removeQuestion($idQuestion)
  {
    try {
      $query = $this->PDO->prepare("DELETE FROM question WHERE id_question = ?");
      $query->execute(array($idQuestion));
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  public function newOpenQuestion($idForm, $title)
  {
    try {
      $idQuestion = newQuestion($idForm, $title);
      $query = $this->PDO->prepare("INSERT INTO question_ouverte (id_question_ouverte) values(?)");
      $query->execute(array($idQuestion));
    } catch (Exception $e) {
      $this->error($e);
    }
  }
}
?>
