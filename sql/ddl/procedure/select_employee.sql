CREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_employee`(
    IN mld varchar(45)
    )
BEGIN
     SELECT  
    NomeDipendente, 
    CognomeDipendente,
    TipologiaDipendente, 
    TelefonoAziendale

FROM dipendente
    WHERE EmailDipendente = mld;
END;