create PROCEDURE if not exists `tripdb`.`select_stay`(
in htl int, 
in cmp int, 
in spt int
)
begin
select
s.DataInizioSoggiorno,
s.DataFineSoggiorno
from soggiorno as s 
join meta as m on s.AlbergoInQuestione = m.IdMeta
join postoprenotato as p on s.Ospite = p.NumeroDiPosto
join camera as c on s.CameraPrenotata = c.NumeroCamera
where s.AlbergoInQuestione = htl and s.CameraPrenotata = cmp and s.Ospite =spt;  
END