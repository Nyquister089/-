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


#pragma once
#include "../model/trpdb.h"

typedef enum {
	VIAGGI_ASSEGNATI,
	ORARI_VISITE,
	MAPPE,
	AGGIORNA_KM, 
	QUIT_DRVR
} drvr_act;

extern void run_drvr_interface (void); 
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


#pragma once

#include "../model/trpdb.h"

typedef enum  {
	TOUR_INFO,
	METE_TOUR,
	SERVIZI_ALBERGO,
	COMFORT_MODELLO, 
	QUIT_CSTMR
} cstmr_act;

extern void show_tour_information(void);
extern void show_tour_destination(void);
extern void show_service_destination(void);
extern void show_comfort_model(void); 
extern void run_cstmr_interface (void);#include <string.h>
#include "../model/trpdb.h"
#include "dlt.h" 
#include "show.h"



void dlt_trip(struct viaggio *viaggio)
{	
	if(show_trip(viaggio)!=-1) 
    if(yes_or_no("Vuoi cancellare questo viaggio? (s/n)",'s','n',false,false) == true)
        do_delete_trip(viaggio); 
}
void dlt_tour(struct tour *tour)
{
	if(show_tour(tour)!=-1) 
    if(yes_or_no("Vuoi cancellare questo tour? (s/n)",'s','n',false,false) == true)
        do_delete_tour(tour); 
}
void dlt_sparepart(struct ricambio *ricambio)
{	if(show_sparepart(ricambio)!=-1)
		 if(yes_or_no("Vuoi cancellare questo ricambio? (s/n)",'s','n',false,false) == true)
        	do_delete_sparepart(ricambio); 

    
}
void dlt_review (struct revisione *revisione)
{
	if(show_review(revisione)!=-1) 
    if(yes_or_no("Vuoi cancellare questa revisione? (s/n)",'s','n',false,false) == true)
        do_delete_review(revisione);
}
void dlt_bus(struct mezzo *mezzo)
{	
	if(show_bus(mezzo)!=-1) 
    if(yes_or_no("Vuoi cancellare questo mezzo? (s/n)",'s','n',false,false) == true)
        do_delete_bus(mezzo);
}
void dlt_reservation (struct prenotazione * prenotazione)
{	
	if(show_reservation(prenotazione)!=-1) 
    if(yes_or_no("Vuoi cancellare questa prenotazione? (s/n)",'s','n',false,false) == true)
        do_delete_reservation(prenotazione);
    
}

void dlt_costumer (struct cliente * cliente)
{	
	if(show_costumer(cliente)!=-1) 
    if(yes_or_no("Vuoi cancellare questo cliente? (s/n)",'s','n',false,false) == true)
        do_delete_costumer(cliente);
    
}
void dlt_stay(struct soggiorno *soggiorno)
{ 	
    if(show_stay(soggiorno)!=-1) 
    if(yes_or_no("Vuoi cancellare questa associazione? (s/n)",'s','n',false,false) == true)
        do_delete_stay(soggiorno);
}
void dlt_skills(struct competenze *competenze)
{ 
    if(show_skills(competenze)!=-1) 
    if(yes_or_no("Vuoi cancellare queste competenze? (s/n)",'s','n',false,false) == true)
        do_delete_skills(competenze);
}
 void dlt_employee(struct dipendente *dipendente)
{	
	if(show_employee(dipendente)!=-1)
	 if(yes_or_no("Vuoi cancellare questo dipendente? (s/n)",'s','n',false,false) == true)
        do_delete_employee(dipendente);

}   
void dlt_fmo(struct fmo *fmo)
{	
	if(show_fmo(fmo)!=-1)
	 if(yes_or_no("Vuoi cancellare questa relazione foto-modello? (s/n)",'s','n',false,false) == true)
        do_delete_fmo(fmo);
}
void dlt_fme(struct fme *fme)
{	
	if(show_fme(fme)!=-1)
	 if(yes_or_no("Vuoi cancellare questa relazione foto-meta? (s/n)",'s','n',false,false) == true)
        do_delete_fme(fme);
}
void dlt_ofr(struct offre *offre)
{	
	if(show_ofr(offre)!=-1)
	 if(yes_or_no("Vuoi cancellare questa offerta? (s/n)",'s','n',false,false) == true)
        do_delete_ofr(offre);
}


void dlt_user(struct utente *utente)
{
	if(show_user(utente)!=-1)
	 if(yes_or_no("Vuoi cancellare questo utente? (s/n)",'s','n',false,false) == true)
        do_delete_user(utente);
}
void dlt_seat(struct postoprenotato *postoprenotato)
{
	if(show_seat(postoprenotato)!=-1)
	 if(yes_or_no("Vuoi cancellare questo posto prenotato? (s/n)",'s','n',false,false) == true)
        do_delete_seat(postoprenotato);
}
void dlt_model(struct modello *modello)
{
	if(show_model(modello)!=-1)
	 if(yes_or_no("Vuoi cancellare questo modello? (s/n)",'s','n',false,false) == true)
        do_delete_model(modello);
}
void dlt_certify(struct tagliando *tagliando)
{
	if(show_certify(tagliando)!=-1)
	 if(yes_or_no("Vuoi cancellare questo tagliando? (s/n)",'s','n',false,false) == true)
        do_delete_certify(tagliando);
}
void dlt_destination(struct meta *meta)
{	
	if(show_destination(meta)!=-1)
	 if(yes_or_no("Vuoi cancellare questa meta? (s/n)",'s','n',false,false) == true)
        do_delete_destination(meta);
}
void dlt_visit(struct visita *visita)
{	
	if(show_visit(visita)!=-1)
	 if(yes_or_no("Vuoi cancellare questa visita? (s/n)",'s','n',false,false) == true)
        do_delete_visit(visita);
}
void dlt_location(struct localita *localita)
{	
	if(show_location(localita)!=-1)
	 if(yes_or_no("Vuoi cancellare questa localita? (s/n)",'s','n',false,false) == true)
        do_delete_location(localita);
}
void dlt_room(struct camera *camera)
{
	if(show_room(camera)!=-1)
	 if(yes_or_no("Vuoi cancellare questa camera? (s/n)",'s','n',false,false) == true)
        do_delete_room(camera);

}
void dlt_map(struct mappa *mappa)
{
	if(show_map(mappa)!=-1)
	 if(yes_or_no("Vuoi cancellare questa mappa? (s/n)",'s','n',false,false) == true)
        do_delete_map(mappa);

}
void dlt_picture(struct documentazionefotografica *documentazionefotografica)
{
	if(show_picture(documentazionefotografica)!=-1)
	 if(yes_or_no("Vuoi cancellare questa foto? (s/n)",'s','n',false,false) == true)
        do_delete_picture(documentazionefotografica);

}
void dlt_comfort(struct comfort *comfort)
{
	if(show_comfort(comfort)!=-1)
	 if(yes_or_no("Vuoi cancellare questo comfort? (s/n)",'s','n',false,false) == true)
        do_delete_comfort(comfort);

}
void dlt_service(struct servizio *servizio)
{
	if(show_service(servizio)!=-1)
	 if(yes_or_no("Vuoi cancellare questo servizio? (s/n)",'s','n',false,false) == true)
        do_delete_service(servizio);

}

void dlt_sostitution( struct sostituito *sostituito)
{
	if(show_sostitution(sostituito)!=-1)
		if(yes_or_no("Vuoi cancellare questa sostituzione? (s/n)",'s','n',false,false) == true)
        	do_delete_sostitution(sostituito);

}

void dlt_rt( struct rt *rt)
{
	if(show_rt(rt)!=-1)
		if(yes_or_no("Vuoi cancellare questa relazione tra revisione e tagliando? (s/n)",'s','n',false,false) == true)
        	do_delete_rt(rt);

}

void dlt_presents( struct presenti *presenti)
{
	if(show_presents(presenti)!=-1)
		if(yes_or_no("Vuoi cancellare questa relazione tra comfort e modello? (s/n)",'s','n',false,false) == true)
        	do_delete_presents(presenti);

}#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../utils/io.h"
#include "../utils/validation.h"
#include "../model/trpdb.h"


extern void dlt_costumer(struct cliente *cliente);
extern void dlt_reservation(struct prenotazione *prenotazione);
extern void dlt_seat(struct postoprenotato *postoprenotato);
extern void dlt_review(struct revisione *revisione);
extern void dlt_sparepart(struct ricambio *ricambio);
extern void dlt_bus(struct mezzo *mezzo);
extern void dlt_model(struct modello *modello);
extern void dlt_certify(struct tagliando *tagliando);
extern void dlt_stay(struct soggiorno *soggiorno);
extern void dlt_sostitution( struct sostituito *sostituito); 
extern void dlt_tour(struct tour *tour);
extern void dlt_trip(struct viaggio *viaggio);
extern void dlt_destination(struct  meta *meta);
extern void dlt_visit(struct visita *visita);
extern void dlt_room(struct camera *camera);
extern void dlt_location(struct localita *localita);
extern void dlt_map(struct mappa *mappa);
extern void dlt_picture(struct documentazionefotografica *documentazionefotografica) ;
extern void dlt_employee(struct dipendente *dipendente);
extern void dlt_user(struct utente *utente);
extern void dlt_ofr(struct offre *offre); 
extern void dlt_service(struct servizio *servizio);
extern void dlt_fmo(struct fmo *fmo); 
extern void dlt_fme(struct fme *fme); 
extern void dlt_bus(struct mezzo *mezzo);
extern void dlt_sparepart(struct ricambio *ricambio);
extern void dlt_comfort(struct comfort *comfort);
extern void dlt_skills(struct competenze *competenze); 
extern void dlt_presents(struct presenti *presenti); 
extern void dlt_rt(struct rt *rt); 

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
#pragma once
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>

#include "../model/trpdb.h"

typedef enum{
	INFO_PRENOTAZIONI,
	INSERT_CLIENTE,
	INSERT_PRENOTAZIONE,
	CONFERMA_PRENOTAZIONE, 
	QUIT_HSST
} hstss_act;
 


extern void run_hstss_interface (void);
#include <string.h>
#include "ins.h"
#include "upd.h"
#include "show.h"

void ins_user(struct utente *utente) 
{	
	char buff[VARCHAR_LEN];
	printf("** Dettagli inserimento utente **\n\n");
	get_input("Inserisci la mail: ", VARCHAR_LEN, utente->email, false);
	get_input("Inserisci la password: ", VARCHAR_LEN, utente->pswrd, false);

	printf("\n Autista =	1; \n Cliente =	2; \n Hostess =	3; \n Meccanico =	4; \n Manager =	5;\n"); 
	get_input("Inserisci la tipologia: ", NUM_LEN, buff, false);
	utente->tipo = atoi(buff); 
		if(utente->tipo >5 || utente->tipo < 1)
	update_user_type(utente,utente->tipo); 
	do_insert_user(utente);
}




