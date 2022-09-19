CREATE TABLE IF NOT EXISTS `tripdb`.`utente` (
  `EmailUtente` varchar(45) NOT NULL,
  `Pswrd` varchar(8) NOT NULL,
  `TipoUtente` int unsigned NOT NULL,
  PRIMARY KEY (`EmailUtente`),
  CONSTRAINT `TipoUtenteNotvalid` CHECK (`TipoUtente` IN ('1','2','3','4','5') )
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`localita` (
  `NomeLocalita` varchar(45) NOT NULL,
  `Regione` varchar(45) NOT NULL,
  `Stato` varchar(45) NOT NULL,
  PRIMARY KEY (`NomeLocalita`,`Regione`),
  Index (`Regione`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`meta` (
  `IdMeta` int unsigned NOT NULL AUTO_INCREMENT,
  `LocalitaDiAppartenenza` varchar(45), 
  `RegioneDiAppartenenza` varchar(45), 
  `NomeMeta` varchar(45) NOT NULL,
  `TelefonoMeta` varchar(15) NOT NULL,
  `EmailMeta` varchar(45) NOT NULL,
  `FaxMeta` varchar(15) NOT NULL,
  `Indirizzo` varchar(45) NOT NULL,
  `TipologiaMeta` varchar(45) NOT NULL,
  `CategoriaAlbergo` varchar(45) DEFAULT NULL,
  `OrarioDiApertura` time DEFAULT NULL,
  PRIMARY KEY (`IdMeta`),
  KEY `LocalitaDiappartenenza_idx` (`LocalitadiAppartenenza`),
  CONSTRAINT `FK_LocalitaDiAppartenenza` FOREIGN KEY (`LocalitaDiAppartenenza`) REFERENCES `localita` (`NomeLocalita`) on delete set null,
  CONSTRAINT `FK_RegioneDiAppartenenza` FOREIGN KEY (`RegioneDiAppartenenza`) REFERENCES `localita` (`Regione`) on delete set null,
  CONSTRAINT `TipologiaMetaNotValid` CHECK (`TipologiaMeta` IN ('Bene','Albergo', 'bene', 'albergo') )
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`servizio` (
  `IdServizio` int unsigned NOT NULL AUTO_INCREMENT ,
  `NomeServizio` varchar(45) NOT NULL,
  `DescrizioneServizio` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdServizio`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`offre` (
  `ServizioOfferto` int unsigned NOT NULL,
  `AlbergoOfferente` int unsigned NOT NULL,
  PRIMARY KEY (`ServizioOfferto`,`AlbergoOfferente`),
  KEY `FK_IdServizio_idx` (`ServizioOfferto`),
  KEY `FK_IdAlbergo_idx` (`AlbergoOfferente`),
  CONSTRAINT `FK_IdAlbergo` FOREIGN KEY (`AlbergoOfferente`) REFERENCES `meta` (`IdMeta`)on delete cascade,
  CONSTRAINT `FK_IdServizio` FOREIGN KEY (`ServizioOfferto`) REFERENCES `servizio` (`IdServizio`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`camera` (
  `NumeroCamera` int unsigned NOT NULL,
  `IdAlbergo` int unsigned NOT NULL,
  `Tipologia` varchar(45) NOT NULL,
  `Costo` decimal(8,2) NOT NULL,
  PRIMARY KEY (`NumeroCamera`,`IdAlbergo`),
  KEY `FK_IdAlbergo_idx` (`IdAlbergo`),
  CONSTRAINT `FK_idAlbergoCamera` FOREIGN KEY (`IdAlbergo`) REFERENCES `meta` (`IdMeta`) on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`cliente` (
  `EmailCliente` varchar(45) NOT NULL,
  `NomeCliente` varchar(45) NOT NULL,
  `CognomeCliente` varchar(45) NOT NULL,
  `IndirizzoCliente` varchar(45) NOT NULL,
  `CodiceFiscale` varchar(45) NOT NULL,
  `DataDocumentazione` date NOT NULL,
  `RecapitoTelefonico` varchar(15) NOT NULL,
  `Fax` varchar(15) NOT NULL,
  PRIMARY KEY (`EmailCliente`),
  KEY `Fk_EmailCliente_idx` (`EmailCliente`), 
  CONSTRAINT `FK_EmailUtente` FOREIGN KEY (`EmailCliente`) REFERENCES `utente` (`EmailUtente`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;


CREATE TABLE IF NOT EXISTS `tripdb`.`modello` (
  `NomeModello` varchar(45) NOT NULL,
  `DatiTecnici` varchar(5000) NOT NULL,
  `CasaCostruttrice` varchar(45) NOT NULL,
  `NumeroPosti` int unsigned NOT NULL,
  `NumeroMeccaniciCompetenti` int unsigned default 0 NOT NULL , 
  PRIMARY KEY (`NomeModello`),
  CONSTRAINT `NumeroCompetenzeNotValid` CHECK  (`NumeroMeccaniciCompetenti`=  0 OR `NumeroMeccaniciCompetenti`>1)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`mezzo` (
  `Targa` varchar(10) NOT NULL,
  `ModelloMezzo` varchar(45) NOT NULL,
  `DataRevisioneMotorizzazione`DATE NOT NULL,
  `Autonomia` int unsigned NOT NULL,
  `ValoreContaKm` int unsigned NOT NULL,
  `Ingombri` varchar(45) NOT NULL,
  `DataImmatricolazione` date NOT NULL,
  PRIMARY KEY (`Targa`),
  KEY `FK_modello_idx` (`ModelloMezzo`),
  CONSTRAINT `FK_ModelloMezzo` FOREIGN KEY (`ModelloMezzo`) REFERENCES `modello` (`NomeModello`) on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`tour` (
  `DenominazioneTour` varchar(45) NOT NULL,
  `DescrizioneTour` varchar(5000) NOT NULL,
  `Minimopartecipanti` int unsigned NOT NULL,
  `CostoAssicurazioneMedica` decimal(8,2) unsigned not null,
  `CostoBagaglio` decimal(8,2) unsigned not null,
  `CostoGaranziaAnnullamento` decimal(8,2) unsigned not null,
  `Accompagnatrice`tinyint DEFAULT NULL,
  PRIMARY KEY (`DenominazioneTour`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci COMMENT='Programma di viaggio consultabile da clienti ed impiegati dell’azienda.';

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


CREATE TABLE IF NOT EXISTS `tripdb`.`prenotazione` (
  `NumeroDiPrenotazione` int unsigned NOT NULL AUTO_INCREMENT,
  `ViaggioAssociato` int unsigned NOT NULL,
  `ClientePrenotante` varchar(45) NOT NULL,
  `NumeroDiPostiPrenotati` int unsigned NOT NULL, 
  `DataDiPrenotazione` DATE NOT NULL,
  `DataDiConferma` DATE DEFAULT NULL,
  `DataSaldo` DATE DEFAULT NULL,
  PRIMARY KEY (`NumeroDiPrenotazione`),
  CONSTRAINT `ClientePrenotatne` FOREIGN KEY (`ClientePrenotante`) REFERENCES `cliente` (`EmailCliente`) on delete cascade,
  CONSTRAINT `viaggioAssociato` FOREIGN KEY (`ViaggioAssociato`) REFERENCES `viaggio` (`idviaggio`) on delete cascade,
  CONSTRAINT `DataDiConfermaCannotBeLesserThanDataDiPrenotazione` CHECK (`DataDiConferma` IS NULL OR `DataDiConferma` >= `DataDiPrenotazione`),
  CONSTRAINT `DataSaldoCannotBeLesserThanDataDiConferma` CHECK (`DataSaldo` IS NULL OR (`DataDiConferma` IS NOT NULL AND `DataSaldo` >= `DataDiConferma`))
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;


CREATE TABLE IF NOT EXISTS `tripdb`.`viaggio` (
  `IdViaggio` int unsigned NOT NULL AUTO_INCREMENT,
  `TourAssociato` varchar(45) not null,
  `Conducente` varchar(45),
  `Accompagnatrice` varchar(45) default null,
  `TargaMezzoImpiegato` varchar(10),
  `DataPartenzaViaggio` date NOT NULL,
  `DataRitornoViaggio` date NOT NULL, 
  `CostoDelViaggio` decimal(8,2) NOT NULL,
  `NumeroKm` int unsigned NOT NULL,
  `PostiDisponibili` int unsigned NOT NULL,
  `DataCancellazione` date DEFAULT NULL,
  PRIMARY KEY (`idviaggio`),
  KEY `FK_TourAssocciato_idx` (`TourAssociato`),
  KEY `FK_Conducente_idx` (`Conducente`),
  KEY `FK_Accompagnatrice_idx`(`Accompagnatrice`),
  KEY `FK_Mezzoimpiegato_idx` (`TargaMezzoImpiegato`),
  CONSTRAINT `FK_Accompagnatrice` FOREIGN KEY (`Accompagnatrice`) REFERENCES `dipendente` (`EmailDipendente`)on delete set null,
  CONSTRAINT `FK_Conducente` FOREIGN KEY (`Conducente`) REFERENCES `dipendente` (`EmailDipendente`)on delete set null,
  CONSTRAINT `FK_Mezzoimpiegato` FOREIGN KEY (`TargaMezzoImpiegato`) REFERENCES `mezzo` (`Targa`) on delete set null,
  CONSTRAINT `FK_TourAssocciato` FOREIGN KEY (`TourAssociato`) REFERENCES `tour` (`DenominazioneTour`) on delete cascade,
  CONSTRAINT `DataRitornoViaggioCannotBeLesserThanDataPartenzaViaggio` CHECK ((`DataRitornoViaggio` IS NULL) OR (`DataPartenzaViaggio` IS NULL AND `DataRitornoViaggio` IS NULL) OR (`DataRitornoViaggio` >= `DataPartenzaViaggio`))
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

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


CREATE TABLE IF NOT EXISTS `tripdb`.`soggiorno` (
  `IdSoggiorno` int unsigned NOT NULL AUTO_INCREMENT, 
  `CameraPrenotata` int unsigned NOT NULL,
  `Ospite` int unsigned NOT NULL,
  `PrenotazioneInQuestione` int unsigned not NULL, 
  `AlbergoInQuestione` int unsigned NOT NULL,
  `DataInizioSoggiorno` DATE NOT NULL, 
  `DataFineSoggiorno` DATE NOT NULL,
  PRIMARY KEY (`IdSoggiorno`),
  KEY `AlbergoInQuestione_idx` (`AlbergoInQuestione`),
  KEY `Ospite_idx` (`Ospite`),
  KEY `CameraPrenotata_idx`(`CameraPrenotata`),
  KEY `PrenotazioneInQuestione_idx` (`PrenotazioneInQuestione`),
  CONSTRAINT `FK_AlbergoInQuestione` FOREIGN KEY (`AlbergoInQuestione`) REFERENCES `camera` (`IdAlbergo`)on delete cascade,
  CONSTRAINT `FK_Camera` FOREIGN KEY (`CameraPrenotata`) REFERENCES `camera` (`NumeroCamera`)on delete cascade,
  CONSTRAINT `FK_Ospite` FOREIGN KEY (`Ospite`) REFERENCES `postoprenotato` (`NumeroDiPosto`) on delete cascade,
  CONSTRAINT `FK_Prenotazione` FOREIGN KEY (`PrenotazioneInQuestione`) REFERENCES `postoprenotato` (`PrenotazioneAssociata`) on delete cascade,
  CONSTRAINT `DataFineSoggiornoCannotBeLesserThanDataDiInizioSoggiorno` CHECK (`DataInizioSoggiorno` <= `DataFineSoggiorno`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`comfort` (
  `IdComfort` int unsigned NOT NULL AUTO_INCREMENT,
  `NomeComfort` varchar(45) NOT NULL,
  `DescrizioneComfort` varchar(1000) NOT NULL,
  PRIMARY KEY (`IdComfort`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`presenti` (
  `ComfortPresenti` int unsigned NOT NULL,
  `ModelloAssociato` varchar(45) NOT NULL,
  PRIMARY KEY (`ComfortPresenti`,`ModelloAssociato`),
  KEY `FK_Modello_associato_idx` (`ModelloAssociato`),
  CONSTRAINT `FK_Comfort` FOREIGN KEY (`ComfortPresenti`) REFERENCES `comfort` (`IdComfort`)on delete cascade,
  CONSTRAINT `FK_Modello_associato` FOREIGN KEY (`ModelloAssociato`) REFERENCES `modello` (`NomeModello`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;


CREATE TABLE IF NOT EXISTS `tripdb`.`revisione` (
  `IdRevisione` int unsigned NOT NULL AUTO_INCREMENT,
  `MezzoRevisionato` varchar(45),
  `AddettoAllaRevisione` varchar(45), 
  `DataInizio` date NOT NULL,
  `DataFine` date NOT NULL,
  `Chilometraggio` int unsigned NOT NULL,
  `ControlliEffettuati` varchar(5000) NOT NULL,
  `Motivazione` varchar(5000) NOT NULL,
  PRIMARY KEY (`IdRevisione`),
  KEY `FK_revisione_mezzo_idx` (`MezzoRevisionato`),
  KEY `Fk_revisione_dipendente_idx`(`AddettoAllaRevisione`),
  CONSTRAINT `FK_revisione_mezzo` FOREIGN KEY (`MezzoRevisionato`) REFERENCES `mezzo` (`Targa`) on delete set null,
  CONSTRAINT `FK_revisione_dipendente` FOREIGN KEY (`AddettoAllaRevisione`) REFERENCES `dipendente` (`EmailDipendente`)on delete set null,
  CONSTRAINT `DataFineCannotBeLesserThanDataInizio` CHECK (`DataFine` >= `DataInizio`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`ricambio` (
  `Codice` varchar(45) NOT NULL,
  `CostoUnitario` decimal(8,2) NOT NULL,
  `QuantitaDiRiordino` int unsigned NOT NULL,
  `Descrizione` varchar(5000) NOT NULL,
  `ScortaMinima` int unsigned NOT NULL,
  `QuantitaMagazzino` int unsigned NOT NULL,
  PRIMARY KEY (`Codice`),
  constraint `QuantitaMagazzino_notvalid` check (`QuantitaMagazzino`>=0)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`documentazionefotografica` (
  `idDocumentazioneFotografica` int unsigned NOT NULL AUTO_INCREMENT,
  `Immagine` blob DEFAULT NULL,
  `DescrizioneFoto` varchar(5000),
  PRIMARY KEY (`idDocumentazioneFotografica`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`tagliando` (
  `IdTagliando` int unsigned NOT NULL AUTO_INCREMENT,
  `TipologiaTagliando` varchar(45) NOT NULL,
  `ValiditaSuperate` varchar(5000) NOT NULL,
  PRIMARY KEY (`IdTagliando`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`rt` (
  `RevisioneRelativa` int unsigned NOT NULL,
  `TagliandoAssociato` int unsigned NOT NULL,
  PRIMARY KEY (`RevisioneRelativa`,`TagliandoAssociato`),
  KEY `rt_tagliando_idx` (`TagliandoAssociato`),
  KEY `rt_revisione` (`RevisioneRelativa`),
  CONSTRAINT `FK_rt_revisione` FOREIGN KEY (`RevisioneRelativa`) REFERENCES `revisione` (`IdRevisione`),
  CONSTRAINT `FK_rt_taglianto` FOREIGN KEY (`TagliandoAssociato`) REFERENCES `tagliando` (`IdTagliando`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;


CREATE TABLE IF NOT EXISTS `tripdb`.`fme` (
  `MetaRappresentata` int unsigned NOT NULL,
  `FotoMeta` int unsigned NOT NULL,
  PRIMARY KEY (`MetaRappresentata`,`FotoMeta`),
  KEY `FK_documentazioneFotografica_idx` (`FotoMeta`),
  CONSTRAINT `FK_documentazioneFotografica` FOREIGN KEY (`FotoMeta`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`)on delete cascade,
  CONSTRAINT `FK_Meta` FOREIGN KEY (`MetaRappresentata`) REFERENCES `meta` (`IdMeta`) on delete cascade
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`fmo` (
  `FotoModello` int unsigned NOT NULL,
  `ModelloRappresentato` varchar(45) NOT NULL,
  PRIMARY KEY (`FotoModello`,`ModelloRappresentato`),
  KEY `FK_Modello_idx` (`ModelloRappresentato`),
  CONSTRAINT `FK_Foto` FOREIGN KEY (`FotoModello`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`)on delete cascade,
  CONSTRAINT `FK_Modello` FOREIGN KEY (`ModelloRappresentato`) REFERENCES `modello` (`NomeModello`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;


CREATE TABLE IF NOT EXISTS `tripdb`.`mappa` (
  `IdMappa` int unsigned NOT NULL AUTO_INCREMENT,
  `Citta` varchar(45) NOT NULL,
  `RegioneInQuestione` varchar (45) NOT NULL,
  `Dettaglio` varchar(45) NOT NULL,
  `Zona` varchar(45) NOT NULL,
  `ImmagineMappa` blob DEFAULT NULL,
  PRIMARY KEY (`IdMappa`),
  KEY `Fk_RegioneInQuestione_idx` (`RegioneInQuestione`),
  KEY `Fk_Citta_idx` (`Citta`),
  CONSTRAINT `Fk_Città` FOREIGN KEY (`Citta`) REFERENCES `localita`(`NomeLocalita`) on delete cascade,
  CONSTRAINT `Fk_RegioneInQuestione`FOREIGN KEY(`RegioneInQuestione`) REFERENCES `localita` (`Regione`) on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`competenze` (
  `CompetenzeModello` varchar(45) NOT NULL,
  `MeccanicoCompetente` varchar(45) not null,
  PRIMARY KEY (`CompetenzeModello`, `MeccanicoCompetente`),
  KEY `CompetenzeModello_idx` (`CompetenzeModello`),
  KEY `MeccanicoCompetente_idx` (`MeccanicoCompetente`),
  CONSTRAINT `FK_CompetenzeModello` FOREIGN KEY (`CompetenzeModello`) REFERENCES `modello` (`NomeModello`)on delete cascade,
  CONSTRAINT `FK_MeccanicoCompetente` FOREIGN KEY (`MeccanicoCompetente`) REFERENCES `dipendente` (`EmailDipendente`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`sostituito` (
  `RevisioneAssociata` int unsigned NOT NULL,
  `CodiceRicambioSostituito` varchar(45) NOT NULL,
  `QuantitàSostituita` int unsigned default '1',
  PRIMARY KEY (`RevisioneAssociata`,`CodiceRicambioSostituito`),
  KEY `sostituito_ricambio_idx` (`CodiceRicambioSostituito`),
  KEY `sostituito_revisione_idx`(`RevisioneAssociata`),
  CONSTRAINT `FK_revisione` FOREIGN KEY (`RevisioneAssociata`) REFERENCES `revisione` (`IdRevisione`)on delete cascade,
  CONSTRAINT `FK_ricambio` FOREIGN KEY (`CodiceRicambioSostituito`) REFERENCES `ricambio` (`Codice`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;


CREATE TABLE IF NOT EXISTS `tripdb`.`visita` (
  `idvisita` int unsigned NOT NULL AUTO_INCREMENT,
  `ViaggioRelativo` int unsigned NOT NULL,
  `MetaVisitata` int unsigned,
  `DataArrivo` date NOT NULL,
  `OraArrivo` time NOT NULL,
  `DataPartenza` date NOT NULL,
  `OraPartenza` time NOT NULL,
  `Guida` tinyint DEFAULT NULL,
  `Supplemento` decimal(8,2) DEFAULT NULL,
  `Trattamento` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idvisita`),
  KEY `FK_ViaggioRelativo_idx` (`ViaggioRelativo`),
  KEY `FK_MetaVisitata_idx` (`MetaVisitata`),
  CONSTRAINT `FK_MetaVisitata` FOREIGN KEY (`MetaVisitata`) REFERENCES `meta` (`IdMeta`)on delete set null,
  CONSTRAINT `FK_ViaggioRelativo` FOREIGN KEY (`ViaggioRelativo`) REFERENCES `viaggio` (`IdViaggio`) on delete cascade,
  CONSTRAINT `DataArrivoCannotBeLesserThanDataPartenza` CHECK (`DataArrivo` >= `DataPartenza`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci COMMENT='    ';
