Create procedure if not exists `tripdb`.`select_assigned_trip`(
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
join dipendente as d on v.IdConducente = d.EmailDipendente
where v.DataPartenzaViaggio > curdate() and d.EmailDipendente = dvr; 
END