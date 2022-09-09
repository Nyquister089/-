create procedure if not exists `tripdb`.`select_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
select
    ComfortPresenti, 
    ModelloAssociato
from presnti 
where ComfortPresenti = cmf and ModelloAssociato = mdl; 
end