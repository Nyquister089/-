CREATE TABLE IF NOT EXISTS `tripdb`.`tour` (
  `DenominazioneTour` varchar(45) NOT NULL,
  `DescrizioneTour` varchar(5000) NOT NULL,
  `Minimopartecipanti` int unsigned NOT NULL,
  `CostoAssicurazioneMedica` decimal(8,2) unsigned not null,
  `CostoBagaglio` decimal(8,2) unsigned not null,
  `CostoGaranziaAnnullamento` decimal(8,2) unsigned not null,
  `Accompagnatrice`tinyint DEFAULT NULL,
  PRIMARY KEY (`DenominazioneTour`),
  UNIQUE KEY `DenominazioneTour_UNIQUE` (`DenominazioneTour`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci COMMENT='Programma di viaggio consultabile da clienti ed impiegati dell’azienda.';