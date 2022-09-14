create procedure if not exists `tripdb`.`delete_bus`(
    in trg varchar (10)
)
begin
delete 
from mezzo
where Targa = trg;  
end
create procedure if not exists `tripdb`.`delete_certify`(
    in idt int
)
begin
delete
from tagliando
where IdTagliando = idt; 
endcreate procedure if not exists `tripdb`.`delete_comfort`(
    in idc int
)
begin
delete 
from comfort
where  IdComfort = idc; 
endcreate procedure if not exists `tripdb`.`delete_costumer`(
    in mlc varchar(45)
)
begin
delete 
from cliente
where EmailCliente= mlc;  
endcreate procedure if not exists `tripdb`.`delete_destination`(
    in idm int
)
begin
delete
from meta 
where IdMeta = idm;
endcreate procedure if not exists `tripdb`.`delete_employee`(
    in mdp varchar (45)
)
begin 
delete 
from dipendente
where EmailDipendente = mdp;   
endcreate procedure if not exists `tripdb`.`delete_fme`(
    in ftm int, 
    in mtr int
)
begin
delete 
from fme
where FotoMeta= ftm and MetaRappresentata =mtr;  
endcreate procedure if not exists `tripdb`.`delete_fmo`(
    in ftm int,
    in mdr varchar (45)
)
begin
delete 
from fmo
where FotoModello = ftm and ModelloRappresentato =mdr;  
endcreate procedure if not exists `tripdb`.`delete_location`(
    in nm varchar (45),
    in rgn varchar (45)
)
begin
delete 
from localita
where NomeLocalita = nm and Regione =rgn; 
endcreate procedure if not exists `tripdb`.`delete_map`(
    in idm int
)
begin
delete 
from mappa
where IdMappa = idm ;  
endcreate procedure if not exists `tripdb`.`delete_model`(
    in nmd varchar (45)
)
begin
delete
from modello
where NomeModello = nmd; 
end create procedure if not exists `tripdb`.`delete_ofr`(
    in htl int,
    in srv int
)
begin 
delete 
from offre
where AlbergoOfferente = htl and ServizioOfferto = srv;  
endcreate procedure if not exists `tripdb`.`delete_picture`(
    in idf int
)
begin
delete 
from documentazionefotografica
where idDocumentazioneFotografica = idf ;  
endcreate procedure if not exists `tripdb`.`delete_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
delete
from presenti
where ModelloAssociato = mdl and ComfortPresenti =cmf; 
endcreate procedure if not exists `tripdb`.`delete_reservation`(
    in nmp int
)
begin
delete 
from prenotazione
where NumeroDiPrenotazione = nmp;  
endcreate procedure if not exists `tripdb`.`delete_review`(
    in idr int
)
begin
delete 
from revisione
where IdRevisione = idr;  
endcreate procedure if not exists `tripdb`.`delete_room`(
    in nmc int,
    in htl int
)
begin
delete 
from camera
where NumeroCamera = nmc and IdAlbergo = htl; 
endcreate procedure if not exists `tripdb`.`delete_rt`(
    in rvs int,
    in tgl int
)
begin
delete
from rt
where TagliandoAssociato = rvs and RevisioneRelativa = tgl; 
endcreate procedure if not exists `tripdb`.`delete_seat`(
    in prn int, 
    in nmp int
)
begin
delete 
from postoprenotato
where PrenotazioneAssociata = prn and NumeroDiPosto = nmp;  
endcreate procedure if not exists `tripdb`.`delete_service`(
    in ids int
)
begin
delete 
from servizio
where  IdServizio = ids; 
endcreate procedure if not exists `tripdb`.`delete_skills`(
    in mcc varchar (45), 
    in cmp varchar (45)
)
begin
delete 
from competenze
where MeccanicoCompetente = mcc and CompetenzeModello = cmp; 
endcreate procedure if not exists `tripdb`.`delete_sostitution` (
in cdc varchar(45), 
in rvs int
)
begin
delete 
from sostituito
where CodiceRicambioSostituito = cdc and RevisioneAssociata = rvs; 
endcreate procedure if not exists `tripdb`.`delete_sparepart`(
    in cdc varchar(45)
)
begin
delete 
from ricambio
where Codice = cdc;  
end
create procedure if not exists `tripdb`.`delete_stay`(
    in ids int
    
)
begin
delete 
from soggiorno
where IdSoggiorno = ids; 
endcreate procedure if not exists `tripdb`.`delete_tour`(
    in dnm varchar(45)
)
begin
delete 
from tour
where DenominazioneTour = dnm;  
end
create procedure if not exists `tripdb`.`delete_trip`(
    in idv int
)
begin
delete 
from viaggio
where idviaggio =idv; 
end
create procedure if not exists `tripdb`.`delete_user`(
    in usr varchar(45)
)
begin
delete 
from utente
where EmailUtente = usr;  
endcreate procedure if not exists `tripdb`.`delete_visit`(
    in idv int
)
begin
delete
from visita 
where idvisita = idv; 
end
DROP PROCEDURE IF EXISTS `tripdb`.`login`;
DROP PROCEDURE IF EXISTS `tripdb`.`insert_assoc`;
DROP PROCEDURE IF EXISTS `tripdb`.`insert_costumer`;
DROP PROCEDURE IF EXISTS `tripdb`.`insert_reservation`;
DROP PROCEDURE IF EXISTS `tripdb`.`insert_seat`;
DROP PROCEDURE IF EXISTS `tripdb`.`select_costumer`;
DROP PROCEDURE IF EXISTS `tripdb`.`select_reservation`;
DROP PROCEDURE IF EXISTS `tripdb`.`select_trip`;
DROP PROCEDURE IF EXISTS `tripdb`.`update_data_doc`;
DROP PROCEDURE IF EXISTS `tripdb`.`update_trip_seat`;
DROP PROCEDURE IF EXISTS `tripdb`.`validate_reservation`;
create procedure if not exists `tripdb`.`insert_bus`(
    in trg varchar (45),
    in mdm varchar (45),
    in ngb varchar (45),
    in tnm int,
    in ckm int, 
    in dtr date,
    in dtm date
)

INSERT INTO mezzo(
   Targa  ,
   ModelloMezzo ,
   DataRevisioneMotorizzazione ,
   Autonomia ,
   ValoreContaKm ,
   Ingombri ,
   DataImmatricolazione ) 
VALUES(
    trg,
    mdm,
    dtr,
    tnm,
    ckm,
    ngb,
    dtm)create procedure if not exists `tripdb`.`insert_certify`(
    in tpl varchar (45),
    in vld varchar (5000)
)
begin
INSERT INTO tagliando ( 
    TipologiaTagliando ,  
    ValiditaSuperate )
VALUES(
    tpl,
    vld);
endcreate procedure if not exists `tripdb`.`insert_comfort`(
    in nmc varchar (45),
    in dsc varchar (45)
)
begin
INSERT INTO comfort  ( 
    NomeComfort ,  
    DescrizioneComfort ) 
VALUES (
    nmc,
    dsc
);
end
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
ENDcreate procedure if not exists  `tripdb`.`insert_costumer_user`(
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
create procedure if not exists `tripdb`.`insert_destination`(
    in lcl varchar(45), 
    in rgn varchar(45),
    in nmm varchar(45),
    in tlf varchar(15), 
    in mlm varchar(45),
    in fxm varchar(15),
    in ndr varchar(45),
    in tpl varchar(45),
    in ctg varchar(45),
    in opn time
)
begin
INSERT INTO meta(  
     LocalitaDiAppartenenza ,
     RegioneDiAppartenenza, 
     NomeMeta , 
     TelefonoMeta , 
     EmailMeta ,
     FaxMeta , 
     Indirizzo , 
     TipologiaMeta , 
     CategoriaAlbergo , 
     OrarioDiApertura ) 
    VALUES (
     lcl,
     rgn,
     nmm,
     tlf, 
     mlm,
     fxm,
     ndr,
     tpl,
     ctg,
     opn);
     endcreate procedure if not exists `tripdb`.`insert_employee`(
 in dpn varchar(45),
 in tlf varchar(15),
 in nmd varchar(45),
 in cgm varchar(45),
 in mlp varchar(45)
)
begin
INSERT INTO dipendente ( 
     TipologiaDipendente , 
     TelefonoAziendale ,
      NomeDipendente , 
      CognomeDipendente,
      EmailDipendente) 
     VALUES ( 
        dpn,
        tlf,
        nmd,
        cgm,
        mlp);
end
create procedure if not exists `tripdb`.`insert_fme`(
    in mtr int, 
    in ftm int
)
begin

INSERT INTO  fme ( 
    MetaRappresentata, 
    FotoMeta )
VALUES(
    mtr,
    ftm);
endcreate procedure if not exists `tripdb`.`insert_fmo`(
    in fmd int, 
    in mdl varchar(45)
)
begin

INSERT INTO fmo(
    FotoModello,
    ModelloRappresentato)
VALUES(
    fmd,
    mdl);
endcreate procedure if not exists `tripdb`.`insert_location`(
    in nml varchar (45), 
    in rgn varchar (45),
    in stt varchar (45)
)
begin
INSERT INTO localita(  
    NomeLocalita , 
    Regione ,
    Stato ) 
 VALUES (
    nml, 
    rgn, 
    stt
 );
 end;
create procedure if not exists `tripdb`.`insert_map`(
    in ctt varchar(45), 
    in rgn varchar(45),
    in dtg varchar(45),
    in zna varchar(45), 
    in mgn blob
)
begin
INSERT INTO mappa  
(
   Citta ,
   RegioneInQuestione,
   Dettaglio ,
   Zona,
   ImmagineMappa)
   VALUES (
    ctt,
    rgn, 
    dtg,
    zna,
    mgn);
end; create procedure if not exists `tripdb`.`insert_model`(
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
questa transazione previene che venga inserito un solo meccanico competente in caso il secondo inserimento fallisca */create procedure if not exists `tripdb`.`insert_offert`(
    in srv int,
    in htl int
)
begin
INSERT INTO  offre  ( 
    ServizioOfferto, 
    AlbergoOfferente )
VALUES(
    srv,
    htl
);
end; create procedure if not exists `tripdb`.`insert_picture` (
    in dsf varchar(5000),
    in pct blob
)
begin
INSERT INTO documentazionefotografica (
    DescrizioneFoto,
    Immagine
    )
VALUES(
    dsf,
    pct
);
endcreate procedure if not exists `tripdb`.`insert_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
insert into presenti (
    ComfortPresenti, 
    ModelloAssociato
)
values (
    cmf, 
    mdl
); 
endcreate procedure if not exists `tripdb`.`insert_reservation`( 
 IN cli VARCHAR(45), 
 IN vgg int, 
 IN nmp int
 )
