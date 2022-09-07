create procedure if not exists `tripdb`.`delete_stay`(
    in htl int,
    in cmp int,
    in spt int
    
)
begin
delete 
from soggiorno
where CameraPrenotata = cmp and Ospite = spt and AlbergoInQuestione = htl; 
end