void ins_prenotation(struct prenotazione *prenotazione)
{	
	char buff[NUM_LEN];
	printf("\n** Dettagli inserimento prenotazione **\n\n");
	get_input("Inserisci l'indirizzo e-mail del cliente che ha effettuato la prenotazione : ", VARCHAR_LEN, prenotazione->clienteprenotante, false);
	get_input("Inserisci l'id del viaggio da prenotare : ", NUM_LEN, buff, false);
	prenotazione->viaggioassociato = atoi(buff); 
	get_input("Inserisci il numero di posti che si desiderano prenotare : ", NUM_LEN, buff, false);
	prenotazione->numerodipostiprenotati = atoi(buff); 

	do_insert_reservation(prenotazione); 
}

void ins_seat(struct postoprenotato *postoprenotato)
{	
	char buff[NUM_LEN]; 
	printf("\n** Dettagli inserimento passeggero **\n\n");
	get_input("Inserisci il numero di prenotazione: ", NUM_LEN, buff, false);
	postoprenotato->prenotazioneassociata = atoi(buff); 
	get_input("Inserisci il numero di posto: ", NUM_LEN, buff, false);
	postoprenotato->numerodiposto = atoi(buff); 
	get_input("Inserisci l'età: ", NUM_LEN, buff, false);
	postoprenotato->etapasseggero = atoi(buff); 
	get_input("Inserisci il nome: ", VARCHAR_LEN, postoprenotato-> nomepasseggero, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, postoprenotato-> cognomepasseggero, false);

	do_insert_seat(postoprenotato); 
}

void ins_review(struct revisione *revisione, struct sostituito *sostituito, struct ricambio *ricambio)
{	
	char buff[NUM_LEN]; 
	bool ans;
	printf("\n** Dettagli inserimento revisione **\n\n");
	get_input("Inserisci la targa del mezzo revisionato : ", VARCHAR_LEN, revisione->mezzorevisionato, false);
	get_input("Inserisci la mail del meccanico che ha eseguito la revisione : ", VARCHAR_LEN, revisione->addettoallarevisione, false);
	get_input("Inserisci la descrizione delle operazioni eseguite (massimo 5000 caratteri): ", DES_LEN, revisione-> operazionieseguite, false);
	get_input("Inserisci il numero di km presenti sul conta chilometri del mezzo revisionato : ",NUM_LEN, buff, false);
	revisione-> chilometraggio = atoi(buff); 
	get_input("Inserisci la motivazione della revisione (massimo 5000 caratteri) : ", DES_LEN, revisione-> motivazione, false);
	while(true){
		get_input("Inserisci la data di inizio[YYYY-MM-DD]: ", DATE_LEN, revisione->datainizio, false);
		if(validate_date(revisione->datainizio))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di conclusione[YYYY-MM-DD]: ", DATE_LEN, revisione->datafine, false);
		if(validate_date(revisione->datafine))
			break;
		fprintf(stderr, "Data errata!\n");
	}

ans = yes_or_no("In questa revisione sono statti sostituiti dei ricambi? ",'s','n',false, false); 
if(ans)
	{	
	get_input("Inserisci il codice del ricambio utilizzato : ", VARCHAR_LEN, sostituito->ricambioutilizzato,false);
	get_input("Inserisci la quantità di ricambi sostituiti : ",NUM_LEN, buff, false);
	sostituito->quantitasostituita = atoi(buff); 
	do_insert_sost_review(revisione,sostituito);
	}
else
	do_insert_review(revisione);
}

