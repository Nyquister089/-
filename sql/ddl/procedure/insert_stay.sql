CREATE PROCEDURE if not exists `tripdb`.`insert_stay`(
in cam int, 
in osp int, 
in alb int, 
in vgg int, 
in dis date,
in dfs date
 )
BEGIN
insert into soggiorno 
			(CameraPrenotata, 
			 Ospite, 
             AlbergoInQuestione,
             ViaggioInQuestione,
             DataInizioSoggiorno, 
             DataFineSoggiorno)
values
			(cam,
             osp,
             alb,
             vgg, 
             dis,
             dfs); 
END