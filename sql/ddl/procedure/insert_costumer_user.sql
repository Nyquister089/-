create procedure if not exists  `tripdb`.`insert_costumer_user`(
    in eml varchar(45),
    in psw varchar(8)
)
begin
INSERT INTO utente 
( EmailUtente ,
   Pswrd ,
   TipoUtente )
 VALUES 
 (eml,
  psw, 
  '2');
  end; 