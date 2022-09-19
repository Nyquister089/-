DROP DATABASE IF EXISTS tripdb; 
CREATE DATABASE IF NOT EXISTS tripdb CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci; 
drop user if exists 'Login'@'localhost'; 
drop user if exists 'Autista'@'localhost'; 
drop user if exists 'Cliente'@'localhost'; 
drop user if exists 'Hostess'@'localhost'; 
drop user if exists 'Manager'@'localhost'; 

create user if not exists 'Login'@'localhost' identified by 'lgn'; 
grant usage on tripdb.* to 'Login'@'localhost'; 

create user if not exists 'Autista'@'localhost' identified by 'drvr'; 
grant usage on tripdb.* to 'Autista'@'localhost'; 

create user  if not exists 'Cliente'@'localhost' identified by 'cstmr'; 
grant usage on tripdb.* to 'Cliente'@'localhost'; 

create user  if not exists 'Hostess'@'localhost' identified by 'hstss'; 
grant usage on tripdb.* to 'Hostess'@'localhost'; 

create user  if not exists 'Meccanico'@'localhost' identified by 'mchn'; 
grant usage on tripdb.* to 'Meccanico'@'localhost'; 

create user  if not exists'Manager'@'localhost' identified by 'mngr'; 
grant usage on tripdb.* to 'Manager'@'localhost'; CREATE TABLE IF NOT EXISTS `tripdb`.`utente` (
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
USE `tripdb`; 
create procedure if not exists `tripdb`.`login`(
	IN usrn VARCHAR(45), 
    IN pass VARCHAR(8),
    OUT tip INT
)
BEGIN
    SET tip = -1;

	SELECT u.TipoUtente
    INTO tip
    FROM utente as u
    WHERE u.EmailUtente = usrn AND u.Pswrd = pass;
END

create procedure if not exists `tripdb`.`delete_bus`(
    in trg varchar (10)
)
begin
delete 
from mezzo
where Targa = trg;  
end
create procedure if not exists `tripdb`.`delete_certify`(
    in idt int
)
begin
delete
from tagliando
where IdTagliando = idt; 
end

create procedure if not exists `tripdb`.`delete_comfort`(
    in idc int
)
begin
delete 
from comfort
where  IdComfort = idc; 
end

create procedure if not exists `tripdb`.`delete_costumer`(
    in mlc varchar(45)
)
begin
delete 
from cliente
where EmailCliente= mlc;  
end

create procedure if not exists `tripdb`.`delete_destination`(
    in idm int
)
begin
delete
from meta 
where IdMeta = idm;
end

create procedure if not exists `tripdb`.`delete_employee`(
    in mdp varchar (45)
)
begin 
delete 
from dipendente
where EmailDipendente = mdp;   
end

create procedure if not exists `tripdb`.`delete_fme`(
    in ftm int, 
    in mtr int
)
begin
delete 
from fme
where FotoMeta= ftm and MetaRappresentata =mtr;  
end

create procedure if not exists `tripdb`.`delete_fmo`(
    in ftm int,
    in mdr varchar (45)
)
begin
delete 
from fmo
where FotoModello = ftm and ModelloRappresentato =mdr;  
end

create procedure if not exists `tripdb`.`delete_location`(
    in nm varchar (45),
    in rgn varchar (45)
)
begin
delete 
from localita
where NomeLocalita = nm and Regione =rgn; 
end

create procedure if not exists `tripdb`.`delete_map`(
    in idm int
)
begin
delete 
from mappa
where IdMappa = idm ;  
end

create procedure if not exists `tripdb`.`delete_model`(
    in nmd varchar (45)
)
begin
delete
from modello
where NomeModello = nmd; 
end 
create procedure if not exists `tripdb`.`delete_ofr`(
    in htl int,
    in srv int
)
begin 
delete 
from offre
where AlbergoOfferente = htl and ServizioOfferto = srv;  
endcreate procedure if not exists `tripdb`.`delete_picture`(
    in idf int
)
begin
delete 
from documentazionefotografica
where idDocumentazioneFotografica = idf ;  
end

create procedure if not exists `tripdb`.`delete_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
delete
from presenti
where ModelloAssociato = mdl and ComfortPresenti =cmf; 
end

create procedure if not exists `tripdb`.`delete_reservation`(
    in nmp int
)
begin
delete 
from prenotazione
where NumeroDiPrenotazione = nmp;  
end

create procedure if not exists `tripdb`.`delete_review`(
    in idr int
)
begin
delete 
from revisione
where IdRevisione = idr;  
end

create procedure if not exists `tripdb`.`delete_room`(
    in nmc int,
    in htl int
)
begin
delete 
from camera
where NumeroCamera = nmc and IdAlbergo = htl; 
end

create procedure if not exists `tripdb`.`delete_rt`(
    in rvs int,
    in tgl int
)
begin
delete
from rt
where TagliandoAssociato = rvs and RevisioneRelativa = tgl; 
end

create procedure if not exists `tripdb`.`delete_seat`(
    in prn int, 
    in nmp int
)
begin
delete 
from postoprenotato
where PrenotazioneAssociata = prn and NumeroDiPosto = nmp;  
end

create procedure if not exists `tripdb`.`delete_service`(
    in ids int
)
begin
delete 
from servizio
where  IdServizio = ids; 
end

create procedure if not exists `tripdb`.`delete_skills`(
    in mcc varchar (45), 
    in cmp varchar (45)
)
begin
delete 
from competenze
where MeccanicoCompetente = mcc and CompetenzeModello = cmp; 
end

create procedure if not exists `tripdb`.`delete_sostitution` (
in cdc varchar(45), 
in rvs int
)
begin
delete 
from sostituito
where CodiceRicambioSostituito = cdc and RevisioneAssociata = rvs; 
end

create procedure if not exists `tripdb`.`delete_sparepart`(
    in cdc varchar(45)
)
begin
delete 
from ricambio
where Codice = cdc;  
end

create procedure if not exists `tripdb`.`delete_stay`(
    in ids int
    
)
begin
delete 
from soggiorno
where IdSoggiorno = ids; 
end

create procedure if not exists `tripdb`.`delete_tour`(
    in dnm varchar(45)
)
begin
delete 
from tour
where DenominazioneTour = dnm;  
end

create procedure if not exists `tripdb`.`delete_trip`(
    in idv int
)
begin
delete 
from viaggio
where idviaggio =idv; 
end

create procedure if not exists `tripdb`.`delete_user`(
    in usr varchar(45)
)
begin
delete 
from utente
where EmailUtente = usr;  
end

create procedure if not exists `tripdb`.`delete_visit`(
    in idv int
)
begin
delete
from visita 
where idvisita = idv; 
end

create procedure if not exists `tripdb`.`insert_bus`(
    in trg varchar (45),
    in mdm varchar (45),
    in ngb varchar (45),
    in tnm int,
    in ckm int, 
    in dtr date,
    in dtm date
)

INSERT INTO mezzo(
   Targa  ,
   ModelloMezzo ,
   DataRevisioneMotorizzazione ,
   Autonomia ,
   ValoreContaKm ,
   Ingombri ,
   DataImmatricolazione ) 
VALUES(
    trg,
    mdm,
    dtr,
    tnm,
    ckm,
    ngb,
    dtm);
  end
    
    
create procedure if not exists `tripdb`.`insert_certify`(
    in tpl varchar (45),
    in vld varchar (5000)
)
begin
INSERT INTO tagliando ( 
    TipologiaTagliando ,  
    ValiditaSuperate )
VALUES(
    tpl,
    vld);
end

create procedure if not exists `tripdb`.`insert_comfort`(
    in nmc varchar (45),
    in dsc varchar (45)
)
begin
INSERT INTO comfort  ( 
    NomeComfort ,  
    DescrizioneComfort ) 
VALUES (
    nmc,
    dsc
);
end


create procedure if not exists `tripdb`.`insert_costumer`(
in eml varchar(45), 
in nom varchar(45),
in cog varchar(45),
in ind varchar(45), 
in cod varchar(45), 
in dat date, 
in rec varchar(45),
in fax varchar(45)
)
BEGIN
insert into cliente 
			(EmailCliente, 
             NomeCliente, 
             CognomeCLiente, 
             IndirizzoCliente, 
             CodiceFiscale, 
             DataDocumentazione, 
             RecapitoTelefonico, 
             Fax)
values
			(eml, 
             nom, 
             cog,
             ind, 
             cod, 
             dat, 
             rec,
             fax); 
END

create procedure if not exists  `tripdb`.`insert_costumer_user`(
    in eml varchar(45),
    in nom varchar(45),
    in cog varchar(45),
    in ind varchar(45), 
    in cod varchar(45), 
    in dat date, 
    in rec varchar(45),
    in fax varchar(45),
    in psw varchar(8)
)
begin

declare count_user int default 0; 
declare count_costumer int default 0; 

declare exit handler for sqlexception
	begin
    rollback;
	  resignal; 
  end;
set transaction isolation level repeatable read;
start transaction;

INSERT INTO utente 
( EmailUtente ,
   Pswrd ,
   TipoUtente )
 VALUES 
 (eml,
  psw, 
  '2');

insert into cliente 
			(EmailCliente, 
             NomeCliente, 
             CognomeCLiente, 
             IndirizzoCliente, 
             CodiceFiscale, 
             DataDocumentazione, 
             RecapitoTelefonico, 
             Fax)
values
			(eml, 
             nom, 
             cog,
             ind, 
             cod, 
             dat, 
             rec,
             fax); 

select COUNT(1) 
into count_user
from utente
where EmailUtente = eml;

select COUNT(1) 
into count_costumer
from cliente
where EmailCliente = eml;

if(count_costumer <> 1 OR count_user <> 1) 
then signal sqlstate '45001' 
set message_text = "Errore nell inserimento delle competenze";
end if;
commit;
end

create procedure if not exists `tripdb`.`insert_destination`(
    in lcl varchar(45), 
    in rgn varchar(45),
    in nmm varchar(45),
    in tlf varchar(15), 
    in mlm varchar(45),
    in fxm varchar(15),
    in ndr varchar(45),
    in tpl varchar(45),
    in ctg varchar(45),
    in opn time
)
begin
INSERT INTO meta(  
     LocalitaDiAppartenenza ,
     RegioneDiAppartenenza, 
     NomeMeta , 
     TelefonoMeta , 
     EmailMeta ,
     FaxMeta , 
     Indirizzo , 
     TipologiaMeta , 
     CategoriaAlbergo , 
     OrarioDiApertura ) 
    VALUES (
     lcl,
     rgn,
     nmm,
     tlf, 
     mlm,
     fxm,
     ndr,
     tpl,
     ctg,
     opn);
     end
 
create procedure if not exists `tripdb`.`insert_employee`(
 in dpn varchar(45),
 in tlf varchar(15),
 in nmd varchar(45),
 in cgm varchar(45),
 in mlp varchar(45)
)
begin
INSERT INTO dipendente ( 
     TipologiaDipendente , 
     TelefonoAziendale ,
      NomeDipendente , 
      CognomeDipendente,
      EmailDipendente) 
     VALUES ( 
        dpn,
        tlf,
        nmd,
        cgm,
        mlp);
end

create procedure if not exists `tripdb`.`insert_fme`(
    in mtr int, 
    in ftm int
)
begin

INSERT INTO  fme ( 
    MetaRappresentata, 
    FotoMeta )
VALUES(
    mtr,
    ftm);
end

create procedure if not exists `tripdb`.`insert_fmo`(
    in fmd int, 
    in mdl varchar(45)
)
begin

INSERT INTO fmo(
    FotoModello,
    ModelloRappresentato)
VALUES(
    fmd,
    mdl);
end

create procedure if not exists `tripdb`.`insert_location`(
    in nml varchar (45), 
    in rgn varchar (45),
    in stt varchar (45)
)
begin
INSERT INTO localita(  
    NomeLocalita , 
    Regione ,
    Stato ) 
 VALUES (
    nml, 
    rgn, 
    stt
 );
 end
 
create procedure if not exists `tripdb`.`insert_map`(
    in ctt varchar(45), 
    in rgn varchar(45),
    in dtg varchar(45),
    in zna varchar(45), 
    in mgn blob
)
begin
INSERT INTO mappa  
(
   Citta ,
   RegioneInQuestione,
   Dettaglio ,
   Zona,
   ImmagineMappa)
   VALUES (
    ctt,
    rgn, 
    dtg,
    zna,
    mgn);
end

create procedure if not exists `tripdb`.`insert_model`(
    in nmd varchar(45),
    in dtt varchar(5000),
    in csc varchar(45),
    in nmp int,
    in mch1 varchar (45),
    in mch2 varchar(45)
)
begin

declare count_mech_per_model int default 0;
declare exit handler for sqlexception
	begin
    rollback;
	resignal; 
    end;

set transaction isolation level repeatable read;
start transaction;

INSERT INTO  modello  ( 
    NomeModello ,
    DatiTecnici ,  
    CasaCostruttrice ,  
    NumeroPosti ) 
VALUES (
    nmd, 
    dtt,
    csc,
    nmp
    );
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    nmd,
    mch1
);
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    nmd,
    mch2
);

update modello
set NumeroMeccaniciCompetenti = '2'
where NomeModello = nmd; 

select COUNT(1) 
into count_mech_per_model 
from competenze 
where CompetenzeModello = nmd;

if(count_mech_per_model <> 2) 
then signal sqlstate '45001' 
set message_text = "Errore nell inserimento delle competenze";
end if;
commit;
end
/*All'inserimento di un modello devono essere associati almeno due meccanici, 
questa transazione previene che venga inserito un solo meccanico competente in caso il secondo inserimento fallisca */

create procedure if not exists `tripdb`.`insert_offert`(
    in srv int,
    in htl int
)
begin
INSERT INTO  offre  ( 
    ServizioOfferto, 
    AlbergoOfferente )
VALUES(
    srv,
    htl
);

end

create procedure if not exists `tripdb`.`insert_picture` (
    in dsf varchar(5000),
    in pct blob
)
begin
INSERT INTO documentazionefotografica (
    DescrizioneFoto,
    Immagine
    )
VALUES(
    dsf,
    pct
);

endcreate procedure if not exists `tripdb`.`insert_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
insert into presenti (
    ComfortPresenti, 
    ModelloAssociato
)
values (
    cmf, 
    mdl
); 
end

create procedure if not exists `tripdb`.`insert_reservation`( 
 IN cli VARCHAR(45), 
 IN vgg int, 
 IN nmp int
 )
BEGIN
INSERT INTO prenotazione
			(ClientePrenotante,
			 ViaggioAssociato,
			 DataDiPrenotazione, 
			 NumeroDiPostiPrenotati
             )
		VALUES
			(cli,
			 vgg, 
			 curdate(),
             nmp
             );
END

create procedure if not exists `tripdb`.`insert_review`(
in mzr varchar(45),
in mch varchar(45),
in dnz date, 
in dfn date,
in clm int, 
in cnt varchar(1000),
in tip varchar(45), 
in mtv varchar(1000)
)
BEGIN
insert into revisione (
   MezzoRevisionato,
   AddettoAllaRevisione,
   DataInizio,
   DataFine,
   Chilometraggio,
   ControlliEffettuati,
   TipologiaRevisione,
   Motivazione 
  )
values(
	mzr,
  mch,
	dnz, 
	dfn,
	clm, 
	cnt,
	tip, 
	mtv
); 
END

create procedure if not exists `tripdb`.`insert_room`(
    in nmc int, 
    in htl int, 
    in tpl varchar(45),
    in cst decimal(8,2)
)  
begin
INSERT INTO camera(
    NumeroCamera , 
    IdAlbergo ,
    Tipologia ,
    Costo)
VALUES(
    nmc, 
    htl, 
    tpl,
    cst);
  end
  
create procedure if not exists `tripdb`.`insert_rt`(
    in rvs int,
    in tgl int
)
begin
insert into rt (
    RevisioneRelativa, 
    TagliandoAssociato
)
values (
    rvs, 
    tgl
); 
end

Create procedure if not exists `tripdb`.`insert_seat`(
in num int, 
in pre int, 
in eta int , 
in nom varchar(45),
in cgn varchar(45)
)
BEGIN
insert into postoprenotato 
			(NumeroDiPosto, 
             PrenotazioneAssociata, 
             EtaPasseggero, 
             NomePasseggero,
             CognomePasseggero)
values
			(num, 
             pre,
             eta, 
             nom,
             cgn
             ); 
END

create procedure if not exists `tripdb`.`insert_service`(
    in nms varchar (45),
    in dss varchar(5000)
)
begin
INSERT INTO servizio  (  
NomeServizio ,  
DescrizioneServizio )
 VALUES (
    nms,
    dss );
end

create procedure if not exists `tripdb`.`insert_skills`(
    in cmp varchar (45),
    in mcc varchar (45)
)
begin
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    cmp,
    mcc
);
end

