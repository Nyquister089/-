CREATE TABLE IF NOT EXISTS `tripdb`.`mappa` (
  `IdMappa` int NOT NULL AUTO_INCREMENT,
  `Citta` varchar(45) NOT NULL,
  `RegioneInQuestione` varchar (45) NOT NULL,
  `Dettaglio` varchar(45) NOT NULL,
  `Zona` varchar(45) NOT NULL,
  `ImmagineMappa` blob DEFAULT NULL,
  PRIMARY KEY (`IdMappa`),
  UNIQUE KEY `IdMappa_UNIQUE` (`IdMappa`),
  KEY `Fk_RegioneInQuestione_idx` (`RegioneInQuestione`),
  KEY `Fk_Citta_idx` (`Citta`),
  CONSTRAINT `Fk_Città` FOREIGN KEY (`Citta`) REFERENCES `localita`(`NomeLocalita`) on delete cascade,
  CONSTRAINT `Fk_RegioneInQuestione`FOREIGN KEY(`RegioneInQuestione`) REFERENCES `localita` (`Regione`) on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
