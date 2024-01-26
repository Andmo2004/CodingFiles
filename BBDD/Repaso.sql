//EJERCICIOS
//1
select nombrecompleto
from votantes
where nombrecompleto like '%n';
//2
select dni
from votantes
where dni like '%5%5%5%';
//3
select nombrecompleto
from votantes 
where fechanacimiento > '01/01/1990';
//4
select v.nombrecompleto, l.nombre
from votantes v, localidades l
where v.localidad = l.idlocalidad 
    and l.numerohabitantes > 300000;
//5
select v.nombrecompleto, p.comunidad
from votantes v, localidades l, provincias p
where v.localidad = l.idlocalidad
    and p.idprovincia = l.provincia
    and l.numerohabitantes > 300000;
//6
select p.idpartido, count(cd.partido)"conteo"
from partidos p, consultas_datos cd
where p.idpartido = cd.partido
group by p.idpartido;
//8
select p.nombrecompleto
from partidos p, consultas_datos cd
where p.idpartido = cd.partido
group by p.nombrecompleto
having count(cd.partido)>10;
//9
select p.nombrecompleto, count(cd.partido)"Conteo"
from partidos p, consultas_datos cd
where p.idpartido = cd.partido
group by p.nombrecompleto
having count(cd.partido)>10
order by p.nombrecompleto;
//10
select p.nombrecompleto, count(c.partido)"conteo"
from partidos p, consultas_datos c
where p.idpartido = c.partido
    and c.respuesta = 'Si'
    and c.certidumbre > 0.8
group by p.nombrecompleto;
//11
select dni, telefono
from votantes 
where telefono like '%6%6%'
    and telefono not like '%6%6%6%';
//12
select dni, telefono
from votantes 
where telefono like '%66%6%'
    and telefono like '%6%66%'
    and telefono not like '%6%6%6%6%';
//13
select l.nombre, p.nombre
from localidades l, provincias p
where l.provincia = p.idprovincia
    and (l.numerohabitantes - p.idprovincia )like '%0'; 
//14
select nombrecompleto 
from votantes 
where (telefono - dni ) like '%0';
//15
select nombrecompleto
from votantes
where nombrecompleto like '%s%'
    and fechanacimiento < '12/02/1990';
//16
select distinct c.votante
from votantes v, consultas c
where v.dni = c.votante
order by v.dni desc;
//17
select v.nombrecompleto
from votantes v, consultas c
where v.dni = c.votante
group by v.nombrecompleto
having count(c.votante)>3
order by v.nombrecompleto;
//18
select v.nombrecompleto, l.nombre
from votantes v, localidades l, consultas c
where v.dni = c.votante
    and v.localidad = l.idlocalidad
    and l.numerohabitantes > 300000;
//19
select p.nombrecompleto, max(cd.certidumbre)"max_certidumbre"
from partidos p, consultas_datos cd
where p.idpartido = cd.partido
group by p.nombrecompleto;
//20
select v.nombrecompleto, avg(cd.certidumbre)"media"
from votantes v, consultas c, consultas_datos cd
where v.dni = c.votante
    and c.idconsulta = cd.consulta
    and cd.respuesta = 'Si'
group by v.nombrecompleto;
//21
select v.nombrecompleto, avg(cd.certidumbre)"media"
from votantes v, consultas c, consultas_datos cd
where v.dni = c.votante
    and c.idconsulta = cd.consulta
    and cd.respuesta = 'Si'
group by v.nombrecompleto
having avg(cd.certidumbre)<0.8
    and avg(cd.certidumbre)>0.5;
//22
select p.nombrecompleto, avg(cd.certidumbre)
from partidos p, consultas_datos cd
where p.idpartido = cd.partido
    and cd.respuesta = 'No'
group by p.nombrecompleto
having avg(cd.certidumbre)>0.6;
//23
select nombrecompleto
from votantes
where (dni - (localidad+1) ) like '%0';
//where dni like '%'||(localidad +1);
//24
select v.nombrecompleto, decode(l.idlocalidad,1,'Madrid',2,'Madrid',3,'Madrid',l.nombre)nombre
from votantes v, localidades l
where v.localidad = l.idlocalidad
order by l.nombre desc;
//25
select p.siglas
from partidos p, eventos_resultados e
where p.idpartido = e.partido
group by p.siglas
having count(e.partido)=(select max(count(partido))
from eventos_resultados
group by partido);
//26
select v.dni
from votantes v
where v.fechanacimiento = (select min(fechanacimiento)
    from votantes 
    where fechanacimiento > (select min(fechanacimiento)
        from votantes));
