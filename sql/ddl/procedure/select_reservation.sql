Create procedure if not exists `tripdb`.`select_reservation`(
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
END