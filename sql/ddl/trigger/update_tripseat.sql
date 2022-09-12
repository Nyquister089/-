create trigger `tripdb`.`update_tripseat` after insert 
on `prenotazione`
for each row 
update viaggio
join prenotazione
set PostiDisponibili = PostiDisponibili - new.NumeroDiPostiPrenotati
where idviaggio = NEW.ViaggioAssociato; 