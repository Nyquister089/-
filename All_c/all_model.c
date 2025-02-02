#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>
#include <err.h>

#include "trpdb.h"
#include "../utils/db.h"



static char *opt_host_name = "localhost"; /* host (default=localhost) */
static char *opt_user_name = "Login";  /* username (default=login name)*/
static char *opt_password = "lgn";	  /* password (default=none) */
static unsigned int opt_port_num = 3306 ;  /* port number (use built-in) */
static char *opt_socket_name = NULL;	  /* socket name (use built-in) */
static char *opt_db_name = "tripdb";	  /* database name (default=none) */
static unsigned int opt_flags = 0;		  /* connection flags (none) */

static MYSQL *conn;

static MYSQL_STMT *login_procedure;

static MYSQL_STMT *insert_tour; 	 	
static MYSQL_STMT *insert_trip; 		
static MYSQL_STMT *insert_destination; 	
static MYSQL_STMT *insert_visit;		
static MYSQL_STMT *insert_room; 		
static MYSQL_STMT *insert_location; 	
static MYSQL_STMT *insert_map; 			 
static MYSQL_STMT *insert_picture; 		
static MYSQL_STMT *insert_employee; 	 
static MYSQL_STMT *insert_user; 		 
static MYSQL_STMT *insert_offert; 		
static MYSQL_STMT *insert_service; 		

static MYSQL_STMT *insert_fmo;			
static MYSQL_STMT *insert_fme; 			
static MYSQL_STMT *insert_model; 		
static MYSQL_STMT *insert_bus; 			
static MYSQL_STMT *insert_sparepart; 	
static MYSQL_STMT *insert_certify; 		
static MYSQL_STMT *insert_comfort; 		
static MYSQL_STMT *insert_skills; 		
static MYSQL_STMT *insert_costumer;		
static MYSQL_STMT *insert_costumer_user; 
static MYSQL_STMT *insert_reservation;	
static MYSQL_STMT *insert_seat;		
static MYSQL_STMT *insert_stay;	
static MYSQL_STMT *insert_review;		
static MYSQL_STMT *insert_sostitution;
static MYSQL_STMT *insert_presents; 
static MYSQL_STMT *insert_rt; 



static MYSQL_STMT *select_trip;		   
static MYSQL_STMT *select_costumer;	   
static MYSQL_STMT *select_reservation; 
static MYSQL_STMT *select_review;	   
static MYSQL_STMT *select_sparepart;   
static MYSQL_STMT *select_stay;   		
static MYSQL_STMT *select_skills; 		
static MYSQL_STMT *select_employee;		 
static MYSQL_STMT *select_fmo;			
static MYSQL_STMT *select_fme;			
static MYSQL_STMT *select_ofr;			

static MYSQL_STMT *select_user; 		
static MYSQL_STMT *select_seat; 		 
static MYSQL_STMT *select_model; 		 
static MYSQL_STMT *select_bus;			 
static MYSQL_STMT *select_certify;		  		
static MYSQL_STMT *select_tour;			 
static MYSQL_STMT *select_destination;	 
static MYSQL_STMT *select_visit; 		 
static MYSQL_STMT *select_location; 	 
static MYSQL_STMT *select_room; 		 
static MYSQL_STMT *select_map; 			  
static MYSQL_STMT *select_picture;	   	 
static MYSQL_STMT *select_comfort;	   	 
static MYSQL_STMT *select_service;	  	 
static MYSQL_STMT *select_sostitution; 
static MYSQL_STMT *select_presents;
static MYSQL_STMT *select_rt;

static MYSQL_STMT *delete_trip;		   
static MYSQL_STMT *delete_costumer;	   
static MYSQL_STMT *delete_reservation; 
static MYSQL_STMT *delete_review;	   
static MYSQL_STMT *delete_sparepart;   
static MYSQL_STMT *delete_stay;   		 
static MYSQL_STMT *delete_skills; 		 
static MYSQL_STMT *delete_employee;		  
static MYSQL_STMT *delete_fmo;			 
static MYSQL_STMT *delete_fme;			 
static MYSQL_STMT *delete_ofr;			 
static MYSQL_STMT *delete_user; 		 
static MYSQL_STMT *delete_seat; 		 
static MYSQL_STMT *delete_model; 		 
static MYSQL_STMT *delete_bus;			 
static MYSQL_STMT *delete_certify;		  		
static MYSQL_STMT *delete_tour;			 
static MYSQL_STMT *delete_destination;	 
static MYSQL_STMT *delete_visit; 		 
static MYSQL_STMT *delete_location; 	 
static MYSQL_STMT *delete_room; 		 
static MYSQL_STMT *delete_map; 			  
static MYSQL_STMT *delete_picture;	   	 
static MYSQL_STMT *delete_comfort;	   	 
static MYSQL_STMT *delete_service;	  	 
static MYSQL_STMT *delete_sostitution; 
static MYSQL_STMT *delete_presents;
static MYSQL_STMT *delete_rt;


static MYSQL_STMT *select_all_tour;		  	 
static MYSQL_STMT *select_dest_tour;	  	 
static MYSQL_STMT *select_hotel_service;  	 
static MYSQL_STMT *select_model_comfort;  	 
static MYSQL_STMT *select_expired_review; 	 
static MYSQL_STMT *insert_sost_review;   	 
static MYSQL_STMT *select_assigned_trip; 	 
static MYSQL_STMT *select_dest_time;		
static MYSQL_STMT *select_dvr_map; 			
static MYSQL_STMT *select_reservation_info; 

static MYSQL_STMT *validate_reservation;	 
static MYSQL_STMT *update_km;				
static MYSQL_STMT *update_user_type; 	


static void close_prepared_stmts(void)
{
	if (login_procedure)
	{
		mysql_stmt_close(login_procedure);
		login_procedure = NULL;
	}
	if (delete_stay)
	{
		mysql_stmt_close(delete_stay);
		delete_stay = NULL;
	}
	if (delete_visit)
	{
		mysql_stmt_close(delete_visit);
		delete_visit = NULL;
	}
	if (delete_comfort)
	{
		mysql_stmt_close(delete_comfort);
		delete_comfort = NULL;
	}
	if (delete_picture)
	{
		mysql_stmt_close(delete_picture);
		delete_picture = NULL;
	}
	if (delete_map)
	{
		mysql_stmt_close(delete_map);
		delete_map= NULL;
	}
	if (delete_room)
	{
		mysql_stmt_close(delete_room);
		delete_room = NULL;
	}
	if (delete_location)
	{
		mysql_stmt_close(delete_location);
		delete_location = NULL;
	}
	if (delete_destination)
	{
		mysql_stmt_close(delete_destination);
		delete_destination = NULL;
	}
	if (delete_tour)
	{
		mysql_stmt_close(delete_tour);
		delete_tour = NULL;
	}
	if (delete_service)
	{
		mysql_stmt_close(delete_service);
		delete_service = NULL;
	}
	if (delete_presents)
	{
		mysql_stmt_close(delete_presents);
		delete_presents = NULL;
	}
	if (delete_rt)
	{
		mysql_stmt_close(delete_rt);
		delete_rt = NULL;
	}
	if (delete_sostitution)
	{
		mysql_stmt_close(delete_sostitution);
		delete_sostitution = NULL;
	}
	if (delete_certify)
	{ 
		mysql_stmt_close(delete_certify);
		delete_certify = NULL;
	}
	if (delete_review)
	{ 
		mysql_stmt_close(delete_review);
		delete_review = NULL;
	}
	if (delete_sparepart)
	{ 
		mysql_stmt_close(delete_sparepart);
		delete_sparepart = NULL;
	}
	if (delete_bus)
	{ 									
		mysql_stmt_close(delete_bus);
		delete_bus = NULL;
	}
	if (delete_employee)
	{
		mysql_stmt_close(delete_employee);
		delete_employee = NULL;
	}
	if (delete_model)
	{
		mysql_stmt_close(delete_model);
		delete_model = NULL;
	}
	if (delete_seat)
	{
		mysql_stmt_close(delete_seat);
		delete_seat = NULL;
	}
	if (delete_user)
	{
		mysql_stmt_close(delete_user);
		delete_user = NULL;
	}
	if (delete_ofr)
	{
		mysql_stmt_close(delete_ofr);
		delete_ofr = NULL;
	}
	if (delete_fmo)
	{
		mysql_stmt_close(delete_fmo);
		delete_fmo = NULL;
	}
	if (delete_fme)
	{
		mysql_stmt_close(delete_fme);
		delete_fme = NULL;
	}
	if (delete_skills)
	{
		mysql_stmt_close(delete_skills);
		delete_skills = NULL;
	}
	if (delete_trip)
	{ 
		mysql_stmt_close(delete_trip);
		delete_trip = NULL;
	}
	if (delete_costumer)
	{ 
		mysql_stmt_close(delete_costumer);
		delete_costumer = NULL;
	}
	if (delete_reservation)
	{ 
		mysql_stmt_close(delete_reservation);
		delete_reservation = NULL;
	}
	if (select_stay)
	{
		mysql_stmt_close(select_stay);
		select_stay = NULL;
	}
	if (select_visit)
	{
		mysql_stmt_close(select_visit);
		select_visit = NULL;
	}
	if (select_comfort)
	{
		mysql_stmt_close(select_comfort);
		select_comfort = NULL;
	}
	if (select_picture)
	{
		mysql_stmt_close(select_picture);
		select_picture = NULL;
	}
	if (select_map)
	{
		mysql_stmt_close(select_map);
		select_map= NULL;
	}
	if (select_room)
	{
		mysql_stmt_close(select_room);
		select_room = NULL;
	}
	if (select_location)
	{
		mysql_stmt_close(select_location);
		select_location = NULL;
	}
	if (select_destination)
	{
		mysql_stmt_close(select_destination);
		select_destination = NULL;
	}
	if (select_tour)
	{
		mysql_stmt_close(select_tour);
		select_tour = NULL;
	}
	if (select_hotel_service)
	{ 
		mysql_stmt_close(select_hotel_service);
		select_hotel_service = NULL;
	}
	if (select_all_tour)
	{
		mysql_stmt_close(select_all_tour);
		select_all_tour = NULL;
	}
	if (select_service)
	{
		mysql_stmt_close(select_service);
		select_service = NULL;
	}
	if (select_presents)
	{
		mysql_stmt_close(select_presents);
		select_presents = NULL;
	}
	if (select_rt)
	{
		mysql_stmt_close(select_rt);
		select_rt = NULL;
	}
	if (select_sostitution)
	{
		mysql_stmt_close(select_sostitution);
		select_sostitution = NULL;
	}
	if (select_model)
	{
		mysql_stmt_close(select_model);
		select_model = NULL;
	}
	if (select_certify)
	{ 
		mysql_stmt_close(select_certify);
		select_certify = NULL;
	}
	if (select_review)
	{ 
		mysql_stmt_close(select_review);
		select_review = NULL;
	}
	if (select_sparepart)
	{ 
		mysql_stmt_close(select_sparepart);
		select_sparepart = NULL;
	}
	if (select_model_comfort)
	{ 
		mysql_stmt_close(select_model_comfort);
		select_model_comfort = NULL;
	}
	if (select_expired_review)
	{ 
		mysql_stmt_close(select_expired_review);
		select_expired_review = NULL;
	}
	if (select_dest_tour)
	{ 
		mysql_stmt_close(select_dest_tour);
		select_dest_tour = NULL;
	}
	if (insert_sost_review)
	{ 
		mysql_stmt_close(insert_sost_review);
		insert_sost_review = NULL;
	}
	if(select_dest_time) {
		mysql_stmt_close(select_dest_time);
		select_dest_time = NULL;
	}
	if(select_assigned_trip) {	
		mysql_stmt_close(select_assigned_trip);
		select_assigned_trip = NULL;
	}
	if (select_reservation_info)
	{ 
		mysql_stmt_close(select_reservation_info);
		select_reservation_info = NULL;
	}
	if (select_dvr_map)
	{ 
		mysql_stmt_close(select_dvr_map);
		select_dvr_map = NULL;
	}
	if (select_bus)
	{ 									
		mysql_stmt_close(select_bus);
		select_bus = NULL;
	}
	if (select_employee)
	{
		mysql_stmt_close(select_employee);
		select_employee = NULL;
	}
	if (select_model)
	{
		mysql_stmt_close(select_model);
		select_model = NULL;
	}
	if (select_seat)
	{
		mysql_stmt_close(select_seat);
		select_seat = NULL;
	}
	if (select_user)
	{
		mysql_stmt_close(select_user);
		select_user = NULL;
	}

	if (select_ofr)
	{
		mysql_stmt_close(select_ofr);
		select_ofr = NULL;
	}
	if (select_fmo)
	{
		mysql_stmt_close(select_fmo);
		select_fmo = NULL;
	}
	if (select_fme)
	{
		mysql_stmt_close(select_fme);
		select_fme = NULL;
	}
	if (select_skills)
	{
		mysql_stmt_close(select_skills);
		select_skills = NULL;
	}
	if (select_trip)
	{
		mysql_stmt_close(select_trip);
		select_trip = NULL;
	}
	if (select_costumer)
	{ 
		mysql_stmt_close(select_costumer);
		select_costumer = NULL;
	}
	if (select_reservation)
	{ 
		mysql_stmt_close(select_reservation);
		select_reservation = NULL;
	}
	if ( insert_tour)
	{ 
		mysql_stmt_close( insert_tour);
		 insert_tour = NULL;
	}
	if (insert_room)
	{ 
		mysql_stmt_close(insert_room);
		insert_room = NULL;
	}
	if ( insert_fmo)
	{ 
		mysql_stmt_close( insert_fmo);
		 insert_fmo = NULL;
	}
	if ( insert_fme)
	{ 
		mysql_stmt_close( insert_fme);
		 insert_fme = NULL;
	}
	if (insert_model)
	{ 
		mysql_stmt_close(insert_model);
		insert_model = NULL;
	}
	if (insert_bus)
	{ 
		mysql_stmt_close(insert_bus);
		insert_bus = NULL;
	}
	if (insert_sparepart)
	{ 
		mysql_stmt_close(insert_sparepart);
		insert_sparepart = NULL;
	}
	if (insert_certify)
	{ 
		mysql_stmt_close(insert_certify);
		insert_certify = NULL;
	}
	if (insert_comfort)
	{ 
		mysql_stmt_close(insert_comfort);
		insert_comfort = NULL;
	}
	if (insert_skills)
	{ 
		mysql_stmt_close(insert_skills);
		insert_skills = NULL;
	}
	if ( insert_service)
	{ 
		mysql_stmt_close( insert_service);
		 insert_service = NULL;
	}
	if (insert_offert)
	{ 
		mysql_stmt_close(insert_offert);
		insert_offert = NULL;
	}
	if (insert_user)
	{ 
		mysql_stmt_close(insert_user);
		insert_user = NULL;
	}
	if (insert_employee)
	{ 
		mysql_stmt_close(insert_employee);
		insert_employee = NULL;
	}
	if ( insert_picture)
	{ 
		mysql_stmt_close( insert_picture);
		 insert_picture = NULL;
	}
	if ( insert_map)
	{ 
		mysql_stmt_close( insert_map);
		 insert_map = NULL;
	}
	if ( insert_location)
	{ 
		mysql_stmt_close( insert_location);
		 insert_location = NULL;
	}
	if (insert_visit)
	{ 
		mysql_stmt_close(insert_visit);
		insert_visit = NULL;
	}
	if ( insert_destination)
	{ 
		mysql_stmt_close( insert_destination);
		 insert_destination = NULL;
	}
	if ( insert_trip)
	{ 
		mysql_stmt_close( insert_trip);
		 insert_trip = NULL;
	}
	if (insert_costumer_user)
	{ 
		mysql_stmt_close(insert_costumer_user);
		insert_costumer_user = NULL;
	}
	if (insert_costumer)
	{ 
		mysql_stmt_close(insert_costumer);
		insert_costumer = NULL;
	}
	if (insert_reservation)
	{ 
		mysql_stmt_close(insert_reservation);
		insert_reservation = NULL;
	}
	if (insert_review)
	{ 
		mysql_stmt_close(insert_review);
		insert_review = NULL;
	}

	if (insert_sostitution)
	{ 
		mysql_stmt_close(insert_sostitution);
		insert_sostitution = NULL;
	}
	if (insert_rt)
	{ 
		mysql_stmt_close(insert_rt);
		insert_rt = NULL;
	}
	if (insert_presents)
	{ 
		mysql_stmt_close(insert_presents);
		insert_presents = NULL;
	}
	if (insert_seat)
	{ 
		mysql_stmt_close(insert_seat);
		insert_seat = NULL;
	}
	if (validate_reservation)
	{ 
		mysql_stmt_close(validate_reservation);
		validate_reservation = NULL;
	}
	if(update_km)
	{ 				
		mysql_stmt_close(update_km);
		update_km = NULL;
	}
	if(update_user_type)
	{ 				
		mysql_stmt_close(update_user_type);
		update_user_type = NULL;
	}
	if (insert_stay)
	{
		mysql_stmt_close(insert_stay);
		insert_stay = NULL;
	}
}

