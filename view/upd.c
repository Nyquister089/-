#include<stdio.h>
#include<stdlib.h>

#include "upd.h"
#include "show.h"

void update_user_type( struct utente *utente, int type) {

	char buff [NUM_LEN]; 
	do{
		if(utente->tipo == type)
			printf("Errore! Il tipo dell'utente deve essere diverso da %d \n Autista =	1; \n Cliente =	2; \n Hostess =	3; \n Meccanico =	4; \n Manager =	5;\n Reinserisci il tipo dell'utente\n", utente->tipo); 
		get_input("Reinserisci la tipologia dell'utente:", NUM_LEN,buff, false); 
		utente->tipo = atoi (buff);
	}while(utente->tipo == type); 
	do_update_user_type(utente); 
}

void update_km(struct mezzo *mezzo)
{
	char buff[VARCHAR_LEN];
	bool ans; 
	printf("** Selezione del mezzo d'interesse **\n\n");
	show_bus(mezzo ); 
	ans =yes_or_no("Vuoi modificare i km di questo mezzo ? ", 's', 'n', false, false); 
	if(ans){
		get_input("\nInserisci l'attuale numero di km : ",NUM_LEN, buff, false); 
		mezzo->valorecontakm = atoi(buff); 
		do_update_km(mezzo ); 
		}

}

			