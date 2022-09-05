#include <string.h>
#include "../model/trpdb.h"
#include "show.h" 

void show_reservation (struct prenotazione * prenotazione)
{	
	char buff[NUM_LEN];
	printf("\n\n**  Dettagli prenotazione ** \n\n"); 
	get_input("Inserisci numero d'interesse : ", NUM_LEN , buff, false); 
	prenotazione->numerodiprenotazione = atoi(buff); 
    if(do_select_reservation(prenotazione)>0) {
		printf("\n\n** Dettagli prenotazione **\n\n");
 		printf(" Prenotazione numero: 	%d \n E-mail cliente: 	%s \n Data di prenotazione: 	%s \n Data di conferma: 	%s \n Data Saldo: 		%s \n\n",
			prenotazione->numerodiprenotazione, 
			prenotazione->clienteprenotante,
			prenotazione->datadiprenotazione, 
			prenotazione->datadiconferma, 
			prenotazione->datasaldo);
			free(prenotazione); }
	else 
		printf("Il numero di prenotazione non esiste\n\n"); 
	
	

}

void show_trip(struct viaggio *viaggio)
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
		free(viaggio); }
	else
		 printf("L'id inserito non esiste\n\n"); 
}

void show_costumer (struct cliente * cliente)
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
		free(cliente); }
	else 
		printf("La mail inserita non esiste\n\n"); 
}

void show_tour(struct tour *tour)
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
		free(tour);}
	else 
		printf("La denominazione inserita non esiste\n\n"); 

}



void show_sparepart(struct ricambio *ricambio)
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
		free(ricambio); }
	else
		printf("Il codice inserito non esisten\n\n"); 
}

void show_review (struct revisione *revisione){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli revisione **\n\n");
	get_input("Inserisci l'id d'interesse: ", NUM_LEN, buff, false); 
	revisione->idrevisione = atoi(buff);
	if(do_select_review(revisione) > 0){
 		printf("*Mezzo revsionato:	%s \n Id adetto: 		%s \n Data inizio: 		%s \n Data fine: 		%s\n Chilometraggio:	%d\n Operazioni eseguite:	%s \n Tipologia revsione:	%s \n Motivazione:	%s \n\n",
			revisione->mezzorevisionato,
			revisione->addettoallarevisione,
			revisione->datainizio,
			revisione->datafine,
			revisione->chilometraggio,
			revisione->operazionieseguite,
			revisione->tipologiarevisione,
			revisione->motivazione);
		free(revisione); }
	else 
		printf("L'id inserito non esiste\n\n"); 

}

void show_bus(struct mezzo *mezzo)
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
		free(mezzo); }
	else 
		printf("La targa insertia non esiste\n\n"); 

}

void show_stay(struct soggiorno *soggiorno)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli soggiorno **\n\n");
	get_input("Inserisci il codice dell'albergo:",NUM_LEN, buff, false); 
	soggiorno->albergoinquestione = atoi(buff); 
	get_input("Inserisci il codice della camera :",NUM_LEN, buff, false);
	soggiorno->cameraprenotata = atoi(buff); 
	get_input("Inserisci il numero dell'ospite :",NUM_LEN, buff, false);
	soggiorno->ospite = atoi(buff); 
	if(do_select_stay(soggiorno) > 0){
 		printf("*Data inizio soggiorno:%s \n Data fine soggiorno:	%s \n\n",
			soggiorno->datainiziosoggiorno,
			soggiorno->datafinesoggiorno); 
			free(soggiorno); }
	else 
		printf("Il soggiorno richiesto non esiste\n\n"); 

}

void show_skills(struct competenze *competenze)
{	
	printf("\n\n** Dettagli competenze  **\n\n");
	get_input("Inserisci la mail del meccanico competente :",VARCHAR_LEN, competenze->meccanicocompetente, false); 
	get_input("Inserisci il modello d'interesse :",VARCHAR_LEN, competenze->modelloassociato, false);
	
	if(do_select_skills(competenze) > 0){
 		printf("*Nome meccanico:%s \n Telefono :	%s \n\n",
			competenze->nomemeccanico,
			competenze->telefono);
			free (competenze);}
	else 
		printf("La competenza richiesta non esiste\n\n"); 
}

