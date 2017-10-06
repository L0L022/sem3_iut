CREATE TABLE IF NOT EXISTS formulaire (
  id_formulaire int NOT NULL AUTO_INCREMENT,
  nom  varchar(255) NOT NULL DEFAULT "",
  description varchar(255) NOT NULL DEFAULT "",
  PRIMARY KEY (id_formulaire)
);

CREATE TABLE IF NOT EXISTS question (
  id_question int NOT NULL AUTO_INCREMENT,
  id_formulaire int NOT NULL,
  intitule varchar(255) NOT NULL DEFAULT "",
  PRIMARY KEY (id_question),
  FOREIGN KEY (id_formulaire) REFERENCES formulaire(id_formulaire)
);

CREATE TABLE IF NOT EXISTS question_ouverte (
  id_question_ouverte int NOT NULL,
  FOREIGN KEY (id_question_ouverte) REFERENCES question(id_question)
);

CREATE TABLE IF NOT EXISTS question_unique (
  id_question_unique int NOT NULL,
  FOREIGN KEY (id_question_unique) REFERENCES question(id_question)
);

CREATE TABLE IF NOT EXISTS question_multiple (
  id_question_multiple int NOT NULL,
  FOREIGN KEY (id_question_multiple) REFERENCES question(id_question)
);

CREATE TABLE IF NOT EXISTS choix (
  id_choix int NOT NULL AUTO_INCREMENT,
  signification varchar(255) NOT NULL DEFAULT "",
  PRIMARY KEY (id_choix)
);

CREATE TABLE IF NOT EXISTS choix_unique (
  id_choix_unique int NOT NULL,
  id_question_unique int NOT NULL,
  FOREIGN KEY (id_choix_unique) REFERENCES choix(id_choix),
  FOREIGN KEY (id_question_unique) REFERENCES question_unique(id_question_unique)
);

CREATE TABLE IF NOT EXISTS choix_multiple (
  id_choix_multiple int NOT NULL,
  id_question_multiple int NOT NULL,
  FOREIGN KEY (id_choix_multiple) REFERENCES choix(id_choix),
  FOREIGN KEY (id_question_multiple) REFERENCES question_multiple(id_question_multiple)
);

CREATE TABLE IF NOT EXISTS sujet (
  id_sujet int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id_sujet)
);

CREATE TABLE IF NOT EXISTS reponse_unique (
  id_sujet int NOT NULL,
  id_choix_unique int NOT NULL,
  FOREIGN KEY (id_sujet) REFERENCES sujet(id_sujet),
  FOREIGN KEY (id_choix_unique) REFERENCES choix_unique(id_choix_unique)
);

CREATE TABLE IF NOT EXISTS reponse_multiple (
  id_reponse_multiple int NOT NULL AUTO_INCREMENT,
  id_sujet int NOT NULL,
  id_choix_multiple int NOT NULL,
  PRIMARY KEY (id_reponse_multiple),
  FOREIGN KEY (id_sujet) REFERENCES sujet(id_sujet),
  FOREIGN KEY (id_choix_multiple) REFERENCES choix_multiple(id_choix_multiple)
);

CREATE TABLE IF NOT EXISTS reponse_ouverte (
  id_sujet int NOT NULL,
  id_question_ouverte int NOT NULL,
  mots varchar(255) NOT NULL DEFAULT "",
  FOREIGN KEY (id_sujet) REFERENCES sujet(id_sujet),
  FOREIGN KEY (id_question_ouverte) REFERENCES question_ouverte(id_question_ouverte)
);

/* faire une vue
SELECT *
FROM question
LEFT JOIN question_ouverte ON question.id_question = question_ouverte.id_question_ouverte
UNION
SELECT *
FROM question
LEFT JOIN question_unique ON question.id_question = question_unique.id_question_unique
UNION
SELECT *
FROM question
LEFT JOIN question_multiple ON question.id_question = question_multiple.id_question_multiple*/