static bool initialize_prepared_stmts(role_t for_role)
{

	switch (for_role)
	{

	case LOGIN_ROLE:
		if (!setup_prepared_stmt(&login_procedure, "call login(?, ?, ?)", conn))
		{
			print_stmt_error(login_procedure, "Unable to initialize login statement\n");
			return false;
		}
		break;

	case AUTISTA: 
			fini_db(); 
			opt_host_name = "localhost"; /* host (default=localhost) */
			opt_user_name = "Autista";  /* username (default=login name)*/
			opt_password = "drvr";	  /* password (default=none) */
			opt_port_num = 3306;  /* port number (use built-in) */
			opt_socket_name = NULL;	  /* socket name (use built-in) */
			opt_db_name = "tripdb";	  /* database name (default=none) */
			opt_flags = 0;		  /* connection flags (none) */
			init_db(); 

			
			if(!setup_prepared_stmt(&select_assigned_trip, "call select_assigned_trip(?)", conn)) {
				print_stmt_error(select_assigned_trip, "Unable to initialize select_assigned_trip statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_dest_time, "call select_dest_time(?)", conn)) {
				print_stmt_error(select_dest_time, "Unable to initialize select_dest_time statement\n");
				return false;
			}
			if (!setup_prepared_stmt(&select_dvr_map, "call select_dvr_map(?)", conn))
			{
			print_stmt_error(select_dvr_map, "Unable to select_dvr_map statement\n");
			return false;
			}
			if (!setup_prepared_stmt(&select_bus, "call select_bus(?)", conn))
			{
			print_stmt_error(select_bus, "Unable to initialize select_bus statement\n");
			return false;
			}
			if (!setup_prepared_stmt(& update_km, "call  update_km(?,?)", conn))
			{
			print_stmt_error( update_km, "Unable to initialize update_km statement\n");
			return false;
			}
		break; 

	case HOSTESS:

		fini_db(); 
		opt_host_name = "localhost"; /* host (default=localhost) */
		opt_user_name = "Hostess";  /* username (default=login name)*/
		opt_password = "hstss";	  /* password (default=none) */
		opt_port_num = 3306;  /* port number (use built-in) */
		opt_socket_name = NULL;	  /* socket name (use built-in) */
		opt_db_name = "tripdb";	  /* database name (default=none) */
		opt_flags = 0;		  /* connection flags (none) */
		init_db(); 

		if (!setup_prepared_stmt(&insert_costumer, "call insert_costumer(?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error(insert_costumer, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_reservation, "call insert_reservation(?, ?, ?)", conn))
		{
			print_stmt_error(insert_reservation, "Unable to initialize insert reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_seat, "call insert_seat (?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(insert_seat, "Unable to initialize insert seat statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&validate_reservation, "call validate_reservation(?, ?, ?)", conn))
		{
			print_stmt_error(validate_reservation, "Unable to initialize validate reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_costumer, "call select_costumer(?)", conn))
		{
			print_stmt_error(select_costumer, "Unable to initialize select costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_reservation, "call select_reservation(?)", conn))
		{
			print_stmt_error(select_reservation, "Unable to initialize select reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_trip, "call select_trip(?)", conn))
		{
			print_stmt_error(select_trip, "Unable to initialize select_trip statement\n");
			return false;
		}

		if (!setup_prepared_stmt(&insert_stay, "call insert_stay(?, ?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(insert_stay, "Unable to initialize insert_stay statement statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_costumer_user, "call insert_costumer_user(?, ?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error(insert_costumer_user, "Unable to initialize insert_costumer_userstatement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_reservation_info, "call select_reservation_info(?)", conn))
		{
		print_stmt_error(select_reservation_info, "Unable to select_reservation_info statement\n");
		return false;
		}
		break;


	case CLIENTE:

		fini_db(); 
		opt_host_name = "localhost"; /* host (default=localhost) */
		opt_user_name = "Cliente";  /* username (default=login name)*/
		opt_password = "cstmr";	  /* password (default=none) */
		opt_port_num = 3306;  /* port number (use built-in) */
		opt_socket_name = NULL;	  /* socket name (use built-in) */
		opt_db_name = "tripdb";	  /* database name (default=none) */
		opt_flags = 0;		  /* connection flags (none) */
		init_db(); 

		if (!setup_prepared_stmt(&select_hotel_service, "call select_hotel_service(?)", conn))
		{
			print_stmt_error(select_hotel_service, "Unable to initialize select_hotel_service statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_all_tour, "call select_all_tour()", conn))
		{
			print_stmt_error(select_all_tour, "Unable to initialize select_all_tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_model_comfort, "call select_model_comfort(?)", conn))
		{
			print_stmt_error(select_model_comfort, "Unable to initialize select dest tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_dest_tour, "call select_dest_tour(?)", conn))
		{
			print_stmt_error(select_dest_tour, "Unable to initialize select dest tour statement\n");
			return false;
		}

		break;
	case MECCANICO:

		fini_db(); 
		opt_host_name = "localhost"; /* host (default=localhost) */
		opt_user_name = "Meccanico";  /* username (default=login name)*/
		opt_password = "mchn";	  /* password (default=none) */
		opt_port_num = 3306;  /* port number (use built-in) */
		opt_socket_name = NULL;	  /* socket name (use built-in) */
		opt_db_name = "tripdb";	  /* database name (default=none) */
		opt_flags = 0;		  /* connection flags (none) */
		init_db(); 



		if (!setup_prepared_stmt(&insert_review, "call insert_review(?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ // Insert
			print_stmt_error(insert_review, "Unable to initialize insert review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_sostitution, "call insert_sostitution(?,?,?)", conn))
		{
			print_stmt_error(insert_sostitution, "Unable to initialize insert_sostitution statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_sparepart, "call select_sparepart(?)", conn))
		{
			print_stmt_error(select_sparepart, "Unable to initialize select_sparepart statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_review, "call select_review(?)", conn))
		{
			print_stmt_error(select_review, "Unable to initialize select_review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_sost_review, "call insert_sost_review(?,?,?,?,?,?,?,?,?)", conn))
		{
			print_stmt_error(insert_sost_review, "Unable to initialize insert_sost_review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_expired_review, "call select_expired_review()", conn))
		{
			print_stmt_error(select_expired_review, "Unable to initialize select_expired_review statement\n");
			return false;
		} 
		break;
		case MANAGER:

		fini_db(); 
		opt_host_name = "localhost"; /* host (default=localhost) */
		opt_user_name = "Manager";  /* username (default=login name)*/
		opt_password = "mngr";	  /* password (default=none) */
		opt_port_num = 3306;  /* port number (use built-in) */
		opt_socket_name = NULL;	  /* socket name (use built-in) */
		opt_db_name = "tripdb";	  /* database name (default=none) */
		opt_flags = 0;		  /* connection flags (none) */
		init_db(); 


		if (!setup_prepared_stmt(&insert_stay, "call insert_stay(?, ?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(insert_stay, "Unable to initialize insert_stay statement statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_review, "call insert_review(?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(insert_review, "Unable to initialize insert review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_presents, "call insert_presents(?,?)", conn))
		{
			print_stmt_error(insert_presents, "Unable to initialize insert_presents statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_rt, "call insert_rt(?,?)", conn))
		{
			print_stmt_error(insert_rt, "Unable to initialize insert_rt statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_sostitution, "call insert_sostitution(?,?,?)", conn))
		{
			print_stmt_error(insert_sostitution, "Unable to initialize insert_sostitution statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_costumer, "call insert_costumer(?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error(insert_costumer, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_reservation, "call insert_reservation(?, ?, ?)", conn))
		{
			print_stmt_error(insert_reservation, "Unable to initialize insert reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_seat, "call insert_seat (?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(insert_seat, "Unable to initialize insert seat statement\n");
			return false;
		}

		if (!setup_prepared_stmt(&insert_fmo, "call  insert_fmo(?, ?)", conn))
		{ 
			print_stmt_error(insert_fmo, "Unable to initialize insert_fmo statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_bus, "call insert_bus(?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error( insert_bus, "Unable to initialize  insert_bus statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_sparepart, "call insert_sparepart(?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error( insert_sparepart, "Unable to initialize  insert_sparepart statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_certify, "call insert_certify(?, ?)", conn))
		{ 
			print_stmt_error( insert_certify, "Unable to initialize  insert_certify statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_skills, "call insert_skills(?, ?)", conn))
		{ 
			print_stmt_error( insert_skills, "Unable to initialize  insert_skills statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_comfort, "call insert_comfort(?, ?)", conn))
		{ 
			print_stmt_error( insert_comfort, "Unable to initialize  insert_comfort statement\n");
			return false;
		}
		if (!setup_prepared_stmt(& insert_model, "call   insert_model(?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error( insert_model, "Unable to initialize  insert_model statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_fme, "call  insert_fme(?, ?)", conn))
		{ 
			print_stmt_error(insert_fme, "Unable to initialize insert_fme statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_service, "call  insert_service(?, ?)", conn))
		{ 
			print_stmt_error(insert_service, "Unable to initialize insert_service statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_offert, "call  insert_offert(?, ?)", conn))
		{ 
			print_stmt_error(insert_offert, "Unable to initialize insert_offert statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_user, "call  insert_user(?, ?, ?)", conn))
		{ 
			print_stmt_error(insert_user, "Unable to initialize insert_user statement\n");
			return false;
		}
		if (!setup_prepared_stmt(& insert_employee, "call  insert_employee(?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error( insert_employee, "Unable to initialize insert_employee statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_picture, "call insert_picture(?, ?)", conn))
		{ 
			print_stmt_error(insert_picture, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_map, "call insert_map(?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error(insert_map, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_location, "call insert_location(?, ?, ?)", conn))
		{ 
			print_stmt_error(insert_location, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&  insert_room, "call insert_room(?, ?, ?, ?)", conn))
		{ 
			print_stmt_error(  insert_room, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&  insert_visit, "call   insert_visit(?, ?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error(  insert_visit, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(& insert_destination, "call  insert_destination(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error( insert_destination, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(& insert_trip, "call  insert_trip(?, ?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error( insert_trip, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(& insert_tour, "call  insert_tour(?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error( insert_tour, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_trip, "call delete_trip(?)", conn))
		{
			print_stmt_error(delete_trip, "Unable to initialize delete_trip statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_tour, "call  delete_tour(?)", conn))
		{ 
			print_stmt_error(delete_tour, "Unable to initialize delete_tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_sparepart, "call delete_sparepart(?)", conn))
		{
			print_stmt_error(delete_sparepart, "Unable to initialize delete_sparepart statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_review, "call delete_review(?)", conn))
		{
			print_stmt_error(delete_review, "Unable to initialize delete_review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_bus, "call  delete_bus(?)", conn))
		{ 
			print_stmt_error(delete_bus, "Unable to initialize delete_bus statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_reservation, "call delete_reservation(?)", conn))
		{
			print_stmt_error(delete_reservation, "Unable to initialize delete reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_costumer, "call delete_costumer(?)", conn))
		{
			print_stmt_error(delete_costumer, "Unable to initialize delete_costumer statement\n");
			return false;
		}
			if (!setup_prepared_stmt(&delete_stay, "call  delete_stay(?)", conn))
		{ 
			print_stmt_error(delete_stay, "Unable to initialize delete_stay statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_skills, "call  delete_skills(?,?)", conn))
		{ 
			print_stmt_error(delete_skills, "Unable to initialize delete_skills statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_employee, "call  delete_employee(?)", conn))
		{ 
			print_stmt_error(delete_employee, "Unable to initialize delete_employee statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_fmo, "call  delete_fmo(?,?)", conn))
		{ 
			print_stmt_error(delete_fmo, "Unable to initialize delete_fmo statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_fme, "call  delete_fme(?,?)", conn))
		{ 
			print_stmt_error(delete_fme, "Unable to initialize delete_fme statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_ofr, "call  delete_ofr(?,?)", conn))
		{ 
			print_stmt_error(delete_ofr, "Unable to initialize delete_ofr statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_user, "call  delete_user(?)", conn))
		{ 
			print_stmt_error(delete_user, "Unable to initialize delete_user statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_seat, "call  delete_seat(?, ?)", conn))
		{ 
			print_stmt_error(delete_seat, "Unable to initialize delete_seat statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_model, "call  delete_model(?)", conn))
		{ 
			print_stmt_error(delete_model, "Unable to initialize delete_model statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_certify, "call  delete_certify(?)", conn))
		{ 
			print_stmt_error(delete_certify, "Unable to initialize delete_certify statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_destination, "call  delete_destination(?)", conn))
		{ 
			print_stmt_error(delete_destination, "Unable to initialize delete_destination statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_visit, "call  delete_visit(?)", conn))
		{ 
			print_stmt_error(delete_visit, "Unable to initialize delete_visit statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_location, "call  delete_location(?, ?)", conn))
		{ 
			print_stmt_error(delete_location, "Unable to initialize delete_location statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_room, "call  delete_room(?, ?)", conn))
		{ 
			print_stmt_error(delete_room, "Unable to initialize delete_room statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_map, "call  delete_map(?)", conn))
		{ 
			print_stmt_error(delete_map, "Unable to initialize delete_map statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_picture, "call  delete_picture(?)", conn))
		{ 
			print_stmt_error(delete_picture, "Unable to initialize delete_picture statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_comfort, "call  delete_comfort(?)", conn))
		{ 
			print_stmt_error(delete_comfort, "Unable to initialize delete_comfort statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_service , "call  delete_service (?)", conn))
		{ 
			print_stmt_error(delete_service , "Unable to initialize delete_service  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_presents , "call  delete_presents (?, ?)", conn))
		{ 
			print_stmt_error(delete_presents , "Unable to initialize delete_presents  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_rt , "call  delete_rt (?, ?)", conn))
		{ 
			print_stmt_error(delete_rt , "Unable to initialize delete_rt  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&delete_sostitution , "call  delete_sostitution (?, ?)", conn))
		{ 
			print_stmt_error(delete_sostitution , "Unable to initialize delete_sostitution  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_sparepart, "call select_sparepart(?)", conn))
		{
			print_stmt_error(select_sparepart, "Unable to initialize select_sparepart statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_review, "call select_review(?)", conn))
		{
			print_stmt_error(select_review, "Unable to initialize select_review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_stay, "call  select_stay(?)", conn))
		{ 
			print_stmt_error(select_stay, "Unable to initialize select_stay statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_employee, "call  select_employee(?)", conn))
		{ 
			print_stmt_error(select_employee, "Unable to initialize select_employee statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_service , "call  select_service (?)", conn))
		{ 
			print_stmt_error(select_service , "Unable to initialize select_service  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_rt , "call  select_rt (?, ?)", conn))
		{ 
			print_stmt_error(select_rt , "Unable to initialize select_rt  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_presents , "call  select_presents (?, ?)", conn))
		{ 
			print_stmt_error(select_presents , "Unable to initialize select_presents  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_sostitution , "call  select_sostitution (?, ?)", conn))
		{ 
			print_stmt_error(select_sostitution , "Unable to initialize select_sostitution  statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_comfort, "call  select_comfort(?)", conn))
		{ 
			print_stmt_error(select_comfort, "Unable to initialize select_comfort statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_costumer, "call select_costumer(? )", conn))
		{
			print_stmt_error(select_costumer, "Unable to initialize select costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_reservation, "call select_reservation(?)", conn))
		{
			print_stmt_error(select_reservation, "Unable to initialize select reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_picture, "call  select_picture(?)", conn))
		{ 
			print_stmt_error(select_picture, "Unable to initialize select_picture statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_map, "call  select_map(?)", conn))
		{ 
			print_stmt_error(select_map, "Unable to initialize select_map statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_room, "call  select_room(?, ?)", conn))
		{ 
			print_stmt_error(select_room, "Unable to initialize select_room statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_location, "call  select_location(?, ?)", conn))
		{ 
			print_stmt_error(select_location, "Unable to initialize select_location statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_visit, "call  select_visit(?)", conn))
		{ 
			print_stmt_error(select_visit, "Unable to initialize select_visit statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_destination, "call  select_destination(?)", conn))
		{ 
			print_stmt_error(select_destination, "Unable to initialize select_destination statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_tour, "call  select_tour(?)", conn))
		{ 
			print_stmt_error(select_tour, "Unable to initialize select_tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_trip, "call select_trip(?)", conn))
		{
			print_stmt_error(select_trip, "Unable to initialize select_trip statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_certify, "call  select_certify(?)", conn))
		{ 
			print_stmt_error(select_certify, "Unable to initialize select_certify statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_bus, "call  select_bus(?)", conn))
		{ 
			print_stmt_error(select_bus, "Unable to initialize select_bus statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_model, "call  select_model(?)", conn))
		{ 
			print_stmt_error(select_model, "Unable to initialize select_model statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_seat, "call  select_seat(?, ?)", conn))
		{ 
			print_stmt_error(select_seat, "Unable to initialize select_seat statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_user, "call  select_user(?)", conn))
		{ 
			print_stmt_error(select_user, "Unable to initialize select_user statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_ofr, "call  select_ofr(?,?)", conn))
		{ 
			print_stmt_error(select_ofr, "Unable to initialize select_ofr statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_fme, "call  select_fme(?,?)", conn))
		{ 
			print_stmt_error(select_fme, "Unable to initialize select_fme statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_fmo, "call  select_fmo(?,?)", conn))
		{ 
			print_stmt_error(select_fmo, "Unable to initialize select_fmo statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_skills, "call  select_skills(?,?)", conn))
		{ 
			print_stmt_error(select_skills, "Unable to initialize select_skills statement\n");
			return false;
		}
		if (!setup_prepared_stmt(& update_user_type, "call  update_user_type(?,?)", conn))
		{
			print_stmt_error( update_user_type, "Unable to initialize update_user_type statement\n");
			return false;
		}
		if (!setup_prepared_stmt(& update_km, "call  update_km(?,?)", conn))
		{
			print_stmt_error( update_km, "Unable to initialize update_km statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_costumer_user, "call insert_costumer_user(?, ?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ 
			print_stmt_error(insert_costumer_user, "Unable to initialize insert_costumer_userstatement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_reservation_info, "call select_reservation_info(?)", conn))
		{
		print_stmt_error(select_reservation_info, "Unable to select_reservation_info statement\n");
		return false;
		}
		if (!setup_prepared_stmt(&insert_sost_review, "call insert_sost_review(?,?,?,?,?,?,?,?,?)", conn))
		{
			print_stmt_error(insert_sost_review, "Unable to initialize insert_sost_review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&validate_reservation, "call validate_reservation(?, ?, ?)", conn))
		{
			print_stmt_error(validate_reservation, "Unable to initialize validate reservation statement\n");
			return false;
		}
		break;

	default:
		fprintf(stderr, "[FATAL] Unexpected role to prepare statements.\n");
		exit(EXIT_FAILURE);
	}

	return true;
}

bool init_db(void){
	unsigned int timeout = 300;
	bool reconnect = true;

	conn = mysql_init(NULL);

	if (conn == NULL)
	{
		finish_with_error(conn, "mysql_init() failed (probably out of memory)\n");
	}
	if (mysql_real_connect(conn, opt_host_name, opt_user_name, opt_password, opt_db_name, opt_port_num, opt_socket_name, opt_flags) == NULL)
	{
		finish_with_error(conn, "mysql_real_connect() failed\n");
	}
	if (mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout))
	{
		print_error(conn, "[mysql_options] failed.");
	}
	if (mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect))
	{
		print_error(conn, "[mysql_options] failed.");
	}
	return initialize_prepared_stmts(LOGIN_ROLE);
}

void fini_db(void){
	close_prepared_stmts();

	mysql_close(conn);
}

role_t attempt_login(struct credentials *cred){
	MYSQL_BIND param[3]; // Used both for input and output
	int role = 0;

	// Prepare parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cred->username, strlen(cred->username));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cred->password, strlen(cred->password));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &role, sizeof(role));

	if (mysql_stmt_bind_param(login_procedure, param) != 0)
	{ // Note _param
		print_stmt_error(login_procedure, "Binding dei parametri non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Run procedure
	if (mysql_stmt_execute(login_procedure) != 0)
	{
		print_stmt_error(login_procedure, "Login non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &role, sizeof(role));

	if (mysql_stmt_bind_result(login_procedure, param))
	{
		print_stmt_error(login_procedure, "Bind_result non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(login_procedure))
	{
		print_stmt_error(login_procedure, "Fetch non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}
out:
	// Consume the possibly-returned table for the output parameter
	while (mysql_stmt_next_result(login_procedure) != -1)
	{
	}

	mysql_stmt_free_result(login_procedure);
	mysql_stmt_reset(login_procedure);

	initialize_prepared_stmts(role);

	return role;
}

void db_switch_to_login(void){
	close_prepared_stmts();
	if (mysql_change_user(conn, getenv("LOGIN_USER"), getenv("LOGIN_PASS"), getenv("DB")))
	{
		fprintf(stderr, "mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}

	if (!initialize_prepared_stmts(LOGIN_ROLE))
	{
		fprintf(stderr, "[FATAL] Cannot initialize prepared statements.\n");
		exit(EXIT_FAILURE);
	}
}



// Richiamo procedure di insert

void do_insert_costumer(struct cliente *cliente)
{
	MYSQL_BIND param[8];
	MYSQL_TIME datadocumentazione;
	char *buff = "insert_costumer"; 

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, strlen(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, strlen(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, strlen(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, strlen(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, strlen(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, strlen(cliente->fax));

	bind_exe(insert_costumer,param, buff); 

	mysql_stmt_free_result(insert_costumer);
	mysql_stmt_reset(insert_costumer);
}

void do_insert_reservation(struct prenotazione *prenotazione)
{
	MYSQL_BIND param[3];
	char *buff = "insert_reservation"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, strlen(prenotazione->clienteprenotante));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &prenotazione->viaggioassociato, sizeof(prenotazione->viaggioassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &prenotazione->numerodipostiprenotati, sizeof(prenotazione->numerodipostiprenotati));

	bind_exe(insert_reservation, param, buff); 

	mysql_stmt_free_result(insert_reservation);
	mysql_stmt_reset(insert_reservation);
}

void do_insert_seat(struct postoprenotato *postoprenotato)
{
	MYSQL_BIND param[5];

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &postoprenotato->numerodiposto, sizeof(postoprenotato->numerodiposto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &postoprenotato->prenotazioneassociata, sizeof(postoprenotato->prenotazioneassociata));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &postoprenotato->etapasseggero, sizeof(postoprenotato->etapasseggero));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, strlen(postoprenotato->nomepasseggero));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, strlen(postoprenotato->cognomepasseggero));

	bind_exe(insert_seat, param, "insert_seat");

	mysql_stmt_free_result(insert_seat);
	mysql_stmt_reset(insert_seat);
}

void do_insert_stay(struct soggiorno *soggiorno)
{
	MYSQL_BIND param[6];
	MYSQL_TIME datafinesoggiorno;
	MYSQL_TIME datainiziosoggiorno;

	char *buff = "insert_stay";

	date_to_mysql_time(soggiorno->datainiziosoggiorno, &datainiziosoggiorno);
	date_to_mysql_time(soggiorno->datafinesoggiorno, &datafinesoggiorno);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &soggiorno->cameraprenotata, sizeof(soggiorno->cameraprenotata));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &soggiorno->ospite, sizeof(soggiorno->ospite));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &soggiorno->albergoinquestione, sizeof(soggiorno->albergoinquestione));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &soggiorno->prenotazioneinquestione, sizeof(soggiorno->prenotazioneinquestione));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datainiziosoggiorno, sizeof(datainiziosoggiorno));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datafinesoggiorno, sizeof(datafinesoggiorno));

	bind_exe(insert_stay, param, buff);

	mysql_stmt_free_result(insert_stay);
	mysql_stmt_reset(insert_stay);
}

void do_insert_review(struct revisione *revisione)
{
	MYSQL_BIND param[7];
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine;

	char *buff = "insert_review";

	date_to_mysql_time(revisione->datainizio, &datainizio);
	date_to_mysql_time(revisione->datafine, &datafine);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, strlen(revisione->mezzorevisionato));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, revisione->addettoallarevisione, strlen(revisione->addettoallarevisione));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &revisione->chilometraggio, sizeof(revisione->chilometraggio));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, strlen(revisione->operazionieseguite));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->motivazione, strlen(revisione->motivazione));
	

	bind_exe(insert_review, param, buff);

	mysql_stmt_free_result(insert_review);
	mysql_stmt_reset(insert_review);
}

void do_validate_reservation(struct prenotazione *prenotazione) // Funziona
{
	MYSQL_BIND param[3];

	MYSQL_TIME datadiconferma;
	MYSQL_TIME datasaldo;
	char *buff = "validate_reservation"; 

 
	date_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	date_to_mysql_time(prenotazione->datasaldo, &datasaldo);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &prenotazione->numerodiprenotazione, sizeof(prenotazione->numerodiprenotazione));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datasaldo, sizeof(datasaldo));

	bind_exe(validate_reservation, param, buff);
	mysql_stmt_free_result(validate_reservation);
	mysql_stmt_reset(validate_reservation);
}

void do_insert_sostitution(struct sostituito *sostituito)
{
	MYSQL_BIND param[3];

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &sostituito->revisioneassociata, sizeof(sostituito->revisioneassociata));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, sostituito->ricambioutilizzato, strlen(sostituito->ricambioutilizzato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &sostituito->quantitasostituita, sizeof(sostituito->quantitasostituita));

	bind_exe(insert_sostitution, param, "insert_sostitution");

	mysql_stmt_free_result(insert_sostitution);
	mysql_stmt_reset(insert_sostitution);
}

void do_insert_rt(struct rt *rt)
{
	MYSQL_BIND param[2];

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &rt->revisionerelativa, sizeof(rt->revisionerelativa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &rt->tagliandoassociato, sizeof(rt->tagliandoassociato));

	bind_exe(insert_rt, param, "insert_rt");

	mysql_stmt_free_result(insert_rt);
	mysql_stmt_reset(insert_rt);
}






void do_insert_presents(struct presenti *presenti)
{
	MYSQL_BIND param[2];

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &presenti->comfortpresenti, sizeof(presenti->comfortpresenti));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, presenti->modelloassciato, strlen(presenti->modelloassciato));

	bind_exe(insert_presents, param, "insert_presents");

	mysql_stmt_free_result(insert_presents);
	mysql_stmt_reset(insert_presents);
}


void do_update_km(struct mezzo *mezzo) 
{
	MYSQL_BIND param[2];
	char *buff = "update_km"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING ,mezzo->targa, strlen(mezzo->targa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &mezzo->valorecontakm, sizeof(mezzo->valorecontakm));

	bind_exe(update_km, param, buff);

	mysql_stmt_free_result(update_km);
	mysql_stmt_reset(update_km);
}

void do_insert_tour(struct tour *tour)
{
	MYSQL_BIND param[7];

	char *buff = "insert_tour"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour->denominazionetour, strlen(tour->denominazionetour));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tour->descrizionetour, strlen(tour->descrizionetour));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &tour->minimopartecipanti, sizeof(tour->minimopartecipanti));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &tour->assicurazionemedica, sizeof(tour->assicurazionemedica));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &tour->bagaglio, sizeof(tour->bagaglio));
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &tour->garanziaannullamento, sizeof(tour->garanziaannullamento));
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &tour->accompagnatrice, sizeof(tour->accompagnatrice));

	bind_exe(insert_tour, param, buff); 

	mysql_stmt_free_result(insert_tour);
	mysql_stmt_reset(insert_tour);
}


void do_insert_destination(struct meta *meta)
{ 	
	MYSQL_BIND param[10]; 
	MYSQL_TIME orariodiapertura; 

	char *buff = "insert_destination"; 
	
	time_to_mysql_time(meta->orariodiapertura, &orariodiapertura);
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, meta->localitadiappartenenza, strlen(meta->localitadiappartenenza));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, meta->regiodiappartenennza, strlen(meta->regiodiappartenennza));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, meta->nomemeta, strlen(meta->nomemeta));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, meta->emailmeta, strlen(meta->emailmeta));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, meta->telefonometa, strlen(meta->telefonometa));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, meta->faxmeta, strlen(meta->faxmeta));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, meta->indirizzo, strlen(meta->indirizzo));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, meta->tipologiameta, strlen(meta->tipologiameta));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, meta->categoriaalbergo, strlen(meta->categoriaalbergo));
	set_binding_param(&param[9], MYSQL_TYPE_TIME, &orariodiapertura, sizeof(orariodiapertura));
	
	bind_exe(insert_destination, param, buff); 

	mysql_stmt_free_result(insert_destination);
	mysql_stmt_reset(insert_destination);

	
}

void do_insert_trip(struct viaggio *viaggio)
{		
	MYSQL_BIND param[9]; 
	MYSQL_TIME datadipartenzaviaggio; 
	MYSQL_TIME datadiritornoviaggio;

	char *buff = "insert_trip"; 
	
	date_to_mysql_time(viaggio->datadipartenzaviaggio, &datadipartenzaviaggio);
	date_to_mysql_time(viaggio->datadiritornoviaggio, &datadiritornoviaggio); 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, strlen(viaggio->tourassociato));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING,	viaggio->conducente, strlen(viaggio->conducente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, viaggio->accompagnatrice, strlen(viaggio->accompagnatrice));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, viaggio->mezzoimpiegato, strlen(viaggio->mezzoimpiegato));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datadipartenzaviaggio, sizeof(datadipartenzaviaggio));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadiritornoviaggio, sizeof(datadiritornoviaggio));
	set_binding_param(&param[6], MYSQL_TYPE_FLOAT, &viaggio->costodelviaggio, sizeof(viaggio->costodelviaggio));
	set_binding_param(&param[7], MYSQL_TYPE_LONG, &viaggio->numerodikm, sizeof(viaggio->numerodikm));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &viaggio->postidisponibili, sizeof(viaggio->postidisponibili));
	
	bind_exe(insert_trip,param,buff); 

	mysql_stmt_free_result(insert_trip);
	mysql_stmt_reset(insert_trip);
	
}

void do_insert_visit(struct visita *visita)
{   
	MYSQL_BIND param[9]; 
	MYSQL_TIME datadiarrivo; 
	MYSQL_TIME datadipartenza; 
	MYSQL_TIME oradiarrivo; 
	MYSQL_TIME oradipartenza; 

	char *buff ="insert_visit"; 

	date_to_mysql_time (visita->datadiarrivo, &datadiarrivo); 
	date_to_mysql_time (visita->datadipartenza, &datadipartenza); 
	time_to_mysql_time (visita->oradiarrivo, &oradiarrivo); 
	time_to_mysql_time (visita->oradipartenza, &oradipartenza); 
	
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &visita->viaggiorelativo, sizeof(visita->viaggiorelativo));
	set_binding_param(&param[1], MYSQL_TYPE_LONG , &visita->metavisitata, sizeof(visita->metavisitata));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datadiarrivo, sizeof(datadiarrivo));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datadipartenza, sizeof(datadipartenza));
	set_binding_param(&param[4], MYSQL_TYPE_TIME, &oradiarrivo, sizeof(oradiarrivo));
	set_binding_param(&param[5], MYSQL_TYPE_TIME, &oradipartenza, sizeof(oradipartenza));
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &visita->guida, sizeof(visita->guida));
	set_binding_param(&param[7], MYSQL_TYPE_FLOAT , &visita->supplemento, sizeof(visita->supplemento));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, visita->trattamentoalberghiero, strlen(visita->trattamentoalberghiero));
	
	bind_exe(insert_visit, param, buff); 

	mysql_stmt_free_result(insert_visit);
	mysql_stmt_reset(insert_visit);
	
}

void do_insert_room(struct camera *camera)
{		
	MYSQL_BIND param[4]; 

	char *buff = "insert_room"; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &camera->numerocamera, sizeof(camera->numerocamera));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &camera->albergo, sizeof(camera->albergo));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, camera->tipologia, strlen(camera->tipologia));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &camera->costo , sizeof(camera->costo));
	
	bind_exe(insert_room, param, buff); 

	mysql_stmt_free_result(insert_room);
	mysql_stmt_reset(insert_room);
}
void do_insert_location(struct localita *localita)
{		
	MYSQL_BIND param[3]; 
	char *buff ="insert_location"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, localita->nomelocalita, strlen(localita->nomelocalita));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, localita->regione, strlen(localita->regione));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, localita->stato, strlen(localita->stato));
	
	bind_exe(insert_location, param, buff); 

	mysql_stmt_free_result(insert_location);
	mysql_stmt_reset(insert_location);
}

void do_insert_map(struct mappa *mappa)
{		
	MYSQL_BIND param[5]; 
	char *buff = "insert_map"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mappa->citta, strlen(mappa->citta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, mappa->localitarappresentata, strlen(mappa->localitarappresentata));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mappa->zona, strlen(mappa->zona));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mappa->dettaglio, strlen(mappa->dettaglio));
	set_binding_param(&param[4], MYSQL_TYPE_BLOB, mappa->immagine, strlen(mappa->immagine));

	bind_exe(insert_map,param, buff); 

	mysql_stmt_free_result(insert_map);
	mysql_stmt_reset(insert_map);
	
}

void do_insert_employee(struct dipendente *dipendente)
{	
	MYSQL_BIND param[5]; 
	char *buff = "insert_employee"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING,dipendente->tipologiadipendente, strlen(dipendente->tipologiadipendente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dipendente->telefonoaziendale, strlen(dipendente->telefonoaziendale));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, dipendente->nomedipendente, strlen(dipendente->nomedipendente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, dipendente->cognomedipendente, strlen(dipendente->cognomedipendente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, dipendente->emaildipendente, strlen(dipendente->emaildipendente));

	
	
	bind_exe( insert_employee, param, buff); 
	
	mysql_stmt_free_result(insert_employee);
	mysql_stmt_reset(insert_employee);
	
}

void do_insert_offert(struct offre *offre)
{	
	MYSQL_BIND param[2]; 
	char *buff = "insert_offert"; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &offre->idservizio, sizeof(offre->idservizio));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &offre->albergoofferente, sizeof(offre->albergoofferente));
	
	bind_exe( insert_offert, param, buff); 
	
	mysql_stmt_free_result(insert_offert);
	mysql_stmt_reset(insert_offert);
	
}

void do_insert_costumer_user(struct utente *utente, struct cliente *cliente)
{	
	MYSQL_BIND param[9]; 
	MYSQL_TIME datadocumentazione;

	char *buff = "insert_costumer_user"; 

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);


	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, strlen(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, strlen(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, strlen(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, strlen(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, strlen(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, strlen(cliente->fax));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, utente->pswrd, strlen(utente->pswrd));
	
	bind_exe( insert_costumer_user, param, buff); 
	
	mysql_stmt_free_result(insert_costumer_user);
	mysql_stmt_reset(insert_costumer_user);
	
}

void do_insert_user(struct utente *utente)
{	
	MYSQL_BIND param[3]; 
	char *buff = "insert_user"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, utente->email, strlen(utente->email));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, utente->pswrd, strlen(utente->pswrd));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &utente->tipo, sizeof(utente->tipo));
	
	bind_exe( insert_user, param, buff); 
	
	mysql_stmt_free_result(insert_user);
	mysql_stmt_reset(insert_user);
	
}

void do_insert_picture(struct documentazionefotografica *documentazionefotografica)
{	
	MYSQL_BIND param[2]; 
	char *buff = "insert_picture"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING,documentazionefotografica->descrzione, strlen(documentazionefotografica->descrzione));
	set_binding_param(&param[1], MYSQL_TYPE_BLOB, documentazionefotografica->foto, strlen(documentazionefotografica->foto));
	
	bind_exe(insert_picture, param, buff); 
	
	mysql_stmt_free_result(insert_picture);
	mysql_stmt_reset(insert_picture);
	
}

void do_insert_service(struct servizio *servizio)
{		
	MYSQL_BIND param[2]; 
	char *buff = "insert_service"; 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, servizio->nomeservizio, strlen(servizio->nomeservizio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, servizio->descrizioneservizio, strlen(servizio->descrizioneservizio));
	
	bind_exe(insert_service,param,buff); 

	mysql_stmt_free_result(insert_service);
	mysql_stmt_reset(insert_service);
	
}


void do_insert_fmo(struct fmo *fmo)
{
	MYSQL_BIND param[2];
	
	char *buff = "insert_fmo";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fmo->foto, sizeof(fmo->foto));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, fmo->modello, strlen(fmo->modello));
	
	bind_exe(insert_fmo, param, buff); 
	
	mysql_stmt_free_result(insert_fmo);
	mysql_stmt_reset(insert_fmo);
}

void do_insert_fme(struct fme *fme)
{
	MYSQL_BIND param[2];
	
	char *buff = "insert_fme";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fme->meta, sizeof(fme->meta));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &fme->foto, sizeof(fme->foto));
	
	bind_exe(insert_fme, param, buff); 
	
	mysql_stmt_free_result(insert_fme);
	mysql_stmt_reset(insert_fme);
}

void do_insert_model(struct modello *modello, struct competenze *competenze)
{		
	MYSQL_BIND param[6]; 
	char *buff = "insert_model"; 
	
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, modello->nomemodello, strlen(modello->nomemodello));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, modello->datitecnici, strlen(modello->datitecnici));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, modello->casacostruttrice, strlen(modello->casacostruttrice));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &modello->numeroposti, sizeof(modello->numeroposti));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, competenze->meccanicocompetente, strlen(competenze->meccanicocompetente));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, competenze->nomemeccanico, strlen(competenze->nomemeccanico));

	if(mysql_stmt_bind_param(insert_model, param) != 0) {
		print_stmt_error(insert_model, "Could not bind parameters for insert_model");
		return;
	}
	if(mysql_stmt_execute(insert_model) != 0) {
		print_stmt_error(insert_model, "Could not execute insert_model");
		return;
		}
	mysql_stmt_free_result(insert_model);
	mysql_stmt_reset(insert_model);
	

}

void do_insert_bus(struct mezzo *mezzo)
{		
	MYSQL_BIND param[7]; 
	MYSQL_TIME dataultimarevisioneinmotorizzazione; 
	MYSQL_TIME dataimmatricolazione; 
	char *buff ="insert_bus"; 
	
	date_to_mysql_time(mezzo->dataultimarevisioneinmotorizzazione, &dataultimarevisioneinmotorizzazione); 
	date_to_mysql_time(mezzo->dataimmatricolazione, &dataimmatricolazione); 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->targa, strlen(mezzo->targa));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, mezzo->modellomezzo, strlen(mezzo->modellomezzo));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mezzo->ingombri, strlen(mezzo->ingombri));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &mezzo->autonomia, sizeof(mezzo->autonomia));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &mezzo->valorecontakm, sizeof(mezzo->valorecontakm));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &dataultimarevisioneinmotorizzazione, sizeof(dataultimarevisioneinmotorizzazione));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &dataimmatricolazione, sizeof(dataimmatricolazione));
	
	bind_exe(insert_bus, param, buff); 

	mysql_stmt_free_result(insert_bus);
	mysql_stmt_reset(insert_bus);
	
}

void do_insert_sparepart(struct ricambio *ricambio)
{		
	MYSQL_BIND param[6]; 
	char *buff ="insert_sparepart"; 

	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambio->codice, strlen(ricambio->codice));
	set_binding_param(&param[1], MYSQL_TYPE_FLOAT, &ricambio->costounitario, sizeof(ricambio->costounitario));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &ricambio->quantitadiriordino, sizeof(ricambio->quantitadiriordino));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, ricambio->descrizione, strlen(ricambio->descrizione));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &ricambio->scortaminima, sizeof(ricambio->scortaminima));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &ricambio->quantitainmagazzino, sizeof(ricambio->quantitainmagazzino));

	bind_exe(insert_sparepart, param, buff); 
	 
	mysql_stmt_free_result(insert_sparepart);
	mysql_stmt_reset(insert_sparepart);
	
}

void do_insert_certify(struct tagliando *tagliando)
{		
	MYSQL_BIND param[2]; 
	char *buff = "insert_certify"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tagliando->tipologiatagliando, strlen(tagliando->tipologiatagliando));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tagliando->validitasuperate, strlen(tagliando->validitasuperate));
	
	bind_exe(insert_certify, param, buff); 

	mysql_stmt_free_result(insert_certify);
	mysql_stmt_reset(insert_certify);
	
}

void do_insert_comfort(struct comfort *comfort)
{		
	MYSQL_BIND param[2]; 
	char *buff ="insert_comfort"; 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, comfort->nomecomfort, strlen(comfort->nomecomfort));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, comfort->descrizionecomfort, strlen(comfort->descrizionecomfort));
	
	bind_exe(insert_comfort,param,buff); 

	mysql_stmt_free_result(insert_comfort);
	mysql_stmt_reset(insert_comfort);
	
}

void do_insert_skills(struct competenze *competenze)
{		
	MYSQL_BIND param[2]; 
	char *buff ="insert_skills"; 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, competenze->modelloassociato, strlen(competenze->modelloassociato));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, competenze->meccanicocompetente, strlen(competenze->meccanicocompetente));
	
	bind_exe(insert_skills,param,buff); 

	mysql_stmt_free_result(insert_skills);
	mysql_stmt_reset(insert_skills);
	
}



// Richiamo procedure di select

int do_select_model(struct modello *modello)
{
	MYSQL_BIND param[4];
	
	char *buff = "select_model";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, modello->nomemodello, strlen(modello->nomemodello));
	
	if (bind_exe(select_model, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, modello->casacostruttrice, sizeof(modello->casacostruttrice));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, modello->datitecnici, sizeof(modello->datitecnici));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &modello->numeroposti, sizeof(modello->numeroposti));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &modello->numeromeccanicicompetenti, sizeof(modello->numeromeccanicicompetenti));
	

	
	rows = take_result(select_model, param, buff);
 
	stop:
	mysql_stmt_free_result(select_model);
	mysql_stmt_reset(select_model);
	return (rows); 
 
}

int do_select_seat(struct postoprenotato *postoprenotato)
{
	MYSQL_BIND param[3];
	
	char *buff = "select_seat";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &postoprenotato->numerodiposto, sizeof(postoprenotato->numerodiposto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &postoprenotato->prenotazioneassociata, sizeof(postoprenotato->prenotazioneassociata));
	
	if (bind_exe(select_seat, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, sizeof(postoprenotato->nomepasseggero));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, sizeof(postoprenotato->cognomepasseggero));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &postoprenotato->etapasseggero, sizeof(postoprenotato->etapasseggero));
	
	rows = take_result(select_seat, param, buff);
 
	stop:
	mysql_stmt_free_result(select_seat);
	mysql_stmt_reset(select_seat);
	return (rows); 
}

int do_select_user(struct utente *utente)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_user";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, utente->email, strlen(utente->email));
	
	if (bind_exe(select_user, param, buff) == -1)
		goto stop;

	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, utente->pswrd, sizeof(utente->pswrd));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &utente->tipo, sizeof(utente->tipo));
	
	rows = take_result(select_user, param, buff);
 
	stop:
	mysql_stmt_free_result(select_user);
	mysql_stmt_reset(select_user);
	return (rows); 
}


int do_select_ofr(struct offre *offre)
{
	MYSQL_BIND param[3];
	
	char *buff = "select_ofr";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &offre->albergoofferente, sizeof(offre->albergoofferente));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &offre->idservizio, sizeof(offre->servizio));

	if (bind_exe(select_ofr, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, offre->meta, sizeof(offre->meta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, offre->servizio, sizeof(offre->servizio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, offre->descrizione, sizeof(offre->descrizione));

	
	rows = take_result(select_ofr, param, buff); 

	
	stop:
	mysql_stmt_free_result(select_ofr);
	mysql_stmt_reset(select_ofr);
	return (rows); 

}

int do_select_fme(struct fme *fme)
{
	MYSQL_BIND param[3];
	
	char *buff = "select_fme";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fme->foto, sizeof(fme->foto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &fme->meta, sizeof(fme->meta));
	
	
	if (bind_exe(select_fme, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fme->nome, sizeof(fme->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, fme->descrizione, sizeof(fme->descrizione));
	set_binding_param(&param[2], MYSQL_TYPE_BLOB, fme->immagine, sizeof(fme->immagine));
	
	rows = take_result(select_fme, param, buff);
	
	stop:
	mysql_stmt_free_result(select_fme);
	mysql_stmt_reset(select_fme);
	return (rows); 
}

int do_select_fmo(struct fmo *fmo)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_fmo";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fmo->foto, sizeof(fmo->foto));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, fmo->modello, strlen(fmo->modello));
	
	
	if (bind_exe(select_fmo, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fmo->descrizione, sizeof(fmo->descrizione));
	set_binding_param(&param[1], MYSQL_TYPE_BLOB, fmo->immagine, sizeof(fmo->immagine));
	
	rows = take_result(select_fmo, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_fmo);
	mysql_stmt_reset(select_fmo);
	return (rows); 
}
 

int do_select_employee(struct dipendente*dipendente)
{
	MYSQL_BIND param[4];
	
	char *buff = "select_employee";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, dipendente->emaildipendente, strlen(dipendente->emaildipendente));
	
	if (bind_exe(select_employee, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, dipendente->nomedipendente, sizeof(dipendente->nomedipendente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dipendente->cognomedipendente, sizeof(dipendente->cognomedipendente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, dipendente->tipologiadipendente, sizeof(dipendente->tipologiadipendente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, dipendente->telefonoaziendale, sizeof(dipendente->telefonoaziendale));

	
	rows = take_result(select_employee, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_employee);
	mysql_stmt_reset(select_employee);
	return (rows); 
 
}

int do_select_skills(struct competenze *competenze)
{
	MYSQL_BIND param[2];
	char *buff = "select_skills";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, competenze->meccanicocompetente, strlen(competenze->meccanicocompetente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, competenze->modelloassociato, strlen(competenze->modelloassociato));
	
	if (bind_exe(select_skills, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, competenze->nomemeccanico, sizeof(competenze->nomemeccanico));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, competenze->telefono, sizeof(competenze->telefono));
	
	rows = take_result(select_skills, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_skills);
	mysql_stmt_reset(select_skills);
	return (rows); 
}


int do_select_stay(struct soggiorno *soggiorno)
{
	MYSQL_BIND param[6];
	MYSQL_TIME datainiziosoggiorno; 
	MYSQL_TIME datafinesoggiorno;


	char *buff = "select_stay";
	int rows; 

	date_to_mysql_time(soggiorno->datainiziosoggiorno, &datainiziosoggiorno);
	date_to_mysql_time(soggiorno->datafinesoggiorno,&datafinesoggiorno);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &soggiorno->idsoggiorno, sizeof(soggiorno->idsoggiorno));
	 
	if (bind_exe(select_stay, param, buff) == -1)
		goto stop;
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &soggiorno->ospite, sizeof(soggiorno->ospite));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &soggiorno->albergoinquestione, sizeof(soggiorno->albergoinquestione));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &soggiorno->cameraprenotata, sizeof(soggiorno->cameraprenotata));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &soggiorno->prenotazioneinquestione, sizeof(soggiorno->prenotazioneinquestione));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datainiziosoggiorno, sizeof(datainiziosoggiorno));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datafinesoggiorno, sizeof(datafinesoggiorno));
	
	rows = take_result(select_stay, param, buff); 
	if(rows == -1)
		goto stop; 

	mysql_date_to_string(&datainiziosoggiorno, soggiorno->datainiziosoggiorno); 
	mysql_date_to_string(&datafinesoggiorno, soggiorno->datafinesoggiorno); 

	stop:

	mysql_stmt_free_result(select_stay);
	mysql_stmt_reset(select_stay);

	return (rows); 
}

int do_select_sparepart(struct ricambio *ricambio)
{
	MYSQL_BIND param[5];
	
	char *buff = "select_sparepart"; 
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambio->codice, strlen(ricambio->codice));

	if (bind_exe(select_sparepart, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_FLOAT, &ricambio->costounitario, sizeof(ricambio->costounitario));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &ricambio->quantitadiriordino, sizeof(ricambio->quantitadiriordino));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, ricambio->descrizione, sizeof(ricambio->descrizione));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &ricambio->scortaminima, sizeof(ricambio->scortaminima));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &ricambio->quantitainmagazzino, sizeof(ricambio->quantitainmagazzino));

	rows = take_result(select_sparepart, param, buff);

	stop:
	mysql_stmt_free_result(select_sparepart);
	mysql_stmt_reset(select_sparepart);
	return (rows); 
}

int do_select_certify(struct tagliando *tagliando)
{
	MYSQL_BIND param[2];

	char *buff = "select_certify";  
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &tagliando->idtagliando, sizeof(tagliando->idtagliando));

	if (bind_exe(select_certify, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tagliando->tipologiatagliando, sizeof(tagliando->tipologiatagliando));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tagliando->validitasuperate, sizeof(tagliando->validitasuperate));
	
	rows = take_result(select_certify, param, buff); 

   	stop:
	mysql_stmt_free_result(select_certify);
	mysql_stmt_reset(select_certify);
	return (rows); 
}

int do_select_bus(struct mezzo *mezzo)
{
	MYSQL_BIND param[6];
	MYSQL_TIME dataultimarevisioneinmotorizzazione;
	MYSQL_TIME dataimmatricolazione;

	char *buff = "select_bus";  
	int rows; 

	date_to_mysql_time(mezzo->dataultimarevisioneinmotorizzazione, &dataultimarevisioneinmotorizzazione);
	date_to_mysql_time(mezzo->dataimmatricolazione, &dataimmatricolazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->targa, strlen(mezzo->targa));

	if (bind_exe(select_bus, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->modellomezzo, sizeof(mezzo->modellomezzo));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &dataultimarevisioneinmotorizzazione, sizeof(dataultimarevisioneinmotorizzazione));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mezzo->ingombri, sizeof(mezzo->ingombri));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &mezzo->autonomia, sizeof(mezzo->autonomia));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &mezzo->valorecontakm, sizeof(mezzo->valorecontakm));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &dataimmatricolazione, sizeof(dataimmatricolazione));

	rows =  take_result(select_bus, param, buff); 
	if(rows == -1)
		goto stop; 

	mysql_date_to_string(&dataultimarevisioneinmotorizzazione, mezzo->dataultimarevisioneinmotorizzazione);
	mysql_date_to_string(&dataimmatricolazione, mezzo->dataimmatricolazione);

	stop:
	mysql_stmt_free_result(select_bus);
	mysql_stmt_reset(select_bus);
	return (rows); 
}

int do_select_review(struct revisione *revisione) 
{
	MYSQL_BIND param[7];
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine;

	char *buff = "select_review";
	int rows; 

	init_mysql_timestamp(&datainizio);
	init_mysql_timestamp(&datafine);
 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &revisione->idrevisione, sizeof(revisione->idrevisione));
	
	if (bind_exe(select_review, param, buff) == -1)
		goto stop;
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, sizeof(revisione->mezzorevisionato));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, revisione->addettoallarevisione, sizeof(revisione->addettoallarevisione));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &revisione->chilometraggio, sizeof(revisione->chilometraggio));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, sizeof(revisione->operazionieseguite));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->motivazione, sizeof(revisione->motivazione));
	
	rows = take_result(select_review, param, buff); 
	if (rows == -1)
		goto stop;
	
	mysql_date_to_string(&datainizio, revisione->datainizio);
	mysql_date_to_string(&datafine, revisione->datafine);
	
	stop:
	mysql_stmt_free_result(select_review);
	mysql_stmt_reset(select_review);
	return(rows); 
}

int do_select_trip(struct viaggio *viaggio)
{
	MYSQL_BIND param[10];
	MYSQL_TIME datadipartenzaviaggio;
	MYSQL_TIME datadiritornoviaggio;
	MYSQL_TIME datadiannullamento;

	char *buff =  "select_trip"; 
	int rows; 

	date_to_mysql_time(viaggio->datadipartenzaviaggio, &datadipartenzaviaggio);
	date_to_mysql_time(viaggio->datadiritornoviaggio, &datadiritornoviaggio);
	date_to_mysql_time(viaggio->datadiannullamento, &datadiannullamento);


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &viaggio->idviaggio, sizeof(viaggio->idviaggio));
	
	if (bind_exe(select_trip, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, sizeof(viaggio->tourassociato));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, viaggio->conducente, sizeof(viaggio->conducente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, viaggio->accompagnatrice, sizeof(viaggio->accompagnatrice));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, viaggio->mezzoimpiegato, sizeof(viaggio->mezzoimpiegato));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datadipartenzaviaggio, sizeof(datadipartenzaviaggio));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadiritornoviaggio, sizeof(datadiritornoviaggio));
	set_binding_param(&param[6], MYSQL_TYPE_FLOAT, &viaggio->costodelviaggio, sizeof(viaggio->costodelviaggio));
	set_binding_param(&param[7], MYSQL_TYPE_LONG, &viaggio->numerodikm, sizeof(viaggio->numerodikm));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &viaggio->postidisponibili, sizeof(viaggio->postidisponibili));
	set_binding_param(&param[9], MYSQL_TYPE_DATE, &datadiannullamento, sizeof(datadiannullamento));

	rows = take_result(select_trip, param,buff); 
	if (rows == -1)
		goto stop;

	mysql_date_to_string(&datadipartenzaviaggio, viaggio->datadipartenzaviaggio);
	mysql_date_to_string(&datadiritornoviaggio, viaggio->datadiritornoviaggio);
	mysql_date_to_string(&datadiannullamento, viaggio->datadiannullamento);

	stop:
	mysql_stmt_free_result(select_trip);
	mysql_stmt_reset(select_trip);
	return(rows); 
}

int do_select_costumer(struct cliente *cliente)
{
	MYSQL_BIND param[7];
	MYSQL_TIME datadocumentazione;

	char *buff ="select_costumer"; 
	int rows; 

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	
	if (bind_exe(select_costumer, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, sizeof(cliente->nomecliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, sizeof(cliente->cognomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, sizeof(cliente->indirizzocliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, sizeof(cliente->codicefiscale));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, sizeof(cliente->recapitotelefonico));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->fax, sizeof(cliente->fax));

	rows = take_result(select_costumer, param, buff); 
	if (rows == -1)
		goto stop;

	mysql_date_to_string(&datadocumentazione, cliente->datadocumentazione);

	stop:
	mysql_stmt_free_result(select_costumer);
	mysql_stmt_reset(select_costumer);
	return(rows); 
}

int do_select_reservation(struct prenotazione *prenotazione)
{
	MYSQL_BIND param[6];
	MYSQL_TIME datadiprenotazione;
	MYSQL_TIME datadiconferma;
	MYSQL_TIME datasaldo;

	char *buff ="select_reservation"; 
	int rows; 

	date_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione);
	date_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	date_to_mysql_time(prenotazione->datasaldo, &datasaldo);


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &prenotazione->numerodiprenotazione, sizeof(prenotazione->numerodiprenotazione));
	
	if (bind_exe(select_reservation, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, sizeof(prenotazione->clienteprenotante));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &prenotazione->viaggioassociato,sizeof(prenotazione->viaggioassociato)); 
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &prenotazione->numerodipostiprenotati,sizeof(prenotazione->numerodipostiprenotati)); 
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datadiprenotazione, sizeof(datadiprenotazione));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datasaldo, sizeof(datasaldo));

	rows = take_result(select_reservation, param, buff);
	if (rows == -1)
		goto stop;


	mysql_date_to_string(&datadiprenotazione, prenotazione->datadiprenotazione);
	mysql_date_to_string(&datadiconferma, prenotazione->datadiconferma);
	mysql_date_to_string(&datasaldo, prenotazione->datasaldo);

    stop:
	mysql_stmt_free_result(select_reservation);
	mysql_stmt_reset(select_reservation);
	return(rows); 
}

int do_select_tour(struct tour *tour)
{
	MYSQL_BIND param[6];
	
	char *buff = "select_tour"; 
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour->denominazionetour, strlen(tour->denominazionetour));
	
	if (bind_exe(select_tour, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour->descrizionetour, sizeof(tour->descrizionetour));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &tour->minimopartecipanti, sizeof(tour->minimopartecipanti));
	set_binding_param(&param[2], MYSQL_TYPE_FLOAT, &tour->assicurazionemedica, sizeof(tour->assicurazionemedica));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &tour->bagaglio, sizeof(tour->bagaglio));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &tour->garanziaannullamento, sizeof(tour->garanziaannullamento));
	set_binding_param(&param[5], MYSQL_TYPE_TINY, &tour->accompagnatrice, sizeof(tour->accompagnatrice));

	rows = take_result(select_tour, param, buff); 

	stop:
	mysql_stmt_free_result(select_tour);
	mysql_stmt_reset(select_tour);
	return(rows); 
}

int do_select_comfort(struct comfort *comfort)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_comfort";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &comfort->idcomfort, sizeof(comfort->idcomfort));

	if(bind_exe(select_comfort, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, comfort->nomecomfort, sizeof(comfort->nomecomfort));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, comfort->descrizionecomfort, sizeof(comfort->descrizionecomfort));
	
	rows = take_result(select_comfort, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_comfort);
	mysql_stmt_reset(select_comfort);
	return(rows); 
}


int do_select_picture(struct documentazionefotografica *documentazionefotografica)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_picture";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &documentazionefotografica->idfoto, sizeof(documentazionefotografica->idfoto));

	if(bind_exe(select_picture, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_BLOB, &documentazionefotografica->foto, sizeof(documentazionefotografica->foto));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, documentazionefotografica->descrzione, sizeof(documentazionefotografica->descrzione));
	
	rows = take_result(select_picture, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_picture);
	mysql_stmt_reset(select_picture);
	return(rows); 
}

int do_select_map(struct mappa *mappa)
{
	MYSQL_BIND param[5];
	
	char *buff = "select_map";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &mappa->idmappa, sizeof(mappa->idmappa));

	if(bind_exe(select_map, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mappa->citta, sizeof(mappa->citta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, mappa->localitarappresentata, sizeof(mappa->localitarappresentata));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mappa->dettaglio, sizeof(mappa->dettaglio));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mappa->zona, sizeof(mappa->zona));
	set_binding_param(&param[4], MYSQL_TYPE_BLOB, &mappa->immagine, sizeof(mappa->immagine));

	rows = take_result(select_map, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_map);
	mysql_stmt_reset(select_map);
	return(rows); 
}

int do_select_room(struct camera *camera)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_room";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &camera->numerocamera, sizeof(camera->numerocamera));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &camera->albergo, sizeof(camera->albergo));
	
	if(bind_exe(select_room, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, camera->tipologia, sizeof(camera->tipologia));
	set_binding_param(&param[1], MYSQL_TYPE_FLOAT, &camera->costo, sizeof(camera->costo));
	
	rows = take_result(select_room, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_room);
	mysql_stmt_reset(select_room);
	return(rows); 
}

int do_select_location(struct localita *localita)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_location";
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, localita->nomelocalita, strlen(localita->nomelocalita));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, localita->regione, strlen(localita->regione));

	if(bind_exe(select_location, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, localita->stato, sizeof(localita->stato));
	
	rows = take_result(select_location, param, buff); 
	
	stop:
	mysql_stmt_free_result(select_location);
	mysql_stmt_reset(select_location);
	return(rows); 
}

int do_select_visit(struct visita *visita)
{
	MYSQL_BIND param[11];
	MYSQL_TIME orariodiarrivo;
	MYSQL_TIME orariodipartenza; 
	MYSQL_TIME datadiarrivo; 
	MYSQL_TIME datadipartenza; 

	char *buff = "select_visit";
	int rows; 

	init_mysql_timestamp(&orariodiarrivo); 
	init_mysql_timestamp(&orariodipartenza);
	date_to_mysql_time(visita->datadiarrivo, &datadiarrivo);
	date_to_mysql_time(visita->datadipartenza, &datadipartenza); 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &visita->idvisita, sizeof(visita->idvisita));

	if(bind_exe(select_visit, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, visita->tour, sizeof(visita->tour));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &visita->viaggiorelativo, sizeof(visita->viaggiorelativo));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, visita->meta, sizeof(visita->meta));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &visita->metavisitata, sizeof(visita->metavisitata));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datadiarrivo, sizeof(datadiarrivo));
	set_binding_param(&param[5], MYSQL_TYPE_TIME, &orariodiarrivo, sizeof(orariodiarrivo));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &datadipartenza, sizeof(datadipartenza));
	set_binding_param(&param[7], MYSQL_TYPE_TIME, &orariodipartenza, sizeof(orariodipartenza));
	set_binding_param(&param[8], MYSQL_TYPE_TINY, &visita->guida, sizeof(visita->guida));
	set_binding_param(&param[9], MYSQL_TYPE_FLOAT, &visita->supplemento, sizeof(visita->supplemento));
	set_binding_param(&param[10], MYSQL_TYPE_VAR_STRING, visita->trattamentoalberghiero, sizeof(visita->trattamentoalberghiero));
	
	rows = take_result(select_visit, param, buff); 
	if(rows ==-1)
		goto stop; 
	
	mysql_time_to_string(&orariodiarrivo,visita->oradiarrivo); 
	mysql_time_to_string(&orariodipartenza, visita->oradipartenza); 
	mysql_date_to_string(&datadiarrivo, visita->datadiarrivo); 
	mysql_date_to_string(&datadipartenza, visita->datadipartenza); 
	
	stop:
	mysql_stmt_free_result(select_visit);
	mysql_stmt_reset(select_visit);
	return(rows); 
}

int do_select_destination(struct meta *meta)
{
	MYSQL_BIND param[10];
	MYSQL_TIME orariodiapertura;

	char *buff = "select_destination";
	int rows; 

	init_mysql_timestamp(&orariodiapertura); 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &meta->idmeta, sizeof(meta->idmeta));

	if(bind_exe(select_destination, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, meta->nomemeta, sizeof(meta->nomemeta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, meta->tipologiameta, sizeof(meta->tipologiameta));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, meta->localitadiappartenenza, sizeof(meta->localitadiappartenenza));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, meta->regiodiappartenennza, sizeof(meta->regiodiappartenennza));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, meta->indirizzo, sizeof(meta->indirizzo));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, meta->telefonometa, sizeof(meta->telefonometa));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, meta->emailmeta, sizeof(meta->emailmeta));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, meta->faxmeta, sizeof(meta->faxmeta));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, meta->categoriaalbergo, sizeof(meta->categoriaalbergo));
	set_binding_param(&param[9], MYSQL_TYPE_TIME, &orariodiapertura, sizeof(orariodiapertura));

	rows = take_result(select_destination, param, buff); 
	if(rows ==-1)
		goto stop; 
	
	mysql_time_to_string(&orariodiapertura,meta->orariodiapertura); 
	
	stop:
	mysql_stmt_free_result(select_destination);
	mysql_stmt_reset(select_destination);
	return(rows); 
}


int do_select_rt(struct rt *rt)
{
	MYSQL_BIND param[2];

	char *buff = "select_rt"; 
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &rt->revisionerelativa, sizeof(rt->revisionerelativa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &rt->tagliandoassociato, sizeof(rt->tagliandoassociato));

	if(bind_exe(select_rt, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &rt->revisionerelativa, sizeof(rt->revisionerelativa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &rt->tagliandoassociato, sizeof(rt->tagliandoassociato));

	rows = take_result(select_rt,param, buff); 
	
	stop: 
	mysql_stmt_free_result(select_rt);
	mysql_stmt_reset(select_rt);
	return(rows); 

}

int do_select_presents(struct presenti *presenti)
{
	MYSQL_BIND param[2];

	char *buff ="select_presents"; 
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &presenti->comfortpresenti, sizeof(presenti->comfortpresenti));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, presenti->modelloassciato, strlen(presenti->modelloassciato));

	if(bind_exe(select_presents, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &presenti->comfortpresenti, sizeof(presenti->comfortpresenti));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, presenti->modelloassciato, strlen(presenti->modelloassciato));

	rows = take_result(select_presents,param, buff); 
	
	stop: 
	mysql_stmt_free_result(select_presents);
	mysql_stmt_reset(select_presents);
	return(rows); 
}

int do_select_sostitution(struct sostituito *sostituito)
{
	MYSQL_BIND param[2];

	char *buff ="select_sostitution"; 
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, sostituito->ricambioutilizzato, strlen(sostituito->ricambioutilizzato));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &sostituito->revisioneassociata, sizeof(sostituito->revisioneassociata));

	if(bind_exe(select_sostitution, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &sostituito->quantitasostituita, sizeof(sostituito->quantitasostituita));
	
	rows = take_result(select_sostitution,param, buff); 
	
	stop: 
	mysql_stmt_free_result(select_sostitution);
	mysql_stmt_reset(select_sostitution);
	return(rows); 
}

int do_select_service(struct servizio *servizio)
{
	MYSQL_BIND param[2];

	char *buff ="select_service"; 
	int rows; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &servizio->idservizio, sizeof(servizio->idservizio));

	if(bind_exe(select_service, param, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, servizio->nomeservizio, sizeof(servizio->nomeservizio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, servizio->descrizioneservizio, sizeof(servizio->descrizioneservizio));

	rows = take_result(select_service,param, buff); 
	
	stop: 
	mysql_stmt_free_result(select_service);
	mysql_stmt_reset(select_service);
	return(rows); 
}



// Richiamo procedure di delete

void do_delete_model(struct modello *modello)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_model";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, modello->nomemodello, strlen(modello->nomemodello));
	
	bind_exe(delete_model, param, buff);

	mysql_stmt_free_result(delete_model);
	mysql_stmt_reset(delete_model);
 
}

void do_delete_seat(struct postoprenotato *postoprenotato)
{
	MYSQL_BIND param[2];
	
	char *buff = "delete_seat";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &postoprenotato->prenotazioneassociata, sizeof(postoprenotato->prenotazioneassociata));

	set_binding_param(&param[1], MYSQL_TYPE_LONG, &postoprenotato->numerodiposto, sizeof(postoprenotato->numerodiposto));
	
	bind_exe(delete_seat, param, buff);

	mysql_stmt_free_result(delete_seat);
	mysql_stmt_reset(delete_seat);
 
}

void do_delete_user(struct utente *utente)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_user";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, utente->email, strlen(utente->email));
	
	bind_exe(delete_user, param, buff); 

	mysql_stmt_free_result(delete_user);
	mysql_stmt_reset(delete_user);
 
}


void do_delete_ofr(struct offre *offre)
{
	MYSQL_BIND param[2];
	
	char *buff = "delete_ofr";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &offre->albergoofferente, sizeof(offre->albergoofferente));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &offre->idservizio, sizeof(offre->servizio));
	
	bind_exe(delete_ofr, param, buff); 

	mysql_stmt_free_result(delete_ofr);
	mysql_stmt_reset(delete_ofr);
 
}

void do_delete_fme(struct fme *fme)
{
	MYSQL_BIND param[2];
	
	char *buff = "delete_fme";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fme->foto, sizeof(fme->foto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &fme->meta, sizeof(fme->meta));
	
	bind_exe(delete_fme, param, buff);

	mysql_stmt_free_result(delete_fme);
	mysql_stmt_reset(delete_fme);
 
}

void do_delete_fmo(struct fmo *fmo)
{
	MYSQL_BIND param[2];
	
	char *buff = "delete_fmo";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fmo->foto, sizeof(fmo->foto));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, fmo->modello, strlen(fmo->modello));
	
	bind_exe(delete_fmo, param, buff); 
	
	mysql_stmt_free_result(delete_fmo);
	mysql_stmt_reset(delete_fmo);
 
}
 

void do_delete_employee(struct dipendente*dipendente)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_employee";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, dipendente->emaildipendente, strlen(dipendente->emaildipendente));
	
	bind_exe(delete_employee, param, buff);

	mysql_stmt_free_result(delete_employee);
	mysql_stmt_reset(delete_employee);
 
}

void do_delete_skills(struct competenze *competenze)
{
	MYSQL_BIND param[2];

	char *buff = "delete_skills";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, competenze->meccanicocompetente, strlen(competenze->meccanicocompetente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, competenze->modelloassociato, strlen(competenze->modelloassociato));
	
	bind_exe(delete_skills, param, buff);
	
	mysql_stmt_free_result(delete_skills);
	mysql_stmt_reset(delete_skills);
}


void do_delete_stay(struct soggiorno *soggiorno)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_stay";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &soggiorno->idsoggiorno, sizeof(soggiorno->idsoggiorno));


	bind_exe(delete_stay, param, buff);

	mysql_stmt_free_result(delete_stay);
	mysql_stmt_reset(delete_stay);
}

void do_delete_sparepart(struct ricambio *ricambio) //FUNZIONA
{
	MYSQL_BIND param[1];
	char *buff ="delete_sparepart";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambio->codice, strlen(ricambio->codice));

	bind_exe(delete_sparepart, param,buff);

	mysql_stmt_free_result(delete_sparepart);
	mysql_stmt_reset(delete_sparepart);
}

void do_delete_certify(struct tagliando *tagliando)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_certify";  

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &tagliando->idtagliando, sizeof(tagliando->idtagliando));

	bind_exe(delete_certify, param, buff);
	
	mysql_stmt_free_result(delete_certify);
	mysql_stmt_reset(delete_certify);
}

void do_delete_bus(struct mezzo *mezzo)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_bus";  

	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->targa, strlen(mezzo->targa));

	bind_exe(delete_bus, param, buff); 


	mysql_stmt_free_result(delete_bus);
	mysql_stmt_reset(delete_bus);
}

void do_delete_review(struct revisione *revisione) {
	MYSQL_BIND param[1];


	char *buff = "delete_review";
 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &revisione->idrevisione, sizeof(revisione->idrevisione));
	
	bind_exe(delete_review, param, buff);

	mysql_stmt_free_result(delete_review);
	mysql_stmt_reset(delete_review);
}

void do_delete_trip(struct viaggio *viaggio) // Funziona
{
	MYSQL_BIND param[1];
	MYSQL_TIME datadipartenzaviaggio;
	MYSQL_TIME datadiritornoviaggio;
	MYSQL_TIME datadiannullamento;

	char *buff =  "delete_trip"; 


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &viaggio->idviaggio, sizeof(viaggio->idviaggio));
	
	bind_exe(delete_trip, param, buff); 


	mysql_stmt_free_result(delete_trip);
	mysql_stmt_reset(delete_trip);
}

void do_delete_costumer(struct cliente *cliente) 
{
	MYSQL_BIND param[1];
	MYSQL_TIME datadocumentazione;
	char *buff="delete_costumer"; 

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);


	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	
	bind_exe(delete_costumer, param, buff); 

	mysql_stmt_free_result(delete_costumer);
	mysql_stmt_reset(delete_costumer);
}

void do_delete_reservation(struct prenotazione *prenotazione)
{
	MYSQL_BIND param[1];
	char *buff ="delete_reservation"; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &prenotazione->numerodiprenotazione, sizeof(prenotazione->numerodiprenotazione));
	
	bind_exe(delete_reservation, param, buff); 
	
	mysql_stmt_free_result(delete_reservation);
	mysql_stmt_reset(delete_reservation);
}

void do_delete_tour(struct tour *tour)
{
	MYSQL_BIND param[1];
	char *buff ="delete_tour"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour->denominazionetour, strlen(tour->denominazionetour));
	
	bind_exe(delete_tour, param,buff); 

	mysql_stmt_free_result(delete_tour);
	mysql_stmt_reset(delete_tour);
}

void do_delete_comfort(struct comfort *comfort)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_comfort";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &comfort->idcomfort, sizeof(comfort->idcomfort));

	bind_exe(delete_comfort, param, buff); 

	mysql_stmt_free_result(delete_comfort);
	mysql_stmt_reset(delete_comfort);
}


void do_delete_picture(struct documentazionefotografica *documentazionefotografica)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_picture";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &documentazionefotografica->idfoto, sizeof(documentazionefotografica->idfoto));

	bind_exe(delete_picture, param, buff);

	mysql_stmt_free_result(delete_picture);
	mysql_stmt_reset(delete_picture);
}

void do_delete_map(struct mappa *mappa)
{
	MYSQL_BIND param[1];
	
	char *buff = "delete_map";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &mappa->idmappa, sizeof(mappa->idmappa));

	bind_exe(delete_map, param, buff); 

	mysql_stmt_free_result(delete_map);
	mysql_stmt_reset(delete_map);
}

void do_delete_room(struct camera *camera)
{
	MYSQL_BIND param[2];
	
	char *buff = "delete_room";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &camera->numerocamera, sizeof(camera->numerocamera));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &camera->albergo, sizeof(camera->albergo));
	
	bind_exe(delete_room, param, buff);

	mysql_stmt_free_result(delete_room);
	mysql_stmt_reset(delete_room);
}

void do_delete_location(struct localita *localita)
{
	MYSQL_BIND param[2];
	
	char *buff = "delete_location";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, localita->nomelocalita, strlen(localita->nomelocalita));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, localita->regione, strlen(localita->regione));


	bind_exe(delete_location, param, buff);

	mysql_stmt_free_result(delete_location);
	mysql_stmt_reset(delete_location);
}

void do_delete_visit(struct visita *visita)
{
	MYSQL_BIND param[1];
	char *buff = "delete_visit";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &visita->idvisita, sizeof(visita->idvisita));

	bind_exe(delete_visit, param, buff);

	mysql_stmt_free_result(delete_visit);
	mysql_stmt_reset(delete_visit);
}

void do_delete_destination(struct meta *meta)
{
	MYSQL_BIND param[1];

	char *buff = "delete_destination";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &meta->idmeta, sizeof(meta->idmeta));

	bind_exe(delete_destination, param, buff);

	mysql_stmt_free_result(delete_destination);
	mysql_stmt_reset(delete_destination);
}

void do_delete_rt(struct rt *rt)
{
	MYSQL_BIND param[2];

	char *buff ="delete_rt"; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &rt->revisionerelativa, sizeof(rt->revisionerelativa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &rt->tagliandoassociato, sizeof(rt->tagliandoassociato));

	bind_exe(delete_rt, param, buff);
	
	mysql_stmt_free_result(delete_rt);
	mysql_stmt_reset(delete_rt);
}

void do_delete_presents(struct presenti *presenti)
{
	MYSQL_BIND param[2];

	char *buff ="delete_presents"; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &presenti->comfortpresenti, sizeof(presenti->comfortpresenti));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, presenti->modelloassciato, strlen(presenti->modelloassciato));

	bind_exe(delete_presents, param, buff);
	
	mysql_stmt_free_result(delete_presents);
	mysql_stmt_reset(delete_presents);
}

void do_delete_sostitution(struct sostituito *sostituito)
{
	MYSQL_BIND param[2];

	char *buff ="delete_sostitution"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, sostituito->ricambioutilizzato, strlen(sostituito->ricambioutilizzato));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &sostituito->revisioneassociata, sizeof(sostituito->revisioneassociata));

	bind_exe(delete_sostitution, param, buff);
	
	mysql_stmt_free_result(delete_sostitution);
	mysql_stmt_reset(delete_sostitution);
}

void do_delete_service(struct servizio *servizio)
{
	MYSQL_BIND param[1];

	char *buff ="delete_service"; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &servizio->idservizio, sizeof(servizio->idservizio));

	bind_exe(delete_service, param, buff);

	mysql_stmt_free_result(delete_service);
	mysql_stmt_reset(delete_service);
}

// Richiamo procedure speciali

void do_insert_sost_review(struct revisione *revisione, struct sostituito *sostituito )
{

	MYSQL_BIND param[9];
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine;

	char *buff = "insert_sost_review";

	date_to_mysql_time(revisione->datainizio, &datainizio);
	date_to_mysql_time(revisione->datafine, &datafine);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, strlen(revisione->mezzorevisionato));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, revisione->addettoallarevisione, strlen(revisione->addettoallarevisione));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &revisione->chilometraggio, sizeof(revisione->chilometraggio));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, strlen(revisione->operazionieseguite));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->motivazione, strlen(revisione->motivazione));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, sostituito->ricambioutilizzato, strlen(sostituito->ricambioutilizzato));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &sostituito->quantitasostituita, sizeof(sostituito->quantitasostituita));
	

	bind_exe(insert_sost_review, param, buff);

	mysql_stmt_free_result(insert_sost_review);
	mysql_stmt_reset(insert_sost_review);
}


void do_update_user_type(struct utente *utente)
{	
	MYSQL_BIND param[2]; 
	char *buff = "update_user_type"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, utente->email, strlen(utente->email));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &utente->tipo, sizeof(utente->tipo));
	
	bind_exe( update_user_type, param, buff); 
	
	mysql_stmt_free_result(update_user_type);
	mysql_stmt_reset(update_user_type);
}



struct info_modelli *get_info_modello(char *nmd)
{
	MYSQL_BIND param[7];

	struct info_modelli *info_modello = NULL;
	char *buff = "select_model_comfort";

	char casacostruttrice[VARCHAR_LEN];
	int numeroposti;
	char nomecomfort[VARCHAR_LEN];
	char descrizionecomfort[DES_LEN];
	char foto[PIC];
	char descrizionefoto[DES_LEN];
	int idfoto;

	size_t rows, count;
	count = 0;
	int cmpr, status;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nmd, strlen(nmd));

	bind_exe(select_model_comfort, param, buff);
	rows = take_rows(select_model_comfort,buff); 
	if(rows == -1)
		goto stop;

	info_modello = malloc((sizeof(struct info_modelli) + sizeof(info_modello)) * rows);
	memset(info_modello, 0, sizeof(*info_modello) + sizeof(struct info_modelli) * rows);

	if (info_modello == NULL)
	{
		printf("Impossibile eseguire la malloc su tour info");
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, casacostruttrice, sizeof(casacostruttrice));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &numeroposti, sizeof(numeroposti));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, nomecomfort, sizeof(nomecomfort));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, descrizionecomfort, sizeof(descrizionecomfort));
	set_binding_param(&param[4], MYSQL_TYPE_BLOB, foto, sizeof(foto));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, descrizionefoto, sizeof(descrizionefoto));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, &idfoto, sizeof(idfoto));

	if (mysql_stmt_bind_result(select_model_comfort, param))
	{
		print_stmt_error(select_model_comfort, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_modello);
		info_modello = NULL;
		goto stop;
	}

	info_modello->num_modelli = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_model_comfort);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_model_comfort, "\nImpossibile eseguire fetch");
		}

		strcpy(info_modello->info_modelli[count].casacostruttrice, casacostruttrice);
		info_modello->info_modelli[count].numeroposti = numeroposti;
		strcpy(info_modello->info_modelli[count].nomecomfort, nomecomfort);
		strcpy(info_modello->info_modelli[count].descrizionecomfort, descrizionecomfort);
		strcpy(info_modello->info_modelli[count].foto, foto);
		strcpy(info_modello->info_modelli[count].descrizionefoto, descrizionefoto);
		info_modello->info_modelli[count].idfoto = idfoto;

		cmpr = strcmp(info_modello->info_modelli[count].casacostruttrice, info_modello->info_modelli[count - 1].casacostruttrice);

		if (cmpr != 0)
		{
			printf("Casa costruttrice:	%s \n", info_modello->info_modelli[count].casacostruttrice);
			printf("Numero di posti:	%d	\n\n", info_modello->info_modelli[count].numeroposti);
		}
		printf("Comfort:	 	%s \n", info_modello->info_modelli[count].nomecomfort);
		printf("%s \n", info_modello->info_modelli[count].descrizionecomfort);

		if (info_modello->info_modelli[count].idfoto != info_modello->info_modelli[count - 1].idfoto)
		{
			printf("%s\n", info_modello->info_modelli[count].foto);
			printf("Descrizione foto:%s\n\n", info_modello->info_modelli[count].descrizionefoto);
		}
		count++;
	}
stop:
	mysql_stmt_free_result(select_model_comfort);
	mysql_stmt_reset(select_model_comfort);
	free(info_modello);
};

