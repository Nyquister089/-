
create procedure if not exists `tripdb`.`insert_destination`(
    in lcl varchar(45), 
    in rgn varchar(45),
    in nmm varchar(45),
    in tlf varchar(15), 
    in mlm varchar(45),
    in fxm varchar(15),
    in ndr varchar(45),
    in tpl varchar(45),
    in ctg varchar(45),
    in opn time
)
begin
INSERT INTO meta(  
     LocalitaDiAppartenenza ,
     RegioneDiAppartenenza, 
     NomeMeta , 
     TelefonoMeta , 
     EmailMeta ,
     FaxMeta , 
     Indirizzo , 
     TipologiaMeta , 
     CategoriaAlbergo , 
     OrarioDiApertura ) 
    VALUES (
     lcl,
     rgn,
     nmm,
     tlf, 
     mlm,
     fxm,
     ndr,
     tpl,
     ctg,
     opn);
     end