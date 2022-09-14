CREATE TABLE IF NOT EXISTS `tripdb`.`dipendente` (
  `EmailDipendente` varchar (45) NOT NULL,
  `TipologiaDipendente` varchar(45) NOT NULL,
  `TelefonoAziendale` varchar (15) NOT NULL,
  `NomeDipendente` varchar(45) NOT NULL,
  `CognomeDipendente` varchar(45) NOT NULL,
  PRIMARY KEY (`EmailDipendente`),
  CONSTRAINT `Fk_EmailDipendente` FOREIGN KEY (`EmailDipendente`) REFERENCES `utente` (`EmailUtente`) on delete cascade,
  CONSTRAINT `TipologiaDipendentiNotValid` CHECK (`TipologiaDipendente` IN ('Autista','Hostess','Meccanico','Manager','autista','hostess','meccanico','manager') )
 ) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;