create procedure if not exists `tripdb`.`insert_sostitution`(
in rvs int, 
in rcm varchar(45), 
in qnt int
)
BEGIN
insert into sostituito 
			(RevisioneAssociata,
             CodiceRicambioSostituito,
             QuantitàSostituita)
values
			(rvs, 
             rcm,
             qnt
             ); 
END

create procedure if not exists `tripdb`.`insert_sost_review`(
in mzr varchar(45),
in mch varchar(45),
in dnz date, 
in dfn date,
in clm int, 
in cnt varchar(1000),
in mtv varchar(1000),
in rcm varchar(45), 
in qnt int
)begin 

declare max_id_review int default 0; 
declare count_sost_per_review int default 0;

declare exit handler for sqlexception
	begin
    rollback;
	  resignal; 
  end;
set transaction isolation level repeatable read;
start transaction;

insert into revisione (
   MezzoRevisionato,
   AddettoAllaRevisione,
   DataInizio,
   DataFine,
   Chilometraggio,
   ControlliEffettuati,
   Motivazione 
  )
values(
	mzr,
  mch,
	dnz, 
	dfn,
	clm, 
	cnt,
	mtv
); 

select max(IdRevisione)
into max_id_review
from revisione;

insert into sostituito 
			      (RevisioneAssociata,
             CodiceRicambioSostituito,
             QuantitàSostituita)
values
			      (max_id_review, 
             rcm,
             qnt
             ); 



select COUNT(1) 
into count_sost_per_review 
from sostituito 
where RevisioneAssociata = max_id_review;

if(count_sost_per_review <> 1) 
then signal sqlstate '45001' 
set message_text = "Errore nell inserimento delle competenze";
end if;
commit;

end

/* Questa transazione viene implementata per garantire che al fallimento dell'insermento di una revisione l'eventuale sostituzione non venga associata*/

create procedure if not exists `tripdb`.`insert_sparepart`(
    in cdc varchar (45),
    in cst int, 
    in qtr int,
    in dsc varchar (5000),
    in scm int, 
    in qtm int
)
begin
insert into ricambio (
   Codice ,
   CostoUnitario ,
   QuantitaDiRiordino ,
   Descrizione ,
   ScortaMinima ,
   QuantitaMagazzino )
  values(
    dsc,
    cst,
    qtr,
    dsc,
    scm,
    qtm); 
  end
  
CREATE PROCEDURE if not exists `tripdb`.`insert_stay`(
in cam int, 
in osp int, 
in alb int, 
in prn int, 
in dis date,
in dfs date
 )
BEGIN
insert into soggiorno 
			(CameraPrenotata, 
			 Ospite, 
             AlbergoInQuestione,
             PrenotazioneInQuestione,
             DataInizioSoggiorno, 
             DataFineSoggiorno)
values
			(cam,
             osp,
             alb,
             prn, 
             dis,
             dfs); 
END

create procedure if not exists`tripdb`.`insert_tour`(
    in dnt varchar(45), 
    in dst varchar(5000), 
    in mnm int, 
    in mdc decimal(8,2),
    in bgl decimal(8,2),
    in gnl decimal(8,2),
    in hst tinyint
) 
begin
insert into tour(
    DenominazioneTour ,
    DescrizioneTour,
    Minimopartecipanti ,
    CostoAssicurazioneMedica ,
    CostoBagaglio ,
    CostoGaranziaAnnullamento ,
    Accompagnatrice)
values(
    dnt,
    dst,
    mnm,
    mdc,
    bgl,
    gnl,
    hst);
end

