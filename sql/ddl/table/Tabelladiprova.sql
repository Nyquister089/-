CREATE TABLE IF NOT EXISTS `tripdb`.`Prova` (
  `idprova` int unsigned default null,
  `rif_modello` varchar(45),
  `rif_meta` varchar(45),
  PRIMARY KEY (`rif_modello`, `rif_meta`),
  Key `rif_modello_fk` (`rif_modello`),
  key `rif_meta_fk` (`rif_meta`),
  CONSTRAINT `rif_modello_fk` FOREIGN key (`rif_modello`) REFERENCES `localita` (`NomeLocalita`),
   CONSTRAINT `rif_meta_fk` FOREIGN key (`rif_meta`) REFERENCES `localita` (`Regione`)

) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;