create procedure if not exists `tripdb`.`insert_costumer`(
in eml varchar(45), 
in nom varchar(45),
in cog varchar(45),
in ind varchar(45), 
in cod varchar(45), 
in dat date, 
in rec varchar(45),
in fax varchar(45)
)
BEGIN
insert into cliente 
			(EmailCliente, 
             NomeCliente, 
             CognomeCLiente, 
             IndirizzoCliente, 
             CodiceFiscale, 
             DataDocumentazione, 
             RecapitoTelefonico, 
             Fax)
values
			(eml, 
             nom, 
             cog,
             ind, 
             cod, 
             dat, 
             rec,
             fax); 
END