create procedure if not exists `tripdb`.`insert_trip`(
    in tsc varchar(45), 
    in idc varchar(45), 
    in ida varchar(45), 
    in trg varchar (10), 
    in ddp date, 
    in ddr date, 
    in cst decimal (8,2), 
    in nkm int, 
    in pst int
 
)
begin
INSERT INTO viaggio
( TourAssociato ,
   Conducente ,
   Accompagnatrice ,
   TargaMezzoImpiegato ,
   DataPartenzaViaggio ,
   DataRitornoViaggio , 
   CostoDelViaggio ,
   NumeroKm ,
   PostiDisponibili )
VALUES
(    tsc, 
     idc, 
     ida, 
     trg, 
     ddp, 
     ddr, 
     cst, 
     nkm, 
     pst);
     end

create procedure if not exists  `tripdb`.`insert_user`(
    in eml varchar(45),
    in psw varchar(8),
    in tpt varchar(45)
)
begin
INSERT INTO utente 
( EmailUtente ,
   Pswrd ,
   TipoUtente )
 VALUES 
 (eml,
  psw, 
  tpt);
  end; 
  
  
 create procedure if not exists `tripdb`.`insert_visit`(
    in vgg int, 
    in mtv int, 
    in drr date, 
    in dpr date, 
    in orr time,
    in orp time, 
    in gui tinyint,
    in spl decimal(8,2),
    in trt varchar(45))
begin
INSERT INTO visita (
   ViaggioRelativo ,
   MetaVisitata ,
   DataArrivo ,
   DataPartenza ,
   OraArrivo ,
   OraPartenza ,
   Guida ,
   Supplemento ,
   Trattamento )
VALUES(
    vgg, 
    mtv, 
    drr, 
    dpr, 
    orr, 
    orp, 
    gui,
    spl,
    trt);
  end
  

create procedure if not exists  `tripdb`.`select_all_tour`(
 )
BEGIN
select distinct t.DenominazioneTour,
 t.DescrizioneTour,
 t.Minimopartecipanti, 
 t.CostoAssicurazioneMedica, 
 t.CostoBagaglio, 
 t.CostoGaranziaAnnullamento, 
 t.Accompagnatrice,
 mo.NomeModello, 
 v.DataPartenzaViaggio, 
 v.DataRitornoViaggio, 
 v.CostoDelViaggio, 
 v.PostiDisponibili,
 v.idviaggio
from tour as t
join viaggio as v on t.DenominazioneTour = v.TourAssociato
join mezzo as m on v.TargaMezzoImpiegato = m.Targa
join modello as mo on m.ModelloMezzo = mo.NomeModello
where v.DataPartenzaViaggio > curdate(); 
END

Create procedure if not exists `tripdb`.`select_assigned_trip`(
in dvr varchar(45)
 )
BEGIN
select distinct t.DenominazioneTour,
				v.idviaggio,
				mo.NomeModello, 
				m.Targa,
				m.Autonomia,
				m.Ingombri,
				m.ValoreContaKm,
				v.DataPartenzaViaggio, 
				v.DataRitornoViaggio 
from tour as t
join viaggio as v on t.DenominazioneTour = v.TourAssociato
join mezzo as m on v.TargaMezzoImpiegato = m.Targa
join modello as mo on m.ModelloMezzo = mo.NomeModello
join dipendente as d on v.Conducente = d.EmailDipendente
where v.DataPartenzaViaggio > curdate() and d.EmailDipendente = dvr; 
END

Create procedure if not exists `tripdb`.`select_bus`(
in trg varchar (10)
 )
BEGIN
select distinct 
  m.ModelloMezzo,
  m.DataRevisioneMotorizzazione,
  m.Autonomia,
  m.ValoreContaKm,
  m.Ingombri,
  m.DataImmatricolazione
from mezzo as m
join modello as mo on m.ModelloMezzo = mo.NomeModello
where m.Targa = trg; 
END

create procedure if not exists `tripdb`.`select_certify`(
    in idt int
)
begin
select 
t.TipologiaTagliando,
t.ValiditaSuperate
from tagliando as t
where t.IdTagliando = idt; 
end

create procedure if not exists `tripdb`.`select_comfort`(
in idc int
)
begin
select
c.NomeComfort,
c.DescrizioneComfort
from comfort as c
where c.IdComfort = idc; 
end

create procedure if not exists `tripdb`.`select_costumer`(
IN eml VARCHAR(45)
)

BEGIN
SELECT	
	c.NomeCliente, 
    c.CognomeCliente, 
    c.IndirizzoCliente, 
    c.CodiceFiscale, 
    c.DataDocumentazione, 
    c.RecapitoTelefonico, 
	c.Fax
FROM cliente as c
WHERE c.EmailCliente = eml;

END

create procedure if not exists `tripdb`.`select_destination`(
    in idm int
)
begin
select 
m.NomeMeta,
m.TipologiaMeta,  
m.LocalitaDiAppartenenza, 
m.RegioneDiAppartenenza,
m.Indirizzo,
m.TelefonoMeta,
m.EmailMeta, 
m.FaxMeta,
m.CategoriaAlbergo, 
m.OrarioDiApertura

from meta as m
join localita as l on m.LocalitaDiAppartenenza = l.NomeLocalita
where m.IdMeta = idm; 
end

Create procedure if not exists `tripdb`.`select_dest_time`(
in idv int)
BEGIN
select distinct
   m.NomeMeta,
   m.TipologiaMeta,
   l.NomeLocalita,
   l.Regione,
   m.Indirizzo,
   v.DataArrivo,
   v.OraArrivo,
   v.DataPartenza,
   v.OraPartenza
from visita as v
join meta as m on v.MetaVisitata = m.IdMeta
join viaggio as vi on v.ViaggioRelativo = vi.idviaggio
join localita as l on m.LocalitaDiAppartenenza = l.NomeLocalita
where vi.idviaggio = idv ;
END

Create procedure if not exists `tripdb`.`select_dest_tour`(
in idv int)
BEGIN
select distinct
   m.NomeMeta,
   v.DataArrivo,
   v.OraArrivo,
   v.DataPartenza,
   v.OraPartenza,
   v.Supplemento,
   m.TipologiaMeta,
   v.Guida,
   m.OrarioDiApertura,
   v.Trattamento,
   m.CategoriaAlbergo,
   d.DescrizioneFoto,
   d.Immagine, 
   m.IdMeta
   
   
from visita as v
join meta as m on v.MetaVisitata = m.IdMeta
join viaggio as vi on v.ViaggioRelativo = vi.idviaggio
join fme as f on m.IdMeta = f.MetaRappresentata
join documentazionefotografica as d on f.FotoMeta = d.idDocumentazioneFotografica
where v.ViaggioRelativo = idv;
END

CREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_dvr_map`(
in lcl varchar(45)
)
BEGIN
SELECT distinct 
    m.Citta,
	m.Dettaglio,
    m.Zona,
    m.ImmagineMappa	
from mappa as m
join localita as l on m.Citta = l.NomeLocalita
join meta as me on l.NomeLocalita = me.LocalitaDiAppartenenza
where m.Citta = lcl;
END


CREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_employee`(
    IN mld varchar(45)
    )
BEGIN
     SELECT  
    NomeDipendente, 
    CognomeDipendente,
    TipologiaDipendente, 
    TelefonoAziendale

FROM dipendente
    WHERE EmailDipendente = mld;
END;

Create procedure if not exists `tripdb`.`select_expired_review`()
begin
select distinct 
m.Targa, 
r.DataFine, 
r.Chilometraggio,
m.ValoreContaKm
from  mezzo as m
join revisione as r on m.Targa = r.MezzoRevisionato
where (m.ValoreContaKm > r.Chilometraggio) and m.Targa 
not in (select m1.Targa
		from mezzo as m1
		join revisione as r1 on m1.Targa=r1.MezzoRevisionato
		where DATE_ADD(r1.DataFine, INTERVAL 1 YEAR) >= CURDATE()
		and (m1.ValoreContaKm - r1.Chilometraggio) < '38000'); 
end

create procedure if not exists `tripdb`.`select_fme`
(   
    in fmt int,
    in mtr int
)
begin
select 
m.NomeMeta,
d.DescrizioneFoto,
d.Immagine

from fme as f
join meta as m on f.MetaRappresentata = m.IdMeta
join documentazionefotografica as d on f.FotoMeta = d.idDocumentazioneFotografica
where f.MetaRappresentata = mtr and f.FotoMeta = fmt; 
end

create procedure if not exists `tripdb`.`select_fmo` (
    in fml int, 
    in mdl Varchar(45)
)
begin
select 
	d.DescrizioneFoto,
	d.Immagine
       

    from fmo as f
    join documentazionefotografica as d on f.FotoModello = d.idDocumentazioneFotografica
    join modello as m on f.ModelloRappresentato = m.NomeModello
    WHERE f.FotoModello = fml  and m.NomeModello = mdl;
end

create procedure if not exists `tripdb`.`select_hotel_service` (
in idh int )
BEGIN
	select 
			s.NomeServizio,
			s.DescrizioneServizio
	from servizio as s 
    join offre as o on s.IdServizio = o.ServizioOfferto
    join meta as m on o.AlbergoOfferente = m.IdMeta
    where IdMeta = idh and (TipologiaMeta = 'Albergo' or TipologiaMeta = 'albergo') ; 
END

create procedure if not exists `tripdb`. `select_location` (
    in nml varchar (45),
	in rgn varchar (45)
 )
begin
select 
	l.Stato
from localita as l 
where l.NomeLocalita = nml and l.Regione = rgn; 
end

create procedure if not exists `tripdb`.`select_map`(
in idm int
)
begin
select
m.Citta, 
m.RegioneInQuestione,
m.Dettaglio,
m.Zona,
m.ImmagineMappa
from mappa as m 
join localita as l on m.Citta = l.NomeLocalita 
where m.IdMappa = idm; 
end

Create procedure if not exists `tripdb`.`select_model_comfort`(
in nmd varchar(45)
)
BEGIN
select distinct
	m.CasaCostruttrice,
	m.NumeroPosti,
	c.NomeComfort, 
	c.DescrizioneComfort,
	d.Immagine, 
	d.DescrizioneFoto,
    d.idDocumentazioneFotografica
from modello as m
join presenti as p on m.NomeModello = p.ModelloAssociato
join comfort as c on  p.ComfortPresenti = c.IdComfort
join fmo as f on m.NomeModello = f.ModelloRappresentato
join documentazionefotografica as d on f.FotoModello = d.idDocumentazioneFotografica
where m.NomeModello = nmd; 
END

