create trigger`tripdb`.`decrement_skills` after delete
on `competenze`
for each row
  update modello
  join competenze 
  set NumeroMeccaniciCompetenti = NumeroMeccaniciCompetenti - 1
  where NomeModello= OLD.CompetenzeModello;
