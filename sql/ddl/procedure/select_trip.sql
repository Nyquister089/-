create procedure if not exists `tripdb`.`select_trip`(
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

END