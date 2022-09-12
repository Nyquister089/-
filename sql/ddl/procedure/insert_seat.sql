Create procedure if not exists `tripdb`.`insert_seat`(
in num int, 
in pre int, 
in eta int , 
in nom varchar(45),
in cgn varchar(45)
)
BEGIN
insert into postoprenotato 
			(NumeroDiPosto, 
             PrenotazioneAssociata, 
             EtaPasseggero, 
             NomePasseggero,
             CognomePasseggero)
values
			(num, 
             pre,
             eta, 
             nom,
             cgn
             ); 
END