create procedure if not exists `tripdb`.`select_sostitution` (
in cdc varchar(45), 
in rvs int
)
begin
select QuantitàSostituita
from sostituito
where CodiceRicambioSostituito = cdc and RevisioneAssociata = rvs; 
end