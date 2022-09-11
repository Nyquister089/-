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
