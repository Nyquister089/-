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




 
