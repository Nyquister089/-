create trigger`tripdb`.`decrement_skills` after delete
on `competenze`
for each row
  update tripdb.dipendente
  set NumeroCompetenze = NumeroCompetenze - 1
  where IdDipendente= new.IdDipenedente;

/*
CREATE TRIGGER `tripdb`.`decrement_numero_competenze` 
ON tripdb.COMPETENZE FOR EACH ROW
BEGIN
  UPDATE tripdb.MECCANICI
  SET NUMERO_COMPETENZE = NUMERO_COMPETENZE - 1
  WHERE ID = NEW.ID;

  COMMIT;
END;*/