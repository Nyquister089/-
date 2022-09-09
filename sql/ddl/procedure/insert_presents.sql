create procedure if not exists `tripdb`.`insert_presents`(
    in cmf int,
    in mdl varchar (45)
)
begin
insert into presenti (
    ComfortPresenti, 
    ModelloAssociato
)
values (
    cmf, 
    mdl
); 
end