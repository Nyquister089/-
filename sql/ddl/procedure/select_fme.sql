create procedure if not exists `tripdb`.`select_fme`
(   
    in fmt int,
    in mtr int
)
begin
select 
m.NomeMeta,
d.DescrizioneFoto,
d.Immagine

from fme as f
join meta as m on f.MetaRappresentata = m.IdMeta
join documentazionefotografica as d on f.FotoMeta = d.idDocumentazioneFotografica
where f.MetaRappresentata = mtr and f.FotoMeta = fmt; 
end
