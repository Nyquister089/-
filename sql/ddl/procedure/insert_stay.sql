CREATE PROCEDURE if not exists `tripdb`.`insert_stay`(
in cam int, 
in osp int, 
in alb int, 
in prn int, 
in dis date,
in dfs date
 )
BEGIN
insert into soggiorno 
			(CameraPrenotata, 
			 Ospite, 
             AlbergoInQuestione,
             PrenotazioneInQuestione,
             DataInizioSoggiorno, 
             DataFineSoggiorno)
values
			(cam,
             osp,
             alb,
             prn, 
             dis,
             dfs); 
END