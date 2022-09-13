create trigger`tripdb`.`increment_skills` after insert
on `competenze`
for each row
  update modello
  join competenze
  set NumeroMeccaniciCompetenti = NumeroMeccaniciCompetenti+1
  where NomeModello = NEW.CompetenzeModello and NumeroMeccaniciCompetenti>='2';