void ins_costumer(struct cliente *cliente)
{	

	
	printf("\n** Dettagli inserimento cliente **\n\n");
	get_input("Inserisci la mail: ", VARCHAR_LEN, cliente->emailcliente, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, cliente->nomecliente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, cliente->cognomecliente, false);
	get_input("Inserisci l'indirizzo: ", VARCHAR_LEN, cliente->indirizzocliente, false);
	get_input("Inserisci il codice fiscale: ", VARCHAR_LEN, cliente->codicefiscale, false);
	get_input("Inserisci il recapito telefonico: ", VARCHAR_LEN, cliente->recapitotelefonico, false);
	get_input("Inserisci il numero di fax: ", VARCHAR_LEN, cliente->fax, false);


	while(true){
		get_input("Inserisci l'ultima data d'invio dei documuenti [YYYY-MM-DD]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	do_insert_costumer(cliente); 
}

void ins_costumer_hstss(struct cliente *cliente, struct utente *utente)
{	
	char buff[VARCHAR_LEN]; 
	printf("** Crea un utente per questo cliente **\n"); 
	get_input("Inserisci la mail: ", VARCHAR_LEN, cliente->emailcliente, false);
	get_input("Inserisci la password: ", VARCHAR_LEN, utente->pswrd, false);
	
	printf("\n** Dettagli inserimento cliente **\n\n");
	get_input("Inserisci il nome: ", VARCHAR_LEN, cliente->nomecliente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, cliente->cognomecliente, false);
	get_input("Inserisci l'indirizzo: ", VARCHAR_LEN, cliente->indirizzocliente, false);
	get_input("Inserisci il codice fiscale: ", VARCHAR_LEN, cliente->codicefiscale, false);
	get_input("Inserisci il recapito telefonico: ", NUM_LEN, cliente->recapitotelefonico, false);
	get_input("Inserisci il numero di fax: ", NUM_LEN, cliente->fax, false);


	while(true){
		get_input("Inserisci l'ultima data d'invio dei documuenti [YYYY-MM-DD]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	do_insert_costumer_user(utente, cliente); 
}

void ins_sparepart(struct ricambio *ricambio)
{	
	char buff[NUM_LEN]; 
	printf("\n** Dettagli inserimento ricambio **\n\n");
	get_input("Inserisci il codice: ", VARCHAR_LEN, ricambio->codice, false);
	get_input("Inserisci il costo unitario: ", NUM_LEN, buff, false);
	ricambio->costounitario = atof(buff);
	get_input("Inserisci la quantità minima di riordino : ", NUM_LEN, buff, false);
	ricambio->quantitadiriordino= atoi(buff); 
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, ricambio-> descrizione, false);
	get_input("Inserisci la scorta minima: ", NUM_LEN, buff, false);
	ricambio->scortaminima = atoi(buff); 
	get_input("Inserisci quantita' di pezzi disponibili: ", NUM_LEN, buff, false);
	ricambio->quantitainmagazzino = atoi(buff);
	do_insert_sparepart(ricambio);
}

void ins_bus(struct mezzo *mezzo)
{	
	char buff[VARCHAR_LEN]; 
	printf("\n** Dettagli inserimento mezzo **\n\n");
	get_input("Inserisci la targa : ", VARCHAR_LEN, mezzo->targa, false);
	get_input("Inserisci il modello : ", VARCHAR_LEN, mezzo->modellomezzo, false);
	get_input("Inserisci gli ingombri : ", VARCHAR_LEN, mezzo->ingombri, false);
	get_input("Inserisci l'autonomia : ", NUM_LEN, buff , false);
	mezzo-> autonomia = atoi(buff); 
	get_input("Inserisci il valore attuale del conta chilometri: ", NUM_LEN, buff, false);
	mezzo-> valorecontakm = atoi(buff); 
		while(true){
		get_input("Inserisci la data dell'ultima revisione presso la motorizzazione [YYYY-MM-DD]: ", DATE_LEN, mezzo->dataultimarevisioneinmotorizzazione, false);
		if(validate_date(mezzo->dataultimarevisioneinmotorizzazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di immatricolazione  [YYYY-MM-DD]: ", DATE_LEN, mezzo->dataimmatricolazione, false);
		if(validate_date(mezzo->dataimmatricolazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
 do_insert_bus(mezzo);

}

void ins_another_skill (struct competenze *competenze)
{	
	printf("** Dettagli inserimento competenze **\n\n");
	get_input("Inserisci la mail del meccanico competente : ", VARCHAR_LEN, competenze->meccanicocompetente, false);
	do_insert_skills(competenze); 
}

void ins_model(struct modello *modello, struct competenze *competenze)
{	
	char buff[NUM_LEN];
	printf("\n** Dettagli inserimento modello **\n\n");
	get_input("Inserisci il nome : ", VARCHAR_LEN, modello->nomemodello, false);
	get_input("Inserisci la casa costruttrice : ", VARCHAR_LEN, modello->casacostruttrice, false);
	get_input("Inserisci i dati tecnici (massimo 5000 caratteri) : ", DES_LEN, modello-> datitecnici, false);
	get_input("Inserisci il numero di posti: ", NUM_LEN, buff, false);
	modello->numeroposti = atoi(buff);
	printf("** Dettagli inizializzazione competenze **\n\n");
	get_input("Inserisci il primo meccanico competente : ", VARCHAR_LEN, competenze->meccanicocompetente, false);
	get_input("Inserisci il secondo meccanico competente : ", VARCHAR_LEN, competenze->nomemeccanico, false);
	do_insert_model(modello, competenze); 
	
	while(yes_or_no("Vuoi inserire un'altro meccanico competente? ", 's', 'n', false, false)){
		strcpy(competenze->modelloassociato, modello->nomemodello); 
		ins_another_skill(competenze); 
	}
}

void ins_certify(struct tagliando *tagliando)
{	
	printf("\n** Dettagli inserimento tagliando **\n\n");
	get_input("Inserisci la tipologia del tagliando: ", VARCHAR_LEN, tagliando->tipologiatagliando, false);
	get_input("Inserisci le validita' superate (massimo 5000 caratteri) : ", DES_LEN, tagliando->validitasuperate, false);
	do_insert_certify(tagliando); 
}

void ins_stay(struct soggiorno *soggiorno)
{	
	char buff[NUM_LEN]; 
	printf("\n** Dettagli soggiorno**\n\n");
	get_input("Inserisci il numero della camera: ", NUM_LEN, buff, false);
	soggiorno->cameraprenotata = atoi(buff); 
	get_input("Inserisci l'albergo in cui è ubicata la camera: ", NUM_LEN, buff,false);	
	soggiorno->albergoinquestione = atoi(buff); 
	get_input("Inserisci il numero della prenotazione in questione: ", NUM_LEN, buff, false);
	soggiorno->prenotazioneinquestione = atoi(buff); 
	get_input("Inserisci il numero di posto di viaggio dell'ospite: ", NUM_LEN, buff, false);
	soggiorno->ospite = atoi(buff); 
	while(true){
	get_input("Inserici la data d'inizio del soggiorno [YYYY-MM-DD]: ",DATE_LEN, soggiorno->datainiziosoggiorno,false); 
	if(validate_date(soggiorno->datainiziosoggiorno))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di fine soggiorno [YYYY-MM-DD]: ",DATE_LEN, soggiorno->datafinesoggiorno, false);
		if(validate_date(soggiorno->datafinesoggiorno))
				break;
			fprintf(stderr, "Data errata!\n");
		} 
	do_insert_stay(soggiorno); 
}

void ins_sostitution( struct sostituito *sostituito)
{	
	char buff[NUM_LEN]; 
	printf("\n** Dettagli sostituzione ricambio**\n\n");
	get_input("Inserisci il numero della revsione in questione: ",NUM_LEN, buff, false);
	sostituito->revisioneassociata = atoi(buff);
	get_input("Inserisci il codice del ricambio utilizzato : ", VARCHAR_LEN, sostituito->ricambioutilizzato,false);
	get_input("Inserisci la quantità di ricambi sostituiti : ",NUM_LEN, buff, false);
	sostituito->quantitasostituita = atoi(buff);
	do_insert_sostitution(sostituito); 
}



void ins_tour(struct tour *tour){

	char buff[NUM_LEN]; 
	char buffer[DEC_LEN]; 
	char bit[BIT_LEN]; 
	
	printf("** Dettagli inserimento tour **\n\n");
	get_input("Inserisci la denominazione: ", VARCHAR_LEN, tour->denominazionetour, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri): ", DES_LEN, tour->descrizionetour, false);
	get_input("Inserisci il numero minimo di partecipanti: ", NUM_LEN,buff, false);
	tour->minimopartecipanti = atoi(buff); 
	get_input("Inserisci il costo dell'assicurazione: ", DEC_LEN, buffer , false);
	tour->assicurazionemedica = atof(buffer); 
	get_input("Inserisci il costo del bagaglio: ", DEC_LEN, buffer, false);
	tour->bagaglio = atof(buffer);
	get_input("Inserisci il costo della garanzia di annullamento: ", DEC_LEN, buffer, false);
	tour->garanziaannullamento = atof(buffer); 
	while(true){
		get_input("Inserisci l'indicazione sulla presenza di un'accompagnatrice: ", BIT_LEN, bit, false);
		if(validate_double(bit))
			break;
		fprintf(stderr, "Inserisci un valore compreso tra[0,1]!\n"); 
	}
	tour->accompagnatrice = atoi(bit); 
	do_insert_tour(tour); 
}

void ins_trip(struct viaggio *viaggio)
{	
	char buff[NUM_LEN]; 
	char buffer[DEC_LEN]; 
	printf("** Dettagli inserimento viaggio **\n\n");
	get_input("Inserisci il tour a cui e' associato: ", VARCHAR_LEN, viaggio->tourassociato, false);
	get_input("Inserisci la mail del conducente assegnato: ", VARCHAR_LEN, viaggio->conducente, false);
	get_input("Inserisci la mail dell'eventuale accompagnatrice: ", VARCHAR_LEN, viaggio->accompagnatrice, false);
	get_input("Inserisci la targa del mezzo impiegato: ", VARCHAR_LEN, viaggio->mezzoimpiegato, false);

	while(true) {
		get_input("Inserisci la data di partenza [YYYY-MM-DD]: ", DATE_LEN, viaggio->datadipartenzaviaggio, false);
		if(validate_date(viaggio->datadipartenzaviaggio))
			break;
		fprintf(stderr, "Data Errata!\n");
		}
	while(true) {
		get_input("Inserisci la data di ritorno [YYYY-MM-DD]: ", DATE_LEN, viaggio->datadiritornoviaggio, false);
		if(validate_date(viaggio->datadiritornoviaggio))
			break;
		fprintf(stderr, "Data Errata!\n");
		}

	get_input("Inserisci il prezzo: ", DEC_LEN, buffer, false);
	viaggio->costodelviaggio = atof(buffer); 
	get_input("Inserisci il numero di Km che verranno percorsi: ", NUM_LEN, buff, false);
	viaggio->numerodikm = atoi (buff); 
	get_input("Inserisci i posti disponibili totali: ", NUM_LEN, buff, false);
	viaggio->postidisponibili = atoi(buff); 
	do_insert_trip(viaggio); 
}


void ins_destination(struct meta *meta)
{	
	printf("** Dettagli inserimento meta **\n\n");
	get_input("Inserisci la localita di appartenenza: ", VARCHAR_LEN, meta->localitadiappartenenza, false);
	get_input("Inserisci la regione di appartenenza: ", VARCHAR_LEN, meta->regiodiappartenennza, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, meta->nomemeta, false);
	get_input("Inserisci l'indirizzo e-mail: ", VARCHAR_LEN, meta->emailmeta, false);
	get_input("Inserisci il numero di telefono: ", VARCHAR_LEN, meta->telefonometa, false);
	get_input("Inserisci il numero di fax: ", VARCHAR_LEN, meta->faxmeta, false);
	get_input("Inserisci l'indirizzo: ", VARCHAR_LEN, meta->indirizzo, false);
	get_input("Inserisci la tipologia (bene o albergo ): ", VARCHAR_LEN, meta->tipologiameta, false);

	if(strcmp(meta->tipologiameta, "albergo") == 0)
		get_input("Inserisci la categoria dell'albergo: ", VARCHAR_LEN, meta->categoriaalbergo, false);
	else
		while(true) {
	get_input("Inserisci l'orario di apertura del bene [HH:MM]: ", TIME_LEN, meta->orariodiapertura, false);
	if(validate_time(meta->orariodiapertura))
		break;
		}

	do_insert_destination(meta); 
}


void ins_visit(struct visita *visita)
{	
	char buff[NUM_LEN]; 
	char buffer[DEC_LEN]; 
	char tiny[BIT_LEN]; 
	printf("** Dettagli inserimento visita **\n\n");
	get_input("Inserisci l'ID del viaggio associato: ", NUM_LEN, buff, false);
	visita->viaggiorelativo = atoi(buff); 
	get_input("Inserisci l'ID della meta visitata: ", NUM_LEN, buff, false);
	visita->metavisitata = atoi(buff); 
	while(true) {
		get_input("Inserisci la data di arrivo prevista [YYYY-MM-DD]: ", DATE_LEN, visita->datadiarrivo, false);
		if(validate_date(visita->datadiarrivo))
			break;
		fprintf(stderr,"Data errata!"); 
			
	}
	while(true) {
		get_input("Inserisci la data di partenza prevista [YYYY-MM-DD]: ", DATE_LEN, visita->datadipartenza, false);
		if(validate_date(visita->datadipartenza))
			break;
		fprintf(stderr,"Data errata!");	
	}

	while(true) {
		get_input("Inserisci l'orario di arrivo previsto [HH:MM]: ", TIME_LEN, visita->oradiarrivo, false);
		if(validate_time(visita->oradiarrivo))
			break;
	fprintf(stderr,"Orario errato!");	
	}
	while(true) {
		get_input("Inserisci l'orario di partenza previsto [HH:MM]: ", TIME_LEN, visita->oradipartenza, false);
		if(validate_time(visita->oradipartenza))
			break;
	fprintf(stderr,"Orario errato!");
	}

	get_input("Inserisci l'indicazione sulla presenza della guida(si/no): ", BIT_LEN, tiny, false);
	visita->guida = atoi(tiny); 
	get_input("Inserisci l'importo dell'eventuale supplemento: ", DEC_LEN, buffer, false);
	visita->supplemento = atof(buffer); 
	get_input("Inserisci la descrizione dell'eventuale trattamento alberghiero (massimo 5000 caratteri): ", DES_LEN, visita->trattamentoalberghiero, false); 
	do_insert_visit(visita); 
}

void ins_room(struct camera *camera)
{	
	char buff[NUM_LEN]; 
	char buffer[DEC_LEN]; 
	printf("** Dettagli inserimento camera di albergo **\n\n");
	get_input("Inserisci il numero della camera : ", NUM_LEN, buff, false);
	camera->numerocamera = atoi(buff); 
	get_input("Inserisci l'ID dell'albergo in cui la camera è ubicata : ", NUM_LEN, buff, false);
	camera->albergo = atoi(buff); 
	get_input("Inserisci la tipologia: ", VARCHAR_LEN, camera->tipologia, false);
	get_input("Inserisci il prezzo giornaliero del soggiorno: ", DEC_LEN, buffer, false);
	camera->costo = atof(buffer); 
	do_insert_room(camera); 
}

void ins_location(struct localita *localita)
{	
	printf("** Dettagli inserimento localita **\n\n");
	get_input("Inserisci il nome: ", VARCHAR_LEN, localita->nomelocalita, false);
	get_input("Inserisci ll nome della regione: ", VARCHAR_LEN, localita->regione, false);
	get_input("Inserisci il nome dello stato: ", VARCHAR_LEN, localita->stato, false);
	do_insert_location(localita); 
}


void ins_map(struct mappa *mappa)
{	
	printf("** Dettagli inserimento mappa **\n\n");
	get_input("Inserisci il nome della citta' rappresentata nella mappa: ", VARCHAR_LEN, mappa->citta, false);
	get_input("Inserisci il nome della regione in cui è ubicata la citta' rappresentata: ", VARCHAR_LEN, mappa->localitarappresentata, false);
	get_input("Inserisci il livello di dettaglio: ", VARCHAR_LEN, mappa->dettaglio, false);
	get_input("Inserisci il nome della zona rappresentata dalla mappa: ", VARCHAR_LEN, mappa->zona, false);
	get_input("Inserisci il file della mappa: ", BLOB_LEN, mappa->immagine, false); 
	do_insert_map(mappa); 
}

void ins_picture(struct documentazionefotografica *documentazionefotografica) 
{	
	printf("** Dettagli inserimento nuova foto **\n\n");
	get_input("Inserisci la descrizione : ", DES_LEN, documentazionefotografica->descrzione, false);
	get_input("Inserisci l'immagine: ", PIC, documentazionefotografica->foto, false);
	do_insert_picture(documentazionefotografica); 
}

void ins_offert(struct offre *offre) 
{	
	char buff[VARCHAR_LEN];
	printf("** Dettagli inserimento offre **\n\n");
	get_input("Inserisci l'id del servizio offerto: ", NUM_LEN, buff, false);
	offre->idservizio = atoi(buff); 
	get_input("Inserisci l'id dell'albergo offerente : ", NUM_LEN, buff, false);
	offre->albergoofferente= atoi(buff); 
	do_insert_offert(offre);
}




void ins_service(struct servizio *servizio)
{	
	printf("** Dettagli inserimento servizio **\n\n");
	get_input("Inserisci il nome: ", VARCHAR_LEN, servizio->nomeservizio, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri): ", DES_LEN, servizio->descrizioneservizio, false);
	do_insert_service(servizio); 
}

void ins_fme(struct fme *fme)
{	
	char buff[NUM_LEN]; 
	printf("** Dettagli inserimento fme **\n\n");
	get_input("Inserisci l'di della meta in questione: ", NUM_LEN, buff, false);
	fme->meta = atoi(buff); 
	get_input("Inserisci l'id della foto in questione: ", NUM_LEN, buff, false);
	fme->foto = atoi(buff); 
	do_insert_fme(fme); 
}

void ins_fmo(struct fmo *fmo)
{	
	char buff[NUM_LEN]; 
	printf("** Dettagli inserimento fmo **\n\n");
	get_input("Inserisci il nome del modello in questione: ", VARCHAR_LEN, fmo->modello, false);
	get_input("Inserisci l'id della foto in questione: ", NUM_LEN, buff, false);
	fmo->foto = atoi(buff); 
	do_insert_fmo(fmo); 
}


void ins_comfort(struct comfort *comfort)
{	
	printf("** Dettagli inserimento comfort **\n\n");
	get_input("Inserisci il nome : ", VARCHAR_LEN, comfort->nomecomfort, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, comfort->descrizionecomfort, false);
	do_insert_comfort(comfort); 
}

void ins_rt(struct rt *rt)
{	
	char buff[NUM_LEN]; 
	printf("** Dettagli inserimento rt **\n\n");
	get_input("Inserisci l'id della revisione in questione: ", NUM_LEN, buff, false);
	rt->revisionerelativa = atoi(buff);
	get_input("Inserisci l'id del tagliando in questione: ", NUM_LEN, buff, false);
	rt->tagliandoassociato= atoi(buff); 
	do_insert_rt(rt); 
}

void ins_presents(struct presenti *presenti)
{	
	char buff[NUM_LEN]; 
	printf("** Dettagli inserimento presenti **\n\n");
	get_input("Inserisci il nome del modello in questione: ", VARCHAR_LEN, presenti->modelloassciato, false);
	get_input("Inserisci l'id del comfort in questione: ", NUM_LEN, buff, false);
	presenti->comfortpresenti= atoi(buff); 
	do_insert_presents(presenti); 
}



void ins_skills(struct competenze *competenze)
{	
	printf("** Dettagli inserimento competenze **\n\n");
	get_input("Inserisci il nome del modello associato: ", VARCHAR_LEN, competenze->modelloassociato, false);
	get_input("Inserisci la mail del meccanico competente : ", VARCHAR_LEN, competenze->meccanicocompetente, false);
	do_insert_skills(competenze); 
}

void ins_employee(struct dipendente *dipendente) 
{	
	printf("** Dettagli inserimento dipendente **\n\n");
	get_input("Inserisci la mail: ", VARCHAR_LEN, dipendente->emaildipendente, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, dipendente->nomedipendente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, dipendente->cognomedipendente, false);
	get_input("Inserisci il numero di telefono aziendale: ", TEL_LEN ,dipendente->telefonoaziendale, false);
	do_insert_employee(dipendente);
	
}

void validate_reservation(struct prenotazione *prenotazione , struct postoprenotato *postoprenotato, struct soggiorno *soggiorno)
{
	char buff[NUM_LEN]; 
	printf("** Procedura conferma prenotazione **\n\n"); 
	get_input("Inserisci la mail del cliente prenotante: ", VARCHAR_LEN,prenotazione->clienteprenotante, false);
	get_reservation_info(prenotazione->clienteprenotante);
 	bool ans = yes_or_no("\n\n Vuoi confermare una di queste prenotazioni? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
		}
	get_input("Inserisci il numero di prenotazione che si intende confermare: ", NUM_LEN, buff, false);
	prenotazione->numerodiprenotazione = atoi(buff); 
	while(true){
		get_input("Modifica data di conferma [YYYY-MM-DD]: ", DATE_LEN, prenotazione ->datadiconferma, false);
		if(validate_date(prenotazione ->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
		}

	while(true){
		get_input("Modifica data di saldo [YYYY-MM-DD]: ", DATE_LEN, prenotazione->datasaldo, false);
		if(validate_date(prenotazione ->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
		}

	do_validate_reservation(prenotazione);

	bool seat_ans, association_ans;   

	do {
		printf("\n\n** Associa un passeggero alla prenotazione ** \n\n"); 

		postoprenotato ->prenotazioneassociata = prenotazione ->numerodiprenotazione; 

		get_input("Inserisci il numero di posto: ", NUM_LEN, buff, false);
		postoprenotato->numerodiposto = atoi(buff); 
		get_input("Inserisci l'età: ", NUM_LEN, buff, false);
		postoprenotato->etapasseggero = atoi(buff); 
		get_input("Inserisci il nome: ", VARCHAR_LEN, postoprenotato-> nomepasseggero, false);
		get_input("Inserisci il cognome: ", VARCHAR_LEN, postoprenotato-> cognomepasseggero, false);

	do_insert_seat(postoprenotato);

		ans = yes_or_no("\n\n Vuoi associare una camera a questo passeggero? (s/n) ",'s','n',false,false);
		if (ans)
			do{	
				soggiorno->prenotazioneinquestione= prenotazione->numerodiprenotazione; 
				soggiorno->ospite  = postoprenotato->numerodiposto; 
				printf("\n** Associa soggiorno**\n\n");
				get_input("Inserisci il numero della camera: ", NUM_LEN, buff, false);
				soggiorno->cameraprenotata = atoi(buff); 
				get_input("Inserisci l'albergo in cui è ubicata la camera: ", NUM_LEN, buff,false);	
				soggiorno->albergoinquestione = atoi(buff); 
				while(true){
					get_input("Inserici la data d'inizio del soggiorno [YYYY-MM-DD]: ",DATE_LEN, soggiorno->datainiziosoggiorno,false); 
					if(validate_date(soggiorno->datainiziosoggiorno))
						break;
					fprintf(stderr, "Data errata!\n");
				}
				while(true){
					get_input("Inserisci la data di fine soggiorno [YYYY-MM-DD]: ",DATE_LEN, soggiorno->datafinesoggiorno, false);
					if(validate_date(soggiorno->datafinesoggiorno))
						break;
					fprintf(stderr, "Data errata!\n");
				} 
				association_ans= yes_or_no("\n\n Vuoi associare un'altra camera a questo passeggero? (s/n) ",'s','n',false,false);
			}while(association_ans);
		seat_ans =yes_or_no("\n\n Vuoi associare un'altro passeggero a questa prenotazione ? (s/n) ",'s','n',false,false);
	} while(seat_ans); 

}#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../utils/io.h"
#include "../utils/validation.h"
#include "../model/trpdb.h"


extern void ins_costumer(struct cliente *cliente);
extern void ins_costumer_hstss(struct cliente *cliente, struct utente *utente );
extern void ins_prenotation(struct prenotazione *prenotazione);
extern void ins_seat(struct postoprenotato *postoprenotato);
extern void ins_review(struct revisione *revisione, struct sostituito *sostituito, struct ricambio *ricambio);
extern void ins_sparepart(struct ricambio *ricambio);
extern void ins_bus(struct mezzo *mezzo);
extern void ins_model(struct modello *modello, struct competenze *competenze);
extern void ins_certify(struct tagliando *tagliando);
extern void ins_stay(struct soggiorno *soggiorno);
extern void ins_sostitution( struct sostituito *sostituito); 
extern void ins_tour(struct tour *tour);
extern void ins_trip(struct viaggio *viaggio);
extern void ins_destination(struct  meta *meta);
extern void ins_visit(struct visita *visita);
extern void ins_room(struct camera *camera);
extern void ins_location(struct localita *localita);
extern void ins_map(struct mappa *mappa);
extern void ins_picture(struct documentazionefotografica *documentazionefotografica) ;
extern void ins_employee(struct dipendente *dipendente);
extern void ins_user(struct utente *utente);
extern void ins_offert(struct offre *offre); 
extern void ins_service(struct servizio *servizio);
extern void ins_fmo(struct fmo *fmo); 
extern void ins_fme(struct fme *fme); 
extern void ins_bus(struct mezzo *mezzo);
extern void ins_sparepart(struct ricambio *ricambio);
extern void ins_comfort(struct comfort *comfort);
extern void ins_skills(struct competenze *competenze); 
extern void ins_costumer_user(struct utente *utente); 
extern void validate_reservation(struct prenotazione *prenotazione , struct postoprenotato *postoprenotato, struct soggiorno *soggiorno); 
extern void ins_presents(struct presenti *presenti); 
extern void ins_rt(struct rt *rt); 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "login.h"
#include "hostess.h"
#include "cliente.h"
#include "meccanico.h"
#include "autista.h"
#include "manager.h"
#include "../utils/io.h"

void view_login(struct credentials *cred)
{
	
	puts("*********************************");
	puts("*   BENVENUTI IN TRIPBUS *");
	puts("*********************************\n");
	get_input("Username: ", USERNAME_LEN, cred->username, false);
	get_input("Password: ", PASSWORD_LEN, cred->password, true);

}

bool ask_for_relogin(void)
{
	return yes_or_no("Vuoi accedere con utente differente?", 's', 'n', false, true);
	clear_screen(); 
	

}

int main (void)
{	
	bool answer = false; 
	bool ans = true; 


	size_t role; 

	struct credentials *cred;

	cred = malloc(sizeof(struct credentials));

	init_db();

	while (!answer){
		
		if(ans){
			view_login(cred); 
			role = attempt_login(cred);
		}

		switch(role){
			case AUTISTA: 
				run_drvr_interface();  
				break;
			case CLIENTE:
				run_cstmr_interface(); 
				break; 
			case HOSTESS:
				run_hstss_interface(); 
				break; 
			case MECCANICO: 
				run_mch_interface();  
				break; 
			case MANAGER: 
				run_mngr_interface(); 
			case QUIT: 
				printf("Quit!\n");
			}
			
			ans = ask_for_relogin(); 
			if(!ans){
				answer = yes_or_no("\n\nVuoi chiudere il database? (s/n) ",'s','n',false,false);
					if(answer){
						fini_db();
					}
			}
	}
	
	return 0; 
}


#pragma once

#include "../model/trpdb.h"

extern bool ask_for_relogin(void);
extern void view_login(struct credentials *cred);
compile: 
	gcc  *.c -o run  ../model/trpdb.c  ../utils/io.c ../utils/validation.c ../utils/db.c ../utils/dotenv.c `mysql_config --cflags --include --libs`

clean: 
	-rm run

#include <stdio.h>

#include "manager.h"
#include "ins.h"
#include "show.h"
#include "dlt.h"

#include "../utils/io.h"
#include "../utils/validation.h"

struct soggiorno * soggiorno;
struct camera *camera; 
struct documentazionefotografica *documentazionefotografica; 
struct cliente *cliente; 
struct comfort *comfort; 
struct competenze *competenze; 
struct dipendente * dipendente; 
struct fmo *fmo; 
struct fme *fme; 
struct localita *localita; 
struct mappa *mappa; 
struct meta *meta; 
struct mezzo *mezzo; 
struct modello *modello; 
struct offre *offre; 
struct postoprenotato *postoprenotato; 
struct prenotazione *prenotazione; 
struct presenti *presenti;
struct revisione *revisione;
struct rt *rt;  
struct ricambio *ricambio; 
struct servizio *servizio; 
struct sostituito *sostituito; 
struct tagliando *tagliando; 
struct tour *tour; 
struct viaggio *viaggio;
struct visita *visita;  
struct utente *utente; 

int allocation_gest(void)
{

	dipendente = malloc(sizeof(struct dipendente));
	if(dipendente == NULL)
		{printf("Fallimento malloc su dipendente (manager) \n\n"); 
		 return -1; 
		}

	servizio= malloc(sizeof(struct servizio));
	if(servizio== NULL)
		{printf("Fallimento malloc servizio(manager) \n\n"); 
		 return -1; 
	    }
	if(utente == NULL)
    	{utente = malloc(sizeof(struct utente));
		if(utente == NULL)
			{printf("Fallimento malloc utente (manager) \n\n"); 
		 return -1; 
			 }
		}

}

int allocation_costumer(void)
{	
	if(utente == NULL)
		{utente  = malloc(sizeof(struct utente )); 
		if(utente  == NULL)
			{printf("Fallimento malloc su utente  (manager)) \n\n"); 
			 return -1; 
			}
		}
	cliente = malloc(sizeof(struct cliente)); 
	if(cliente == NULL)
		{printf("Fallimento malloc su cliente (manager)) \n\n"); 
		 return -1; 
		}
	prenotazione = malloc(sizeof(struct prenotazione)); 
	if(prenotazione == NULL)
		{printf("Fallimento malloc su prenotazione (manager) \n\n");
		 return -1; 
		}
	postoprenotato = malloc(sizeof(struct postoprenotato));
	if(postoprenotato == NULL)
		{printf("Fallimento malloc su postoprenotato (manager) \n\n"); 
		 return -1; 
		}
	
	soggiorno = malloc(sizeof(struct soggiorno)); 
	if(soggiorno == NULL)
		{printf("Fallimento malloc su soggiorno (manager)) \n\n"); 
		 return -1; 
		}
		

}

int allocation_workshop(void)
{	

	mezzo = malloc(sizeof(struct mezzo));
	if(mezzo == NULL)
		{printf("Fallimento malloc su mezzo (manager) \n\n"); 
		 return -1;
		}
	modello = malloc (sizeof(struct modello));
	if(modello == NULL)
		{printf("Fallimento malloc su modello (manager) \n\n"); 
		 return -1;
		}
	revisione = malloc(sizeof(struct revisione));
	if(revisione == NULL)
		{printf("Fallimento malloc su revisione (manager) \n\n"); 
		 return -1;
		}

	ricambio = malloc(sizeof(struct ricambio));
	if(ricambio == NULL)
		{printf("Fallimento malloc su ricambio (manager) \n\n"); 
		 return -1;
		}
	
	tagliando = malloc(sizeof(struct tagliando));
	if(tagliando == NULL)
		{printf("Fallimento malloc su tagliando (manager) \n\n"); 
		 return -1;
		}
	comfort = malloc(sizeof(struct comfort));
	if(comfort == NULL)
		{printf("Fallimento malloc su comfort (manager) \n\n"); 
		 return -1;
		}
	competenze = malloc(sizeof(struct competenze)); 
	if(competenze == NULL)
		{printf("Fallimento malloc su competenze (manager) \n\n");
		 return -1; 
		}
	sostituito= malloc(sizeof(struct sostituito)); 
	if(sostituito== NULL)
		{printf("Fallimento malloc su sostituito(manager) \n\n");
		 return -1; 
		}

}

int allocation_tour(void){

	camera = malloc(sizeof(struct camera));
	if(camera == NULL)
		{printf("Fallimento malloc su camera (manager) \n\n"); 
		 return -1;
		}
	documentazionefotografica = malloc(sizeof(struct documentazionefotografica));
	if(documentazionefotografica == NULL)
		{printf("Fallimento malloc su documentazionefotografica (manager) \n\n"); 
		 return -1;
		}
	localita = malloc(sizeof(struct localita));
	if(localita == NULL)
		{printf("Fallimento malloc su localita (manager) \n\n"); 
		 return -1;
		}
	mappa = malloc(sizeof(struct mappa));
	if(mappa == NULL)
		{printf("Fallimento malloc su mappa (manager) \n\n"); 
		 return -1;
		}
	meta = malloc(sizeof(struct meta));
	if(meta == NULL)
		{printf("Fallimento malloc su meta (manager) \n\n"); 
		 return -1;
		}
	viaggio = malloc(sizeof(struct viaggio));
	if(viaggio == NULL)
		{printf("Fallimento malloc su viaggio (manager) \n\n"); 
		 return -1;
		}
	visita = malloc(sizeof(struct visita));
	if(visita == NULL)
		{printf("Fallimento malloc su visita (manager) \n\n"); 
		 return -1;
		}
	tour = malloc(sizeof(struct tour));
	if(tour == NULL)
		{printf("Fallimento malloc su tour (manager) \n\n"); 
		 return -1;
		}

}

int allocation_con_table(void)
{
	presenti = malloc(sizeof(struct presenti)); 
	if(presenti == NULL)
		{printf("Fallimento malloc su presenti (manager) \n\n"); 
		 return -1;
		}
	rt = malloc(sizeof(struct rt)); 
	if(rt == NULL)
		{printf("Fallimento malloc su rt (manager) \n\n"); 
		 return -1;
		}
	fmo = malloc(sizeof(struct fmo)); 
	if(fmo == NULL)
		{printf("Fallimento malloc su fmo (manager) \n\n"); 
		 return -1;
		}
	fme = malloc(sizeof(struct fme));
	if(fme == NULL)
		{printf("Fallimento malloc fme (manager) \n\n"); 
		 return -1; 
		 }
	offre = malloc(sizeof(struct offre));
	if(offre == NULL)
		{printf("Fallimento malloc offre (manager) \n\n"); 
		 return -1; 
	    }
	
}


int get_mngr_action(void) 
{	char options[4] = {'1','2','3','4'};
	char op; 
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Visualizzazione");
	puts("2) Inserimento");
	puts("3) Cancellazione");
	puts("4) Esci");
	op = multi_choice("Seleziona un'opzione", options, 4);
	return op - '1';
}

int get_mngr_group(void)
{	char options[6] = {'1','2','3','4','5','6'};
	char op; 
	puts("*********************************");
	puts("*   INTERFACCIA AMMINISTRATORE    *");
	puts("*********************************\n");
	puts("*** In quale ambito ? ***\n");
	puts("1) Gestione interna");
	puts("2) Gestione tour");
	puts("3) Gestione officina");
	puts("4) Gestione clienti");
	puts("5) Gestione tabelle connessione");
	puts("6) Esci");

	op = multi_choice("Seleziona un'opzione", options, 6);
	return op - '1';

}


bool get_table_tour(char sel)
{
	char act; 
	if(camera == NULL || documentazionefotografica == NULL || localita == NULL || mappa == NULL || meta == NULL ){
		allocation_tour();
		printf("Allocazione tour avvenuta\n\n"); 
	}
	switch(sel){
		case TABELLA_TOUR:{
			act = get_mngr_action();
				switch(act){
					case GESTIONE_SELECT: {
                    	show_tour(tour); 
               			return true; 
               		}
	            	case GESTIONE_INSERT: {
                   		ins_tour(tour); 
                		return true; 
                	}
	            	case GESTIONE_DELETE: {
                    	dlt_tour(tour); 
                	return true; 
               		}
	            	case QUIT_GEST_OP: {
                    	return false; 
                	}
				} 
			}
    	case TABELLA_VIAGGIO:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_trip(viaggio); 
                return true; 
                }
	            case GESTIONE_INSERT: {
					ins_trip(viaggio); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_trip(viaggio);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}
    	case TABELLA_META:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_destination(meta); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_destination(meta); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_destination(meta); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		} 
    	case TABELLA_VISITA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_visit(visita); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_visit(visita); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_visit(visita); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		} 
		case TABELLA_CAMERA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_room(camera); 
                return true; 
                }
	            case GESTIONE_INSERT: {
					ins_room(camera);
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_room(camera); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}
    	case TABELLA_LOCALITA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_location(localita); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_location(localita); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_location(localita); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}
    	case TABELLA_MAPPA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_map(mappa); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_map(mappa); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_map(mappa);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}
		case TABELLA_DOCUMENTAZIONEFOTOGRAFICA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_picture(documentazionefotografica); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_picture(documentazionefotografica); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_picture(documentazionefotografica);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}
    	case QUIT_GEST_TOUR:{
		return false; 
	}
	}
}

int tour_section(void) //sezione tour
{	
	char options[9] = {'1','2','3','4','5','6','7','8','9'};
    char op; 
		puts("*** Su quale tabella della gestione tour? ***\n");
		puts("1) Tour");
		puts("2) Viaggio");
		puts("3) Meta");
		puts("4) Visita");
		puts("5) Camera"); 
		puts("6) Località"); 
		puts("7) Mappa");
		puts("8) Documentazione fotografica"); 
		puts("9) Esci");
		op = multi_choice("Seleziona un'opzione", options, 9);
		get_table_tour(( op - '1'));
}


bool get_table_workshop(char sel){ 
	char act; 
	if (mezzo == NULL || modello == NULL || revisione == NULL || ricambio == NULL || tagliando == NULL || comfort == NULL || competenze == NULL)
		{
			allocation_workshop(); 
			printf("Allocazione costumer avvenuta\n\n"); 
		}
	switch(sel){
		case TABELLA_MODELLO: {
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_model(modello); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_model(modello, competenze); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_model(modello); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}
    	case TABELLA_MEZZO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_bus(mezzo); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_bus(mezzo); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_bus(mezzo); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		} 
    	case TABELLA_RICAMBIO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_sparepart(ricambio); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_sparepart(ricambio); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_sparepart(ricambio); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}  
    	case TABELLA_REVISIONE:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_review(revisione); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_review(revisione,sostituito,ricambio); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_review(revisione); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}  
    	case TABELLA_TAGLIANDO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_certify(tagliando); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_certify(tagliando); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_certify(tagliando);
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		} 
		case TABELLA_COMFORT:{
		
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_comfort(comfort); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                	ins_comfort(comfort); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_comfort(comfort);
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		} 
		case TABELLA_COMPETENZE:{
		
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_skills(competenze); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                	ins_skills(competenze); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_skills(competenze);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		} 
		case TABELLA_SOSTITUITO:{
		
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_sostitution(sostituito); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                	ins_sostitution(sostituito); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_sostitution(sostituito);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		} 
    	case QUIT_GEST_OFFICINA:{
			return false; 
		}
	}
}

int workshop_section(void) // sezione officina 
 {	    
		char options[9] = {'1','2','3','4','5','6','7','8','9'};
        char op; 
		 puts("*** Su quale tabella della gestione officina? ***\n");
	 	 puts("1) Modello ");
	 	 puts("2) Mezzo");
	 	 puts("3) Ricambio");
		 puts("4) Revisione");
		 puts("5) Tagliando");
		 puts("6) Comfort"); 
		 puts("7) Competenze"); 
		 puts("8) Sostituzione");
		 puts("9) Esci");
		 op = multi_choice("Seleziona un'opzione", options, 9);
		 get_table_workshop((op - '1'));
}


bool get_table_costumer (char sel )
{ 	
	char act; 
	if(cliente == NULL || prenotazione  == NULL || postoprenotato == NULL) {
		allocation_costumer();
		printf("\n\nAllocazione costumer avvenuta.\n\n");
     } 
    switch(sel){
		case TABELLA_CLIENTE: {
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_costumer(cliente); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_costumer(cliente);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			}
		}

    	case TABELLA_PRENOTAZIONE:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_reservation(prenotazione); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                	ins_prenotation(prenotazione); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_reservation(prenotazione);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			}
		} 

    	case TABELLA_POSTO_PRENOTATO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_seat(postoprenotato); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_seat(postoprenotato); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_seat(postoprenotato); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
		}
		case TABELLA_SOGGIORNO: {
        act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_stay(soggiorno); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_stay(soggiorno); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_stay(soggiorno); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
            } 
			return true;
        } 
		case VALIDAZIONE_PRENOTAZIONE: {
			validate_reservation(prenotazione, postoprenotato,soggiorno); 
			return true; 
		}

    	case QUIT_GEST_CLIENTE: {
		return false; 
		}
	}

}

