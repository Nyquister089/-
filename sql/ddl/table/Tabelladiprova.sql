CREATE TABLE IF NOT EXISTS `tripdb`.`Prova` (
  `idprova` int unsigned NOT NULL AUTO_INCREMENT,
  `rif_modello` varchar(45) DEFAULT NULL,
  `rif_meta` int unsigned default null,
  PRIMARY KEY (`idprova`),
  Key `rif_modello_fk` (`rif_modello`),
  key `rif_meta_fk` (`rif_meta`),
  CONSTRAINT `rif_modello_fk` FOREIGN key (`rif_modello`) REFERENCES `modello` (`NomeModello`),
  CONSTRAINT `rif_meta_fk` FOREIGN key (`rif_meta`) REFERENCES `meta` (`IdMeta`)

) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;