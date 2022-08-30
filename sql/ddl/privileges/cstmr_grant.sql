grant execute on procedure tripdb.login to 'Cliente'@'localhost'; 

grant execute on procedure
tripdb.select_all_tour
to 'Cliente'@'localhost'; 

grant execute on procedure
tripdb.select_dest_tour
to'Cliente'@'localhost'; 	

grant execute on procedure
tripdb.select_hotel_service
to 'Cliente'@'localhost'; 

grant execute on procedure
tripdb.select_model_comfort
to 'Cliente'@'localhost';  

flush privileges; 