create procedure if not exists `tripdb`.`select_model`(
    in nmd varchar(45)
)
begin
select 
m.CasaCostruttrice,
m.DatiTecnici,
m.NumeroPosti,
m.NumeroMeccaniciCompetenti
from modello as m 
where m.NomeModello = nmd; 
end

create procedure if not exists `tripdb`.`select_ofr` (
    in lbr int,
    in srv int 
)
begin
select 
m.NomeMeta,
s.NomeServizio,
s.DescrizioneServizio
from offre as o 
join meta as m on o.AlbergoOfferente = m.IdMeta
join servizio as s on o.ServizioOfferto = s.IdServizio
where o.AlbergoOfferente = lbr and o.ServizioOfferto = srv; 
end

create procedure if not exists `tripdb`.`select_picture`(
in idf int
)
begin
select
d.Immagine, 
d.DescrizioneFoto
from documentazionefotografica as d
where d.idDocumentazioneFotografica = idf; 
end

create procedure if not exists `tripdb`.`select_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
select
    ComfortPresenti, 
    ModelloAssociato
from presenti 
where ComfortPresenti = cmf and ModelloAssociato = mdl; 
end

Create procedure if not exists `tripdb`.`select_reservation_info`(
    in mlc varchar(45)
    )
BEGIN
SELECT
 p.NumeroDiPrenotazione, 
 p.DataDiPrenotazione

FROM prenotazione as p
JOIN cliente as c on p.ClientePrenotante = c.EmailCliente
WHERE p.ClientePrenotante = mlc; 
END

Create procedure if not exists `tripdb`.`select_reservation`(
    in npr int
    )
BEGIN
SELECT
 p.ClientePrenotante, 
 p.ViaggioAssociato, 
 p.NumeroDiPostiPrenotati,
 p.DataDiPrenotazione,
 p.DataDiConferma, 
 p.DataSaldo
FROM prenotazione as p
JOIN cliente as c on p.ClientePrenotante = c.EmailCliente
WHERE NumeroDiPrenotazione = npr;
END

create procedure if not exists `tripdb`.`select_review`(
in idr int
)
BEGIN
SELECT  
   r.MezzoRevisionato,
   r.AddettoAllaRevisione, 
   r.DataInizio,
   r.DataFine,
   r.Chilometraggio,
   r.ControlliEffettuati,
   r.Motivazione 
FROM revisione as r
join mezzo as m on r.MezzoRevisionato = m.Targa
join dipendente as d on r.AddettoAllaRevisione = d.EmailDipendente
WHERE r.IdRevisione = idr; 
END

create procedure if not exists `tripdb`.`select_room`(
in nmc int, 
in htl int
)
begin
select
c.Tipologia, 
c.Costo
from camera as c
where c.NumeroCamera = nmc and c.IdAlbergo = htl;
end

create procedure if not exists `tripdb`.`select_rt`(
    in rvs int,
    in tgl int
)
begin
select 
     RevisioneRelativa, 
     TagliandoAssociato
from rt
where RevisioneRelativa = rvs and TagliandoAssociato = tgl; 
end

create procedure if not exists `tripdb`.`select_seat`(
    in nmp int, 
    in prn int
)
begin
select
p.NomePasseggero,
p.CognomePasseggero,
p.EtaPasseggero
from postoprenotato as p
join prenotazione as r on p.PrenotazioneAssociata = r.NumeroDiPrenotazione
where p.NumeroDiPosto = nmp and p.PrenotazioneAssociata = prn; 
end

create procedure if not exists `tripdb`.`select_service` (
in ids int
)
begin
select 
s.NomeServizio,
s.DescrizioneServizio
from servizio as s
where s.IdServizio = ids; 
end

create procedure if not exists `tripdb`.`select_skills` (
in mch varchar(45), 
in mdl varchar(45)
)
begin
select
d.NomeDipendente,
d.TelefonoAziendale
from competenze as c
join dipendente as d on c.MeccanicoCompetente = d.EmailDipendente
join modello as m on c.CompetenzeModello = m.NomeModello
where c.CompetenzeModello = mdl and c.MeccanicoCompetente = mch;
end

create procedure if not exists `tripdb`.`select_sostitution` (
in cdc varchar(45), 
in rvs int
)
begin
select QuantitàSostituita
from sostituito
where CodiceRicambioSostituito = cdc and RevisioneAssociata = rvs; 
end

create procedure if not exists `tripdb`.`select_sparepart`(
in cdc VARCHAR(45)
)
BEGIN
SELECT  
   r.CostoUnitario,
   r.QuantitaDiRiordino,
   r.Descrizione,
   r.ScortaMinima,
   r.QuantitaMagazzino
FROM ricambio as r
WHERE r.Codice = cdc; 
END

create PROCEDURE if not exists `tripdb`.`select_stay`(
in ids int

)
begin
select
s.Ospite,
s.AlbergoInQuestione,
s.CameraPrenotata,
s.PrenotazioneInQuestione,
s.DataInizioSoggiorno,
s.DataFineSoggiorno
from soggiorno as s 
where s.IdSoggiorno = ids;  
END

create procedure if not exists `tripdb`.`select_tour`(
IN dnm VARCHAR(45)
)
BEGIN
SELECT 
    t.DescrizioneTour,
    t.Minimopartecipanti,
    t.CostoAssicurazioneMedica,
    t.CostoBagaglio,
    t.CostoGaranziaAnnullamento,
    t.Accompagnatrice  
FROM tour as t
WHERE t.DenominazioneTour = dnm;
END

create procedure if not exists `tripdb`.`select_trip`(
IN trip INT
  )
BEGIN


SELECT 
	v.TourAssociato,
	v.Conducente,
    v.Accompagnatrice, 
	v.TargaMezzoImpiegato, 
	v.DataPartenzaViaggio,
    v.DataRitornoViaggio, 
	v.CostoDelViaggio,
	v.NumeroKm, 
	v.PostiDisponibili, 
	v.DataCancellazione

FROM viaggio as v
JOIN dipendente as d on v.Conducente = d.EmailDipendente 
JOIN dipendente as d1 on v.Accompagnatrice = d1.EmailDipendente
JOIN mezzo as m on v.TargaMezzoImpiegato = m.Targa
JOIN tour as t on v.TourAssociato = t.DenominazioneTour
WHERE v.IdViaggio = trip; 

END

create procedure if not exists `tripdb`.`select_user`(
    in usr varchar(45)
)
begin
select 
u.Pswrd, 
u.TipoUtente
from  utente as u
Where u.EmailUtente = usr; 
end

create procedure if not exists `tripdb`.`select_visit`(
    in idv int
)
begin
select 
t.DenominazioneTour,
v.ViaggioRelativo,
m.NomeMeta,
v.MetaVisitata,
v.DataArrivo,  
v.OraArrivo,
v.DataPartenza,
v.OraPartenza, 
v.Guida,
v.Supplemento, 
v.Trattamento

from visita as v
join viaggio as via on v.ViaggioRelativo = via.idviaggio
join meta as m on v.MetaVisitata = m.IdMeta
join tour as t on via.TourAssociato = t.DenominazioneTour

where v.idvisita = idv; 
end

Create procedure if not exists `tripdb`.`update_km`(
in trg varchar (10),
in vlk int
 )
BEGIN
    update mezzo as m
    set m.ValoreContaKm = vlk
    where m.targa = trg; 
END


create procedure if not exists `tripdb`.`update_user_type` (
    in sml varchar (45),
    in tpl int 

)
begin 
update utente 
set TipoUtente = tpl 
where EmailUtente = sml; 
end

Create procedure if not exists `tripdb`.`validate_reservation`(
IN ndp INT, 
IN ddc DATE, 
IN dds DATE)
BEGIN 
UPDATE prenotazione AS p
SET p.DataDiConferma = ddc, 
    p.DataSaldo = dds
WHERE p.NumeroDiPrenotazione = ndp; 

END
create trigger`tripdb`.`decrement_skills` after delete
on `competenze`
for each row
  update modello
  join competenze 
  set NumeroMeccaniciCompetenti = NumeroMeccaniciCompetenti - 1
  where NomeModello= OLD.CompetenzeModello;
  
create trigger `tripdb`.`decrement_sparepart` after insert 
on `sostituito`
for each row 
update ricambio
join sostituito
set QuantitaMagazzino = QuantitaMagazzino-NEW.QuantitàSostituita
where Codice = NEW.CodiceRicambioSostituito; 

create trigger`tripdb`.`increment_skills` after insert
on `competenze`
for each row
  update modello
  join competenze
  set NumeroMeccaniciCompetenti = NumeroMeccaniciCompetenti+1
  where NomeModello = NEW.CompetenzeModello and NumeroMeccaniciCompetenti>='2';
  
create trigger`tripdb`.`update_data_doc_trigger` after insert
on `prenotazione`
for each row
update cliente
join prenotazione 
set DataDocumentazione = curdate()
where EmailCliente = NEW.ClientePrenotante;

create trigger `tripdb`.`update_km_after_review` after insert 
on `revisione`
for each row 
update mezzo
join revisione 
set ValoreContaKm = NEW.Chilometraggio
where targa = NEW.MezzoRevisionato; 

create trigger `tripdb`.`update_tripseat` after insert 
on `prenotazione`
for each row 
update viaggio
join prenotazione
set PostiDisponibili = PostiDisponibili - new.NumeroDiPostiPrenotati
where idviaggio = NEW.ViaggioAssociato; 
DELETE FROM `tripdb`.`utente`;
INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('1',
  '1',
  '5');
  INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('drvr@mail.com',
  '1',
  '1');
  INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('cstmr@mail.com',
  '1',
  '2');
  INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('hstss@mail.com',
  '1',
  '3');
  INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('mch@mail.com',
  '1',
  '4');
  INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('mngr@mail.com',
  '1',
  '5');
   INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('ldn@mail.com',
  '1',
  '2');
 INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('gdn@mail.com',
  '1',
  '2');
  INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('gvnn@mail.com',
  '1',
  '2');
 INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('smn@mail.com',
  '1',
  '2');
  INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('mch1@mail.com',
  '1',
  '4');
    INSERT INTO `tripdb`.`utente` 
(`EmailUtente`,
  `Pswrd`,
  `TipoUtente`)
 VALUES 
 ('mch2@mail.com',
  '1',
  '4');
  
  DELETE FROM `tripdb`.`tour`;
INSERT INTO `tripdb`.`tour` 
(`DenominazioneTour`,
`DescrizioneTour`,
`Minimopartecipanti`,
`CostoAssicurazioneMedica`,
`CostoBagaglio`,
`CostoGaranziaAnnullamento`,
`Accompagnatrice`)
VALUES('1','prova','20','90.00','10.00','15.00','1');

INSERT INTO `tripdb`.`tour` 
(`DenominazioneTour`,
`DescrizioneTour`,
`Minimopartecipanti`,
`CostoAssicurazioneMedica` ,
`CostoBagaglio`,
`CostoGaranziaAnnullamento`,
`Accompagnatrice`)
VALUES
('Roma tour',
'Tour che si svolge presso le piazze di Roma ',
'58',
'90.00' ,
'10.00',
'15.00',
'1');
INSERT INTO `tripdb`.`tour` 
(`DenominazioneTour`,
`DescrizioneTour`,
`Minimopartecipanti`,
`CostoAssicurazioneMedica` ,
`CostoBagaglio`,
`CostoGaranziaAnnullamento`,
`Accompagnatrice`)
VALUES
(
'Milano tour',
'Tour per le strade di Milano',
'54',
'90.00' ,
'10.00',
'15.00',
'0');
INSERT INTO `tripdb`.`tour` 
(`DenominazioneTour`,
`DescrizioneTour`,
`Minimopartecipanti`,
`CostoAssicurazioneMedica` ,
`CostoBagaglio`,
`CostoGaranziaAnnullamento`,
`Accompagnatrice`)
VALUES
(
'Tour',
'Tour per le strade',
'54',
'90.00' ,
'10.00',
'15.00',
'0');  

DELETE FROM `tripdb`.`servizio`;
INSERT INTO `tripdb`.`servizio` 
(`IdServizio`, `NomeServizio`, `DescrizioneServizio`)
 VALUES ('1', 'ServizioA', 'servizio corrispondente alla lettera A');
INSERT INTO `tripdb`.`servizio`
 (`IdServizio`, `NomeServizio`, `DescrizioneServizio`) 
 VALUES ('2', 'ServizioB', 'servizio corrispondente alla lettera B');
INSERT INTO `tripdb`.`servizio` 
(`IdServizio`, `NomeServizio`, `DescrizioneServizio`) 
VALUES ('3', 'ServizioC', 'servizio corrispondente alla lettera C');

   DELETE FROM `tripdb`.`localita`;
INSERT INTO `tripdb`.`localita` (`NomeLocalita`, `Regione`, `Stato`) 
VALUES ('Roma', 'Lazio', 'Italia');
INSERT INTO `tripdb`.`localita` (`NomeLocalita`, `Regione`, `Stato`)
 VALUES ('Milano', 'Lombardia', 'Italia');
INSERT INTO `tripdb`.`localita` (`NomeLocalita`, `Regione`, `Stato`)
 VALUES ('Graz', 'Stiria', 'Austria');
INSERT INTO `tripdb`.`localita` (`NomeLocalita`, `Regione`, `Stato`) 
VALUES ('Napoli', 'Campania', 'Italia');
INSERT INTO `tripdb`.`localita` (`NomeLocalita`, `Regione`, `Stato`)
 VALUES ('Castelli romani', 'Lazio', 'Italia');
 
 DELETE FROM `tripdb`.`dipendente`;
INSERT INTO `tripdb`.`dipendente` ( 
 `TipologiaDipendente`,
 `TelefonoAziendale`,
 `NomeDipendente`, 
 `CognomeDipendente`,
 `EmailDipendente`) 
 VALUES(
'autista',
'1234', 
'Mario', 
'Rossi',
'drvr@mail.com');
INSERT INTO `tripdb`.`dipendente` ( 
`TipologiaDipendente`, 
`TelefonoAziendale`, 
`NomeDipendente`, 
`CognomeDipendente`,
`EmailDipendente`) 
VALUES ( 
    'hostess', 
    '4453', 
    'Anna', 
    'Bianchi',
    'hstss@mail.com');
INSERT INTO `tripdb`.`dipendente` ( 
    `TipologiaDipendente`, 
    `TelefonoAziendale`, 
    `NomeDipendente`, 
    `CognomeDipendente`,
    `EmailDipendente`)
     VALUES ( 
        'meccanico', 
        '7801', 
        'Paolo','Verdi',
        'mch@mail.com');
INSERT INTO `tripdb`.`dipendente` ( 
    `TipologiaDipendente`, 
    `TelefonoAziendale`, 
    `NomeDipendente`, 
    `CognomeDipendente`,
    `EmailDipendente`)
     VALUES ( 
        'meccanico', 
        '7801', 
        'Mario','Verdi',
        'mch1@mail.com');
INSERT INTO `tripdb`.`dipendente` ( 
    `TipologiaDipendente`, 
    `TelefonoAziendale`, 
    `NomeDipendente`, 
    `CognomeDipendente`,
    `EmailDipendente`)
     VALUES ( 
        'meccanico', 
        '7801', 
        'Giuseppe','Verdi',
        'mch2@mail.com');

DELETE FROM `tripdb`.`modello`;
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('AXA', 'UNO', 'ALFA ROMEO', '10');
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('DAXA', 'DUE', 'FIAT', '12');
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('RAXA', 'TRE', 'ALFA ROMEO', '14');
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('HONDA', 'TRE', 'ALFA ROMEO', '14');
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('IVECO', 'TRE', 'ALFA ROMEO', '14');
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('SCANIA', 'TRE', 'ALFA ROMEO', '14');
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('MERCEDES', 'TRE', 'ALFA ROMEO', '14');
INSERT INTO `tripdb`.`modello` (`NomeModello`, `DatiTecnici`, `CasaCostruttrice`, `NumeroPosti`) 
VALUES ('FORD', 'TRE', 'ALFA ROMEO', '14');



INSERT INTO `tripdb`.`mezzo` 
(`Targa` ,
  `ModelloMezzo`,
  `DataRevisioneMotorizzazione`,
  `Autonomia`,
  `ValoreContaKm`,
  `Ingombri`,
  `DataImmatricolazione`
  ) 
  VALUES
  (
'DS1029RM' ,
  'AXA',
  '2019-12-01',
  '1500',
  '250000',
  '15*4*5.5',
  '2019-11-30');
  INSERT INTO `tripdb`.`mezzo` 
(`Targa` ,
  `ModelloMezzo`,
  `DataRevisioneMotorizzazione`,
  `Autonomia`,
  `ValoreContaKm`,
  `Ingombri`,
  `DataImmatricolazione`
  )
VALUES
(
'AY1099DY' ,
  'DAXA',
  '2019-12-01',
  '1500',
  '250000',
  '15*4*5.5',
  '2019-11-30');
  INSERT INTO `tripdb`.`mezzo` 
(`Targa` ,
  `ModelloMezzo`,
  `DataRevisioneMotorizzazione`,
  `Autonomia`,
  `ValoreContaKm`,
  `Ingombri`,
  `DataImmatricolazione`
  )
VALUES
(

'ET1098EX' ,
  'RAXA',
  '2019-12-01',
  '1500',
  '250000',
  '15*4*5.5',
  '2019-11-30');
   INSERT INTO `tripdb`.`mezzo` 
(`Targa` ,
  `ModelloMezzo`,
  `DataRevisioneMotorizzazione`,
  `Autonomia`,
  `ValoreContaKm`,
  `Ingombri`,
  `DataImmatricolazione`
  )
VALUES
(

'1' ,
  'RAXA',
  '2019-12-01',
  '1500',
  '250000',
  '15*4*5.5',
  '2019-11-30');
  
  
delete from `tripdb`.`revisione`; 
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`)
  values(
'AY1099DY','drvr@mail.com','2021-01-01','2022-01-01','250000','Cambio olio e filtri', 'Ordinaria'); 
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`)
  values(
'DS1029RM','drvr@mail.com','2022-07-01','2022-07-01','200000','Sostituzione gomma','Foratura gomma');
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`)
  values(
'ET1098EX','drvr@mail.com','2022-07-01','2022-07-01','230000','Sostituzione gomma','Foratura gomma');
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`
   )
  values(
'AY1099DY','drvr@mail.com','2018-07-01','2018-07-01','250000','Cambio olio e filtri','ordinaria'); 
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`)
  values(
'DS1029RM','drvr@mail.com','2020-07-01','2020-07-01','200000','Sostituzione gomma','Foratura gomma');
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`
   )
  values(
'AY1099DY','drvr@mail.com','2019-07-01','2019-07-01','250000','Cambio olio e filtri','ordinaria'); 
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`
   )
  values(
'AY1099DY','drvr@mail.com','2020-07-01','2020-07-01','250000','Cambio olio e filtri','ordinaria'); 
insert into `tripdb`.`revisione`(
  `MezzoRevisionato`,
  `AddettoAllaRevisione`, 
  `DataInizio`,
  `DataFine`,
  `Chilometraggio`,
  `ControlliEffettuati`,
  `Motivazione`
   )
  values(
'AY1099DY','drvr@mail.com','2017-07-01','2017-07-01','250000','Cambio olio e filtri','ordinaria'); 