void show_employee(struct dipendente *dipendente)
{	
	printf("\n\n** Dettagli Dipendente  **\n\n");
	get_input("Inserisci la mail d'interesse:",VARCHAR_LEN,dipendente->emaildipendente, false); 
	if(do_select_employee(dipendente) > 0){
 		printf("*Nome:		%s \n Cognome:	%s \n Tipologia:	%s \n Telefono:	%s \n\n",
			dipendente->nomedipendente,
			dipendente->cognomedipendente,
			dipendente->tipologiadipendente,
			dipendente->telefonoaziendale); 
		if (strcmp(dipendente->tipologiadipendente,"Meccanico") || strcmp(dipendente->tipologiadipendente,"Meccanico") == 0 )
			printf("Numero competenze:	%d \n", dipendente->numerocompetenze); 
			free(dipendente); }
	else 
		printf("La mail d'interesse non esiste\n\n"); 
}


void show_fmo(struct fmo *fmo)
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
		free(fmo); }
	else
		printf("La relazione foto-modello d'interesse non esiste\n\n"); 
}

void show_fme(struct fme *fme)
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
		free(fme); }
	else 
		printf("La relazione foto-mete d'interesse non esiste\n\n"); 
}

void show_ofr(struct offre *offre)
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
		free(offre); }
	else 
		printf("La realzione offre d'interesse non esiste\n\n"); 
}

void show_tome(struct tome *tome)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli tour-meta  **\n\n");
	get_input("Inserisci il nome del tour d'interesse:",VARCHAR_LEN, tome->tourinquestione, false); 
	get_input("Inserisci l'id della meta d'interesse:",NUM_LEN, buff, false);
	tome->metainquestione = atoi(buff); 
	if(do_select_tome(tome) > 0){
 		printf("*Descrizione tour:	%s\n Meta:		%s\n\n",
			tome->descrizione,
			tome->meta); 
		free(tome);}
	else
		printf("La relazione tour-mete d'interesse non esiste\n\n"); 
}


void show_user(struct utente *utente){

	printf("\n\n** Dettagli utente **\n\n");
	get_input("Inserisci l'id dell'utente d'interesse:", NUM_LEN, utente->email, false);
	if(do_select_user(utente) > 0){
 		printf("*Password:	%s \n Tipo:		%d\n\n",
			utente->pswrd,
			utente->tipo); 
		free(utente); }
	else 
		printf("L'id inserito non esiste\n\n"); 
}

void show_seat(struct postoprenotato *postoprenotato){

	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli posto prenotato  **\n\n");
	get_input("Inserisci il numero di posto d'interesse:",NUM_LEN, buff, false); 
	postoprenotato->numerodiposto = atoi(buff); 
	get_input("Inserisci l'id del viaggio d'interesse:",NUM_LEN, buff, false);
	postoprenotato->viaggioassociato = atoi(buff); 
	if(do_select_seat(postoprenotato) > 0){
 		printf("*Nome passeggero:	%s\n Cognome passeggero:	%s \n Età:			%d \n Numero di prenotazione:%d\n\n",
			postoprenotato->nomepasseggero,
			postoprenotato->cognomepasseggero,
			postoprenotato->etapasseggero,
			postoprenotato->prenotazioneassociata);
		free(postoprenotato); }
	else
		printf("Il posto prenotato d'interesse non esiste\n\n"); 

}

void show_model(struct modello *modello){
	
	printf("\n\n** Dettagli modello  **\n\n");
	get_input("Inserisci il nome d'interesse:",VARCHAR_LEN, modello->nomemodello, false); 
	if(do_select_model(modello) > 0){
 		printf("* Casa costruttrice:	%s\n Dati tecnici:		%s \n Numero di posti:	%d\n\n",
			modello->casacostruttrice,
			modello->datitecnici,
			modello->numeroposti);
		free(modello); }
	else 
		printf("Il nome del modello inserito non esiste\n\n"); 
}