//27
select v.dni, count(c.votante)"participaciones"
from votantes v, consultas c
where v.dni = c.votante
group by v.dni
order by count(c.votante) desc;
//28
select c.votante, count(c.votante)"participacion"
from consultas c
group by c.votante
having count(c.votante) > (select avg(count(votante))
    from consultas
    group by votante)
order by count(c.votante) desc;
//29
select nombrecompleto
    from votantes, consultas
    where dni = votante
    group by nombrecompleto
    having count(votante) > (select avg(count(votante))
        from consultas 
        group by votante);
        
//30
select c.votante, count(c.votante)"participacion"
from consultas c, votantes v
where v.dni = c.votante
    and v.fechanacimiento not like (select min(fechanacimiento)
        from votantes
        where fechanacimiento > (select min(fechanacimiento)
            from votantes))
group by c.votante
order by count(c.votante) desc;
//31
select SUBSTR(v.nombrecompleto,1,INSTR(v.nombrecompleto,' '))  "Apodo", l.nombre "Localidad", p.comunidad "Comunidad"
from votantes v, localidades l, provincias p
where v.localidad in (1, 3, 9)
    and v.localidad = l.idlocalidad
    and l.provincia = p.idprovincia;
//32
select l1.nombre || ' va antes que ' || l2.nombre "Ordenacion"
from localidades l1, localidades l2
where l1.idlocalidad = l2.idlocalidad-1
order by l1.idlocalidad asc;
//33
select nombre 
from localidades
where numerohabitantes > (select numerohabitantes
    from localidades, votantes
    where localidad = idlocalidad 
        and fechanacimiento = (select min(fechanacimiento)
            from votantes
            where fechanacimiento > (select min(fechanacimiento)
                from votantes)));
//34
select l.nombre, l.numerohabitantes, p.comunidad
from localidades l, provincias p
where l.provincia = p.idprovincia
    and l.provincia in (1,2,3)
    and l.numerohabitantes > (select min(l1.numerohabitantes)
        from localidades l1
        where provincia = 4);
//35
select v.nombrecompleto
from votantes v, consultas c
where v.dni = c.votante
    and v.situacionlaboral = 'Activo'
group by v.nombrecompleto
having count(c.votante) < (select avg(count(c1.votante))
    from consultas c1
    group by c1.votante);
//36
select nombre, avg(decode(estudiossuperiores, 'Basicos', 1, 'Ninguno', 0, 'Superiores', 2, 'Doctorado', 3, 0))estudios
from votantes, localidades
where idlocalidad = localidad
group by nombre
order by estudios desc;
//37
select l.nombre 
from votantes v, localidades l
where v.localidad = l.idlocalidad
group by l.nombre
having avg(decode ( v.estudiossuperiores, 'Ninguno',0,'Basicos',1,'Superiores',2,'Doctorado',3,
    v.estudiossuperiores)) > all (select avg(decode (v.estudiossuperiores, 'Ninguno',0,'Basicos',1,'Superiores',2,'Doctorado',3,
        v.estudiossuperiores))
        from votantes v, localidades l, provincias p
        where v.localidad = l.idlocalidad
            and l.provincia = p.idprovincia);

//38
select l.nombre,
    100*((select count(dni)from votantes where localidad = v.localidad 
        and estudiossuperiores = 'Ninguno') / count(dni)) as Ninguno,
    100*((select count(dni)from votantes where localidad = v.localidad 
        and estudiossuperiores = 'Basicos') / count(dni)) as Basicos,
    100*((select count(dni)from votantes where localidad = v.localidad 
        and estudiossuperiores = 'Superiores') / count(dni)) as Superiores,
    100*((select count(dni)from votantes where localidad = v.localidad 
        and estudiossuperiores = 'Doctorado') / count(dni)) as Doctorado
from votantes v, localidades l
where v.localidad = l.idlocalidad
group by v.localidad, l.nombre
order by l.nombre;
