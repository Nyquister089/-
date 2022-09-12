CREATE TABLE IF NOT EXISTS `tripdb`.`postoprenotato` (
  `NumeroDiPosto` int unsigned NOT NULL,
  `PrenotazioneAssociata` int unsigned NOT NULL,
  `EtaPasseggero` int unsigned NOT NULL,
  `NomePasseggero` varchar(45) NOT NULL,
  `CognomePasseggero` varchar(45) NOT NULL,
  PRIMARY KEY (`NumeroDiPosto`,`PrenotazioneAssociata`),
  KEY `prenotazioneAssociata_idx` (`PrenotazioneAssociata`),
  CONSTRAINT `prenotazioneAssociata` FOREIGN KEY (`PrenotazioneAssociata`) REFERENCES `prenotazione` (`NumeroDiPrenotazione`)on delete cascade

) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
