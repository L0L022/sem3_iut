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
  PRIMARY KEY (id_question_ouverte),
  FOREIGN KEY (id_question_ouverte) REFERENCES question(id_question)
);

CREATE TABLE IF NOT EXISTS question_unique (
  id_question_unique int NOT NULL,
  PRIMARY KEY (id_question_unique),
  FOREIGN KEY (id_question_unique) REFERENCES question(id_question)
);

CREATE TABLE IF NOT EXISTS question_multiple (
  id_question_multiple int NOT NULL,
  PRIMARY KEY (id_question_multiple),
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
  PRIMARY KEY (id_choix_unique, id_question_unique),
  FOREIGN KEY (id_choix_unique) REFERENCES choix(id_choix),
  FOREIGN KEY (id_question_unique) REFERENCES question_unique(id_question_unique)
);

CREATE TABLE IF NOT EXISTS choix_multiple (
  id_choix_multiple int NOT NULL,
  id_question_multiple int NOT NULL,
  PRIMARY KEY (id_choix_multiple, id_question_multiple),
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
  PRIMARY KEY (id_sujet, id_choix_unique),
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
  PRIMARY KEY (id_sujet, id_question_ouverte),
  FOREIGN KEY (id_sujet) REFERENCES sujet(id_sujet),
  FOREIGN KEY (id_question_ouverte) REFERENCES question_ouverte(id_question_ouverte)
);

-- création d'un formulaire

INSERT INTO `formulaire` (`nom`, `description`) VALUES ('Premier formulaire', 'Description du premier formulaire');
INSERT INTO `formulaire` (`nom`, `description`) VALUES ('Deuxième formulaire', 'Description du deuxième formulaire');

INSERT INTO `question` (`id_formulaire`, `intitule`) VALUES ('1', 'Quel est votre genre ?');
INSERT INTO `question_unique` (`id_question_unique`) VALUES ('1');
INSERT INTO `choix` (`signification`) VALUES ('Homme');
INSERT INTO `choix` (`signification`) VALUES ('Femme');
INSERT INTO `choix` (`signification`) VALUES ('Autre');
INSERT INTO `choix_unique` (`id_choix_unique`, `id_question_unique`) VALUES ('1', '1');
INSERT INTO `choix_unique` (`id_choix_unique`, `id_question_unique`) VALUES ('2', '1');
INSERT INTO `choix_unique` (`id_choix_unique`, `id_question_unique`) VALUES ('3', '1');

INSERT INTO `question` (`id_formulaire`, `intitule`) VALUES ('2', 'Quel est votre genre ?');
INSERT INTO `question_unique` (`id_question_unique`) VALUES ('2');
INSERT INTO `choix` (`signification`) VALUES ('Homme');
INSERT INTO `choix` (`signification`) VALUES ('Femme');
INSERT INTO `choix` (`signification`) VALUES ('Autre');
INSERT INTO `choix_unique` (`id_choix_unique`, `id_question_unique`) VALUES ('4', '2');
INSERT INTO `choix_unique` (`id_choix_unique`, `id_question_unique`) VALUES ('5', '2');
INSERT INTO `choix_unique` (`id_choix_unique`, `id_question_unique`) VALUES ('6', '2');

INSERT INTO `question` (`id_formulaire`, `intitule`) VALUES ('1', 'Tu sais faire quoi ?');
INSERT INTO `question_multiple` (`id_question_multiple`) VALUES ('3');
INSERT INTO `choix` (`signification`) VALUES ('C++');
INSERT INTO `choix` (`signification`) VALUES ('PHP');
INSERT INTO `choix` (`signification`) VALUES ('Java');
INSERT INTO `choix_multiple` (`id_choix_multiple`, `id_question_multiple`) VALUES ('7', '3');
INSERT INTO `choix_multiple` (`id_choix_multiple`, `id_question_multiple`) VALUES ('8', '3');
INSERT INTO `choix_multiple` (`id_choix_multiple`, `id_question_multiple`) VALUES ('9', '3');

INSERT INTO `question` (`id_formulaire`, `intitule`) VALUES ('2', 'Choisi ce que tu préfères faire.');
INSERT INTO `question_multiple` (`id_question_multiple`) VALUES ('4');
INSERT INTO `choix` (`signification`) VALUES ('Jouer');
INSERT INTO `choix` (`signification`) VALUES ('Travailler');
INSERT INTO `choix` (`signification`) VALUES ('Rien');
INSERT INTO `choix_multiple` (`id_choix_multiple`, `id_question_multiple`) VALUES ('10', '4');
INSERT INTO `choix_multiple` (`id_choix_multiple`, `id_question_multiple`) VALUES ('11', '4');
INSERT INTO `choix_multiple` (`id_choix_multiple`, `id_question_multiple`) VALUES ('12', '4');

