create procedure if not exists `tripdb`.`select_model`(
    in nmd varchar(45)
)
begin
select 
m.CasaCostruttrice,
m.DatiTecnici,
m.NumeroPosti,
m.NumeroMeccaniciCompetenti
from modello as m 
where m.NomeModello = nmd; 
end