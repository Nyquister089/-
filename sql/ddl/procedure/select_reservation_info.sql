Create procedure if not exists `tripdb`.`select_reservation_info`(
    in mlc varchar(45)
    )
BEGIN
SELECT
 p.ClientePrenotante, 
 p.DataDiPrenotazione

FROM prenotazione as p
JOIN cliente as c on p.ClientePrenotante = c.EmailCliente
WHERE p.ClientePrenotante = c.EmailCliente; 
END