int costumer_section(void) // sezione clienti
{	
	char options[6] = {'1','2','3','4','5','6'};
    char op; 
    puts("*** Su quale tabella della gestione clienti? ***\n");
	puts("1) Cliente");
    puts("2) Prenotazione");
	puts("3) Posto prenotato");
	puts("4) Soggiorno");
	puts("5) Validazione prenotazioni");
	puts("6) Esci");
    op = multi_choice("Seleziona un'opzione", options, 6);
	get_table_costumer((op-'1')); 
}


bool get_table_gest (char sel)
{   char act;
    if( dipendente == NULL || servizio == NULL  || utente == NULL) {
		allocation_gest();
		printf("\n\nAllocazione gest avvenuta.\n\n");
     } 
    switch(sel){
        case TABELLA_DIPENDENTI: {
         act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_employee(dipendente); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_employee(dipendente); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_employee(dipendente); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
			} 
			return true; 
        }

        case TABELLA_UTENTI: {
         act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_user(utente); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_user(utente); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_user(utente); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
            } 
        return true; 
        }


		case TABELLA_SERVIZI: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_service(servizio); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_service(servizio); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                     dlt_service(servizio);  
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
            } 
		return true; 
        }
        case QUIT_ANAG: {
        return false; 
        }
    }

}

