Create procedure if not exists `tripdb`.`update_data_doc`(
    IN cli NVARCHAR (45),
    IN dat DATE )
BEGIN
UPDATE cliente AS c
SET c.DataDocumentazione = dat
WHERE c.EmailCliente = cli; 
END