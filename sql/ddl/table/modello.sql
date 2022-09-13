CREATE TABLE IF NOT EXISTS `tripdb`.`modello` (
  `NomeModello` varchar(45) NOT NULL,
  `DatiTecnici` varchar(5000) NOT NULL,
  `CasaCostruttrice` varchar(45) NOT NULL,
  `NumeroPosti` int unsigned NOT NULL,
  `NumeroMeccaniciCompetenti` int unsigned default 0 NOT NULL , 
  PRIMARY KEY (`NomeModello`),
  CONSTRAINT `NumeroCompetenzeNotValid` CHECK  (`NumeroMeccaniciCompetenti`=  0 OR `NumeroMeccaniciCompetenti`>1)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
