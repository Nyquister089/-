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
update dipendente
set NumeroCompetenze = '3'
where EmailDipendente = 'mch@mail.com';