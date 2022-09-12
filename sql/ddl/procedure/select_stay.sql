create PROCEDURE if not exists `tripdb`.`select_stay`(
in ids int

)
begin
select
m.NomeMeta,
/*p.NomePasseggero,*/
s.CameraPrenotata,
s.PrenotazioneInQuestione,
s.DataInizioSoggiorno,
s.DataFineSoggiorno
from soggiorno as s 
join meta as m on s.AlbergoInQuestione = m.IdMeta
join postoprenotato as p on s.Ospite = p.NumeroDiPosto and
 s.PrenotazioneInQuestione = p.PrenotazioneAssociata
join camera as c on s.CameraPrenotata = c.NumeroCamera and 
s.AlbergoInQuestione = c.IdAlbergo
where s.IdSoggiorno = ids;  
END