struct revisioni_scadute *get_info_revisioni(void)
{
	MYSQL_BIND param[4];
	MYSQL_TIME datafine;

	struct revisioni_scadute *info_revisioni = NULL;
	char *buff = "select_expired_review";
	char mezzorevisionato[VARCHAR_LEN];
	int chilometraggio;
	int valorekm;

	size_t rows;
	int count, status, cmpr;
	count = 0;

	init_mysql_timestamp(&datafine);

	rows = take_rows(select_expired_review, buff);
	if(rows == -1)
		goto stop;

	info_revisioni = malloc((sizeof(struct revisioni_scadute) + sizeof(info_revisioni)) * rows);
	memset(info_revisioni, 0, sizeof(*info_revisioni) + sizeof(struct revisioni_scadute) * rows);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzorevisionato, sizeof(mezzorevisionato));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &chilometraggio, sizeof(chilometraggio));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &valorekm, sizeof(valorekm));

	if (mysql_stmt_bind_result(select_expired_review, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_expired_review, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_revisioni);
		info_revisioni = NULL;
		goto stop;
	}

	info_revisioni->num_revisione = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_expired_review);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			printf("Procedura: %s", buff);
			print_stmt_error(select_expired_review, "\nImpossibile eseguire fetch");
		}
		strcpy(info_revisioni->revisioni_scadute[count].mezzorevisionato, mezzorevisionato);
		mysql_date_to_string(&datafine, info_revisioni->revisioni_scadute[count].datafine);
		info_revisioni->revisioni_scadute[count].chilometraggio = chilometraggio;
		info_revisioni->revisioni_scadute[count].idrevisione = valorekm;
		cmpr = strcmp(info_revisioni->revisioni_scadute[count].mezzorevisionato, info_revisioni->revisioni_scadute[count - 1].mezzorevisionato);
		if (cmpr != 0)
		{
			printf("*Targa mezzo:		%s \n", info_revisioni->revisioni_scadute[count].mezzorevisionato);
			printf("Data ultima revisione:	%s	\n", info_revisioni->revisioni_scadute[count].datafine);
			printf("Chilometri revisone:	%d \n", info_revisioni->revisioni_scadute[count].chilometraggio);
			printf("Chilometri attuali:	%d	\n\n", info_revisioni->revisioni_scadute[count].idrevisione);
		}

		count++;
	}
