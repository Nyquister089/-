create procedure if not exists `tripdb`.`select_map`(
in idm int
)
begin
select
m.Citta, 
m.RegioneInQuestione,
m.Dettaglio,
m.Zona,
m.ImmagineMappa
from mappa as m 
join localita as l on m.Citta = l.NomeLocalita 
where m.IdMappa = idm; 
end