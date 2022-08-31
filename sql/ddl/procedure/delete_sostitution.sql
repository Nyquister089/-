create procedure if not exists `tripdb`.`delete_sostitution` (
in cdc varchar(45), 
in rvs int
)
begin
delete 
from sostituito
where CodiceRicambioSostituito = cdc and RevisioneAssociata = rvs; 
end