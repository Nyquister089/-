CREATE TABLE IF NOT EXISTS `tripdb`.`utente` (
  `EmailUtente` varchar(45) NOT NULL,
  `Pswrd` varchar(8) NOT NULL,
  `TipoUtente` int unsigned NOT NULL,
  PRIMARY KEY (`EmailUtente`),
  UNIQUE KEY `EmailUtente_UNIQUE` (`EmailUtente`), 
  CONSTRAINT `TipoUtenteNotvalid` CHECK (`TipoUtente` IN ('1','2','3','4','5') )
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
