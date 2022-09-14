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

flush privileges; grant execute on procedure tripdb.login to 'Autista'@'localhost';

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

flush privileges; grant execute on procedure tripdb.login to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 
insert_costumer_user
to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 
insert_costumer
to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 
insert_reservation 
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
select_reservation_info
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
insert_seat
to 'Hostess'@'localhost'; 

grant execute on procedure
tripdb. 			
insert_stay
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb. 
select_trip 
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
select_costumer
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb.    
select_reservation
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 		
validate_reservation 
to 'Hostess'@'localhost';

grant execute on procedure
tripdb. 
delete_trip 
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb. 	  
delete_costumer 
to 'Hostess'@'localhost';	

grant execute on procedure
tripdb. 
delete_reservation 
to 'Hostess'@'localhost';

flush privileges; grant execute on procedure tripdb.login TO 'Login'@'localhost';
grant select on tripdb.utente to 'Login'@'localhost'; 

flush privileges; 
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
grant execute on procedure tripdb. delete_tour to 'Manager'@'localhost';                              	 	 
grant execute on procedure tripdb. delete_trip to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_destination to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. delete_visit to 'Manager'@'localhost';  		 
grant execute on procedure tripdb. delete_room to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_location to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. delete_map to 'Manager'@'localhost';   			  
grant execute on procedure tripdb. delete_picture to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_employee to 'Manager'@'localhost';   	  
grant execute on procedure tripdb. delete_user to 'Manager'@'localhost';   		  
grant execute on procedure tripdb. delete_ofr to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_service to 'Manager'@'localhost';   		  		 
grant execute on procedure tripdb. delete_fmo to 'Manager'@'localhost';  			 
grant execute on procedure tripdb. delete_fme to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. delete_model to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_bus to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. delete_sparepart to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. delete_certify to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_comfort to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_skills to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. delete_costumer to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_reservation to 'Manager'@'localhost';  
grant execute on procedure tripdb. delete_seat to 'Manager'@'localhost';  		
grant execute on procedure tripdb. delete_stay to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_review to 'Manager'@'localhost';  
grant execute on procedure tripdb. delete_sostitution to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_presents to 'Manager'@'localhost'; 
grant execute on procedure tripdb. delete_rt to 'Manager'@'localhost'; 

flush privileges; 
grant execute on procedure tripdb. login to 'Manager'@'localhost'; 



grant execute on procedure tripdb. insert_tour to 'Manager'@'localhost';                              	 	 
grant execute on procedure tripdb. insert_trip to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_destination to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. insert_visit to 'Manager'@'localhost';  		 
grant execute on procedure tripdb. insert_room to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_location to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. insert_map to 'Manager'@'localhost';   			  
grant execute on procedure tripdb. insert_picture to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_employee to 'Manager'@'localhost';   	  
grant execute on procedure tripdb. insert_user to 'Manager'@'localhost';   		  
grant execute on procedure tripdb. insert_offert to 'Manager'@'localhost'; 	 
grant execute on procedure tripdb. insert_service to 'Manager'@'localhost';   		 	 
grant execute on procedure tripdb. insert_fmo to 'Manager'@'localhost';  			 
grant execute on procedure tripdb. insert_fme to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. insert_model to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_bus to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. insert_sparepart to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. insert_certify to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_comfort to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_skills to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. insert_costumer_user to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_costumer to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_reservation to 'Manager'@'localhost';  
grant execute on procedure tripdb. insert_seat to 'Manager'@'localhost';  		
grant execute on procedure tripdb. insert_stay to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_review to 'Manager'@'localhost';  
grant execute on procedure tripdb. insert_sostitution to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_presents to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_rt to 'Manager'@'localhost'; 
grant execute on procedure tripdb. insert_sost_review to 'Manager'@'localhost';  

grant execute on procedure tripdb. validate_reservation to 'Manager'@'localhost'; 


flush privileges; 
	


grant execute on procedure tripdb. select_tour to 'Manager'@'localhost';                              	 	 
grant execute on procedure tripdb. select_trip to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_destination to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. select_visit to 'Manager'@'localhost';  		 
grant execute on procedure tripdb. select_room to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_location to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. select_map to 'Manager'@'localhost';   			  
grant execute on procedure tripdb. select_picture to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_employee to 'Manager'@'localhost';   	  
grant execute on procedure tripdb. select_user to 'Manager'@'localhost';   		  
grant execute on procedure tripdb. select_ofr to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_service to 'Manager'@'localhost';   		 	 
grant execute on procedure tripdb. select_fmo to 'Manager'@'localhost';  			 
grant execute on procedure tripdb. select_fme to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. select_model to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_bus to 'Manager'@'localhost';   			 
grant execute on procedure tripdb. select_sparepart to 'Manager'@'localhost';   	 
grant execute on procedure tripdb. select_certify to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_comfort to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_skills to 'Manager'@'localhost';   		 
grant execute on procedure tripdb. select_costumer to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_reservation to 'Manager'@'localhost';  
grant execute on procedure tripdb. select_reservation_info to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_seat to 'Manager'@'localhost';  		
grant execute on procedure tripdb. select_stay to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_review to 'Manager'@'localhost';  
grant execute on procedure tripdb. select_sostitution  to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_presents to 'Manager'@'localhost'; 
grant execute on procedure tripdb. select_rt to 'Manager'@'localhost'; 


flush privileges; grant execute on procedure tripdb. update_user_type to 'Manager'@'localhost';    
grant execute on procedure tripdb. update_km to 'Manager'@'localhost';         
  

flush privileges; 