void show_certify(struct tagliando *tagliando){
	
	char buff[NUM_LEN];
	printf("\n\n** Dettagli tagliando  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	tagliando->idtagliando= atoi(buff); 
	if(do_select_certify(tagliando) > 0){
 		printf("*Tipologia:		%s\n Validità superate:	%s \n\n",
			tagliando->tipologiatagliando,
			tagliando->validitasuperate);
		free(tagliando); }
	else
		printf("L'id inserito non esiste\n\n"); 
}

void show_destination(struct meta *meta){

	char buff[NUM_LEN];
	printf("\n\n** Dettagli meta  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	meta->idmeta= atoi(buff); 
	if(do_select_destination(meta) > 0){
		printf("*Nome:		%s\n Tipologia:	%s\n Località:	%s\n Indirizzo:	%s\n Telefono:	%s\n E-mail:	%s\n Fax:		%s\n",
			meta->nomemeta,
			meta->tipologiameta,
			meta->localitadiappartenenza,
			meta->indirizzo,
			meta->telefonometa,
			meta->emailmeta,
			meta->faxmeta); 
		if(strcmp((meta->tipologiameta), "Albergo")||strcmp((meta->tipologiameta),"albergo" )== 0)
			printf(" Categoria:	%s\n\n", meta->categoriaalbergo); 
		else
			printf(" Orario di apertura:%s\n\n", meta->orariodiapertura); 
		free(meta);}
	else 
		printf("L'id inserito non esiste\n\n"); 

}

void show_service (struct servizio  *servizio ){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli servizio   **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	servizio ->idservizio  = atoi(buff); 
	if(do_select_service (servizio ) > 0){
		printf("*Nome:		%s \n Descrizione:	%s  \n\n",
			servizio->nomeservizio ,
			servizio->descrizioneservizio);
			free(servizio);}
	else
		printf("L'id inserito non esiste\n\n");
}

void show_comfort(struct comfort *comfort){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli comfort  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	comfort->idcomfort = atoi(buff); 
	if(do_select_comfort(comfort) > 0){
		printf("*Nome:		%s \n Descrizione:	%s  \n\n",
			comfort->nomecomfort,
			comfort->descrizionecomfort);
		free(comfort); }
	else	
		printf("L'id inserito non esiste\n\n"); 
}


void show_picture(struct documentazionefotografica *documentazionefotografica){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli documentazionefotografica  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	documentazionefotografica->idfoto = atoi(buff); 
	if(do_select_picture(documentazionefotografica) > 0) {
		printf("*Foto:		%s \n Descrizione:	%s  \n\n",
			documentazionefotografica->foto,
			documentazionefotografica->descrzione);
		free(documentazionefotografica); }
	else
		printf("L'id inserito non esiste\n\n"); 
}


void show_map(struct mappa *mappa){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli mappa  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	mappa->idmappa = atoi(buff); 
	if(do_select_map(mappa) > 0) {
		printf("*Città:		%s \n Località:	%s \n Dettaglio:	%s \n Zona:		%s \n Immagine: 	%s \n\n",
			mappa->citta,
			mappa->localitarappresentata,
			mappa->dettaglio, 
			mappa->zona,
			mappa->immagine);
			free(mappa); }
	else
		printf("L'id inserito non esiste \n\n"); 

}

void show_room(struct camera *camera){

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
		free(camera); }
	else
		printf("La camera d'interesse non esiste \n\n"); 

}

void show_location(struct localita *localita){


	printf("\n\n** Dettagli localita  **\n\n");
	get_input("Inserisci il nome d'interesse: ",VARCHAR_LEN, localita->nomelocalita, false); 
	get_input("Inserisci il nome della regione: ", VARCHAR_LEN, localita->regione, false);
	if (do_select_location(localita) > 0){
		printf("*Stato:		%s\n\n",
			localita->stato);
		free(localita); }
	else
		printf("Il nome d'interesse non esiste\n\n"); 

}

void show_visit(struct visita *visita){
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
		free(visita); }
	else
		printf("L'id d'interesse non esiste\n\n"); 

}

 void show_sostitution(struct sostituito *sostituito){
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli sostituzione  **\n\n");
	get_input("Inserisci l'id della revisione d'interesse:",NUM_LEN, buff, false); 
	sostituito->revisioneassociata = atoi(buff); 
	get_input("Inserisci il codice del ricambio d'interesse:",VARCHAR_LEN, sostituito->ricambioutilizzato,  false);

	if(do_select_sostitution(sostituito) > 0) {
 		printf("*Quantità:	%d\n\n",
			sostituito->quantitasostituita); 
		free(sostituito); }
	else
		printf("La sostizione d'interesse non esiste\n\n"); 
 }


void show_expired_review (void) 
{	
	printf("** Ecco i mezzi le cui revisioni risultano scadute o in scadenza**\n\n");
	get_info_revisioni();
}


