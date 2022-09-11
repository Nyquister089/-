create procedure if not exists `tripdb`.`insert_map`(
    in ctt varchar(45), 
    in rgn varchar(45),
    in dtg varchar(45),
    in zna varchar(45), 
    in mgn blob
)
begin
INSERT INTO mappa  
(
   Citta ,
   RegioneInQuestione,
   Dettaglio ,
   Zona,
   ImmagineMappa)
   VALUES (
    ctt,
    rgn, 
    dtg,
    zna,
    mgn);
end; 