stop:
	mysql_stmt_free_result(select_expired_review);
	mysql_stmt_reset(select_expired_review);
	free(info_revisioni);
};

struct servizi_albergo *get_servizi_albergo(int idh)
{
	MYSQL_BIND param[2];

	struct servizi_albergo *info_servizi = NULL;
	char *buff = "select_hotel_service";
	char nomeservizio[VARCHAR_LEN];
	char descrizioneservizio[DES_LEN];
	size_t rows;
	int count, status;
	count = 0;

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idh, sizeof(idh));

	bind_exe(select_hotel_service, param, buff);
	rows = take_rows(select_hotel_service, buff);
	if(rows == -1)
		goto stop;

	info_servizi = malloc((sizeof(struct servizi_albergo) + sizeof(info_servizi)) * rows);
	memset(info_servizi, 0, sizeof(*info_servizi) + sizeof(struct servizi_albergo) * rows);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nomeservizio, sizeof(nomeservizio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, descrizioneservizio, sizeof(descrizioneservizio));

	if (mysql_stmt_bind_result(select_hotel_service, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_hotel_service, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_servizi);
		info_servizi = NULL;
		goto stop;
	}

	info_servizi->num_servizi = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_hotel_service);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			printf("Procedura: %s", buff);
			print_stmt_error(select_hotel_service, "\nImpossibile eseguire fetch");
		}
		strcpy(info_servizi->servizi_albergo[count].nomeservizio, nomeservizio);
		strcpy(info_servizi->servizi_albergo[count].descrizioneservizio, descrizioneservizio);

		printf("* %s *\n", info_servizi->servizi_albergo[count].nomeservizio);
		printf("Descrizione:		%s	\n\n", info_servizi->servizi_albergo[count].descrizioneservizio);

		count++;
	}
