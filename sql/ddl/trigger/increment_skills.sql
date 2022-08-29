create trigger`tripdb`.`increment_skills` after insert
on `competenze`
for each row
  update dipendente
  join competenze
  set NumeroCompetenze = NumeroCompetenze+1
  where IdDipendente = MeccanicoCompetente;

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
  
end; 

5. Crea la procedure insert_skill_no_increment:
CREATE PROCEDURE IF NOT EXISTS `tripdb`.`insert_skill_no_increment` (
 in cmp varchar (45),
 in mcc int 
)
BEGIN
  
  UPDATE tripdb.meccanico SET NUMERO_COMPETENZE = NUMERO_COMPETENZE - 1 WHERE id = mcc;
  
  CALL `tripdb`.`insert_skills`(cmp,mcc);
END;
*/