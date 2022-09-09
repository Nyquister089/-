create procedure if not exists `tripdb`.`select_rt`(
    in rvs int,
    in tgl int
)
begin
select 
     RevisioneRelativa, 
     TagliandoAssociato
from rt
where RevisioneRelativa = rvs and TagliandoAssociato = tgl; 
end