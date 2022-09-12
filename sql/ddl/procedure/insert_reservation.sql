create procedure if not exists `tripdb`.`insert_reservation`( 
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
END