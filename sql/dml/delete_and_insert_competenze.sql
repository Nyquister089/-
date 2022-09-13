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