DELETE FROM `tripdb`.`comfort`;
INSERT INTO `tripdb`.`comfort` (`IdComfort`, `NomeComfort`, `DescrizioneComfort`) 
VALUES ('1', 'Cuscino', 'Un cuscino blu');
INSERT INTO `tripdb`.`comfort` (`IdComfort`, `NomeComfort`, `DescrizioneComfort`)
 VALUES ('2', 'Internet', 'Connessione alla rete');
INSERT INTO `tripdb`.`comfort` (`IdComfort`, `NomeComfort`, `DescrizioneComfort`)
 VALUES ('3', 'Acqua', '');
 
   
DELETE FROM `tripdb`.`meta`;
INSERT INTO `tripdb`.`meta` (  
    `LocalitaDiAppartenenza`,
    `RegioneDiAppartenenza`,
    `NomeMeta`, 
    `TelefonoMeta`, 
    `EmailMeta`,
    `FaxMeta`, 
    `Indirizzo`, 
    `TipologiaMeta`, 
    `CategoriaAlbergo`, 
    `OrarioDiApertura`) 
    VALUES (
        'Roma', 
        'Lazio',
        'Chiesa', 
        '123', 
        's@gmail.com', 
        '123', 
        'viale dei clamini', 
        'Bene', 
        '-', 
        '08:00');
        INSERT INTO `tripdb`.`meta` (  
    `LocalitaDiAppartenenza`,
    `RegioneDiAppartenenza`,
    `NomeMeta`, 
    `TelefonoMeta`, 
    `EmailMeta`,
    `FaxMeta`, 
    `Indirizzo`, 
    `TipologiaMeta`, 
    `CategoriaAlbergo`, 
    `OrarioDiApertura`) 
    VALUES (
        'Roma', 
        'Lazio',
        'Piazza', 
        '123', 
        's@gmail.com', 
        '123', 
        'viale dei clamini', 
        'Bene', 
        '-', 
        '08:00');
        INSERT INTO `tripdb`.`meta` (  
    `LocalitaDiAppartenenza`,
    `RegioneDiAppartenenza`,
    `NomeMeta`, 
    `TelefonoMeta`, 
    `EmailMeta`,
    `FaxMeta`, 
    `Indirizzo`, 
    `TipologiaMeta`, 
    `CategoriaAlbergo`, 
    `OrarioDiApertura`) 
    VALUES (
        'Roma', 
        'Lazio',
        'Domus', 
        '123', 
        's@gmail.com', 
        '123', 
        'viale dei clamini', 
        'Albergo', 
        '5 stelle', 
        '-');
        INSERT INTO `tripdb`.`meta` (  
    `LocalitaDiAppartenenza`,
    `RegioneDiAppartenenza`,
    `NomeMeta`, 
    `TelefonoMeta`, 
    `EmailMeta`,
    `FaxMeta`, 
    `Indirizzo`, 
    `TipologiaMeta`, 
    `CategoriaAlbergo`, 
    `OrarioDiApertura`) 
    VALUES (
        'Milano',
        'Lombardia', 
        'Chiesa', 
        '123', 
        's@gmail.com', 
        '123', 
        'viale dei clamini', 
        'Bene', 
        '-', 
        '08:00');

    INSERT INTO `tripdb`.`meta` (  
    `LocalitaDiAppartenenza`,
    `RegioneDiAppartenenza`,
    `NomeMeta`, 
    `TelefonoMeta`, 
    `EmailMeta`,
    `FaxMeta`, 
    `Indirizzo`, 
    `TipologiaMeta`, 
    `CategoriaAlbergo`, 
    `OrarioDiApertura`) 
    VALUES (
        'Milano', 
        'Lombardia',
        'museo', 
        '123', 
        's@gmail.com', 
        '123', 
        'via Milano ', 
        'Bene', 
        '-', 
        '08:00');
         INSERT INTO `tripdb`.`meta` (  
    `LocalitaDiAppartenenza`,
    `RegioneDiAppartenenza`,
    `NomeMeta`, 
    `TelefonoMeta`, 
    `EmailMeta`,
    `FaxMeta`, 
    `Indirizzo`, 
    `TipologiaMeta`, 
    `CategoriaAlbergo`, 
    `OrarioDiApertura`) 
    VALUES (
        'Milano', 
        'Lombardia',
        'Albergo Milano ', 
        '123', 
        's@gmail.com', 
        '123', 
        'via albergo', 
        'Albergo', 
        '4 stelle', 
        '-');
        

