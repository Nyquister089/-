Create procedure if not exists `tripdb`.`update_km`(
in trg varchar (10),
in vlk int
 )
BEGIN
    update mezzo as m
    set m.ValoreContaKm = vlk
    where m.targa = trg; 
END