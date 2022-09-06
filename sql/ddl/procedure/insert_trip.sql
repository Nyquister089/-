create procedure if not exists `tripdb`.`insert_trip`(
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
     end