BEGIN
INSERT INTO prenotazione
			(ClientePrenotante,
			 ViaggioAssociato,
			 DataDiPrenotazione, 
			 NumeroDiPostiPrenotati
             )
		VALUES
			(cli,
			 vgg, 
			 curdate(),
             nmp
             );
ENDcreate procedure if not exists `tripdb`.`insert_review`(
in mzr varchar(45),
in mch varchar(45),
in dnz date, 
in dfn date,
in clm int, 
in cnt varchar(1000),
in tip varchar(45), 
in mtv varchar(1000)
)
BEGIN
insert into revisione (
   MezzoRevisionato,
   AddettoAllaRevisione,
   DataInizio,
   DataFine,
   Chilometraggio,
   ControlliEffettuati,
   TipologiaRevisione,
   Motivazione 
  )
values(
	mzr,
  mch,
	dnz, 
	dfn,
	clm, 
	cnt,
	tip, 
	mtv
); 
ENDcreate procedure if not exists `tripdb`.`insert_room`(
    in nmc int, 
    in htl int, 
    in tpl varchar(45),
    in cst decimal(8,2)
)  
begin
INSERT INTO camera(
    NumeroCamera , 
    IdAlbergo ,
    Tipologia ,
    Costo)
VALUES(
    nmc, 
    htl, 
    tpl,
    cst);
  endcreate procedure if not exists `tripdb`.`insert_rt`(
    in rvs int,
    in tgl int
)
begin
insert into rt (
    RevisioneRelativa, 
    TagliandoAssociato
)
values (
    rvs, 
    tgl
); 
endCreate procedure if not exists `tripdb`.`insert_seat`(
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
ENDcreate procedure if not exists `tripdb`.`insert_service`(
    in nms varchar (45),
    in dss varchar(5000)
)
begin
INSERT INTO servizio  (  
NomeServizio ,  
DescrizioneServizio )
 VALUES (
    nms,
    dss );
end
create procedure if not exists `tripdb`.`insert_skills`(
    in cmp varchar (45),
    in mcc varchar (45)
)
begin
INSERT INTO  competenze (
 CompetenzeModello ,
 MeccanicoCompetente )
VALUES(
    cmp,
    mcc
);
endcreate procedure if not exists `tripdb`.`insert_sostitution`(
in rvs int, 
in rcm varchar(45), 
in qnt int
)
BEGIN
insert into sostituito 
			(RevisioneAssociata,
             CodiceRicambioSostituito,
             QuantitàSostituita)
values
			(rvs, 
             rcm,
             qnt
             ); 
ENDcreate procedure if not exists `tripdb`.`insert_sost_review`(
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

/* Questa transazione viene implementata per garantire che al fallimento dell'insermento di una revisione l'eventuale sostituzione non venga associata*/create procedure if not exists `tripdb`.`insert_sparepart`(
    in cdc varchar (45),
    in cst int, 
    in qtr int,
    in dsc varchar (5000),
    in scm int, 
    in qtm int
)
begin
insert into ricambio (
   Codice ,
   CostoUnitario ,
   QuantitaDiRiordino ,
   Descrizione ,
   ScortaMinima ,
   QuantitaMagazzino )
  values(
    dsc,
    cst,
    qtr,
    dsc,
    scm,
    qtm); 
  end
CREATE PROCEDURE if not exists `tripdb`.`insert_stay`(
in cam int, 
in osp int, 
in alb int, 
in prn int, 
in dis date,
in dfs date
 )
BEGIN
insert into soggiorno 
			(CameraPrenotata, 
			 Ospite, 
             AlbergoInQuestione,
             PrenotazioneInQuestione,
             DataInizioSoggiorno, 
             DataFineSoggiorno)
values
			(cam,
             osp,
             alb,
             prn, 
             dis,
             dfs); 
ENDcreate procedure if not exists`tripdb`.`insert_tour`(
    in dnt varchar(45), 
    in dst varchar(5000), 
    in mnm int, 
    in mdc decimal(8,2),
    in bgl decimal(8,2),
    in gnl decimal(8,2),
    in hst tinyint
) 
begin
insert into tour(
    DenominazioneTour ,
    DescrizioneTour,
    Minimopartecipanti ,
    CostoAssicurazioneMedica ,
    CostoBagaglio ,
    CostoGaranziaAnnullamento ,
    Accompagnatrice)
values(
    dnt,
    dst,
    mnm,
    mdc,
    bgl,
    gnl,
    hst);
endcreate procedure if not exists `tripdb`.`insert_trip`(
    in tsc varchar(45), 
    in idc varchar(45), 
    in ida varchar(45), 
    in trg varchar (10), 
    in ddp date, 
    in ddr date, 
    in cst decimal (8,2), 
    in nkm int, 
    in pst int
 
)
begin
INSERT INTO viaggio
( TourAssociato ,
   Conducente ,
   Accompagnatrice ,
   TargaMezzoImpiegato ,
   DataPartenzaViaggio ,
   DataRitornoViaggio , 
   CostoDelViaggio ,
   NumeroKm ,
   PostiDisponibili )
VALUES
(    tsc, 
     idc, 
     ida, 
     trg, 
     ddp, 
     ddr, 
     cst, 
     nkm, 
     pst);
     endcreate procedure if not exists  `tripdb`.`insert_user`(
    in eml varchar(45),
    in psw varchar(8),
    in tpt varchar(45)
)
begin
INSERT INTO utente 
( EmailUtente ,
   Pswrd ,
   TipoUtente )
 VALUES 
 (eml,
  psw, 
  tpt);
  end; create procedure if not exists `tripdb`.`insert_visit`(
    in vgg int, 
    in mtv int, 
    in drr date, 
    in dpr date, 
    in orr time,
    in orp time, 
    in gui tinyint,
    in spl decimal(8,2),
    in trt varchar(45))
begin
INSERT INTO visita (
   ViaggioRelativo ,
   MetaVisitata ,
   DataArrivo ,
   DataPartenza ,
   OraArrivo ,
   OraPartenza ,
   Guida ,
   Supplemento ,
   Trattamento )
VALUES(
    vgg, 
    mtv, 
    drr, 
    dpr, 
    orr, 
    orp, 
    gui,
    spl,
    trt);
  endUSE `tripdb`; 
create procedure if not exists `tripdb`.`login`(
	IN usrn VARCHAR(45), 
    IN pass VARCHAR(8),
    OUT tip INT
)
BEGIN
    SET tip = -1;

	SELECT u.TipoUtente
    INTO tip
    FROM utente as u
    WHERE u.EmailUtente = usrn AND u.Pswrd = pass;
ENDcreate procedure if not exists  `tripdb`.`select_all_tour`(
 )
BEGIN
select distinct t.DenominazioneTour,
 t.DescrizioneTour,
 t.Minimopartecipanti, 
 t.CostoAssicurazioneMedica, 
 t.CostoBagaglio, 
 t.CostoGaranziaAnnullamento, 
 t.Accompagnatrice,
 mo.NomeModello, 
 v.DataPartenzaViaggio, 
 v.DataRitornoViaggio, 
 v.CostoDelViaggio, 
 v.PostiDisponibili,
 v.idviaggio
from tour as t
join viaggio as v on t.DenominazioneTour = v.TourAssociato
join mezzo as m on v.TargaMezzoImpiegato = m.Targa
join modello as mo on m.ModelloMezzo = mo.NomeModello
where v.DataPartenzaViaggio > curdate(); 
ENDCreate procedure if not exists `tripdb`.`select_assigned_trip`(
in dvr varchar(45)
 )
BEGIN
select distinct t.DenominazioneTour,
				v.idviaggio,
				mo.NomeModello, 
				m.Targa,
				m.Autonomia,
				m.Ingombri,
				m.ValoreContaKm,
				v.DataPartenzaViaggio, 
				v.DataRitornoViaggio 
from tour as t
join viaggio as v on t.DenominazioneTour = v.TourAssociato
join mezzo as m on v.TargaMezzoImpiegato = m.Targa
join modello as mo on m.ModelloMezzo = mo.NomeModello
join dipendente as d on v.Conducente = d.EmailDipendente
where v.DataPartenzaViaggio > curdate() and d.EmailDipendente = dvr; 
ENDCreate procedure if not exists `tripdb`.`select_bus`(
in trg varchar (10)
 )
BEGIN
select distinct 
  m.ModelloMezzo,
  m.DataRevisioneMotorizzazione,
  m.Autonomia,
  m.ValoreContaKm,
  m.Ingombri,
  m.DataImmatricolazione
from mezzo as m
join modello as mo on m.ModelloMezzo = mo.NomeModello
where m.Targa = trg; 
ENDcreate procedure if not exists `tripdb`.`select_certify`(
    in idt int
)
begin
select 
t.TipologiaTagliando,
t.ValiditaSuperate
from tagliando as t
where t.IdTagliando = idt; 
endcreate procedure if not exists `tripdb`.`select_comfort`(
in idc int
)
begin
select
c.NomeComfort,
c.DescrizioneComfort
from comfort as c
where c.IdComfort = idc; 
endcreate procedure if not exists `tripdb`.`select_costumer`(
IN eml VARCHAR(45)
)

BEGIN
SELECT	
	c.NomeCliente, 
    c.CognomeCliente, 
    c.IndirizzoCliente, 
    c.CodiceFiscale, 
    c.DataDocumentazione, 
    c.RecapitoTelefonico, 
	c.Fax
FROM cliente as c
WHERE c.EmailCliente = eml;

ENDcreate procedure if not exists `tripdb`.`select_destination`(
    in idm int
)
begin
select 
m.NomeMeta,
m.TipologiaMeta,  
m.LocalitaDiAppartenenza, 
m.RegioneDiAppartenenza,
m.Indirizzo,
m.TelefonoMeta,
m.EmailMeta, 
m.FaxMeta,
m.CategoriaAlbergo, 
m.OrarioDiApertura

from meta as m
join localita as l on m.LocalitaDiAppartenenza = l.NomeLocalita
where m.IdMeta = idm; 
endCreate procedure if not exists `tripdb`.`select_dest_time`(
in idv int)
BEGIN
select distinct
   m.NomeMeta,
   m.TipologiaMeta,
   l.NomeLocalita,
   l.Regione,
   m.Indirizzo,
   v.DataArrivo,
   v.OraArrivo,
   v.DataPartenza,
   v.OraPartenza
from visita as v
join meta as m on v.MetaVisitata = m.IdMeta
join viaggio as vi on v.ViaggioRelativo = vi.idviaggio
join localita as l on m.LocalitaDiAppartenenza = l.NomeLocalita
where vi.idviaggio = idv ;
END
Create procedure if not exists `tripdb`.`select_dest_tour`(
in idv int)
BEGIN
select distinct
   m.NomeMeta,
   v.DataArrivo,
   v.OraArrivo,
   v.DataPartenza,
   v.OraPartenza,
   v.Supplemento,
   m.TipologiaMeta,
   v.Guida,
   m.OrarioDiApertura,
   v.Trattamento,
   m.CategoriaAlbergo,
   d.DescrizioneFoto,
   d.Immagine, 
   m.IdMeta
   
   
from visita as v
join meta as m on v.MetaVisitata = m.IdMeta
join viaggio as vi on v.ViaggioRelativo = vi.idviaggio
join fme as f on m.IdMeta = f.MetaRappresentata
join documentazionefotografica as d on f.FotoMeta = d.idDocumentazioneFotografica
where v.ViaggioRelativo = idv;
ENDCREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_dvr_map`(
in lcl varchar(45)
)
BEGIN
SELECT distinct 
    m.Citta,
	m.Dettaglio,
    m.Zona,
    m.ImmagineMappa	
from mappa as m
join localita as l on m.Citta = l.NomeLocalita
join meta as me on l.NomeLocalita = me.LocalitaDiAppartenenza
where m.Citta = lcl;
END


CREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_employee`(
    IN mld varchar(45)
    )
BEGIN
     SELECT  
    NomeDipendente, 
    CognomeDipendente,
    TipologiaDipendente, 
    TelefonoAziendale

FROM dipendente
    WHERE EmailDipendente = mld;
END;

Create procedure if not exists `tripdb`.`select_expired_review`()
begin
select distinct 
m.Targa, 
r.DataFine, 
r.Chilometraggio,
m.ValoreContaKm
from  mezzo as m
join revisione as r on m.Targa = r.MezzoRevisionato
where (m.ValoreContaKm > r.Chilometraggio) and m.Targa 
not in (select m1.Targa
		from mezzo as m1
		join revisione as r1 on m1.Targa=r1.MezzoRevisionato
		where DATE_ADD(r1.DataFine, INTERVAL 1 YEAR) >= CURDATE()
		and (m1.ValoreContaKm - r1.Chilometraggio) < '38000'); 
endcreate procedure if not exists `tripdb`.`select_fme`
(   
    in fmt int,
    in mtr int
)
begin
select 
m.NomeMeta,
d.DescrizioneFoto,
d.Immagine

from fme as f
join meta as m on f.MetaRappresentata = m.IdMeta
join documentazionefotografica as d on f.FotoMeta = d.idDocumentazioneFotografica
where f.MetaRappresentata = mtr and f.FotoMeta = fmt; 
end
create procedure if not exists `tripdb`.`select_fmo` (
    in fml int, 
    in mdl Varchar(45)
)
begin
select 
	d.DescrizioneFoto,
	d.Immagine
       

    from fmo as f
    join documentazionefotografica as d on f.FotoModello = d.idDocumentazioneFotografica
    join modello as m on f.ModelloRappresentato = m.NomeModello
    WHERE f.FotoModello = fml  and m.NomeModello = mdl;
endcreate procedure if not exists `tripdb`.`select_hotel_service` (
in idh int )
BEGIN
	select 
			s.NomeServizio,
			s.DescrizioneServizio
	from servizio as s 
    join offre as o on s.IdServizio = o.ServizioOfferto
    join meta as m on o.AlbergoOfferente = m.IdMeta
    where IdMeta = idh and (TipologiaMeta = 'Albergo' or TipologiaMeta = 'albergo') ; 
END
create procedure if not exists `tripdb`. `select_location` (
    in nml varchar (45),
	in rgn varchar (45)
 )
begin
select 
	l.Stato
from localita as l 
where l.NomeLocalita = nml and l.Regione = rgn; 
endcreate procedure if not exists `tripdb`.`select_map`(
in idm int
)
begin
select
m.Citta, 
m.RegioneInQuestione,
m.Dettaglio,
m.Zona,
m.ImmagineMappa
from mappa as m 
join localita as l on m.Citta = l.NomeLocalita 
where m.IdMappa = idm; 
endCreate procedure if not exists `tripdb`.`select_model_comfort`(
in nmd varchar(45)
)
BEGIN
select distinct
	m.CasaCostruttrice,
	m.NumeroPosti,
	c.NomeComfort, 
	c.DescrizioneComfort,
	d.Immagine, 
	d.DescrizioneFoto,
    d.idDocumentazioneFotografica
from modello as m
join presenti as p on m.NomeModello = p.ModelloAssociato
join comfort as c on  p.ComfortPresenti = c.IdComfort
join fmo as f on m.NomeModello = f.ModelloRappresentato
join documentazionefotografica as d on f.FotoModello = d.idDocumentazioneFotografica
where m.NomeModello = nmd; 
ENDcreate procedure if not exists `tripdb`.`select_model`(
    in nmd varchar(45)
)
begin
select 
m.CasaCostruttrice,
m.DatiTecnici,
m.NumeroPosti,
m.NumeroMeccaniciCompetenti
from modello as m 
where m.NomeModello = nmd; 
endcreate procedure if not exists `tripdb`.`select_ofr` (
    in lbr int,
    in srv int 
)
begin
select 
m.NomeMeta,
s.NomeServizio,
s.DescrizioneServizio
from offre as o 
join meta as m on o.AlbergoOfferente = m.IdMeta
join servizio as s on o.ServizioOfferto = s.IdServizio
where o.AlbergoOfferente = lbr and o.ServizioOfferto = srv; 
endcreate procedure if not exists `tripdb`.`select_picture`(
in idf int
)
begin
select
d.Immagine, 
d.DescrizioneFoto
from documentazionefotografica as d
where d.idDocumentazioneFotografica = idf; 
endcreate procedure if not exists `tripdb`.`select_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
select
    ComfortPresenti, 
    ModelloAssociato
from presenti 
where ComfortPresenti = cmf and ModelloAssociato = mdl; 
endCreate procedure if not exists `tripdb`.`select_reservation_info`(
    in mlc varchar(45)
    )
BEGIN
SELECT
 p.NumeroDiPrenotazione, 
 p.DataDiPrenotazione

FROM prenotazione as p
JOIN cliente as c on p.ClientePrenotante = c.EmailCliente
WHERE p.ClientePrenotante = mlc; 
ENDCreate procedure if not exists `tripdb`.`select_reservation`(
    in npr int
    )
BEGIN
SELECT
 p.ClientePrenotante, 
 p.ViaggioAssociato, 
 p.NumeroDiPostiPrenotati,
 p.DataDiPrenotazione,
 p.DataDiConferma, 
 p.DataSaldo
FROM prenotazione as p
JOIN cliente as c on p.ClientePrenotante = c.EmailCliente
WHERE NumeroDiPrenotazione = npr;
ENDcreate procedure if not exists `tripdb`.`select_review`(
in idr int
)
BEGIN
SELECT  
   r.MezzoRevisionato,
   r.AddettoAllaRevisione, 
   r.DataInizio,
   r.DataFine,
   r.Chilometraggio,
   r.ControlliEffettuati,
   r.Motivazione 
FROM revisione as r
join mezzo as m on r.MezzoRevisionato = m.Targa
join dipendente as d on r.AddettoAllaRevisione = d.EmailDipendente
WHERE r.IdRevisione = idr; 
END
create procedure if not exists `tripdb`.`select_room`(
in nmc int, 
in htl int
)
begin
select
c.Tipologia, 
c.Costo
from camera as c
where c.NumeroCamera = nmc and c.IdAlbergo = htl;
end
create procedure if not exists `tripdb`.`select_rt`(
    in rvs int,
    in tgl int
)
begin
select 
     RevisioneRelativa, 
     TagliandoAssociato
from rt
where RevisioneRelativa = rvs and TagliandoAssociato = tgl; 
endcreate procedure if not exists `tripdb`.`select_seat`(
    in nmp int, 
    in prn int
)
begin
select
p.NomePasseggero,
p.CognomePasseggero,
p.EtaPasseggero
from postoprenotato as p
join prenotazione as r on p.PrenotazioneAssociata = r.NumeroDiPrenotazione
where p.NumeroDiPosto = nmp and p.PrenotazioneAssociata = prn; 
endcreate procedure if not exists `tripdb`.`select_service` (
in ids int
)
begin
select 
s.NomeServizio,
s.DescrizioneServizio
from servizio as s
where s.IdServizio = ids; 
endcreate procedure if not exists `tripdb`.`select_skills` (
in mch varchar(45), 
in mdl varchar(45)
)
begin
select
d.NomeDipendente,
d.TelefonoAziendale
from competenze as c
join dipendente as d on c.MeccanicoCompetente = d.EmailDipendente
join modello as m on c.CompetenzeModello = m.NomeModello
where c.CompetenzeModello = mdl and c.MeccanicoCompetente = mch;
end
create procedure if not exists `tripdb`.`select_sostitution` (
in cdc varchar(45), 
in rvs int
)
begin
select QuantitàSostituita
from sostituito
where CodiceRicambioSostituito = cdc and RevisioneAssociata = rvs; 
endcreate procedure if not exists `tripdb`.`select_sparepart`(
in cdc VARCHAR(45)
)
BEGIN
SELECT  
   r.CostoUnitario,
   r.QuantitaDiRiordino,
   r.Descrizione,
   r.ScortaMinima,
   r.QuantitaMagazzino
FROM ricambio as r
WHERE r.Codice = cdc; 
ENDcreate PROCEDURE if not exists `tripdb`.`select_stay`(
in ids int

)
begin
select
s.Ospite,
s.AlbergoInQuestione,
s.CameraPrenotata,
s.PrenotazioneInQuestione,
s.DataInizioSoggiorno,
s.DataFineSoggiorno
from soggiorno as s 
where s.IdSoggiorno = ids;  
END

create procedure if not exists `tripdb`.`select_tour`(
IN dnm VARCHAR(45)
)
BEGIN
SELECT 
    t.DescrizioneTour,
    t.Minimopartecipanti,
    t.CostoAssicurazioneMedica,
    t.CostoBagaglio,
    t.CostoGaranziaAnnullamento,
    t.Accompagnatrice  
FROM tour as t
WHERE t.DenominazioneTour = dnm;
ENDcreate procedure if not exists `tripdb`.`select_trip`(
IN trip INT
  )
BEGIN


SELECT 
	v.TourAssociato,
	v.Conducente,
    v.Accompagnatrice, 
	v.TargaMezzoImpiegato, 
	v.DataPartenzaViaggio,
    v.DataRitornoViaggio, 
	v.CostoDelViaggio,
	v.NumeroKm, 
	v.PostiDisponibili, 
	v.DataCancellazione

FROM viaggio as v
JOIN dipendente as d on v.Conducente = d.EmailDipendente 
JOIN dipendente as d1 on v.Accompagnatrice = d1.EmailDipendente
JOIN mezzo as m on v.TargaMezzoImpiegato = m.Targa
JOIN tour as t on v.TourAssociato = t.DenominazioneTour
WHERE v.IdViaggio = trip; 

ENDcreate procedure if not exists `tripdb`.`select_user`(
    in usr varchar(45)
)
begin
select 
u.Pswrd, 
u.TipoUtente
from  utente as u
Where u.EmailUtente = usr; 
endcreate procedure if not exists `tripdb`.`select_visit`(
    in idv int
)
begin
select 
t.DenominazioneTour,
v.ViaggioRelativo,
m.NomeMeta,
v.MetaVisitata,
v.DataArrivo,  
v.OraArrivo,
v.DataPartenza,
v.OraPartenza, 
v.Guida,
v.Supplemento, 
v.Trattamento

from visita as v
join viaggio as via on v.ViaggioRelativo = via.idviaggio
join meta as m on v.MetaVisitata = m.IdMeta
join tour as t on via.TourAssociato = t.DenominazioneTour

where v.idvisita = idv; 
endCreate procedure if not exists `tripdb`.`update_km`(
in trg varchar (10),
in vlk int
 )
BEGIN
    update mezzo as m
    set m.ValoreContaKm = vlk
    where m.targa = trg; 
ENDcreate procedure if not exists `tripdb`.`update_user_type` (
    in sml varchar (45),
    in tpl int 

)
begin 
update utente 
set TipoUtente = tpl 
where EmailUtente = sml; 
endCreate procedure if not exists `tripdb`.`validate_reservation`(
IN ndp INT, 
IN ddc DATE, 
IN dds DATE)
BEGIN 
UPDATE prenotazione AS p
SET p.DataDiConferma = ddc, 
    p.DataSaldo = dds
WHERE p.NumeroDiPrenotazione = ndp; 

END