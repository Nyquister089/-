create procedure if not exists `tripdb`.`delete_skills`(
    in mcc varchar (45), 
    in cmp varchar (45)
)
begin
delete 
from competenze
where MeccanicoCompetente = mcc and CompetenzeModello = cmp; 
end