INSERT INTO `question` (`id_formulaire`, `intitule`) VALUES ('1', 'Tu penses quoi de l\'iut ?');
INSERT INTO `question_ouverte` (`id_question_ouverte`) VALUES ('5');

INSERT INTO `question` (`id_formulaire`, `intitule`) VALUES ('2', 'À quoi tu penses quand je dis : chat !');
INSERT INTO `question_ouverte` (`id_question_ouverte`) VALUES ('6');

-- replissage du formulaire

INSERT INTO `sujet` (`id_sujet`) VALUES (NULL);
INSERT INTO `reponse_unique` (`id_sujet`, `id_choix_unique`) VALUES ('1', '1');
INSERT INTO `reponse_multiple` (`id_sujet`, `id_choix_multiple`) VALUES ('1', '7');
INSERT INTO `reponse_multiple` (`id_sujet`, `id_choix_multiple`) VALUES ('1', '8');
INSERT INTO `reponse_ouverte` (`id_sujet`, `id_question_ouverte`, `mots`) VALUES ('1', '5', 'l\'iut c\'est vraiment trop bien');

INSERT INTO `sujet` (`id_sujet`) VALUES (NULL);
INSERT INTO `reponse_unique` (`id_sujet`, `id_choix_unique`) VALUES ('2', '2');
INSERT INTO `reponse_multiple` (`id_sujet`, `id_choix_multiple`) VALUES ('2', '7');
INSERT INTO `reponse_multiple` (`id_sujet`, `id_choix_multiple`) VALUES ('2', '9');
INSERT INTO `reponse_ouverte` (`id_sujet`, `id_question_ouverte`, `mots`) VALUES ('2', '5', 'bof.');

-- création des vues

CREATE VIEW view_question_unique AS
SELECT id_formulaire, id_question, intitule, id_choix, signification
FROM question
INNER JOIN question_unique ON question.id_question = question_unique.id_question_unique
INNER JOIN choix_unique ON question_unique.id_question_unique = choix_unique.id_question_unique
INNER JOIN choix ON choix_unique.id_choix_unique = choix.id_choix;

CREATE VIEW view_question_multiple AS
SELECT id_formulaire, id_question, intitule, id_choix, signification
FROM question
INNER JOIN question_multiple ON question.id_question = question_multiple.id_question_multiple
INNER JOIN choix_multiple ON question_multiple.id_question_multiple = choix_multiple.id_question_multiple
INNER JOIN choix ON choix_multiple.id_choix_multiple = choix.id_choix;

CREATE VIEW view_question_ouverte AS
SELECT id_formulaire, id_question, intitule
FROM question
INNER JOIN question_ouverte ON question.id_question = question_ouverte.id_question_ouverte;

CREATE VIEW view_question AS
SELECT *, 'unique' AS 'type'
FROM `view_question_unique`
UNION
SELECT *, 'multiple' AS 'type'
FROM `view_question_multiple`
UNION
SELECT *, NULL AS 'id_choix', NULL AS 'signification', 'ouverte' AS 'type'
FROM `view_question_ouverte`;

CREATE VIEW view_reponse_unique AS
SELECT id_formulaire, id_question, intitule, id_sujet, id_choix, signification
FROM `reponse_unique`
INNER JOIN `choix` ON reponse_unique.id_choix_unique = choix.id_choix
INNER JOIN `choix_unique` ON reponse_unique.id_choix_unique = choix_unique.id_choix_unique
INNER JOIN `question` ON choix_unique.id_question_unique = question.id_question;

CREATE VIEW view_reponse_multiple AS
SELECT id_formulaire, id_question, intitule, id_sujet, id_choix, signification, id_reponse_multiple
FROM `reponse_multiple`
INNER JOIN `choix` ON reponse_multiple.id_choix_multiple = choix.id_choix
INNER JOIN `choix_multiple` ON reponse_multiple.id_choix_multiple = choix_multiple.id_choix_multiple
INNER JOIN `question` ON choix_multiple.id_question_multiple = question.id_question;

CREATE VIEW view_reponse_ouverte AS
SELECT id_formulaire, id_question, intitule, id_sujet, mots
FROM `reponse_ouverte`
INNER JOIN `question` ON reponse_ouverte.id_question_ouverte = question.id_question;

CREATE VIEW view_reponse AS
SELECT id_formulaire, id_question, intitule, id_sujet, id_choix, signification, NULL AS 'id_reponse_multiple', NULL AS 'mots', 'unique' AS 'type'
FROM `view_reponse_unique`
UNION
SELECT id_formulaire, id_question, intitule, id_sujet, id_choix, signification, id_reponse_multiple, NULL AS 'mots', 'multiple' AS 'type'
FROM `view_reponse_multiple`
UNION
SELECT id_formulaire, id_question, intitule, id_sujet, NULL AS 'id_choix', NULL AS 'signification', NULL AS 'id_reponse_multiple', mots, 'ouverte' AS 'type'
FROM `view_reponse_ouverte`;
