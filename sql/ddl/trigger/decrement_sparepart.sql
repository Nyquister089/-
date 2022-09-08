create trigger `tripdb`.`decrement_sparepart` after insert 
on `sostituito`
for each row 
update ricambio
join sostituito
set QuantitaMagazzino = QuantitaMagazzino-NEW.QuantitàSostituita
where Codice = NEW.CodiceRicambioSostituito; 