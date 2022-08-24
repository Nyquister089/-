DELETE FROM `tripdb`.`dipendente`;
INSERT INTO `tripdb`.`dipendente` ( 
 `TipologiaDipendente`,
 `TelefonoAziendale`,
 `NomeDipendente`, 
 `CognomeDipendente`,
 `EmailDipendente`) 
 VALUES(
'autista',
'1234', 
'Mario', 
'Rossi',
'drvr@mail.com');
INSERT INTO `tripdb`.`dipendente` ( 
`TipologiaDipendente`, 
`TelefonoAziendale`, 
`NomeDipendente`, 
`CognomeDipendente`,
`EmailDipendente`) 
VALUES ( 
    'hostess', 
    '4453', 
    'Anna', 
    'Bianchi',
    'hstss@mail.com');
INSERT INTO `tripdb`.`dipendente` ( 
    `TipologiaDipendente`, 
    `TelefonoAziendale`, 
    `NomeDipendente`, 
    `CognomeDipendente`,
    `EmailDipendente`)
     VALUES ( 
        'meccanico', 
        '7801', 
        'Paolo','Verdi',
        'mch@mail.com');
