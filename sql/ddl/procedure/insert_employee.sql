create procedure if not exists `tripdb`.`insert_employee`(
 in dpn varchar(45),
 in tlf varchar(15),
 in nmd varchar(45),
 in cgm varchar(45),
 in mlp varchar(45)
 
)
begin
  declare n_cmp int; 
  if dpn = 'Meccanico' or dpn = 'meccanico' then 
    set n_cmp = 0;
  else 
    set n_cmp = null; 
  end if; 

INSERT INTO dipendente ( 
     TipologiaDipendente , 
     TelefonoAziendale ,
      NomeDipendente , 
      CognomeDipendente,
      EmailDipendente,  
      NumeroCompetenze) 
     VALUES ( 
        dpn,
        tlf,
        nmd,
        cgm,
        mlp,
		    n_cmp);
end

/*
4. Modifica la procedure insert_employee:
create procedure if not exists `tripdb`.`insert_employee`(
 in dpn varchar(45),
 in tlf varchar(15),
 in nmd varchar(45),
 in cgm varchar(45)
)
begin
  DECLARE INIT_NUMERO_COMPETENZE INT DEFAULT 0;
  
  INIT_NUMERO_COMPETENZE = IF(dpn='Meccanico',2,0);

INSERT INTO dipendente ( 
     TipologiaDipendente , 
     TelefonoAziendale ,
      NomeDipendente , 
      CognomeDipendente, 
    NUMERO_COMPETENZE) 
     VALUES ( 
        dpn,
        tlf,
        nmd,
        cgm,
    INIT_NUMERO_COMPETENZE);
  
end; */