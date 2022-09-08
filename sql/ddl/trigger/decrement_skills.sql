create trigger`tripdb`.`decrement_skills` after delete
on `competenze`
for each row
  update dipendente
  join competenze 
  set NumeroCompetenze = NumeroCompetenze - 1
  where EmailDipendente= OLD.MeccanicoCompetente;