stop:
	mysql_stmt_free_result(select_hotel_service);
	mysql_stmt_reset(select_hotel_service);
};

struct info_mete *get_mete_info(int idv)
{
	MYSQL_BIND param[14];
	MYSQL_TIME darrivo;
	MYSQL_TIME dpartenza;
	MYSQL_TIME oarrivo;
	MYSQL_TIME opartenza;
	MYSQL_TIME oapertura;
	
	struct info_mete *info_mete = NULL;
	int status;
	int cmpr;
	char *buff = "select_dest_tour";
	char nome[VARCHAR_LEN];
	float supplemento;
	int codicealbergo;
	char tipologiameta[VARCHAR_LEN];
	char desfoto[VARCHAR_LEN];
	char foto[BLOB_LEN];
	signed char guida;
	char trattamento[VARCHAR_LEN];
	char categoriaalbergo[VARCHAR_LEN];
	size_t rows, count;
	count = 0;

	init_mysql_timestamp(&darrivo);
	init_mysql_timestamp(&dpartenza);
	init_mysql_timestamp(&oarrivo);
	init_mysql_timestamp(&opartenza);
	init_mysql_timestamp(&oapertura); 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idv, sizeof(idv));

	bind_exe(select_dest_tour, param, buff);

	rows = take_rows(select_dest_tour, buff);
	if(rows == -1)
		goto stop;

	info_mete = malloc((sizeof(struct mete_tour) + sizeof(info_mete)) * rows);
	memset(info_mete, 0, sizeof(*info_mete) + sizeof(struct mete_tour) * rows);

	if (info_mete == NULL)
	{
		printf("Impossibile eseguire la malloc su %s", buff);
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome, sizeof(nome));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &darrivo, sizeof(darrivo));
	set_binding_param(&param[2], MYSQL_TYPE_TIME, &oarrivo, sizeof(oarrivo));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &dpartenza, sizeof(dpartenza));
	set_binding_param(&param[4], MYSQL_TYPE_TIME, &opartenza, sizeof(opartenza));
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &supplemento, sizeof(supplemento));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, tipologiameta, sizeof(tipologiameta));
	set_binding_param(&param[7], MYSQL_TYPE_TINY, &guida, sizeof(guida));
	set_binding_param(&param[8], MYSQL_TYPE_TIME, &oapertura, sizeof(oapertura));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, trattamento, sizeof(trattamento));
	set_binding_param(&param[10], MYSQL_TYPE_VAR_STRING, categoriaalbergo, sizeof(categoriaalbergo));
	set_binding_param(&param[11], MYSQL_TYPE_VAR_STRING, desfoto, sizeof(desfoto));
	set_binding_param(&param[12], MYSQL_TYPE_BLOB, foto, sizeof(foto));
	set_binding_param(&param[13], MYSQL_TYPE_LONG, &codicealbergo, sizeof(codicealbergo));

	if (mysql_stmt_bind_result(select_dest_tour, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_dest_tour, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_mete);
		info_mete = NULL;
		goto stop;
	}

	info_mete->num_mete = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_dest_tour);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_dest_tour, "\nImpossibile eseguire fetch");
		}
		strcpy(info_mete->info_mete[count].nome, nome);
		strcpy(info_mete->info_mete[count].tipologiameta, tipologiameta);
		mysql_date_to_string(&darrivo, info_mete->info_mete[count].darrivo);
		mysql_date_to_string(&dpartenza, info_mete->info_mete[count].dpartenza);
		mysql_time_to_string(&oarrivo, info_mete->info_mete[count].oarrivo);
		mysql_time_to_string(&opartenza, info_mete->info_mete[count].opartenza);
		mysql_time_to_string(&oapertura, info_mete->info_mete[count].oapertura);

		info_mete->info_mete[count].supplemento = supplemento;
		info_mete->info_mete[count].codicealbergo = codicealbergo;

		strcpy(info_mete->info_mete[count].trattamento, trattamento);
		strcpy(info_mete->info_mete[count].categoriaalbergo, categoriaalbergo);
		strcpy(info_mete->info_mete[count].desfoto, desfoto);
		strcpy(info_mete->info_mete[count].foto, foto);

		cmpr = strcmp(info_mete->info_mete[count].nome, info_mete->info_mete[count - 1].nome);
		if (cmpr != 0)
		{
			printf("* %s *\n", info_mete->info_mete[count].nome);
			printf("Data di arrivo:		%s	", info_mete->info_mete[count].darrivo);
			printf("Ora di arrivo:	  	%s \n", info_mete->info_mete[count].oarrivo);
			printf("Data di partenza:	%s	", info_mete->info_mete[count].dpartenza);
			printf("Ora di partenza: 	%s \n", info_mete->info_mete[count].opartenza);
			printf("Supplemento:		%f euro\n", info_mete->info_mete[count].supplemento);
			printf("Tipologia meta:		%s 	\n", info_mete->info_mete[count].tipologiameta);

			if (strcmp(info_mete->info_mete[count].tipologiameta, "Bene") == 0)
			{
				printf("Orario di apertura:	%s 	\n", info_mete->info_mete[count].oapertura);
				printf("Guida prevista:		%d 	\n", info_mete->info_mete[count].guida);
			}
			else
			{
				printf("Trattamento:		%s \n", info_mete->info_mete[count].trattamento);
				printf("Categoria:		%s 	\n", info_mete->info_mete[count].categoriaalbergo);
				printf("Codice albergo:		%d \n", info_mete->info_mete[count].codicealbergo);
			}
		}
		printf("\n");
		printf("Foto:  %s	\n", info_mete->info_mete[count].foto);
		printf("Descrizione foto:	%s \n\n", info_mete->info_mete[count].desfoto);

		count++;
	}
