create procedure if not exists `tripdb`.`delete_rt`(
    in rvs int,
    in tgl int
)
begin
delete
from rt
where TagliandoAssociato = rvs and RevisioneRelativa = tgl; 
end