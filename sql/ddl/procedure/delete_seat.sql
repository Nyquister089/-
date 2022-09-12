create procedure if not exists `tripdb`.`delete_seat`(
    in prn int, 
    in nmp int
)
begin
delete 
from postoprenotato
where PrenotazioneAssociata = prn and NumeroDiPosto = nmp;  
end