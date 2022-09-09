#include <string.h>
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

void dlt_tome(struct tome *tome)
{		
	if(show_tome(tome)!=-1)
	 if(yes_or_no("Vuoi cancellare questa associazione tour-mete? (s/n)",'s','n',false,false) == true)
        do_delete_tome(tome); 
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

}