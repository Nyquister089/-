create trigger`tripdb`.`increment_skills` after insert
on `competenze`
for each row
  update dipendente
  join competenze
  set NumeroCompetenze = NumeroCompetenze+1
  where EmailDipendente = NEW.MeccanicoCompetente and NumeroCompetenze>='2';
