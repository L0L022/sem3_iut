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

  public function isUniqueLogin($login)
  {
    try {
      $query = $this->PDO->prepare("SELECT COUNT(*) = 0 AS \"IS_UNIQUE\" FROM T_UTILISATEUR_UTI WHERE UTI_LOGIN = ?");
      $query->execute(array($login));
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res[0]["IS_UNIQUE"] == 1;
  }

  public function newUser($login, $name, $firstname, $email, $password, $phone)
  {
    try {
      $query = $this->PDO->prepare("INSERT INTO T_UTILISATEUR_UTI values(?,sha1(?),?,?,?,?,default)");
      $query->execute(array($login, $password, $email, $phone, $name, $firstname));
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  public function validLogin($login, $password)
  {
    try {
      $query = $this->PDO->prepare("SELECT COUNT(*) > 0 AS \"IS_VALID\" FROM T_UTILISATEUR_UTI WHERE UTI_LOGIN = ? AND UTI_PWD = sha1(?)");
      $query->execute(array($login, $password));
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res[0]["IS_VALID"] == 1;
  }

  public function getInfos($login)
  {
    try {
      $query = $this->PDO->prepare("SELECT * FROM T_UTILISATEUR_UTI WHERE UTI_LOGIN = ?");
      $query->execute(array($login));
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res[0];
  }
}
?>