stop:
	mysql_stmt_free_result(select_dest_tour);
	mysql_stmt_reset(select_dest_tour);
	free(info_mete);
};

struct tour_info *get_tour_info(void)
{
	MYSQL_BIND param[13];
	MYSQL_TIME dpv;
	MYSQL_TIME drv;

	struct tour_info *tour_info = NULL;
	char *buff = "select_all_tour";
	char dnm[VARCHAR_LEN];
	char dsc[DES_LEN];
	char nmd[VARCHAR_LEN];
	int mnp;
	int pds;
	int cmpr;
	int cdv;
	int status;
	float mdc;
	float bgl;
	float gnl;
	float csv;
	signed char acm;
	size_t rows, count;
	count = 0;

	init_mysql_timestamp(&dpv);
	init_mysql_timestamp(&drv);

	rows = take_rows(select_all_tour, buff);
	if(rows == -1)
		goto stop;

	tour_info = malloc((sizeof(struct tour_viaggi) + sizeof(tour_info)) * rows);
	memset(tour_info, 0, sizeof(*tour_info) + sizeof(struct tour_viaggi) * rows);

	if (tour_info == NULL)
	{
		printf("Impossibile eseguire la malloc su tour info");
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, dnm, sizeof(dnm));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dsc, sizeof(dsc));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &mnp, sizeof(mnp));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &mdc, sizeof(mdc));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &bgl, sizeof(bgl));
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &gnl, sizeof(gnl));
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &acm, sizeof(acm));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, nmd, sizeof(nmd));
	set_binding_param(&param[8], MYSQL_TYPE_DATE, &dpv, sizeof(dpv));
	set_binding_param(&param[9], MYSQL_TYPE_DATE, &drv, sizeof(drv));
	set_binding_param(&param[10], MYSQL_TYPE_FLOAT, &csv, sizeof(csv));
	set_binding_param(&param[11], MYSQL_TYPE_LONG, &pds, sizeof(pds));
	set_binding_param(&param[12], MYSQL_TYPE_LONG, &cdv, sizeof(cdv));

	if (mysql_stmt_bind_result(select_all_tour, param))
	{
		print_stmt_error(select_all_tour, "\n\n Impossibile eseguire il bind risult\n\n");
		free(tour_info);
		tour_info = NULL;
		goto stop;
	}

	tour_info->num_tour = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_all_tour);
		if (status == MYSQL_NO_DATA)
			break;
		if (status == 1)
		{
			print_stmt_error(select_all_tour, "\nImpossibile eseguire fetch");
		}
		strcpy(tour_info->tour_info[count].denominazionetour, dnm);
		strcpy(tour_info->tour_info[count].descrizionetour, dsc);

		tour_info->tour_info[count].minimopartecipanti = mnp;
		tour_info->tour_info[count].assicurazionemedica = mdc;
		tour_info->tour_info[count].bagaglio = bgl;
		tour_info->tour_info[count].garanziaannullamento = gnl;
		tour_info->tour_info[count].accompagnatrice = acm;
		tour_info->tour_info[count].codiceviaggio = cdv;

		cmpr = strcmp(tour_info->tour_info[count].denominazionetour, tour_info->tour_info[count - 1].denominazionetour);

		if (cmpr != 0)
		{
			printf("* %s *\n", tour_info->tour_info[count].denominazionetour);
			printf("Descrizione tour:	%s 	\n", tour_info->tour_info[count].descrizionetour);
			printf("Minimo partecipanti:	 %d 	\n", tour_info->tour_info[count].minimopartecipanti);
			printf("Diritti iscrizione: \n");
			printf("Assicurazione medica:	 %f euro\n", tour_info->tour_info[count].assicurazionemedica);
			printf("Bagaglio:		 %f euro\n", tour_info->tour_info[count].bagaglio);
			printf("Garanzia di annullamento:%f euro\n", tour_info->tour_info[count].garanziaannullamento);
			printf("\n-Accompagnatrice prevista:%d 	\n", tour_info->tour_info[count].accompagnatrice);
			printf("\n\nViaggi previsti :\n");
		}
		strcpy(tour_info->tour_info[count].nomemodello, nmd);
		mysql_date_to_string(&dpv, tour_info->tour_info[count].datadipartenzaviaggio);
		mysql_date_to_string(&drv, tour_info->tour_info[count].datadiritornoviaggio);
		tour_info->tour_info[count].costodelviaggio = csv;
		tour_info->tour_info[count].postidisponibili = pds;
		tour_info->tour_info[count].codiceviaggio = cdv;

		printf("Modello pullman:	%s \n", tour_info->tour_info[count].nomemodello);
		printf("Codice viaggio: 	%d \n", tour_info->tour_info[count].codiceviaggio);
		printf("Data di partenza:	%s 	\n", tour_info->tour_info[count].datadipartenzaviaggio);
		printf("Data di riotrno:	%s 	\n", tour_info->tour_info[count].datadiritornoviaggio);
		printf("Prezzo:			%f euro	\n", tour_info->tour_info[count].costodelviaggio);
		printf("Posti disponibili:	%d 	\n", tour_info->tour_info[count].postidisponibili);
		printf("\n");
		count++;
	}
