create procedure if not exists `tripdb`.`delete_stay`(
    in ids int
    
)
begin
delete 
from soggiorno
where IdSoggiorno = ids; 
end