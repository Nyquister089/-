create trigger`tripdb`.`update_data_doc_trigger` after insert
on `prenotazione`
for each row
update cliente
join prenotazione 
set DataDocumentazione = curdate()
where EmailCliente = NEW.ClientePrenotante; 