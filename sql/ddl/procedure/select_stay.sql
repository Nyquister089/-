create PROCEDURE if not exists `tripdb`.`select_stay`(
in ids int

)
begin
select
s.Ospite,
s.AlbergoInQuestione,
s.CameraPrenotata,
s.PrenotazioneInQuestione,
s.DataInizioSoggiorno,
s.DataFineSoggiorno
from soggiorno as s 
where s.IdSoggiorno = ids;  
END