DELETE FROM `tripdb`.`viaggio`;
INSERT INTO `tripdb`.`viaggio` 
(`TourAssociato`,
  `Conducente`,
  `Accompagnatrice`,
  `TargaMezzoImpiegato`,
  `DataPartenzaViaggio`,
  `DataRitornoViaggio`, 
  `CostoDelViaggio`,
  `NumeroKm`,
  `PostiDisponibili`)
VALUES
('1',
  'drvr@mail.com',
  'hstss@mail.com',
  'DS1029RM',
  '2022-10-09',
  '2022-10-12',
  '200',
  '750',
  '30'
  );

INSERT INTO `tripdb`.`viaggio` 
(`TourAssociato`,
  `Conducente`,
  `Accompagnatrice`,
  `TargaMezzoImpiegato`,
  `DataPartenzaViaggio`,
  `DataRitornoViaggio`, 
  `CostoDelViaggio`,
  `NumeroKm`,
  `PostiDisponibili`)
VALUES
('Roma tour',
  'drvr@mail.com',
  'hstss@mail.com',
  'DS1029RM',
  '2022-10-10',
  '2022-10-13',
  '300',
  '750',
  '58'
  );

INSERT INTO `tripdb`.`viaggio` 
(`TourAssociato`,
  `Conducente`,
  `Accompagnatrice`,
  `TargaMezzoImpiegato`,
  `DataPartenzaViaggio`,
  `DataRitornoViaggio`, 
  `CostoDelViaggio`,
  `NumeroKm`,
  `PostiDisponibili`)
VALUES
('Roma tour',
  'drvr@mail.com',
  'hstss@mail.com',
  'DS1029RM',
  '2022-12-11',
  '2022-12-14',
  '350',
  '750',
  '42'
  );

INSERT INTO `tripdb`.`viaggio` 
(`TourAssociato`,
  `Conducente`,
  `Accompagnatrice`,
  `TargaMezzoImpiegato`,
  `DataPartenzaViaggio`,
  `DataRitornoViaggio`, 
  `CostoDelViaggio`,
  `NumeroKm`,
  `PostiDisponibili`)
VALUES
('Milano tour',
  'drvr@mail.com',
  'hstss@mail.com',
  'DS1029RM',
  '2022-11-09',
  '2022-11-12',
  '400',
  '750',
  '62'
  );
  
 DELETE FROM `tripdb`.`cliente`;
INSERT INTO `tripdb`.`cliente` 
(`EmailCliente`,
  `NomeCliente`,
  `CognomeCliente`,
  `IndirizzoCliente`,
  `CodiceFiscale`,
  `DataDocumentazione`,
  `RecapitoTelefonico`,
  `Fax`)
VALUES
('gdn@mail.com',
  'Giordano',
  'Di Censo',
  'Via Bagheria 18',
  'DCNGDN30H501k',
  '2022-06-15',
  '3664788624',
  '-');
  INSERT INTO `tripdb`.`cliente` 
(`EmailCliente`,
  `NomeCliente`,
  `CognomeCliente`,
  `IndirizzoCliente`,
  `CodiceFiscale`,
  `DataDocumentazione`,
  `RecapitoTelefonico`,
  `Fax`)
VALUES
('ldn@mail.com',
  'Lucrezia',
  'Di Nardo',
  'Via sapienza 8',
  'LCRZDNR96',
  '2022-06-15',
  '3219820354',
  '-');
  INSERT INTO `tripdb`.`cliente` 
(`EmailCliente`,
  `NomeCliente`,
  `CognomeCliente`,
  `IndirizzoCliente`,
  `CodiceFiscale`,
  `DataDocumentazione`,
  `RecapitoTelefonico`,
  `Fax`)
VALUES
('gvnn@mail.com',
  'Giovanni',
  'Caporali',
  'Via vaticano 28',
  'CPRLGVNN28',
  '2022-06-15',
  '341989755',
  '-');
  INSERT INTO `tripdb`.`cliente` 
(`EmailCliente`,
  `NomeCliente`,
  `CognomeCliente`,
  `IndirizzoCliente`,
  `CodiceFiscale`,
  `DataDocumentazione`,
  `RecapitoTelefonico`,
  `Fax`)
VALUES
('smn@mail.com',
  'Simone',
  'Russo',
  'Via austria 87',
  'RSSSMN87',
  '2022-07-15',
  '348009889',
  '-');


DELETE FROM `tripdb`.`camera`;
INSERT INTO `tripdb`.`camera` 
( `NumeroCamera`, 
  `IdAlbergo`,
  `Tipologia`,
  `Costo`
  )
VALUES
( '1',
  '3',
  'doppia',
  '125.00'
  );
  INSERT INTO `tripdb`.`camera` 
( `NumeroCamera`, 
  `IdAlbergo`,
  `Tipologia`,
  `Costo`
  )
VALUES
 ('2',
  '3',
  'singola',
  '60'
  );
  INSERT INTO `tripdb`.`camera` 
( `NumeroCamera`, 
  `IdAlbergo`,
  `Tipologia`,
  `Costo`
  )
VALUES
('3',
  '3',
  'doppia',
  '125.00'
  );
  
  INSERT INTO `tripdb`.`camera`
  ( `NumeroCamera`, 
  `IdAlbergo`,
  `Tipologia`,
  `Costo`
  )
VALUES
( '1',
  '6',
  'doppia',
  '125.00'
  );
  
  INSERT INTO `tripdb`.`camera` 
( `NumeroCamera`, 
  `IdAlbergo`,
  `Tipologia`,
  `Costo`
  )
VALUES
 ('2',
  '6',
  'singola',
  '60'
  );
  INSERT INTO `tripdb`.`camera` 
( `NumeroCamera`, 
  `IdAlbergo`,
  `Tipologia`,
  `Costo`
  )
VALUES
('3',
  '6',
  'doppia',
  '125.00'
  );
  
