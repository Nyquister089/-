CREATE TABLE IF NOT EXISTS `tripdb`.`soggiorno` (
  `IdSoggiorno` int NOT NULL AUTO_INCREMENT, 
  `CameraPrenotata` int NOT NULL,
  `Ospite` int unsigned NOT NULL,
  `ViaggioInQuestione` int not NULL, 
  `AlbergoInQuestione` int unsigned NOT NULL,
  `DataInizioSoggiorno` DATE NOT NULL, 
  `DataFineSoggiorno` DATE NOT NULL,
  PRIMARY KEY (`IdSoggiorno`),
  KEY `AlbergoInQuestione_idx` (`AlbergoInQuestione`),
  KEY `Ospite_idx` (`Ospite`),
  CONSTRAINT `FK_AlbergoInQuestione` FOREIGN KEY (`AlbergoInQuestione`) REFERENCES `camera` (`IdAlbergo`)on delete cascade,
  CONSTRAINT `FK_Camera` FOREIGN KEY (`CameraPrenotata`) REFERENCES `camera` (`NumeroCamera`)on delete cascade,
  CONSTRAINT `FK_Ospite` FOREIGN KEY (`Ospite`) REFERENCES `postoprenotato` (`NumeroDiPosto`) on delete cascade,
  CONSTRAINT `FK_Viaggio` FOREIGN KEY (`ViaggioInQuestione`) REFERENCES `viaggio` (`IdViaggio`) on delete cascade,
  CONSTRAINT `DataFineSoggiornoCannotBeLesserThanDataDiInizioSoggiorno` CHECK (`DataInizioSoggiorno` <= `DataFineSoggiorno`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
