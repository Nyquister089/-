grant execute on procedure tripdb.login to 'Meccanico'@'localhost'; 

grant execute on procedure 
tripdb.insert_review 
to 'Meccanico'@'localhost';

grant execute on procedure 
tripdb.insert_sostitution 
to 'Meccanico'@'localhost'; 	

grant execute on procedure 
tripdb.select_review 
to 'Meccanico'@'localhost'; 	  

grant execute on procedure 
tripdb.select_sparepart 
to 'Meccanico'@'localhost';

grant execute on procedure 
tripdb.delete_review 
to 'Meccanico'@'localhost';

grant execute on procedure 
tripdb.delete_sparepart 
to 'Meccanico'@'localhost';   

grant execute on procedure 
tripdb.select_expired_review 
to 'Meccanico'@'localhost'; 

grant execute on procedure 
tripdb.insert_sost_review 
to 'Meccanico'@'localhost'; 


flush privileges; 
