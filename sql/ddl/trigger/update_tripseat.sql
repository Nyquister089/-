create trigger `tripdb`.`update_tripseat` after insert 
on `postoprenotato`
for each row 
update viaggio
join postoprenotato
set PostiDisponibili = PostiDisponibili -1
where idviaggio = NEW.ViaggioAssociato; 