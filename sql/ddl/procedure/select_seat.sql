create procedure if not exists `tripdb`.`select_seat`(
    in nmp int, 
    in prn int
)
begin
select
p.NomePasseggero,
p.CognomePasseggero,
p.EtaPasseggero
from postoprenotato as p
join prenotazione as r on p.PrenotazioneAssociata = r.NumeroDiPrenotazione
where p.NumeroDiPosto = nmp and p.PrenotazioneAssociata = prn; 
end