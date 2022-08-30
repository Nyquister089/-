create procedure if not exists `tripdb`.`select_max_idreview`(

 )
BEGIN
select max(IdRevisione)
from revisione; 
END