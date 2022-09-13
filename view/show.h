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
