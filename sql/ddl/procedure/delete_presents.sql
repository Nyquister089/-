create procedure if not exists `tripdb`.`delete_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
delete
from presenti
where ModelloAssociato = mdl and ComfortPresenti =cmf; 
end