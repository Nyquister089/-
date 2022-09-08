
#include <stdio.h>

#include "hostess.h"
#include "ins.h"
#include "show.h"
#include "upd.h"

#include "../utils/io.h"
#include "../utils/validation.h"

struct cliente *cliente_hstss; 
struct prenotazione *prenotazione_hstss;
struct postoprenotato *postoprenotato_hstss;
struct  viaggio *viaggio_hstss;
struct soggiorno * soggiorno_hstss;
struct utente * utente_hstss; 

int allocation_hstss(void)
{
	cliente_hstss = malloc(sizeof(struct cliente)); 
	if(cliente_hstss == NULL)
		{printf("Fallimento malloc su cliente (hostess) \n\n"); 
		 return -1; 
		}
	prenotazione_hstss = malloc(sizeof(struct prenotazione)); 
	if(prenotazione_hstss == NULL)
		{printf("Fallimento malloc su prenotazione (hostess) \n\n");
		 return -1; 
		}
	postoprenotato_hstss = malloc(sizeof(struct postoprenotato));
	if(postoprenotato_hstss == NULL)
		{printf("Fallimento malloc su postoprenotato (hostess) \n\n"); 
		 return -1; 
		}
	viaggio_hstss = malloc(sizeof(struct viaggio)); 
	if(viaggio_hstss == NULL)
		{printf("Fallimento malloc su viaggio (hostess) \n\n"); 
		 return -1;
		}
	soggiorno_hstss = malloc(sizeof(struct soggiorno));
	if(soggiorno_hstss == NULL)
		{printf("Fallimento malloc soggiorno (hostess) \n\n"); 
		 return -1; 
		 }
	utente_hstss = malloc(sizeof(struct utente ));
	if(utente_hstss == NULL)
		{printf("Fallimento malloc utente  (hostess) \n\n"); 
		 return -1; 
		 }
	
}

int get_hstss_action(void)
{
	char options[7] = {'1','2','3','4','5'};
	char op;
	
	puts("*********************************");
	puts("*   INTERFACCIA HOSTESS    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consultare prenotazioni");
	puts("2) Inserire un nuovo cliente");
	puts("3) Inserire una nuova prenotazione");  
	puts("4) Conferma prenotazione ed intestazione posti");
	puts("5) Esci");

	op = multi_choice("Scegli un opzione", options, 5);

	return op -'1'; 
}

bool exe_hstss_act(char sel)
{	

	switch (sel)
		{	
			case INFO_PRENOTAZIONI: {
				show_reservation(prenotazione_hstss); 
				return true;
				}
			case INSERT_CLIENTE:{
				ins_costumer_hstss(cliente_hstss, utente_hstss); 
				return true; 
				}
		
			case INSERT_PRENOTAZIONE:{
				ins_prenotation(prenotazione_hstss); 
				return true;
				}
			case CONFERMA_PRENOTAZIONE:{
				validate_reservation (prenotazione_hstss, postoprenotato_hstss, soggiorno_hstss); 
				return true;
		 		}
			case QUIT_HSST: 
				return false; 
		
	}
	return true;
}




void run_hstss_interface (void)
{ 	
	char sel;
				
	if(	cliente_hstss == NULL || prenotazione_hstss == NULL || postoprenotato_hstss == NULL ||viaggio_hstss == NULL||soggiorno_hstss == NULL) {
		allocation_hstss();
		printf("\n\nAllocazione avvenuta.\n\n"); }

	while (true){
	sel = get_hstss_action(); 
	if (!exe_hstss_act(sel))
		break; 
	}

}	
