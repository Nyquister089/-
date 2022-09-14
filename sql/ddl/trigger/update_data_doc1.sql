create trigger`tripdb`.`update_data_doc_trigger1` after update
on `prenotazione`
for each row
update cliente
join prenotazione 
set DataDocumentazione = NEW.DataDiConferma
where EmailCliente = NEW.ClientePrenotante; 