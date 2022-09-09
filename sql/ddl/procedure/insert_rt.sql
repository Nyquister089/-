create procedure if not exists `tripdb`.`insert_rt`(
    in rvs int,
    in tgl int
)
begin
insert into rt (
    RevisioneRelativa, 
    TagliandoAssociato
)
values (
    rvs, 
    tgl
); 
end