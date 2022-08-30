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

void ins_user_costumer(struct utente *utente){
	printf("** Dettagli inserimento utente **\n\n");
	get_input("Inserisci la mail: ", VARCHAR_LEN, utente->email, false);
	get_input("Inserisci la password: ", VARCHAR_LEN, utente->pswrd, false);
	utente->tipo = 2;
	do_insert_user(utente); 
}

void ins_prenotation(struct prenotazione *prenotazione)
{	
	
	printf("\n** Dettagli inserimento prenotazione **\n\n");
	get_input("Inserisci l'indirizzo e-mail del cliente che ha effettuato la prenotazione : ", VARCHAR_LEN, prenotazione->clienteprenotante, false);
	while(true){
		get_input("Inserisci data [YYYY-MM-DD]: ", DATE_LEN, prenotazione->datadiprenotazione, false);
		if(validate_date(prenotazione->datadiprenotazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}

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
	get_input("Inserisci l'ID del viaggio a cui partecipera' il passeggero: ", NUM_LEN, buff, false);
	postoprenotato->viaggioassociato = atoi(buff); 
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
	get_input("Inserisci la tipologia(ordinaria o straordinaria) : ", VARCHAR_LEN, revisione-> tipologiarevisione, false);
	if(strcmp(revisione->tipologiarevisione,"straordinaria") == 0)
		get_input("Inserisci la motivazione della revisione straordinaria (massimo 5000 caratteri) : ", DES_LEN, revisione-> motivazione, false);
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
do_insert_review(revisione);


ans = yes_or_no("In questa revisione sono statti sostituiti dei ricambi? ",'s','n',false, false); 
if(ans)
	{	do_select_max_idreview(revisione); 
		sostituito->revisioneassociata = revisione->idrevisione; 
		
		ins_sostitution(sostituito); 
	}

}

void ins_costumer(struct cliente *cliente, struct utente *utente)
{	
	char buff[VARCHAR_LEN]; 
	printf("** Crea un utente per questo cliente **\n"); 
	ins_user_costumer(utente); 
	strcpy(cliente->emailcliente, utente->email); 
	printf("\nEmail: %s \n\n",cliente->emailcliente ); 
	
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
	do_insert_costumer(cliente); 
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

void ins_model(struct modello *modello)
{	
	char buff[VARCHAR_LEN];
	printf("\n** Dettagli inserimento modello **\n\n");
	get_input("Inserisci il nome : ", DEC_LEN, modello->nomemodello, false);
	get_input("Inserisci la casa costruttrice : ", NUM_LEN, modello->casacostruttrice, false);
	get_input("Inserisci i dati tecnici (massimo 5000 caratteri) : ", DES_LEN, modello-> datitecnici, false);
	get_input("Inserisci il numero di posti: ", NUM_LEN, buff, false);
	modello->numeroposti = atoi(buff);
	do_insert_model(modello); 
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
	printf("\n** Dettagli associazione camera**\n\n");
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
	do_insert_stay(soggiorno); 
}

void ins_sostitution( struct sostituito *sostituito)
{	
	char buff[NUM_LEN]; 
	int num; 
	printf("\n** Dettagli sostituzione ricambio**\n\n");
	if(&sostituito->revisioneassociata == NULL){
		get_input("Inserisci il numero della revsione in questione: ",NUM_LEN, buff, false);
		sostituito->revisioneassociata = atoi(buff);
	} 
	get_input("Inserisci il codice del ricambio utilizzato : ", NUM_LEN, sostituito->ricambioutilizzato,false);
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
	get_input("Inserisci il nome della località in cui è ubicata la citta' rappresentata: ", VARCHAR_LEN, mappa->localitarappresentata, false);
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

void ins_tome(struct tome *tome)
{	
	char buff[NUM_LEN]; 
	printf("** Dettagli inserimento tome **\n\n");
	get_input("Inserisci il nome del tour in questione: ", VARCHAR_LEN, tome->tourinquestione, false);
	get_input("Inserisci l'id della meta in questione: ", NUM_LEN, buff, false);
	tome->metainquestione = atoi(buff); 
	do_insert_tome(tome); 
}

void ins_comfort(struct comfort *comfort)
{	
	printf("** Dettagli inserimento comfort **\n\n");
	get_input("Inserisci il nome : ", VARCHAR_LEN, comfort->nomecomfort, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, comfort->descrizionecomfort, false);
	do_insert_comfort(comfort); 
}

void ins_skills(struct competenze *competenze)
{	
	printf("** Dettagli inserimento competenze **\n\n");
	get_input("Inserisci il nome del modello associato: ", VARCHAR_LEN, competenze->modelloassociato, false);
	get_input("Inserisci la mail del meccanico competente : ", VARCHAR_LEN, competenze->meccanicocompetente, false);
	do_insert_skills(competenze); 
}

void ins_employee(struct dipendente *dipendente, struct utente *utente, struct competenze *competenze) 
{	
	printf("** Crea un utente per questo dipendente **\n\n");
	do{
		ins_user(utente); 
		if(utente->tipo == 2)
			 update_user_type(utente, utente->tipo); 
	}while (utente->tipo == 2); 

	strcpy(dipendente->emaildipendente, utente->email); 
	switch (utente->tipo)
	{
	case 1:
		strcpy(dipendente->tipologiadipendente, "Autista"); 
		break;
	case 3: 
		strcpy(dipendente->tipologiadipendente, "Hostess"); 
		break; 
	case 4: 
		strcpy(dipendente->tipologiadipendente, "Meccanico"); 
		break; 
	case 5: 
		strcpy(dipendente->tipologiadipendente, "Manager"); 
		break; 
	default:
		break;
	}
	printf("** Dettagli inserimento dipendente **\n\n");
	get_input("Inserisci il nome: ", VARCHAR_LEN, dipendente->nomedipendente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, dipendente->cognomedipendente, false);
	get_input("Inserisci il numero di telefono aziendale: ", TEL_LEN ,dipendente->telefonoaziendale, false);
	do_insert_employee(dipendente);
	if (utente->tipo == 4)
		{
		printf("Ogni Meccanico richiede l'iserimento di almeno 2 competenze"); 
		strcpy(competenze->meccanicocompetente, dipendente->emaildipendente); 
		bool ans = false; 
		int i;
		i = 0; 
		while(ans){
			
			ins_skills(competenze); 
			i++; 
			if ( i == 2)
				ans = yes_or_no("Vuoi inserire un altra competenza ? ", 's', 'n', false, false); 
			}
		}
}

void validate_reservation(struct prenotazione *prenotazione , struct postoprenotato *postoprenotato, struct soggiorno *soggiorno)
{
	char buff[NUM_LEN]; 
	printf("** Procedura conferma prenotazione **\n\n"); 
	show_reservation(prenotazione ); 

 	bool ans = yes_or_no("\n\n Vuoi confermare questa prenotazione? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
		}

	while(true){
		get_input("\nModifica data di conferma [YYYY-MM-DD]: ", DATE_LEN, prenotazione ->datadiconferma, false);
		if(validate_date(prenotazione ->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
		}

	while(true){
		get_input("\nModifica data di saldo [YYYY-MM-DD]: ", DATE_LEN, prenotazione ->datasaldo, false);
		if(validate_date(prenotazione ->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
		}
		do_validate_reservation(prenotazione );
		bool seat_ans, association_ans;   

	do {
		printf("\n\n** Associa un passeggero alla prenotazione ** \n\n"); 

		postoprenotato ->prenotazioneassociata = prenotazione ->numerodiprenotazione; 
		printf(" Numero di prenotazione hostess %d \n", postoprenotato ->prenotazioneassociata);

		get_input("Inserisci il numero di posto: ", NUM_LEN, buff, false);
		postoprenotato->numerodiposto = atoi(buff); 
		get_input("Inserisci l'ID del viaggio a cui partecipera' il passeggero: ", NUM_LEN, buff, false);
		postoprenotato->viaggioassociato = atoi(buff); 
		get_input("Inserisci l'età: ", NUM_LEN, buff, false);
		postoprenotato->etapasseggero = atoi(buff); 
		get_input("Inserisci il nome: ", VARCHAR_LEN, postoprenotato-> nomepasseggero, false);
		get_input("Inserisci il cognome: ", VARCHAR_LEN, postoprenotato-> cognomepasseggero, false);

	do_insert_seat(postoprenotato);

		ans = yes_or_no("\n\n Vuoi associare una camera a questo passeggero? (s/n) ",'s','n',false,false);
		if (ans)
			do{	printf("** Associa camera al passeggero ** ");
			 	soggiorno ->ospite = postoprenotato ->numerodiposto; 
				ins_stay(soggiorno); 
				association_ans= yes_or_no("\n\n Vuoi associare un'altra camera a questo passeggero? (s/n) ",'s','n',false,false);
			}while(association_ans);
		seat_ans =yes_or_no("\n\n Vuoi associare un'altro passeggero a questa prenotazione ? (s/n) ",'s','n',false,false);
	} while(seat_ans); 

}