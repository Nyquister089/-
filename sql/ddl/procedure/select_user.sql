create procedure if not exists `tripdb`.`select_user`(
    in usr varchar(45)
)
begin
select 
u.Pswrd, 
u.TipoUtente
from  utente as u
Where u.EmailUtente = usr; 
end