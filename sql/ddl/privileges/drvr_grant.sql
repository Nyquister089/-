grant execute on procedure tripdb.login to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_bus
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_assigned_trip 
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_dest_time	
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.update_km 
to 'Autista'@'localhost';

grant execute on procedure 
tripdb.select_dvr_map 
to 'Autista'@'localhost';

flush privileges; 