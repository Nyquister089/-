create procedure if not exists `tripdb`.`insert_employee`(
 in dpn varchar(45),
 in tlf varchar(15),
 in nmd varchar(45),
 in cgm varchar(45),
 in mlp varchar(45)
)
begin
INSERT INTO dipendente ( 
     TipologiaDipendente , 
     TelefonoAziendale ,
      NomeDipendente , 
      CognomeDipendente,
      EmailDipendente) 
     VALUES ( 
        dpn,
        tlf,
        nmd,
        cgm,
        mlp);
end
