create procedure if not exists  `tripdb`.`insert_costumer_user`(
    in eml varchar(45),
    in nom varchar(45),
    in cog varchar(45),
    in ind varchar(45), 
    in cod varchar(45), 
    in dat date, 
    in rec varchar(45),
    in fax varchar(45),
    in psw varchar(8)
)
begin

declare count_user int default 0; 
declare count_costumer int default 0; 

declare exit handler for sqlexception
	begin
    rollback;
	  resignal; 
  end;
set transaction isolation level repeatable read;
start transaction;

INSERT INTO utente 
( EmailUtente ,
   Pswrd ,
   TipoUtente )
 VALUES 
 (eml,
  psw, 
  '2');

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

select COUNT(1) 
into count_user
from utente
where EmailUtente = eml;

select COUNT(1) 
into count_costumer
from cliente
where EmailCliente = eml;

if(count_costumer <> 1 OR count_user <> 1) 
then signal sqlstate '45001' 
set message_text = "Errore nell'inserimento delle competenze";
end if;
commit;
end

/*Questa transazione viene implementata per evitare di perdere informazioni a seguito dell'iserimento di un utente e di un cliente da parte di un hostess*/