int gest_section(void)
 {	    
		char options[4] = {'1','2','3','4'};
        char op; 
		 puts("*** Su quale tabella della gestione interna? ***\n");
	 	 puts("1) Dipendenti");
	 	 puts("2) Utenti");
		 puts("3) Servizi"); 
         puts("4) Esci"); 
		 op = multi_choice("Seleziona un'opzione", options, 4);
         get_table_gest((op - '1')); 
}

bool get_table_con_tab (char sel)
{   char act;
    if(offre == NULL||fme == NULL ||fmo == NULL || presenti == NULL || rt == NULL) {
		allocation_con_table();
		printf("\n\nAllocazione gest avvenuta.\n\n");
     } 
    switch(sel){    
		
        case TABELLA_OFFRE: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_ofr(offre); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_offert(offre); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_ofr(offre); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
            } 
		return true; 
        }    

		 case TABELLA_PRESENTI: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_presents(presenti); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_presents(presenti); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_presents(presenti); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
            } 
		return true; 
        }    

        case TABELLA_FMO: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_fmo(fmo); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_fmo(fmo); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_fmo(fmo);
                return true; 
                }
	            case QUIT_GEST_OP: {
                return false; 
				}
			}
			return true;
        
        } 
 
        case TABELLA_FME: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_fme(fme); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    ins_fme(fme); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    dlt_fme(fme); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                return false; 
				}
			}
			return true;
        }
		case TABELLA_RT: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                   show_rt(rt); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                   ins_rt(rt); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                  dlt_rt(rt); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                return false; 
				}
			}
			return true;
        }
        case QUIT_GEST_TAB: {
        return false; 
        }
    }
}


