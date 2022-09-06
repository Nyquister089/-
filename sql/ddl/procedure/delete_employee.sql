create procedure if not exists `tripdb`.`delete_employee`(
    in mdp varchar (45)
)
begin 
delete 
from dipendente
where EmailDipendente = mdp;   
end