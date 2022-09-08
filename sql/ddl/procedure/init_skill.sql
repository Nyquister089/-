create procedure if not exists `tripdb`.`init_skill`(
    in mcc varchar (45),
    in cmp1 varchar (45),
    in cmp2 varchar(45)


)
begin
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    cmp1,
    mcc
);
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    cmp2,
    mcc
);
update dipendente
set NumeroCompetenze = '2'
where EmailDipendente = mcc; 
end