int tab_con_section(void)
 {	    
		char options[6] = {'1','2','3','4','5','6'};
        char op; 
		 puts("*** Su quale delle tabelle di connessione ? ***\n");
		 puts("1) Offre");
		 puts("2) Presenti"); 							///
         puts("3) Collegamento foto-modelli");
         puts("4) Collegamento foto-mete");
		 puts("5) Collegamento revisione-tagliando");  ///
         puts("6) Esci"); 
		 op = multi_choice("Seleziona un'opzione", options, 6);
         get_table_con_tab ((op - '1')); 
}



bool exe_mngr_group(char sel)
{	

	switch (sel)
		{	
			case GESTIONE_DIPENDENTI: {
				gest_section(); 
				return true;
				}
			case GESTIONE_CLIENTI:{
				costumer_section();  
				return true; 
				}
		
			case GESTIONE_OFFICINA:{
				workshop_section();  
				return true;
				}
     		case GESTIONE_TOUR:{
                tour_section(); 
				return true; 
				}
			case GESTIONE_TABELLE_CONNESSIONE:{
				tab_con_section();
				return true; 
			}
			case QUIT_GEST_GROUP:{ 
				return false;
		 		} 
		
	}
	return true;
}

void run_mngr_interface (void)
{ 	
	char sel;
	while (true){
	sel = get_mngr_group(); 
	if (!exe_mngr_group(sel))
		break; 
	}

}	
#pragma once
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>

#include "../model/trpdb.h"

typedef enum{
	GESTIONE_DIPENDENTI,
	GESTIONE_TOUR,
	GESTIONE_OFFICINA,
    GESTIONE_CLIENTI,
    GESTIONE_TABELLE_CONNESSIONE, 
	QUIT_GEST_GROUP
} gest_act;


typedef enum{
	GESTIONE_SELECT,
	GESTIONE_INSERT,
	GESTIONE_DELETE,
	QUIT_GEST_OP
} gest_op;

typedef enum{
    TABELLA_OFFRE,
    TABELLA_PRESENTI,
    TABELLA_FMO, 
    TABELLA_FME,
    TABELLA_RT,
	QUIT_GEST_TAB
} gest_con_tab;

typedef enum{
    TABELLA_DIPENDENTI,
    TABELLA_UTENTI,
    TABELLA_SERVIZI,
    QUIT_ANAG
}gest_str;

typedef enum{
    TABELLA_TOUR,
    TABELLA_VIAGGIO, 
    TABELLA_META, 
    TABELLA_VISITA, 
    TABELLA_CAMERA, 
    TABELLA_LOCALITA,
    TABELLA_MAPPA,
    TABELLA_DOCUMENTAZIONEFOTOGRAFICA,
    QUIT_GEST_TOUR
}gest_tour;

typedef enum{
    TABELLA_MODELLO,
    TABELLA_MEZZO, 
    TABELLA_RICAMBIO, 
    TABELLA_REVISIONE, 
    TABELLA_TAGLIANDO,
    TABELLA_COMFORT,
    TABELLA_COMPETENZE,
    TABELLA_SOSTITUITO,
    QUIT_GEST_OFFICINA
}gest_workshop;

typedef enum{
    TABELLA_CLIENTE,
    TABELLA_PRENOTAZIONE, 
    TABELLA_POSTO_PRENOTATO,
    TABELLA_SOGGIORNO, 
    VALIDAZIONE_PRENOTAZIONE, 
    QUIT_GEST_CLIENTE
}gest_costumer;




 
extern void run_mngr_interface (void);
#include <stdio.h>

#include "meccanico.h"
#include "ins.h"
#include "show.h"
#include "../utils/io.h"
#include "../utils/validation.h"

struct revisione *revisione_mch; 
struct sostituito *sostituito_mch; 
struct ricambio *ricambio_mch; 

int allocation_mch(void)
{
	revisione_mch = malloc(sizeof( struct revisione)); 
	if(revisione_mch == NULL){
		printf("Impossibile eseguire malloc su revisone\n"); 
		return -1; 
	}

	sostituito_mch = malloc(sizeof(struct sostituito));
	if(sostituito_mch == NULL){
		printf("Impossibile eseguire malloc su sostituito\n"); 
		return -1;
	} 

	ricambio_mch = malloc(sizeof(struct ricambio));
	if(ricambio_mch == NULL){
		printf("Impossibile eseguire malloc su ricambio\n"); 
		return -1;
	}
}

void selection (void)
{
char buff[NUM_LEN];
get_input("Inserisci il codice ricambio : ", VARCHAR_LEN, buff, false); 
revisione_mch->idrevisione = atoi(buff);
do_select_review(revisione_mch); 
show_review(revisione_mch); 
}


int get_mch_action(void)
{
	char options[3] = {'1','2','3'};
	char op;
			
	puts("*********************************");
	puts("*   INTERFACCIA MECCANICO    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Inserisci una nuova revisione");
	puts("2) Consulta le revisioni scadute");
	puts("3) Esci");

	op = multi_choice("Select an option", options,3);
	return op - '1';
}

bool exe_mch_act(mch_act sel)
{	
	 
	switch (sel){
		case INS_REVISIONE:{
			ins_review(revisione_mch, sostituito_mch, ricambio_mch); 
		return true;   
		}
		case PIANIFICA_REVISIONE: {
			show_expired_review(); 
		return true; 
		}
		case QUIT_MCH:
		return false;
		
	break;
	}

	return true; 
}

void run_mch_interface (void)
{ 	
	char sel; 
	if(revisione_mch == NULL || sostituito_mch == NULL || ricambio_mch == NULL) 
		allocation_mch(); 
	while (true){
	sel = get_mch_action(); 
	if(!exe_mch_act(sel))
		break; 
	
	}
}



#pragma once
#include "../model/trpdb.h"

typedef enum {
	INS_REVISIONE,
	PIANIFICA_REVISIONE,
	QUIT_MCH
}mch_act;

	
/*
extern void show_expired_revisions(struct revisioni_scadute *revisioni_scadute); // Procedura visualizazzione revisioni scadute
extern void show_sparepart(struct ricambio *ricambio); // procedura visualizazzione ricambio
extern void update_sparepart_number(struct ricambio *ricambio);// Procedura modifica quantità in magazzino
*/
extern void run_mch_interface (void);
#include <string.h>
#include "../model/trpdb.h"
#include "show.h" 