stop:
	mysql_stmt_free_result(select_all_tour);
	mysql_stmt_reset(select_all_tour);
	free(tour_info);
}

struct viaggi_assegnati *get_viaggi_assegnati(char *dvr)
{
	MYSQL_BIND param[9];
	MYSQL_TIME ddp;
	MYSQL_TIME ddr;

	struct viaggi_assegnati *viaggi_assegnati = NULL;
	char *buff = "select_assigned_trip";
	int status; 
	size_t rows, count;
	count = 0;

	char tour[VARCHAR_LEN];
	int viaggio; 
	char modello[VARCHAR_LEN];
	char targa[TAR_LEN];
	int autonomia; 
	char ingombri [VARCHAR_LEN]; 
	int contakm; 

	init_mysql_timestamp(&ddp);
	init_mysql_timestamp(&ddr);


	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, dvr, strlen(dvr));


	 
	 bind_exe(select_assigned_trip, param, buff);
	 rows = take_rows(select_assigned_trip, buff);
	if(rows == -1)
		goto stop; 

	viaggi_assegnati = malloc((sizeof(struct viaggi_mezzi) + sizeof(viaggi_assegnati)) * rows);
	memset(viaggi_assegnati, 0, sizeof(*viaggi_assegnati) + sizeof(struct viaggi_mezzi) * rows);

	if (viaggi_assegnati == NULL)
	{
		printf("Impossibile eseguire la malloc su tour info");
		goto stop;
	}


	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour,  sizeof(tour));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggio, sizeof(viaggio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, modello, sizeof(modello));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, targa, sizeof(targa));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &autonomia, sizeof(autonomia));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, ingombri, sizeof(ingombri));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, &contakm, sizeof(contakm));
	set_binding_param(&param[7], MYSQL_TYPE_DATE, &ddp, sizeof(ddp));
	set_binding_param(&param[8], MYSQL_TYPE_DATE, &ddr, sizeof(ddr));
	
	if (mysql_stmt_bind_result(select_assigned_trip, param))
	{
		print_stmt_error(select_assigned_trip, "\n\n Impossibile eseguire il bind risult\n\n");
		free(viaggi_assegnati);
		viaggi_assegnati = NULL;
		goto stop;
	}

	viaggi_assegnati->num_viaggi = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_assigned_trip);
		if (status == MYSQL_NO_DATA)
			break;
		if (status == 1)
		{
			print_stmt_error(select_assigned_trip, "\nImpossibile eseguire fetch");
		}

		strcpy(viaggi_assegnati->viaggi_assegnati[count].tour, tour);
		strcpy(viaggi_assegnati->viaggi_assegnati[count].modello, modello);
		strcpy(viaggi_assegnati->viaggi_assegnati[count].targa, targa);
		strcpy(viaggi_assegnati->viaggi_assegnati[count].ingombri, ingombri);
		mysql_date_to_string(&ddp,viaggi_assegnati->viaggi_assegnati[count].partenza ); 
		mysql_date_to_string(&ddr,viaggi_assegnati->viaggi_assegnati[count].ritorno);


		viaggi_assegnati->viaggi_assegnati[count].viaggio = viaggio;
		viaggi_assegnati->viaggi_assegnati[count].autonomia= autonomia;
		viaggi_assegnati->viaggi_assegnati[count].contakm = contakm;

		printf("* %s *\n", viaggi_assegnati->viaggi_assegnati[count].tour);
		printf("Codice viaggio: 	%d \n", viaggi_assegnati->viaggi_assegnati[count].viaggio);
		printf("Data di partenza:	%s 	\n", viaggi_assegnati->viaggi_assegnati[count].partenza);
		printf("Data di riotrno:	%s 	\n\n", viaggi_assegnati->viaggi_assegnati[count].ritorno);
		printf("Mezzo impiegato\n");
		printf("Modello pullman:	%s \n", viaggi_assegnati->viaggi_assegnati[count].modello);
		printf("Targa:			%s 	\n", viaggi_assegnati->viaggi_assegnati[count].targa);
		printf("Autonomia mezzo:	%d km	\n", viaggi_assegnati->viaggi_assegnati[count].autonomia);
		printf("Ingombri:		%s \n", viaggi_assegnati->viaggi_assegnati[count].ingombri);	
		printf("Valore conta km:	%d 	\n\n", viaggi_assegnati->viaggi_assegnati[count].contakm);
		count++;
	}
stop:
	mysql_stmt_free_result(select_assigned_trip);
	mysql_stmt_reset(select_assigned_trip);
	free(viaggi_assegnati);
}

struct mete_visite *get_mete_visite(int idv)
{
	MYSQL_BIND param[9];
	MYSQL_TIME darrivo;
	MYSQL_TIME dpartenza;
	MYSQL_TIME oarrivo;
	MYSQL_TIME opartenza;
	

	struct mete_visite *mete_visite = NULL;
	int status;
	int cmpr;
	char *buff = "select_dest_time";

	char nome [VARCHAR_LEN]; 
	char tipologia[VARCHAR_LEN]; 
	char localita[VARCHAR_LEN];
	char regione[VARCHAR_LEN]; 
	char indirizzo[VARCHAR_LEN];
	char arrivo[DATE_LEN];
	char ingresso[TIME_LEN]; 
	char partenza[DATE_LEN]; 
	char uscita[TIME_LEN]; 
	
	size_t rows, count;
	count = 0;

	init_mysql_timestamp(&darrivo);
	init_mysql_timestamp(&dpartenza);
	init_mysql_timestamp(&oarrivo);
	init_mysql_timestamp(&opartenza);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idv, sizeof(idv));

	bind_exe(select_dest_time, param, buff);
	rows =take_rows(select_dest_time, buff); 
	if(rows ==-1)
		goto stop; 

	mete_visite = malloc((sizeof(struct mete_visite) + sizeof(mete_visite)) * rows);
	memset(mete_visite, 0, sizeof(*mete_visite) + sizeof(struct mete_visite) * rows);

	if (mete_visite == NULL)
	{
		printf("Impossibile eseguire la malloc su %s", buff);
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome, sizeof(nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tipologia, sizeof(tipologia));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, localita, sizeof(localita));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, regione, sizeof(regione));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, indirizzo, sizeof(indirizzo));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &darrivo, sizeof(darrivo));
	set_binding_param(&param[6], MYSQL_TYPE_TIME, &oarrivo, sizeof(oarrivo));
	set_binding_param(&param[7], MYSQL_TYPE_DATE, &dpartenza, sizeof(dpartenza));
	set_binding_param(&param[8], MYSQL_TYPE_TIME, &opartenza, sizeof(opartenza));
	
	if (mysql_stmt_bind_result(select_dest_time, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_dest_time, "\n\n Impossibile eseguire il bind risult\n\n");
		free(mete_visite);
		mete_visite = NULL;
		goto stop;
	}

	mete_visite->num_visite = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_dest_time);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_dest_time, "\nImpossibile eseguire fetch");
		}
		strcpy(mete_visite->mete_visite[count].nome, nome);
		strcpy(mete_visite->mete_visite[count].tipologia, tipologia);
		strcpy(mete_visite->mete_visite[count].localita, localita);
		strcpy(mete_visite->mete_visite[count].regione, regione);
		strcpy(mete_visite->mete_visite[count].indirizzo, indirizzo);
		mysql_date_to_string(&darrivo, mete_visite->mete_visite[count].arrivo);
		mysql_date_to_string(&dpartenza, mete_visite->mete_visite[count].partenza);
		mysql_time_to_string(&oarrivo, mete_visite->mete_visite[count].ingresso);
		mysql_time_to_string(&opartenza, mete_visite->mete_visite[count].uscita);
		
		printf("* %s *\n", mete_visite->mete_visite[count].nome);
		printf("Tipologia meta:		%s 	\n", mete_visite->mete_visite[count].tipologia);
		printf("Località:		%s 	\n", mete_visite->mete_visite[count].localita);
		printf("Regione:		%s 	\n", mete_visite->mete_visite[count].regione);
		printf("Indirizzo:		%s 	\n", mete_visite->mete_visite[count].indirizzo);
		printf("Data di arrivo:		%s	", mete_visite->mete_visite[count].arrivo);
		printf("Ora di arrivo:	  	%s \n", mete_visite->mete_visite[count].ingresso);
		printf("Data di partenza:	%s	", mete_visite->mete_visite[count].partenza);
		printf("Ora di partenza: 	%s \n\n", mete_visite->mete_visite[count].uscita);
		
		count++;
	}
stop:
	mysql_stmt_free_result(select_dest_time);
	mysql_stmt_reset(select_dest_time);
	free(mete_visite);
};

struct mappe *get_mappe (char* nml)
{
	MYSQL_BIND param[4];

	struct mappe *mappe = NULL;
	int status;
	int cmpr;
	char *buff = "select_dvr_map";

	char citta[VARCHAR_LEN];
	char dettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char immagine[VARCHAR_LEN];	

	size_t rows, count;
	count = 0;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nml, strlen(nml));

	bind_exe(select_dvr_map, param, buff);
	rows = take_rows(select_dvr_map, buff);
	if(rows == -1)
		goto stop; 

	mappe = malloc((sizeof(struct mappe) + sizeof(mappe)) * rows);

	memset(mappe, 0, sizeof(*mappe) + sizeof(struct mappe) * rows);

	if (mappe == NULL)
	{
		printf("Impossibile eseguire la malloc su %s", buff);
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, citta, sizeof(citta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dettaglio, sizeof(dettaglio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, zona, sizeof(zona));
	set_binding_param(&param[3], MYSQL_TYPE_BLOB, immagine, sizeof(immagine));
	
	
	if (mysql_stmt_bind_result(select_dvr_map, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_dvr_map, "\n\n Impossibile eseguire il bind risult\n\n");
		free(mappe);
		mappe = NULL;
		goto stop;
	}

	mappe->num_mappe = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_dvr_map);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_dvr_map, "\nImpossibile eseguire fetch");
		}

		strcpy(mappe->mappe[count].citta, citta);
		strcpy(mappe->mappe[count].dettaglio, dettaglio);
		strcpy(mappe->mappe[count].zona, zona);
		strcpy(mappe->mappe[count].immagine, immagine);
		
		printf("* %s *\n", mappe->mappe[count].citta);
		printf("Dettaglio:		%s 	\n", mappe->mappe[count].dettaglio);
		printf("Zona:			%s 	\n", mappe->mappe[count].zona);
		printf("Immagine:		%s 	\n\n", mappe->mappe[count].immagine);
		
		count++;
	}
stop:
	mysql_stmt_free_result(select_dvr_map);
	mysql_stmt_reset(select_dvr_map);
	free(mappe);
}



struct prenotazioni_info *get_reservation_info (char *mlc)
{
	MYSQL_BIND param[2];
	MYSQL_TIME ddp;

	struct prenotazioni_info *prenotazioni_info = NULL;
	char *buff = "select_reservation_info";
	int status; 
	size_t rows, count;
	count = 0;

	int nmp; 

	init_mysql_timestamp(&ddp);
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mlc, strlen(mlc));

	bind_exe(select_reservation_info, param, buff);
	rows = take_rows(select_reservation_info, buff);


	if(rows == -1)
		goto stop; 

	prenotazioni_info = malloc((sizeof(struct prenotazione) + sizeof(prenotazioni_info)) * rows);

	memset(prenotazioni_info, 0, sizeof(*prenotazioni_info) + sizeof(struct prenotazione) * rows);

	if (prenotazioni_info == NULL)
	{
		printf("Impossibile eseguire la malloc su prenotazioni info");
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &nmp  , sizeof(nmp));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &ddp,  sizeof(ddp));

	
	if (mysql_stmt_bind_result(select_reservation_info, param))
	{
		print_stmt_error(select_reservation_info, "\n\n Impossibile eseguire il bind risult\n\n");
		free(prenotazioni_info);
		prenotazioni_info = NULL;
		goto stop;
	}
	
	prenotazioni_info->num_prenotazioni = rows; 
			
	while (true)
	{
		status = mysql_stmt_fetch(select_reservation_info);
			
		if (status == MYSQL_NO_DATA)
			break;
		if (status == 1)
		{
			print_stmt_error(select_reservation_info, "\nImpossibile eseguire fetch");
		}

		prenotazioni_info->prenotazioni_info[count].numerodiprenotazione = nmp; 
		mysql_date_to_string(&ddp,prenotazioni_info->prenotazioni_info[count].datadiconferma ); 

		printf("* Cliente %s *\n", mlc);
		printf("Numero prenotazione: 	%d \n", prenotazioni_info->prenotazioni_info[count].numerodiprenotazione);
		printf("Data di prenotazione:	%s 	\n", prenotazioni_info->prenotazioni_info[count].datadiconferma);
		count++;
	}
stop:

	mysql_stmt_free_result(select_reservation_info);
	mysql_stmt_reset(select_reservation_info);
	free(prenotazioni_info);
}
#pragma once
#include <stdbool.h>
#include <stdlib.h>	

#include "../utils/io.h"


extern bool init_db(void);
extern void fini_db(void);
							
#define DATE_LEN 11
#define TIME_LEN 6
#define DATETIME_LEN (DATE_LEN + TIME_LEN)
#define NUM_LEN 45
#define DEC_LEN 10
#define TEL_LEN 16 
#define TAR_LEN 10
#define BLOB_LEN 45
#define USERNAME_LEN 45
#define PASSWORD_LEN 8
#define PIC 45
#define BIT_LEN 2
#define VARCHAR_LEN 45
#define DES_LEN 5000



struct credentials {
	char username[USERNAME_LEN];
	char password[PASSWORD_LEN];
};

