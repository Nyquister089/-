create trigger `tripdb`.`update_km_after_review` after insert 
on `revisione`
for each row 
update mezzo
join revisione 
set ValoreContaKm = NEW.Chilometraggio
where targa = NEW.MezzoRevisionato; 