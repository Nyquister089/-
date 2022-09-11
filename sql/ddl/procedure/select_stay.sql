create PROCEDURE if not exists `tripdb`.`select_stay`(
in ids int

)
begin
select
m.NomeMeta,
p.NomePasseggero,
s.ViaggioInQuestione,
s.CameraPrenotata,
s.DataInizioSoggiorno,
s.DataFineSoggiorno
from soggiorno as s 
join meta as m on s.AlbergoInQuestione = m.IdMeta
join postoprenotato as p on s.Ospite = p.NumeroDiPosto
join camera as c on s.CameraPrenotata = c.NumeroCamera
join viaggio as v on p.ViaggioAssociato = v.IdViaggio
where s.IdSoggiorno = ids;  
END

