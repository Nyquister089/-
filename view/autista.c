#include <stdio.h>

#include "autista.h"
#include "show.h"
#include "upd.h"
#include "../utils/io.h"
#include "../utils/validation.h"

struct mezzo *mezzo_drvr;

int drvr_allocation (void)
{
	mezzo_drvr = malloc (sizeof(struct mezzo));
	if(mezzo_drvr == NULL){
		printf("Fallimento malloc su mezzo (Autista)\n\n"); 
		return -1; 
	}
}

int get_drvr_action(void)
{
	char options[5] = {'1','2','3','4','5'};
	char op;

	puts("*********************************");
	puts("*   INTERFACCIA AUTISTA    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consulta i viaggi ed i mezzi a cui sei assegnato");
	puts("2) Consulta le località ed i dati temporali delle mete previste per un viaggio ");
	puts("3) Consulta le mappe");
	puts("4) Aggiorna il valore del conta km dopo un viaggio"); 
	puts("5) Esci");


	op = multi_choice("Select an option", options, 5);
	return op - '1';
}


bool exe_drvr_act(drvr_act sel)
{	
	switch (sel)
		{case VIAGGI_ASSEGNATI:{
		show_assigned_trip(); 
		return true;
		}
     	
     	case ORARI_VISITE:{
     	show_dest_time();
		return true; 
		 }

	 	case MAPPE:	{
	 	show_drvr_map(); 
		return true;
		 }

	 	case AGGIORNA_KM:{ 
		update_km(mezzo_drvr);
		return true; 
		 }

		case QUIT_DRVR:
		return false; 
		
	break;
	}

	return true;
}

void run_drvr_interface (void)
{ 	char sel; 
	if(mezzo_drvr == NULL)
		drvr_allocation(); 
	while (true){
	sel =  get_drvr_action(); 
	if (!exe_drvr_act(sel))
		break; 
	
	}
}

