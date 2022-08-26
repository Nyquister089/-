create procedure if not exists `tripdb`.`update_user_type` (
    in sml varchar (45),
    in tpl int 

)
begin 
update utente 
set TipoUtente = tpl 
where EmailUtente = sml; 
end