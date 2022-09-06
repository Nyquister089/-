create procedure if not exists `tripdb`.`delete_user`(
    in usr varchar(45)
)
begin
delete 
from utente
where EmailUtente = usr;  
end