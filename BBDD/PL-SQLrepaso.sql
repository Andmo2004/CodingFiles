--1

set serveroutput on;
BEGIN
dbms_output.put_line('Hola mundo, hoy es el dia '||sysdate);
END;

--2
set serveroutput on;
DECLARE
    v_nombre votantes.nombrecompleto%type;
    v_correo votantes.email%type;
    mydni NUMBER := 30983712;
BEGIN
    SELECT nombrecompleto, email INTO v_nombre, v_correo FROM votantes where dni=mydni;
    dbms_output.put_line(v_nombre||' con correo: '||v_correo);
END;

--3

set serveroutput on;
DECLARE
    v_nombre_completo votantes.nombrecompleto%type;
    v_correo votantes.email%type;
    v_dni NUMBER := 30983712;
    v_nombre VARCHAR2(20);
BEGIN
    select nombrecompleto, email into v_nombre_completo, v_correo from votantes
        where v_dni = dni;
    v_nombre := substr(v_nombre_completo, 1, instr(v_nombre_completo, ' '));
    dbms_output.put_line(v_nombre||'con correo: '|| v_correo);
END;

--4

set serveroutput on;
DECLARE 
    v_nombre votantes.nombrecompleto%type; 
    v_dni number := 30983712;
    nombre varchar2(20);
BEGIN
    select nombrecompleto into v_nombre from votantes where dni = v_dni;
    nombre := 'Pepe' || substr(v_nombre,instr(v_nombre, ' '), length(v_nombre));
    dbms_output.put_line(nombre);
END;

 --5
set serveroutput on;
DECLARE
    v_nombre votantes.nombrecompleto%type;
    v_dni votantes.dni%type;
BEGIN
    select nombrecompleto, dni into v_nombre, v_dni from votantes 
        where fechanacimiento =(select min(v.fechanacimiento) from votantes v);
    dbms_output.put_line('El señor '||v_nombre||' con dni '||v_dni || 'es el votante mas longevo');
END;

--6

set serveroutput on;
DECLARE
    v_nombre1 votantes.nombrecompleto%type;
    v_nombre2 votantes.nombrecompleto%type;
    v_correo1 votantes.email%type;
    v_correo2 votantes.email%type;
    string1 varchar2(20);
    string2 varchar2(20);
BEGIN
    select nombrecompleto, email into v_nombre1, v_correo1 from votantes 
        where fechanacimiento = (select min(fechanacimiento) from votantes);
    select nombrecompleto, email into v_nombre2, v_correo2 from votantes 
        where fechanacimiento = (select max(fechanacimiento) from votantes);
    string1 := substr(v_correo1, 1, instr(v_correo1,'@'))||'uco.es';
    string2 := substr(v_correo2, 1, instr(v_correo2,'@'))||'uco.es';
    dbms_output.put_line(v_nombre1||' -- Email: '||string1);
    dbms_output.put_line(v_nombre2||' -- Email: '||string2);
END;

--7

set serveroutput on;
DECLARE
    v_nombre1 votantes.nombrecompleto%type;
    v_nombre2 votantes.nombrecompleto%type;
    string1 varchar2(20);
    string2 varchar2(20);
BEGIN
    select nombrecompleto into v_nombre1 from votantes 
        where fechanacimiento = (select max(fechanacimiento) from votantes);
    select nombrecompleto into v_nombre2 from votantes 
        where fechanacimiento = (select max(fechanacimiento) from votantes
            where fechanacimiento < (select max(fechanacimiento) from votantes));
            
    string1 := substr(v_nombre1, instr(v_nombre1, ' ')+1, length(v_nombre1));
    string1 := substr(string1, 1, instr(string1, ' '));
    string2 := substr(v_nombre2, instr(v_nombre2, ' ')+1, length(v_nombre2));
    string2 := substr(string2, 1, instr(string2, ' '));
    
    dbms_output.put_line(string1);
    dbms_output.put_line(string2);
    dbms_output.put_line('El hijo se llama Juan '||string2||string1);
END;

--8

set serveroutput on;
DECLARE
    numhab1 localidades.numerohabitantes%type;
    numhab2 localidades.numerohabitantes%type;
    numtotal localidades.numerohabitantes%type;
    counter number(5);
BEGIN
    select numerohabitantes into numhab1 from localidades
        where idlocalidad = 1;
    select numerohabitantes into numhab2 from localidades
        where idlocalidad = 2;
    numtotal := numhab1 + numhab2;
    select count(idlocalidad) into counter from localidades 
        where numerohabitantes > numtotal;
    dbms_output.put_line('Hay '||counter||' ciudades con mas de '||numtotal||' habitantes, que es la suma de las dos localidades con IDs mas pequeños');
END;

--9

set serveroutput on;
DECLARE
    cursor c is select * from votantes
        where dni-(localidad+1) like '%0';
    counter number:=0;
BEGIN
    for num_row in c loop
        dbms_output.put_line(num_row.nombrecompleto);
        counter := counter+1;
    end loop;
    dbms_output.put_line('Hay un total de '||counter||' votantes');
END;

--10

set serveroutput on;
DECLARE
    cursor c is select * from votantes where dni-(localidad+1) like '%0';
    counter number := 0;
    n votantes%rowtype;
BEGIN
    open c;
    loop
        fetch c into n;
        exit when c% notfound;
        dbms_output.put_line(n.nombrecompleto);
        counter := counter + 1;
    end loop;
    dbms_output.put_line('Hay un total de '||counter||' votantes');
END;

--11

set serveroutput on;
DECLARE
    counter number := 0;
    cursor c is select * from votantes where dni-(localidad+1) like '%0';
    n votantes%rowtype;
BEGIN
    open c;
    while counter <=2 loop
        fetch c into n;
        dbms_output.put_line(n.nombrecompleto);
        counter := counter + 1;
    end loop;
    dbms_output.put_line('Hay un total de '||counter||' votantes');
END;

--12

set serveroutput on;
DECLARE
    cursor c is select nombrecompleto, localidad from votantes;
    s_ciudad localidades.nombre%type;
    counter number := 0;
BEGIN
    for n in c loop
        if n.localidad in (1,2,3) then n.localidad := 9; 
        end if;
        select nombre into s_ciudad from localidades where idlocalidad = n.localidad;
        dbms_output.put_line(n.nombrecompleto||' es de '||s_ciudad);
        if s_ciudad = 'Madrid' then counter := counter +1;
        end if;
    end loop;
        dbms_output.put_line('Hay un total de '||counter||' votantes de madrid');
END;

--13

set serveroutput on;
DECLARE
    cursor c is select dni from votantes 
        where dni !=(select max(dni) from votantes)order by dni desc;
    v_dni votantes.dni%type;
BEGIN
    select max(dni) into v_dni from votantes; 
    for n in c loop
        dbms_output.put_line(v_dni||' va ante que '||n.dni);
        v_dni := n.dni;
    end loop;
    dbms_output.put_line(v_dni||' es el menor.');
END;

--14

set serveroutput on;
DECLARE
    cursor c is select v.dni from votantes v, consultas cd
        where v.dni = cd.votante
        having count(cd.votante) > 3
        group by votante
        order by count(cd.votante) desc;
    s_num number(10);
BEGIN
    for n in c loop
        select count(votante) into s_num from consultas 
            where votante = n.dni;
        dbms_output.put_line(n.dni||' ha participado '||s_num||' veces');
    end loop;
END;

