create trigger`tripdb`.`decrement_skills` after delete
on `competenze`
for each row
  update modello
  join competenze 
  set NumeroMeccaniciCompetenti = NumeroMeccaniciCompetenti - 1
  where NomeModello= OLD.CompetenzeModello;
create trigger `tripdb`.`decrement_sparepart` after insert 
on `sostituito`
for each row 
update ricambio
join sostituito
set QuantitaMagazzino = QuantitaMagazzino-NEW.QuantitàSostituita
where Codice = NEW.CodiceRicambioSostituito; create trigger`tripdb`.`increment_skills` after insert
on `competenze`
for each row
  update modello
  join competenze
  set NumeroMeccaniciCompetenti = NumeroMeccaniciCompetenti+1
  where NomeModello = NEW.CompetenzeModello and NumeroMeccaniciCompetenti>='2';
create trigger`tripdb`.`update_data_doc_trigger` after insert
on `prenotazione`
for each row
update cliente
join prenotazione 
set DataDocumentazione = curdate()
where EmailCliente = NEW.ClientePrenotante; create trigger `tripdb`.`update_km_after_review` after insert 
on `revisione`
for each row 
update mezzo
join revisione 
set ValoreContaKm = NEW.Chilometraggio
where targa = NEW.MezzoRevisionato; create trigger `tripdb`.`update_tripseat` after insert 
on `prenotazione`
for each row 
update viaggio
join prenotazione
set PostiDisponibili = PostiDisponibili - new.NumeroDiPostiPrenotati
where idviaggio = NEW.ViaggioAssociato; 