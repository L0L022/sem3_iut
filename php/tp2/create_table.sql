CREATE TABLE IF NOT EXISTS `T_UTILISATEUR_UTI` (
  UTI_LOGIN varchar(255)  PRIMARY KEY ,
  UTI_PWD  varchar(255) NOT NULL,
  UTI_MAIL varchar(255) NOT NULL,
  UTI_TEL varchar(20) default NULL,
  UTI_NOM varchar(255) NOT NULL,
  UTI_PRENOM varchar(255) NOT NULL,
  UTI_ADMIN boolean NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;