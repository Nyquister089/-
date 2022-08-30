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