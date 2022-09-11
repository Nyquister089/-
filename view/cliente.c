#include <stdio.h>

#include"cliente.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"


int get_cstmr_action(void)
{
	char options[5] = {'1','2','3','4','5'};
	char op;
	puts("*********************************");
	puts("*   Interfaccia cliente     *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Visualizza i tour disponibili ed i relativi viaggi previsti");
	puts("2) Consulta le mete relative ad un viaggio");
	puts("3) Consulta i servizi offerti da un albergo");
	puts("4) Consulta i comfort presenti su un modello");
	puts("5) Esci ");

	op = multi_choice("Scegli un opzione? ", options, 5);
	return op - '1';
}

bool exe_cstmr_act(cstmr_act sel)
{
	switch (sel)
		{case TOUR_INFO:{
		show_tour_information(); 
		return true; 
		}
		
		case METE_TOUR:{
		show_tour_destination(); 
		return true;
		}

	 	case SERVIZI_ALBERGO:{
		show_service_destination();
		return true;
		 }

	 	case COMFORT_MODELLO:{
		show_comfort_model();
		return true; 
		 }
		
		case QUIT_CSTMR:
		return false;
	}

	return true;
}




void run_cstmr_interface (void)
{ 	char sel; 
	while (true){
	sel = get_cstmr_action(); 
	if (!exe_cstmr_act(sel))
		break; 
	}
}