DELETE FROM `tripdb`.`prenotazione`;
INSERT INTO `tripdb`.`prenotazione` 
(
  `ClientePrenotante`,
  `DataDiPrenotazione`,  
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('gdn@mail.com',
  '2022-07-09',
  '1',
  '6',
  NULL, 
  NULL
 );
 INSERT INTO `tripdb`.`prenotazione` 
(
    `ClientePrenotante`,
  `DataDiPrenotazione`, 
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('ldn@mail.com',
  '2022-07-09',
  '1',
  '4',
   NULL,
   NULL
 );
 INSERT INTO `tripdb`.`prenotazione` 
(
    `ClientePrenotante`,
  `DataDiPrenotazione`, 
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('gvnn@mail.com',
  '2022-07-09',
  '1',
  '5',
   NULL,
   NULL
 );
INSERT INTO `tripdb`.`prenotazione` 
(
    `ClientePrenotante`,
  `DataDiPrenotazione`, 
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('smn@mail.com',
  '2022-07-09',
  '2',
  '2',
   NULL,
   NULL
 );
INSERT INTO `tripdb`.`prenotazione` 
(
    `ClientePrenotante`,
  `DataDiPrenotazione`, 
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('gdn@mail.com',
  '2022-07-09',
  '2',
  '1',
  NULL, 
  NULL
 );
 INSERT INTO `tripdb`.`prenotazione` 
(
    `ClientePrenotante`,
  `DataDiPrenotazione`, 
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('ldn@mail.com',
  '2022-07-09',
  '2',
  '2',
   NULL,
   NULL
 );
 INSERT INTO `tripdb`.`prenotazione` 
(
    `ClientePrenotante`,
  `DataDiPrenotazione`, 
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('gvnn@mail.com',
  '2022-07-09',
  '2',
  '1',
   NULL,
   NULL
 );
INSERT INTO `tripdb`.`prenotazione` 
(
    `ClientePrenotante`,
  `DataDiPrenotazione`, 
  `ViaggioAssociato`,
  `NumeroDiPostiPrenotati`,
  `DataDiConferma`, 
  `DataSaldo`)
VALUES
('smn@mail.com',
  '2022-07-09',
  '3',
  '12',
   NULL,
   NULL
 );



DELETE FROM `tripdb`.`visita`;
INSERT INTO `tripdb`.`visita` 
( `ViaggioRelativo`,
  `MetaVisitata`,
  `DataArrivo`,
  `OraArrivo`,
  `DataPartenza`,
  `OraPartenza`,
  `Guida`,
  `Supplemento`,
  `Trattamento`)
VALUES
( '1',
  '1',
  '2022-10-09',
  '11:30',
  '2022-10-09',
  '12:30',
  '1',
  '0',
  '-'
  );
  INSERT INTO `tripdb`.`visita` 
(
  `ViaggioRelativo`,
  `MetaVisitata`,
  `DataArrivo`,
  `OraArrivo`,
  `DataPartenza`,
  `OraPartenza`,
  `Guida`,
  `Supplemento`,
  `Trattamento`)
VALUES
('2',
  '1',
  '2022-10-13',
  '11:35',
  '2022-10-10',
  '12:35',
  '1',
  '0',
  '-'
  );
   INSERT INTO `tripdb`.`visita` 
(
  `ViaggioRelativo`,
  `MetaVisitata`,
  `DataArrivo`,
  `OraArrivo`,
  `DataPartenza`,
  `OraPartenza`,
  `Guida`,
  `Supplemento`,
  `Trattamento`)
VALUES
('2',
  '3',
  '2022-10-11',
  '18:30',
  '2022-10-10',
  '11:30',
  '0',
  '0',
  'Pernottamento+Colazione Buffet'
  );
   INSERT INTO `tripdb`.`visita` 
(
  `ViaggioRelativo`,
  `MetaVisitata`,
  `DataArrivo`,
  `OraArrivo`,
  `DataPartenza`,
  `OraPartenza`,
  `Guida`,
  `Supplemento`,
  `Trattamento`)
VALUES
('4',
  '4',
  '2022-11-09',
  '11:00',
  '2022-11-09',
  '12:35',
  '0',
  '0',
  '-'
  );
     INSERT INTO `tripdb`.`visita` 
(
  `ViaggioRelativo`,
  `MetaVisitata`,
  `DataArrivo`,
  `OraArrivo`,
  `DataPartenza`,
  `OraPartenza`,
  `Guida`,
  `Supplemento`,
  `Trattamento`)
VALUES
('4',
  '6',
  '2022-11-11',
  '15:00',
  '2022-11-09',
  '12:35',
  '1',
  '0',
  'Mezza pensione'
  );
  
  DELETE FROM `tripdb`.`offre`;
INSERT INTO `tripdb`.`offre` (`ServizioOfferto`,`AlbergoOfferente`)
VALUES('3','3');
INSERT INTO `tripdb`.`offre` (`ServizioOfferto`,`AlbergoOfferente`)
VALUES('1','3');
INSERT INTO `tripdb`.`offre` (`ServizioOfferto`,`AlbergoOfferente`)
VALUES('1','6');
INSERT INTO `tripdb`.`offre` (`ServizioOfferto`,`AlbergoOfferente`)
VALUES('2','6');
INSERT INTO `tripdb`.`offre` (`ServizioOfferto`,`AlbergoOfferente`)
VALUES('3','6');

DELETE FROM `tripdb`.`presenti`;
INSERT INTO `tripdb`.`presenti`(`ComfortPresenti`,`ModelloAssociato`)
VALUES('1','AXA');
INSERT INTO `tripdb`.`presenti`(`ComfortPresenti`,`ModelloAssociato`)
VALUES('2','AXA');
INSERT INTO `tripdb`.`presenti`(`ComfortPresenti`,`ModelloAssociato`)
VALUES('3','AXA');
INSERT INTO `tripdb`.`presenti`(`ComfortPresenti`,`ModelloAssociato`)
VALUES('1','DAXA');
INSERT INTO `tripdb`.`presenti`(`ComfortPresenti`,`ModelloAssociato`)
VALUES('2','DAXA');
INSERT INTO `tripdb`.`presenti`(`ComfortPresenti`,`ModelloAssociato`)
VALUES('1','RAXA');
INSERT INTO `tripdb`.`presenti`(`ComfortPresenti`,`ModelloAssociato`)
VALUES('3','RAXA');


DELETE FROM `tripdb`.`documentazionefotografica`;
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 1'); 
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 2');
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 3');
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 4');
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 5');
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 6');
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 7');
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 8');
INSERT INTO `tripdb`.`documentazionefotografica` (`DescrizioneFoto`)
VALUES('foto 9');

DELETE FROM `tripdb`.`fme`; 
INSERT INTO `tripdb`.`fme`(`MetaRappresentata`,`FotoMeta`)
VALUES('1','1');
INSERT INTO `tripdb`.`fme`(`MetaRappresentata`,`FotoMeta`)
VALUES('2','2');
INSERT INTO `tripdb`.`fme`(`MetaRappresentata`,`FotoMeta`)
VALUES('3','3');
INSERT INTO `tripdb`.`fme`(`MetaRappresentata`,`FotoMeta`)
VALUES('4','4');
INSERT INTO `tripdb`.`fme`(`MetaRappresentata`,`FotoMeta`)
VALUES('5','5');
INSERT INTO `tripdb`.`fme`(`MetaRappresentata`,`FotoMeta`)
VALUES('6','6');

DELETE FROM `tripdb`.`fmo`; 
INSERT INTO `tripdb`.`fmo`(`FotoModello`,`ModelloRappresentato`)
VALUES('7','AXA');
INSERT INTO `tripdb`.`fmo`(`FotoModello`,`ModelloRappresentato`)
VALUES('8','DAXA');
INSERT INTO `tripdb`.`fmo`(`FotoModello`,`ModelloRappresentato`)
VALUES('9','RAXA');

delete from `tripdb`.`ricambio`; 
insert into `tripdb`.`ricambio`(
  `Codice`,
  `CostoUnitario`,
  `QuantitaDiRiordino`,
  `Descrizione`,
  `ScortaMinima`,
  `QuantitaMagazzino`)
  values(
'1','160','3','valvola egr','3','7'); 
insert into `tripdb`.`ricambio`(
  `Codice`,
  `CostoUnitario`,
  `QuantitaDiRiordino`,
  `Descrizione`,
  `ScortaMinima`,
  `QuantitaMagazzino`)
  values(
'34AH01','12','10','Tergicristallo anteriore','20','35'); 
insert into `tripdb`.`ricambio`(
  `Codice`,
  `CostoUnitario`,
  `QuantitaDiRiordino`,
  `Descrizione`,
  `ScortaMinima`,
  `QuantitaMagazzino`)
  values(
'67BD01','120','10','iniettore diesel','3','2'); 

DELETE FROM `tripdb`.`mappa`;
INSERT INTO `tripdb`.`mappa` 
(
  `Citta`,
  `RegioneInQuestione`,
  `Dettaglio`,
  `Zona`)
   VALUES ('Roma','Lazio', 'Medio', 'Roma Sud');
INSERT INTO `tripdb`.`mappa` (
  `Citta`,
  `RegioneInQuestione`,
  `Dettaglio`,
  `Zona`) 
  VALUES ('Milano', 'Lombardia', 'Basso', 'Navigli');
INSERT INTO `tripdb`.`mappa` (
  `Citta`,
  `RegioneInQuestione`,
  `Dettaglio`,
  `Zona`) 
  VALUES ('Graz', 'Stiria', 'Alto', 'Graz');


DELETE FROM `tripdb`.`postoprenotato`; 
INSERT INTO `tripdb`.`postoprenotato`(
    `NumeroDiPosto` ,
  `PrenotazioneAssociata`,
  `EtaPasseggero`,
  `NomePasseggero`,
  `CognomePasseggero`)
VALUES('1','1','20','Giordano',' Di Censo');
INSERT INTO `tripdb`.`postoprenotato`(  
     `NumeroDiPosto` ,
  `PrenotazioneAssociata`,
  `EtaPasseggero`,
  `NomePasseggero`,
  `CognomePasseggero`)
VALUES('2','1','21','Simone','Russo');
INSERT INTO `tripdb`.`postoprenotato`(  
     `NumeroDiPosto` ,
  `PrenotazioneAssociata`,
  `EtaPasseggero`,
  `NomePasseggero`,
  `CognomePasseggero`)
VALUES('3','2','22','Lucrezia', 'Di Nardo');
INSERT INTO `tripdb`.`postoprenotato`(  
     `NumeroDiPosto` ,
  `PrenotazioneAssociata`,
  `EtaPasseggero`,
  `NomePasseggero`,
  `CognomePasseggero`)
VALUES('1','2','23', 'Micaela', 'Ciani');
INSERT INTO `tripdb`.`postoprenotato`(  
     `NumeroDiPosto` ,
  `PrenotazioneAssociata`,
  `EtaPasseggero`,
  `NomePasseggero`,
  `CognomePasseggero`)
VALUES('2','3','25', 'Giovanni', 'Caporali');
INSERT INTO `tripdb`.`postoprenotato`(  
     `NumeroDiPosto` ,
  `PrenotazioneAssociata`,
  `EtaPasseggero`,
  `NomePasseggero`,
  `CognomePasseggero`)
VALUES('3','3','24','Simone', 'Gaetani');

DELETE FROM `tripdb`.`soggiorno`; 
INSERT INTO `tripdb`.`soggiorno`(
    `CameraPrenotata`,
    `Ospite`,
    `AlbergoInQuestione`,
    `PrenotazioneInQuestione`,
    `DataInizioSoggiorno`, 
    `DataFineSoggiorno`)
VALUES('1','1','3','1','2022-07-12','2022-07-12');
INSERT INTO `tripdb`.`soggiorno`(
    `CameraPrenotata`,
    `Ospite`,
    `AlbergoInQuestione`,
    `PrenotazioneInQuestione`,
    `DataInizioSoggiorno`, 
    `DataFineSoggiorno`)
VALUES('2','1', '3','1','2022-07-12','2022-07-12');
INSERT INTO `tripdb`.`soggiorno`(
    `CameraPrenotata`,
    `Ospite`,
    `AlbergoInQuestione`,
    `PrenotazioneInQuestione`, 
    `DataInizioSoggiorno`,
    `DataFineSoggiorno`)
VALUES('3','2','3','1','2022-07-12','2022-07-12');
INSERT INTO `tripdb`.`soggiorno`(
    `CameraPrenotata`,
    `Ospite`,
    `AlbergoInQuestione`,
    `PrenotazioneInQuestione`,
    `DataInizioSoggiorno`, 
    `DataFineSoggiorno`)
VALUES('1','3','3','2','2022-07-12','2022-07-12');
INSERT INTO `tripdb`.`soggiorno`(
    `CameraPrenotata`,
    `Ospite`,
    `AlbergoInQuestione`,
    `PrenotazioneInQuestione`,
    `DataInizioSoggiorno`, 
    `DataFineSoggiorno`)
VALUES('2','2','6','2','2022-07-12','2022-07-12');
INSERT INTO `tripdb`.`soggiorno`(
    `CameraPrenotata`,
    `Ospite`,
    `AlbergoInQuestione`,
    `PrenotazioneInQuestione`,
    `DataInizioSoggiorno`, 
    `DataFineSoggiorno`)
VALUES('3','3','6','3','2022-07-12','2022-07-12');

DELETE FROM `tripdb`.`competenze`; 
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('AXA','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('DAXA','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('RAXA','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('RAXA','mch1@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('AXA','mch1@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('DAXA','mch1@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('HONDA','mch1@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('HONDA','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('IVECO','mch1@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('IVECO','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('SCANIA','mch1@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('SCANIA','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('SCANIA','mch2@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('MERCEDES','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('MERCEDES','mch1@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('FORD','mch@mail.com');
INSERT INTO `tripdb`.`competenze`(
`CompetenzeModello`,
`MeccanicoCompetente`)
VALUES('FORD','mch1@mail.com');
update modello 
set NumeroMeccaniciCompetenti = 2
where NomeModello = 'AXA'; 
update modello 
set NumeroMeccaniciCompetenti = 2
where NomeModello = 'DAXA'; 
update modello 
set NumeroMeccaniciCompetenti = 2
where NomeModello = 'RAXA'; 
update modello 
set NumeroMeccaniciCompetenti = 2
where NomeModello = 'HONDA'; 
update modello 
set NumeroMeccaniciCompetenti = 3
where NomeModello = 'SCANIA'; 
update modello 
set NumeroMeccaniciCompetenti = 2
where NomeModello = 'IVECO'; 
update modello 
set NumeroMeccaniciCompetenti = 2
where NomeModello = 'MERCEDES'; 
update modello 
set NumeroMeccaniciCompetenti = 2
where NomeModello = 'FORD'; 

DELETE FROM `tripdb`.`tagliando`; 
INSERT INTO `tripdb`.`tagliando`(`TipologiaTagliando`, `ValiditaSuperate`)
VALUES('Luci','tutte');
INSERT INTO `tripdb`.`tagliando`(`TipologiaTagliando`, `ValiditaSuperate`)
VALUES('Gomme','alcune');
INSERT INTO `tripdb`.`tagliando`(`TipologiaTagliando`, `ValiditaSuperate`)
VALUES('Freni','nessuna');




 
grant execute on procedure tripdb.login to 'Cliente'@'localhost'; 

grant execute on procedure
tripdb.select_all_tour
to 'Cliente'@'localhost'; 

grant execute on procedure
tripdb.select_dest_tour
to'Cliente'@'localhost'; 	

grant execute on procedure
tripdb.select_hotel_service
to 'Cliente'@'localhost'; 

grant execute on procedure
tripdb.select_model_comfort
to 'Cliente'@'localhost';  

flush privileges; grant execute on procedure tripdb.login to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_bus
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_assigned_trip 
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_dest_time	
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.update_km 
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_dvr_map 
to 'Autista'@'localhost';

flush privileges; grant execute on procedure tripdb.login to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 
insert_costumer_user
to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 
insert_costumer
to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 
insert_reservation 
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
select_reservation_info
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
insert_seat
to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 			
insert_stay
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb. 
select_trip 
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
select_costumer
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb.    
select_reservation
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 		
validate_reservation 
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
delete_trip 
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb. 	  
delete_costumer 
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb. 
delete_reservation 
to 'Hostess'@'localhost';

flush privileges; grant execute on procedure tripdb.login TO 'Login'@'localhost';
grant select on tripdb.utente to 'Login'@'localhost'; 

flush privileges; 
grant execute on procedure tripdb.login to 'Meccanico'@'localhost'; 

grant execute on procedure 
tripdb.insert_review 
to 'Meccanico'@'localhost';

grant execute on procedure 
tripdb.insert_sostitution 
to 'Meccanico'@'localhost'; 	

grant execute on procedure 
tripdb.select_review 
to 'Meccanico'@'localhost'; 	  

grant execute on procedure 
tripdb.select_sparepart 
to 'Meccanico'@'localhost';

grant execute on procedure 
tripdb.delete_review 
to 'Meccanico'@'localhost';

grant execute on procedure 
tripdb.delete_sparepart 
to 'Meccanico'@'localhost';   

grant execute on procedure 
tripdb.select_expired_review 
to 'Meccanico'@'localhost'; 

grant execute on procedure 
tripdb.insert_sost_review 
to 'Meccanico'@'localhost'; 


flush privileges; 
grant execute on procedure tripdb. delete_tour to 'Manager'@'localhost';                              	 	 
grant execute on procedure tripdb. delete_trip to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_destination to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. delete_visit to 'Manager'@'localhost';  		 
grant execute on procedure tripdb. delete_room to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_location to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. delete_map to 'Manager'@'localhost';   			  
grant execute on procedure tripdb. delete_picture to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_employee to 'Manager'@'localhost';   	  
grant execute on procedure tripdb. delete_user to 'Manager'@'localhost';   		  
grant execute on procedure tripdb. delete_ofr to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_service to 'Manager'@'localhost';   		  		 
grant execute on procedure tripdb. delete_fmo to 'Manager'@'localhost';  			 
grant execute on procedure tripdb. delete_fme to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. delete_model to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_bus to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. delete_sparepart to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. delete_certify to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_comfort to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_skills to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_costumer to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_reservation to 'Manager'@'localhost';  
grant execute on procedure tripdb. delete_seat to 'Manager'@'localhost';  		
grant execute on procedure tripdb. delete_stay to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_review to 'Manager'@'localhost';  
grant execute on procedure tripdb. delete_sostitution to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_presents to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_rt to 'Manager'@'localhost'; 

flush privileges; 
grant execute on procedure tripdb. login to 'Manager'@'localhost'; 



grant execute on procedure tripdb. insert_tour to 'Manager'@'localhost';                              	 	 
grant execute on procedure tripdb. insert_trip to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_destination to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. insert_visit to 'Manager'@'localhost';  		 
grant execute on procedure tripdb. insert_room to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_location to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. insert_map to 'Manager'@'localhost';   			  
grant execute on procedure tripdb. insert_picture to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_employee to 'Manager'@'localhost';   	  
grant execute on procedure tripdb. insert_user to 'Manager'@'localhost';   		  
grant execute on procedure tripdb. insert_offert to 'Manager'@'localhost'; 	 
grant execute on procedure tripdb. insert_service to 'Manager'@'localhost';   		 	 
grant execute on procedure tripdb. insert_fmo to 'Manager'@'localhost';  			 
grant execute on procedure tripdb. insert_fme to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. insert_model to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_bus to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. insert_sparepart to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. insert_certify to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_comfort to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_skills to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_costumer_user to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_costumer to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_reservation to 'Manager'@'localhost';  
grant execute on procedure tripdb. insert_seat to 'Manager'@'localhost';  		
grant execute on procedure tripdb. insert_stay to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_review to 'Manager'@'localhost';  
grant execute on procedure tripdb. insert_sostitution to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_presents to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_rt to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_sost_review to 'Manager'@'localhost';  

grant execute on procedure tripdb. validate_reservation to 'Manager'@'localhost'; 


flush privileges; 
	


grant execute on procedure tripdb. select_tour to 'Manager'@'localhost';                              	 	 
grant execute on procedure tripdb. select_trip to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_destination to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. select_visit to 'Manager'@'localhost';  		 
grant execute on procedure tripdb. select_room to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_location to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. select_map to 'Manager'@'localhost';   			  
grant execute on procedure tripdb. select_picture to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_employee to 'Manager'@'localhost';   	  
grant execute on procedure tripdb. select_user to 'Manager'@'localhost';   		  
grant execute on procedure tripdb. select_ofr to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_service to 'Manager'@'localhost';   		 	 
grant execute on procedure tripdb. select_fmo to 'Manager'@'localhost';  			 
grant execute on procedure tripdb. select_fme to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. select_model to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_bus to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. select_sparepart to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. select_certify to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_comfort to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_skills to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_costumer to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_reservation to 'Manager'@'localhost';  
grant execute on procedure tripdb. select_reservation_info to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_seat to 'Manager'@'localhost';  		
grant execute on procedure tripdb. select_stay to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_review to 'Manager'@'localhost';  
grant execute on procedure tripdb. select_sostitution  to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_presents to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_rt to 'Manager'@'localhost'; 


flush privileges; grant execute on procedure tripdb. update_user_type to 'Manager'@'localhost';    
grant execute on procedure tripdb. update_km to 'Manager'@'localhost';         
  

flush privileges; 
