create procedure if not exists `tripdb`.`insert_model`(
    in nmd varchar(45),
    in dtt varchar(5000),
    in csc varchar(45),
    in nmp int,
    in mch1 varchar (45),
    in mch2 varchar(45)
)
begin

declare count_mech_per_model int default 0;
declare exit handler for sqlexception
	begin
    rollback;
	resignal; 
    end;

set transaction isolation level repeatable read;
start transaction;

INSERT INTO  modello  ( 
    NomeModello ,
    DatiTecnici ,  
    CasaCostruttrice ,  
    NumeroPosti ) 
VALUES (
    nmd, 
    dtt,
    csc,
    nmp
    );
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    nmd,
    mch1
);
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    nmd,
    mch2
);

update modello
set NumeroMeccaniciCompetenti = '2'
where NomeModello = nmd; 

select COUNT(1) 
into count_mech_per_model 
from competenze 
where CompetenzeModello = nmd;

if(count_mech_per_model <> 2) 
then signal sqlstate '45001' 
set message_text = "Errore nell'inserimento delle competenze";
end if;



commit;
end
/*All'inserimento di un modello devono essere associati almeno due meccanici, 
questa transazione previene che venga inserito un solo meccanico competente in caso il secondo inserimento fallisca */