typedef enum {
	LOGIN_ROLE,
	AUTISTA,
	CLIENTE,
	HOSTESS,
	MECCANICO,
	MANAGER,
	QUIT,
	FAILED_LOGIN
} role_t;

extern void db_switch_to_login(void);
extern role_t attempt_login(struct credentials *cred);
extern void db_switch_to_administrator(void);

struct soggiorno{
	int  idsoggiorno; 
	int  cameraprenotata; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  ospite; 						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  albergoinquestione; 			//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  prenotazioneinquestione;
	char datainiziosoggiorno[DATE_LEN]; 
	char datafinesoggiorno[DATE_LEN];
}; 

struct camera {
	int numerocamera;
	int albergo;						//FK
	char tipologia[VARCHAR_LEN];
	float costo ;
};

struct cliente {
	char emailcliente[VARCHAR_LEN];
	char nomecliente[VARCHAR_LEN];
	char cognomecliente[VARCHAR_LEN];
	char indirizzocliente[VARCHAR_LEN];
	char codicefiscale[VARCHAR_LEN];
	char datadocumentazione[DATE_LEN];
	char recapitotelefonico[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char fax[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
};

struct comfort {
	int idcomfort; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomecomfort[VARCHAR_LEN]; 
	char descrizionecomfort[DES_LEN]; 

};

struct comfort_mezzo{
	size_t num_comfort; 
	struct comfort comfort_mezzo[]; 
};

struct competenze {
	char meccanicocompetente[VARCHAR_LEN]; 
	char modelloassociato[VARCHAR_LEN];
	// viariabili d'appoggio
	char nomemeccanico [VARCHAR_LEN]; 
	char telefono[TEL_LEN];
}; 

struct dipendente{
	char emaildipendente[VARCHAR_LEN]; 
	char tipologiadipendente[VARCHAR_LEN];
	char telefonoaziendale [TEL_LEN]; 
	char nomedipendente[VARCHAR_LEN];
	char cognomedipendente[VARCHAR_LEN];
};

struct documentazionefotografica {
	
	 int idfoto; 
	 char foto [BLOB_LEN]; 
	 char descrzione[DES_LEN]; 
	 
};

struct fmo{
	int foto; 
	char modello[VARCHAR_LEN]; 
	//
	char descrizione[DES_LEN];
	char immagine[BLOB_LEN];  
};

struct fme{
	int foto; 
	int meta; 
	//
	char nome[VARCHAR_LEN];
	char descrizione[DES_LEN]; 
	char immagine[BLOB_LEN];
}; 

struct foto_mete {
	size_t num_pic;
	struct documentazionefotografica foto_mete[]; 
}; 

struct localita {
	char nomelocalita[VARCHAR_LEN];
	char regione[VARCHAR_LEN];
	char stato[VARCHAR_LEN];
};

struct mappa {
	int idmappa; //Corretto trasformandolo da carattere a puntatore di carattere
	char citta[VARCHAR_LEN];
	char dettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char immagine[BLOB_LEN]; 
	char localitarappresentata[VARCHAR_LEN]; 		//FK
};

struct meta { 
	int idmeta; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomemeta[VARCHAR_LEN]; 
	char emailmeta[VARCHAR_LEN]; 
	char telefonometa[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char faxmeta[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char indirizzo[VARCHAR_LEN]; 
	char tipologiameta[VARCHAR_LEN]; 
	char categoriaalbergo[VARCHAR_LEN]; 
	char orariodiapertura[TIME_LEN]; 
	char localitadiappartenenza[VARCHAR_LEN]; 		//FK
	char regiodiappartenennza[VARCHAR_LEN]; 
};

struct mete_viaggio{	
	size_t num_vme; 
	struct meta mete_viaggio[]; 
}; 

struct mezzo {
	char targa[TAR_LEN];
	char modellomezzo[VARCHAR_LEN]; 
	char dataultimarevisioneinmotorizzazione[DATE_LEN]; 					
	char ingombri[VARCHAR_LEN];	
	int autonomia; //Corretto trasformandolo da carattere a puntatore di carattere
	int valorecontakm; //Corretto trasformandolo da carattere a puntatore di carattere
	char dataimmatricolazione[DATE_LEN]; 
};

struct modello {
	char nomemodello[VARCHAR_LEN];
	char datitecnici[DES_LEN]; 
	char casacostruttrice[VARCHAR_LEN];
	int numeroposti; //Corretto trasformandolo da carattere a puntatore di carattere
	int numeromeccanicicompetenti; 
}; 

struct modelli_comfort {
	char casacostruttrice[VARCHAR_LEN];
	int numeroposti;
	char nomecomfort[VARCHAR_LEN]; 
	char descrizionecomfort[DES_LEN];
	char foto [PIC]; 
	char descrizionefoto[DES_LEN]; 
	int idfoto; 
}; 

struct info_modelli {
	size_t num_modelli; 
	struct modelli_comfort info_modelli[]; 
};

struct offre {
	int idservizio; 
	int albergoofferente; 					

	char servizio[VARCHAR_LEN]; 
	char meta [VARCHAR_LEN]; 
	char descrizione [DES_LEN]; 
}; 

struct postoprenotato {
	int numerodiposto; //Corretto trasformandolo da carattere a puntatore di carattere					//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	int prenotazioneassociata; 				//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	int etapasseggero;  //Corretto trasformandolo da carattere a puntatore di carattere
	char nomepasseggero[VARCHAR_LEN]; 
	char cognomepasseggero[VARCHAR_LEN]; 
}; 

struct prenotazione {
	int numerodiprenotazione;
	int viaggioassociato; 
	int numerodipostiprenotati; 
	char clienteprenotante[VARCHAR_LEN];
	char datadiprenotazione[DATE_LEN]; 
	char datadiconferma[DATE_LEN]; 
	char datasaldo[DATE_LEN]; 
}; 


struct prenotazioni_info{
	size_t num_prenotazioni; 
	struct prenotazione prenotazioni_info[]; 
};

struct presenti {
	int comfortpresenti; //Corretto trasformandolo da carattere a puntatore di carattere
	char modelloassciato[VARCHAR_LEN]; 
};

struct revisione {
	int idrevisione; //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzorevisionato[VARCHAR_LEN]; 			// Fk
	char addettoallarevisione[VARCHAR_LEN];  				// Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char datainizio[DATE_LEN]; 
	char datafine[DATE_LEN]; 
	int chilometraggio;//Corretto trasformandolo da carattere a puntatore di carattere
	char operazionieseguite[DES_LEN]; 
	char motivazione[DES_LEN]; 
};

struct revisioni_scadute {
	size_t num_revisione; 
	struct revisione revisioni_scadute [];
};

struct ricambio {
	char codice [VARCHAR_LEN]; 
	float costounitario; //Corretto trasformandolo da carattere a puntatore di carattere
	int quantitadiriordino; //Corretto trasformandolo da carattere a puntatore di carattere
	char descrizione[DES_LEN]; 
	int scortaminima; //Corretto trasformandolo da carattere a puntatore di carattere
	int quantitainmagazzino;  //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct rt {
	int  revisionerelativa; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  tagliandoassociato; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct servizio {
	int idservizio; 
	char nomeservizio[VARCHAR_LEN];
	char descrizioneservizio[DES_LEN]; 
}; 

struct  servizi_albergo{
	size_t num_servizi; 
	struct servizio servizi_albergo[]; 
};

struct sostituito{
	int revisioneassociata; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char ricambioutilizzato [VARCHAR_LEN]; 			//FK
	int quantitasostituita; 
}; 


struct tagliando {
	int idtagliando; //Corretto trasformandolo da carattere a puntatore di carattere
	char tipologiatagliando[VARCHAR_LEN]; 
	char validitasuperate[DES_LEN];
}; 


struct tour {
	char denominazionetour[VARCHAR_LEN]; 
	char descrizionetour[DES_LEN]; 
	int minimopartecipanti; //Corretto trasformandolo da carattere a puntatore di carattere
	float assicurazionemedica; //Corretto trasformandolo da carattere a puntatore di carattere
	float bagaglio; //Corretto trasformandolo da carattere a puntatore di carattere
	float garanziaannullamento; 
	signed char accompagnatrice; //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct viaggio {
	int idviaggio; //Corretto trasformandolo da carattere a puntatore di carattere
	char tourassociato[VARCHAR_LEN]; 
	char conducente [VARCHAR_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char accompagnatrice[VARCHAR_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzoimpiegato[TAR_LEN]; 			// FK
	char datadipartenzaviaggio[DATE_LEN]; 
	char datadiritornoviaggio[DATE_LEN]; 
	float costodelviaggio;  //Corretto trasformandolo da carattere a puntatore di carattere
	int numerodikm; //Corretto trasformandolo da carattere a puntatore di carattere
	int postidisponibili; //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiannullamento[DATE_LEN]; 
};

struct tour_viaggi{
	char denominazionetour[VARCHAR_LEN]; 
	char descrizionetour[DES_LEN]; 
	int minimopartecipanti; //Corretto trasformandolo da carattere a puntatore di carattere
	float assicurazionemedica; //Corretto trasformandolo da carattere a puntatore di carattere
	float bagaglio; //Corretto trasformandolo da carattere a puntatore di carattere
	float garanziaannullamento; 
	signed char accompagnatrice;
	char nomemodello[VARCHAR_LEN];
	char datadipartenzaviaggio[DATETIME_LEN]; 
	char datadiritornoviaggio[DATETIME_LEN]; 
	float costodelviaggio;
	int postidisponibili;
	int codiceviaggio; 
}; 

struct tour_info{
	size_t num_tour; 
	struct tour_viaggi tour_info[]; 
}; 

struct utente {
	char email[VARCHAR_LEN];
	char pswrd[PASSWORD_LEN]; 
	int tipo;
};

struct visita {
	int idvisita;  //Corretto trasformandolo da carattere a puntatore di carattere
	int viaggiorelativo; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	int metavisitata; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiarrivo[DATE_LEN]; 
	char datadipartenza[DATE_LEN]; 
	char oradiarrivo[TIME_LEN]; 
	char oradipartenza[TIME_LEN]; 
	signed char guida; //Corretto trasformandolo da carattere a puntatore di carattere
	float supplemento; //Corretto trasformandolo da carattere a puntatore di carattere
	char trattamentoalberghiero[VARCHAR_LEN]; 
	//
	char tour [VARCHAR_LEN]; 
	char meta [VARCHAR_LEN]; 


}; 
struct mete_tour{
	char nome[VARCHAR_LEN];
	char darrivo[DATE_LEN];
	char oarrivo[TIME_LEN];
	char dpartenza[DATE_LEN];
   	char opartenza[TIME_LEN];
   	float supplemento;
	char desfoto[VARCHAR_LEN]; 
	char foto[BLOB_LEN]; 
	char tipologiameta[VARCHAR_LEN];
	signed char guida;
   	char oapertura[TIME_LEN];
   	char trattamento[VARCHAR_LEN];
	char categoriaalbergo[VARCHAR_LEN];
	int codicealbergo; 
}; 

struct info_mete{
	size_t num_mete; 
	struct mete_tour info_mete[]; 
};

struct viaggi_mezzi{
	char tour[VARCHAR_LEN];
	int viaggio; 
	char modello[VARCHAR_LEN];
	char targa[TAR_LEN];
	int autonomia; 
	char ingombri [VARCHAR_LEN]; 
	int contakm; 
	char partenza[DATE_LEN]; 
	char ritorno[DATE_LEN]; 
};

struct viaggi_assegnati{
	size_t num_viaggi; 
	struct viaggi_mezzi viaggi_assegnati[]; 
};

struct meta_visita{
	char nome [VARCHAR_LEN]; 
	char tipologia[VARCHAR_LEN]; 
	char localita[VARCHAR_LEN];
	char regione[VARCHAR_LEN]; 
	char indirizzo[VARCHAR_LEN]; 
	char arrivo[DATE_LEN];
	char ingresso[TIME_LEN]; 
	char partenza[DATE_LEN]; 
	char uscita[TIME_LEN]; 
};

struct mete_visite{
	size_t num_visite; 
	struct meta_visita mete_visite[]; 
};

struct mappa_autista{
	char citta[VARCHAR_LEN];
	char dettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char immagine[VARCHAR_LEN];	
};

struct mappe{
	size_t num_mappe; 
	struct mappa_autista mappe[]; 
};

extern void do_insert_tour(struct tour *tour); 
extern void do_insert_trip(struct viaggio *viaggio); 
extern void do_insert_destination(struct meta *meta); 
extern void do_insert_visit(struct visita *visita); 
extern void do_insert_room(struct camera *camera); 
extern void do_insert_costumer(struct cliente *cliente);
extern void do_insert_costumer_user(struct utente *utente, struct cliente *cliente);
extern void do_insert_reservation(struct prenotazione *prenotazione);
extern void do_insert_seat(struct postoprenotato *postoprenotato);
extern void do_insert_stay(struct soggiorno *soggiorno);
extern void do_insert_review(struct revisione *revisione);
extern void do_insert_sostitution (struct sostituito *sostituito); 
extern void do_insert_location(struct localita *localita); 
extern void do_insert_map(struct mappa *mappa); 
extern void do_insert_picture(struct documentazionefotografica *documentazionefotografica); 
extern void do_insert_employee(struct dipendente *dipendente); 
extern void do_insert_user(struct utente *utente); 
extern void do_insert_offert(struct offre *offre); 
extern void do_insert_service(struct servizio *servizio); 
extern void do_insert_fmo(struct fmo *fmo); 
extern void do_insert_fme(struct fme *fme); 
extern void do_insert_model(struct modello * modello, struct competenze *competenze); 
extern void do_insert_bus(struct mezzo *mezzo); 
extern void do_insert_sparepart(struct ricambio *ricambio);
extern void do_insert_certify(struct tagliando *tagliando); 
extern void do_insert_comfort(struct comfort *comfort); 
extern void do_insert_skills(struct competenze *competenze); 
extern void do_insert_presents(struct presenti *presenti);
extern void do_insert_rt(struct rt *rt); 

extern int do_select_trip(struct viaggio *viaggio);
extern int do_select_costumer(struct cliente *cliente);
extern int do_select_reservation(struct prenotazione *prenotazione);
extern int do_select_tour( struct tour *tour);
extern int do_select_sparepart(struct ricambio *ricambio); 
extern int do_select_review(struct revisione *revisione);
extern int do_select_bus(struct mezzo *mezzo); 
extern int do_select_stay(struct soggiorno *soggiorno); 
extern int do_select_skills(struct competenze *competenze); 
extern int do_select_employee(struct dipendente* dipendente); 
extern int do_select_fmo(struct fmo *fmo); 
extern int do_select_fme(struct fme *fme);
extern int do_select_ofr(struct offre *offre);  
extern int do_select_user(struct utente *utente); 
extern int do_select_seat(struct postoprenotato *postoprenotato); 
extern int do_select_model(struct modello *modello); 
extern int do_select_certify(struct tagliando *tagliando);
extern int do_select_destination(struct meta *meta);  
extern int do_select_visit(struct visita *visita); 
extern int do_select_location(struct localita *localita);
extern int do_select_room(struct camera *camera); 
extern int do_select_map(struct mappa *mappa); 
extern int do_select_picture(struct documentazionefotografica *documentazionefotografica);
extern int do_select_comfort(struct comfort *comfort); 
extern int do_select_service(struct servizio *servizio); 
extern int do_select_sostitution(struct sostituito*sostituito); 
extern int do_select_presents(struct presenti *presenti);
extern int do_select_rt(struct rt *rt); 

extern void do_delete_trip(struct viaggio *viaggio);
extern void do_delete_costumer(struct cliente *cliente);
extern void do_delete_reservation(struct prenotazione *prenotazione);
extern void do_delete_tour( struct tour *tour);
extern void do_delete_sparepart(struct ricambio *ricambio); 
extern void do_delete_review(struct revisione *revisione);
extern void do_delete_bus(struct mezzo *mezzo); 
extern void do_delete_stay(struct soggiorno *soggiorno); 
extern void do_delete_skills(struct competenze *competenze); 
extern void do_delete_employee(struct dipendente* dipendente); 
extern void do_delete_fmo(struct fmo *fmo); 
extern void do_delete_fme(struct fme *fme);
extern void do_delete_ofr(struct offre *offre);  
extern void do_delete_user(struct utente *utente); 
extern void do_delete_seat(struct postoprenotato *postoprenotato); 
extern void do_delete_model(struct modello *modello); 
extern void do_delete_certify(struct tagliando *tagliando);
extern void do_delete_destination(struct meta *meta);  
extern void do_delete_visit(struct visita *visita); 
extern void do_delete_location(struct localita *localita);
extern void do_delete_room(struct camera *camera); 
extern void do_delete_map(struct mappa *mappa); 
extern void do_delete_picture(struct documentazionefotografica *documentazionefotografica);
extern void do_delete_comfort(struct comfort *comfort); 
extern void do_delete_service(struct servizio *servizio); 
extern void do_delete_sostitution(struct sostituito *sostituito); 
extern void do_delete_presents(struct presenti *presenti);
extern void do_delete_rt(struct rt *rt); 

extern void do_insert_sost_review(struct revisione *revisione, struct sostituito *sostituito ); 
extern void do_init_skill(struct competenze *competenze);

extern struct tour_info *get_tour_info (void);
extern struct info_mete *get_mete_info(int idv);
extern struct servizi_albergo *get_servizi_albergo(int idh); 
extern struct info_modelli *get_info_modello(char *nmd);
extern struct revisioni_scadute *get_info_revisioni(void); 
extern struct viaggi_assegnati *get_viaggi_assegnati(char *dvr);
extern struct mete_visite *get_mete_visite(int idv);
extern struct mappe *get_mappe(char* nml); 
extern struct prenotazioni_info *get_reservation_info (char *mlc); 

extern void do_update_user_type(struct utente *utente); 
extern void do_validate_reservation(struct prenotazione *prenotazione);
extern void do_update_spareparts_number(struct ricambio *ricambio); 
extern void do_update_km(struct mezzo *mezzo); 