int show_reservation (struct prenotazione * prenotazione)
{	

	char buff[NUM_LEN];
	printf("\n\n**  Dettagli prenotazione ** \n\n"); 
	get_input("Inserisci numero d'interesse : ", NUM_LEN , buff, false); 
	prenotazione->numerodiprenotazione = atoi(buff); 
    if(do_select_reservation(prenotazione)>0) {
		printf("\n\n** Dettagli prenotazione **\n\n");
 		printf(" E-mail cliente: 	%s \n Id viaggio: 		%d \n Posti prenotati:	%d \n Data di prenotazione: 	%s \n Data di conferma: 	%s \n Data Saldo: 		%s \n\n",
			prenotazione->clienteprenotante,
			prenotazione->viaggioassociato, 
			prenotazione->numerodipostiprenotati,
			prenotazione->datadiprenotazione, 
			prenotazione->datadiconferma, 
			prenotazione->datasaldo);
		 }
	else {
		printf("Il numero di prenotazione non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

int show_trip(struct viaggio *viaggio)
{	
	char buff[NUM_LEN]; 
	printf("\n\n**  Dettagli viaggio ** \n\n"); 
	get_input("Inserisci l'id d'interesse: ", NUM_LEN, buff, false); 
	viaggio->idviaggio = atoi(buff); 
	if(do_select_trip(viaggio)>0){
 		printf("*Tour:				%s \n Conducente:			%s \n Accompagnatrice:		%s \n Targa mezzo:			%s \n Data di partenza:		%s \n Data di ritorno:		%s \n Costo:				%f \n Chilometri da percorrere:	%d \n Posti disponibili:		%d \n Data annullamento:		%s \n\n", 
			viaggio->tourassociato,
			viaggio->conducente, 					
			viaggio->accompagnatrice, 				
			viaggio->mezzoimpiegato, 			
			viaggio->datadipartenzaviaggio, 
			viaggio->datadiritornoviaggio, 
			viaggio->costodelviaggio, 
			viaggio->numerodikm, 
			viaggio->postidisponibili,
			viaggio->datadiannullamento); 
		 }
	else{
		 printf("L'id inserito non esiste\n\n"); 
		 	return -1; 
	}
	return 0; 
}

int show_costumer (struct cliente * cliente)
{	
	
	get_input("Inserisci la mail d'interesse : ", VARCHAR_LEN , cliente->emailcliente, false);
    if(do_select_costumer(cliente)>0){
		printf("\n\n**  Dettagli cliente ** \n\n");
			printf("\n E-mail:  %s \n Nome: %s \n Cognome: %s \n Indirizzo: %s \n Codice fiscale: %s \n Recapito telefonico: %s \n Fax: %s \n Data documentazione: %s \n", 
			cliente->emailcliente,
			cliente->nomecliente,
			cliente->cognomecliente,
			cliente->indirizzocliente,
			cliente->codicefiscale,
			cliente->recapitotelefonico,
			cliente->fax,
			cliente->datadocumentazione);
		}
	else {
		printf("La mail inserita non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_tour(struct tour *tour)
{
	printf("\n\n**  Dettagli tour ** \n\n");
	get_input("Inserisci la denomiazione d'interesse: ", VARCHAR_LEN, tour->denominazionetour, false); 
	if(do_select_tour(tour) > 0) {
		printf("*Descrizione:		%s \n Minimo partecipanti:	%d \n Assicurazione medica:	%f \n Bagaglio: 		%f \n Garanzia annullamento:	%f \n Accompagnatrice:	%d \n",  
			tour->descrizionetour, 
			tour->minimopartecipanti,
			tour->assicurazionemedica, 
			tour->bagaglio, 
			tour->garanziaannullamento, 
			tour->accompagnatrice);
		}
	else { 
		printf("La denominazione inserita non esiste\n\n"); 
			return -1; 
	}
	return 0; 

}



int show_sparepart(struct ricambio *ricambio)
{	


	printf("\n\n**  Dettagli ricambio ** \n\n");
	get_input("Inserisci il codice del ricambio d'interesse: ",VARCHAR_LEN, ricambio->codice, false);
	if(do_select_sparepart(ricambio) > 0){
		printf("*Costo unitario:	%f \n Quatità di Riordino: 	%d \n Scorta Minima:		%d \n Quantità in magazzino:	%d \n Descrizione:		%s \n", 
			ricambio->costounitario,
			ricambio->quantitadiriordino,
			ricambio->scortaminima,
			ricambio->quantitainmagazzino,
			ricambio->descrizione);	
		}
	else {
		printf("Il codice inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_review (struct revisione *revisione){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli revisione **\n\n");
	get_input("Inserisci l'id d'interesse: ", NUM_LEN, buff, false); 
	revisione->idrevisione = atoi(buff);
	if(do_select_review(revisione) > 0){
 		printf("*Mezzo revsionato:	%s \n Mail adetto: 		%s \n Data inizio: 		%s \n Data fine: 		%s\n Chilometraggio:	%d\n Operazioni eseguite:	%s \n Motivazione:	%s \n\n",
			revisione->mezzorevisionato,
			revisione->addettoallarevisione,
			revisione->datainizio,
			revisione->datafine,
			revisione->chilometraggio,
			revisione->operazionieseguite,
			revisione->motivazione);
		}
	else { 
		printf("L'id inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

int show_bus(struct mezzo *mezzo)
{	
	printf("\n\n** Dettagli mezzo **\n\n");
	get_input("Inserisci la targa del mezzo d'interesse: ", VARCHAR_LEN, mezzo->targa, false); 
	if(do_select_bus(mezzo) > 0){
 		printf(" *Modello:		%s\n Ultima revisone mtc: 	%s \n Ingombri: 		%s \n Autonomia: 		%d\n Chilometraggio:	%d\n Data immatricolazione:	%s \n\n",
			mezzo->modellomezzo,
			mezzo->dataultimarevisioneinmotorizzazione, 
			mezzo->ingombri, 
			mezzo->autonomia,
			mezzo->valorecontakm, 
			mezzo->dataimmatricolazione); 
		}
	else { 
		printf("La targa insertia non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

int show_stay(struct soggiorno *soggiorno)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli soggiorno **\n\n");
	get_input("Inserisci l'id del soggiorno:",NUM_LEN, buff, false); 
	soggiorno->idsoggiorno = atoi(buff); 
	printf("show\n\n"); 
	if(do_select_stay(soggiorno) > 0){
		printf("show\n\n"); 
 		printf("*Albergo:	%d \n Camera:	%d \n Ospite:	%d\n Prenotazione:	%d \n Data inizio soggiorno: %s \n Data fine soggiorno:	%s \n\n",
			soggiorno->albergoinquestione,
			soggiorno->cameraprenotata,
			soggiorno->ospite,
			soggiorno->prenotazioneinquestione,
			soggiorno->datainiziosoggiorno,
			soggiorno->datafinesoggiorno); 
		}
	else { 
		printf("Il soggiorno richiesto non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

int show_skills(struct competenze *competenze)
{	
	printf("\n\n** Dettagli competenze  **\n\n");
	get_input("Inserisci la mail del meccanico competente :",VARCHAR_LEN, competenze->meccanicocompetente, false); 
	get_input("Inserisci il modello d'interesse :",VARCHAR_LEN, competenze->modelloassociato, false);
	
	if(do_select_skills(competenze) > 0){
 		printf("*Nome meccanico:%s \n Telefono :	%s \n\n",
			competenze->nomemeccanico,
			competenze->telefono);
			}
	else { 
		printf("La competenza richiesta non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_employee(struct dipendente *dipendente)
{	
	printf("\n\n** Dettagli Dipendente  **\n\n");
	get_input("Inserisci la mail d'interesse:",VARCHAR_LEN,dipendente->emaildipendente, false); 
	if(do_select_employee(dipendente) > 0){
 		printf("*Nome:		%s \n Cognome:	%s \n Tipologia:	%s \n Telefono:	%s \n\n",
			dipendente->nomedipendente,
			dipendente->cognomedipendente,
			dipendente->tipologiadipendente,
			dipendente->telefonoaziendale);
		
	}
	else { 
		printf("La mail d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}


int show_fmo(struct fmo *fmo)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli Foto-Modelli  **\n\n");
	get_input("Inserisci l'id della foto d'interesse:",NUM_LEN, buff, false); 
	fmo->foto = atoi(buff); 
	get_input("Inserisci il nome del modello d'interesse:",VARCHAR_LEN, fmo->modello,  false);

	if(do_select_fmo(fmo) > 0) {
 		printf("*Descrizione:	%s \n Immagine:	%s\n\n",
			fmo->descrizione,
			fmo->immagine); 
	}
	else {
		printf("La relazione foto-modello d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_fme(struct fme *fme)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli Foto-Mete  **\n\n");
	get_input("Inserisci l'id della foto d'interesse:",NUM_LEN, buff, false); 
	fme->foto = atoi(buff); 
	get_input("Inserisci l'id della meta d'interesse:",NUM_LEN, buff, false);
	fme->meta = atoi(buff); 
	if(do_select_fme(fme) > 0){
 		printf("*Nome:	%s\n Descrizione:	%s \n Immagine:	%s\n\n",
			fme->nome,
			fme->descrizione,
			fme->immagine); 
	}
	else { 
		printf("La relazione foto-mete d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_ofr(struct offre *offre)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli servizi-offerti  **\n\n");
	get_input("Inserisci l'id del servizio d'interesse:",NUM_LEN, buff, false); 
	offre->idservizio = atoi(buff); 
	get_input("Inserisci l'id dell'albergo offerente:",NUM_LEN, buff, false);
	offre->albergoofferente = atoi(buff); 
	if(do_select_ofr(offre) > 0) {
 		printf("*Albergo:	%s\n Servizio:	%s \n Descrizione:	%s\n\n",
			offre->meta,
			offre->servizio,
			offre->descrizione); 
	}
	else { 
		printf("La realzione offre d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}



int show_presents(struct presenti *presenti){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli presenti **\n\n");
	get_input("Inserisci il modello d'interesse:", VARCHAR_LEN, presenti->modelloassciato, false);
	get_input("Inserici l'id del servizio d'interesse: ", NUM_LEN, buff, false); 
	presenti->comfortpresenti = atoi(buff); 
	if(do_select_presents(presenti) > 0 ){
 		printf("*Modello:	%s \n Comfort:		%d\n\n",
			presenti->modelloassciato,
			presenti->comfortpresenti); 
	}
	else { 
		printf("La relazione tra comfort e modelli d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_rt(struct rt *rt){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli relazione tagliando-revsione **\n\n");
	get_input("Inserisci l'id del tagliando  d'interesse:", NUM_LEN, buff, false);
	rt->tagliandoassociato = atoi(buff); 
	get_input("Inserisci l'id della revisione  d'interesse: ", NUM_LEN, buff, false); 
	rt->revisionerelativa = atoi(buff); 
	if(do_select_rt(rt) > 0 ){
 		printf("*Tagliando:	%d \n Revisione:		%d\n\n",
			rt->tagliandoassociato,
			rt->revisionerelativa); 
	}
	else { 
		printf("La relazione tra comfort e modelli d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_user(struct utente *utente){

	printf("\n\n** Dettagli utente **\n\n");
	get_input("Inserisci la mail d'interesse:", VARCHAR_LEN, utente->email, false);
	if(do_select_user(utente) > 0){
 		printf("*Password:	%s \n Tipo:		%d\n\n",
			utente->pswrd,
			utente->tipo); 
	}
	else { 
		printf("L'id inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_seat(struct postoprenotato *postoprenotato){

	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli posto prenotato  **\n\n");
	get_input("Inserisci il numero di posto d'interesse:",NUM_LEN, buff, false); 
	postoprenotato->numerodiposto = atoi(buff); 
	get_input("Inserisci il numero di prenotazione associata ",NUM_LEN, buff, false);
	postoprenotato->prenotazioneassociata = atoi(buff); 
	if(do_select_seat(postoprenotato) > 0){
 		printf("*Nome passeggero:	%s\n Cognome passeggero:	%s \n Età:			%d \n\n",
			postoprenotato->nomepasseggero,
			postoprenotato->cognomepasseggero,
			postoprenotato->etapasseggero);
	}
	else {
		printf("Il posto prenotato d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

int show_model(struct modello *modello){
	
	printf("\n\n** Dettagli modello  **\n\n");
	get_input("Inserisci il nome d'interesse:",VARCHAR_LEN, modello->nomemodello, false); 
	if(do_select_model(modello) > 0){
 		printf("* Casa costruttrice:	%s\n Dati tecnici:		%s \n Numero di posti:	%d\n Meccanici competenti:	%d\n",
			modello->casacostruttrice,
			modello->datitecnici,
			modello->numeroposti,
			modello->numeromeccanicicompetenti);
	}
	else { 
		printf("Il nome del modello inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_certify(struct tagliando *tagliando){
	
	char buff[NUM_LEN];
	printf("\n\n** Dettagli tagliando  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	tagliando->idtagliando= atoi(buff); 
	if(do_select_certify(tagliando) > 0){
 		printf("*Tipologia:		%s\n Validità superate:	%s \n\n",
			tagliando->tipologiatagliando,
			tagliando->validitasuperate);
	}
	else {
		printf("L'id inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}

int show_destination(struct meta *meta){

	char buff[NUM_LEN];
	printf("\n\n** Dettagli meta  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	meta->idmeta= atoi(buff); 
	if(do_select_destination(meta) > 0){
		printf("*Nome:		%s\n Tipologia:	%s\n Località:	%s\n Regione:	%s \n Indirizzo:	%s\n Telefono:	%s\n E-mail:	%s\n Fax:		%s\n",
			meta->nomemeta,
			meta->tipologiameta,
			meta->localitadiappartenenza,
			meta->regiodiappartenennza,
			meta->indirizzo,
			meta->telefonometa,
			meta->emailmeta,
			meta->faxmeta); 
		if(strcmp((meta->tipologiameta), "Albergo")||strcmp((meta->tipologiameta),"albergo" )== 0)
			printf(" Categoria:	%s\n\n", meta->categoriaalbergo); 
		else
			printf(" Orario di apertura:%s\n\n", meta->orariodiapertura); 
	}
	else { 
		printf("L'id inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

int show_service (struct servizio  *servizio ){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli servizio   **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	servizio ->idservizio  = atoi(buff); 
	if(do_select_service (servizio ) > 0){
		printf("*Nome:		%s \n Descrizione:	%s  \n\n",
			servizio->nomeservizio ,
			servizio->descrizioneservizio);
			}
	else {
		printf("L'id inserito non esiste\n\n");
		return -1; 
	}
	return 0; 
}

int show_comfort(struct comfort *comfort){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli comfort  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	comfort->idcomfort = atoi(buff); 
	if(do_select_comfort(comfort) > 0){
		printf("*Nome:		%s \n Descrizione:	%s  \n\n",
			comfort->nomecomfort,
			comfort->descrizionecomfort);
	}
	else {	
		printf("L'id inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}


int show_picture(struct documentazionefotografica *documentazionefotografica){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli documentazionefotografica  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	documentazionefotografica->idfoto = atoi(buff); 
	if(do_select_picture(documentazionefotografica) > 0) {
		printf("*Foto:		%s \n Descrizione:	%s  \n\n",
			documentazionefotografica->foto,
			documentazionefotografica->descrzione);
	}
	else {
		printf("L'id inserito non esiste\n\n"); 
		return -1; 
	}
	return 0; 
}


int show_map(struct mappa *mappa){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli mappa  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	mappa->idmappa = atoi(buff); 
	if(do_select_map(mappa) > 0) {
		printf("*Città:		%s \n Regione:	%s \n Dettaglio:	%s \n Zona:		%s \n Immagine: 	%s \n\n",
			mappa->citta,
			mappa->localitarappresentata,
			mappa->dettaglio, 
			mappa->zona,
			mappa->immagine);
	}
	else {
		printf("L'id inserito non esiste \n\n"); 
		return -1; 
	}
	return 0; 

}

int show_room(struct camera *camera){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli camera  **\n\n");
	get_input("Inserisci il numero d'interesse:",NUM_LEN, buff, false); 
	camera->numerocamera = atoi(buff); 
	get_input("Inserisci l'id dell'albergo d'interesse:",NUM_LEN, buff, false); 
	camera->albergo = atoi(buff);
	if(do_select_room(camera) >0) {
		printf("*Tipologia:	%s \n Costo:		%f\n\n",
			camera->tipologia,
			camera->costo);
	}
	else {
		printf("La camera d'interesse non esiste \n\n"); 
		return -1; 
	}
	return 0; 

}

int show_location(struct localita *localita){


	printf("\n\n** Dettagli localita  **\n\n");
	get_input("Inserisci il nome d'interesse: ",VARCHAR_LEN, localita->nomelocalita, false); 
	get_input("Inserisci il nome della regione: ", VARCHAR_LEN, localita->regione, false);
	if (do_select_location(localita) > 0){
		printf("*Stato:		%s\n\n",
			localita->stato);
	}
	else {
		printf("Il nome d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

int show_visit(struct visita *visita){
	char buff[NUM_LEN];
	printf("\n\n** Dettagli visita  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	visita->idvisita= atoi(buff); 
	if(do_select_visit(visita) > 0){
		printf("*Tour:		%s  Id viaggio:	%d*\n*Nome meta:	%s Id meta:	%d*\n Data di arrivo:	%s\n Ora di arrivo:		%s\n Data di partenza:	%s\n Ora di partenza:	%s\n Guida:			%d\n Supplemento:		%f\n Trattamento:		%s\n\n",
			visita->tour,
			visita->viaggiorelativo,
			visita->meta,
			visita->metavisitata,
			visita->datadiarrivo,
			visita->oradiarrivo,
			visita->datadipartenza,
			visita->oradipartenza, 
			visita->guida,
			visita->supplemento,
			visita->trattamentoalberghiero);
	}
	else {
		printf("L'id d'interesse non esiste\n\n"); 
		return -1; 
	}
	return 0; 

}

 int show_sostitution(struct sostituito *sostituito){
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli sostituzione  **\n\n");
	get_input("Inserisci l'id della revisione d'interesse:",NUM_LEN, buff, false); 
	sostituito->revisioneassociata = atoi(buff); 
	get_input("Inserisci il codice del ricambio d'interesse:",VARCHAR_LEN, sostituito->ricambioutilizzato,  false);

	if(do_select_sostitution(sostituito) > 0) {
 		printf("*Quantità:	%d\n\n",
			sostituito->quantitasostituita); 
	}
	else {
		printf("La sostizione d'interesse non esiste\n\n"); 
			return -1; 
	}
	return 0; 
 }


void show_expired_review (void) 
{	
	printf("** Ecco i mezzi le cui revisioni risultano scadute o in scadenza**\n\n");
	get_info_revisioni();
}


void show_tour_information(void)
{	
	printf("\n\n** Tour offerti  **\n\n"); 
	get_tour_info(); 
}

void show_tour_destination(void)
{
	char buff[VARCHAR_LEN]; 
	int idv; 
	printf("\n\n ** Esplora le destinazioni dei viaggi **\n\n"); 
	get_input("Inserisca il numero del viaggio a cui è interessato: ",VARCHAR_LEN, buff, false);  
	printf("\n**\n**\n"); 
	idv = atoi(buff); 
	get_mete_info(idv); 
}


void show_service_destination(void)
{	
	char buff[VARCHAR_LEN]; 
	int idh; 
	printf("\n\n ** Esplora i servizi offerti dagli alberghi **\n\n"); 
	get_input("Inserisca il codice dell'albergo a cui è interessato: ",VARCHAR_LEN, buff, false);  
	printf("\n**\n**\n"); 
	idh = atoi(buff); 
	get_servizi_albergo(idh); 
}


void show_comfort_model(void)
{	
	char buff[VARCHAR_LEN]; 
	
	printf("\n\n ** Esplora comfort presenti sui nostri pullman  **\n\n"); 
	get_input("Inserisca il nome del modello a cui è interessato: ",VARCHAR_LEN, buff, false);  
	printf("\n**\n**\n");  
	get_info_modello(buff); 
}


void show_assigned_trip(void)
{	
	char buff[VARCHAR_LEN];

	printf("** Ricerca viaggi assegnati **\n\n");
	get_input("Inserisci la mail del conducente:", VARCHAR_LEN,buff, false);
	printf("** Dettagli del viaggio assegnato **\n\n");
	get_viaggi_assegnati(buff); 
}

void show_dest_time(void)
{	
	char buff[NUM_LEN];
	int dvr; 

	printf("** Ricerca visite d'interesse **\n\n");
	get_input("Inserisci l'ID del viaggio:", VARCHAR_LEN, buff, false);
	dvr = atoi(buff); 
	printf("** Dettagli temporali delle visite **\n\n");
	get_mete_visite(dvr); 
}

void show_drvr_map(void)
{
	char buff[VARCHAR_LEN];
	printf("** Ricerca la mappa d'interesse **\n\n");
	get_input("Inserisci il nome della località:", VARCHAR_LEN, buff, false);
	printf("** Dettagli mappe relative alla località inserita **\n\n");
	get_mappe(buff); 
}

#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../utils/io.h"
#include "../utils/validation.h"

#include "../model/trpdb.h"

extern int show_reservation (struct prenotazione * prenotazione);
extern int show_trip(struct viaggio *viaggio); 
extern int show_costumer (struct cliente * cliente); 
extern int show_tour(struct tour *tour); 
extern int show_service(struct servizio * servizio); 
extern int show_sparepart(struct ricambio *ricambio);
extern int show_review(struct revisione *revisione); 
extern int show_bus(struct mezzo *mezzo); 
extern int show_stay(struct soggiorno *soggiorno); 
extern int show_skills(struct competenze *competenze);
extern int show_employee(struct dipendente *dipendente); 
extern int show_fmo(struct fmo *fmo); 
extern int show_fme(struct fme *fme); 
extern int show_ofr(struct offre *offre);
extern int show_user(struct utente *utente); 
extern int show_seat(struct postoprenotato *postoprenotato); 
extern int show_model(struct modello *modello); 
extern int show_certify(struct tagliando *tagliando); 
extern int show_destination(struct meta *meta); 
extern int show_visit(struct visita *visita); 
extern int show_location(struct localita *localita); 
extern int show_room(struct camera *camera); 
extern int show_map(struct mappa *mappa); 
extern int show_picture(struct documentazionefotografica *documentazionefotografica); 
extern int show_comfort(struct comfort *comfort); 
extern int show_service(struct servizio *servizio); 
extern void show_expired_review (void); 
extern int show_prenotation_details(struct prenotazione *prenotazione ); 
extern int show_sostitution(struct sostituito *sostituito); 
extern int show_presents(struct presenti *presenti); 
extern int show_rt(struct rt *rt); 
extern void show_tour_information(void);
extern void show_tour_destination(void);
extern void show_service_destination(void); 
extern void show_comfort_model(void); 
extern void show_assigned_trip(void); 
extern void show_dest_time(void); 
extern void show_drvr_map(void); 
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

			#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "../utils/validation.h"
#include "../model/trpdb.h"

extern void update_user_type( struct utente *utente, int type); 
extern void update_km(struct mezzo *mezzo); 

