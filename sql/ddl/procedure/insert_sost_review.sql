create procedure if not exists `tripdb`.`insert_sost_review`(
in mzr varchar(45),
in mch varchar(45),
in dnz date, 
in dfn date,
in clm int, 
in cnt varchar(1000),
in mtv varchar(1000),
in rcm varchar(45), 
in qnt int
)begin 

declare max_id_review int default 0; 
declare count_sost_per_review int default 0;

declare exit handler for sqlexception
	begin
    rollback;
	  resignal; 
  end;
set transaction isolation level repeatable read;
start transaction;

insert into revisione (
   MezzoRevisionato,
   AddettoAllaRevisione,
   DataInizio,
   DataFine,
   Chilometraggio,
   ControlliEffettuati,
   Motivazione 
  )
values(
	mzr,
  mch,
	dnz, 
	dfn,
	clm, 
	cnt,
	mtv
); 

select max(IdRevisione)
into max_id_review
from revisione;

insert into sostituito 
			      (RevisioneAssociata,
             CodiceRicambioSostituito,
             QuantitàSostituita)
values
			      (max_id_review, 
             rcm,
             qnt
             ); 



select COUNT(1) 
into count_sost_per_review 
from sostituito 
where RevisioneAssociata = max_id_review;

if(count_sost_per_review <> 1) 
then signal sqlstate '45001' 
set message_text = "Errore nell'inserimento delle competenze";
end if;
commit;

end

/* Questa transazione viene implementata per garantire che al fallimento dell'insermento di una revisione l'eventuale sostituzione non venga associata*/