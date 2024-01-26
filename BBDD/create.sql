-- Crear la tabla "votantesAntiguos" con el nuevo campo "Sueldo"
CREATE TABLE votantesAntiguos (
    dni INT PRIMARY KEY,
    nombrecompleto VARCHAR(100),
    email VARCHAR(100),
    fechanacimiento DATE,
    sueldo NUMERIC
);

-- Insertar votantes nacidos antes de 1980 en la nueva tabla
INSERT INTO votantesAntiguos (dni, nombrecompleto, email, fechanacimiento, sueldo)
SELECT dni, nombrecompleto, email, fechanacimiento,
       CASE WHEN votantes.situacionlaboral = 'Activo' 
       AND fechanacimiento < '01/01/1980' THEN 1500 ELSE 0 END AS sueldo
FROM votantes
WHERE fechanacimiento < '01/01/1980';

-- 15

set serveroutput on;
DECLARE
    cursor c is select nombrecompleto from votantesantiguos;
    n_length number:=0;
    n_total number:=0;
    s_name varchar2(20);
BEGIN
    for num_row in c loop
        s_name := substr(num_row.nombrecompleto, 1, instr(num_row.nombrecompleto, ' '));
        n_length := length(s_name)-1;
        dbms_output.put_line(s_name||'tiene '||n_length||' letras');
        n_total:=n_total+n_length;
    end loop;
    dbms_output.put_line('En total hay '||n_total);
END;

--16

set serveroutput on;
DECLARE
    cursor c is select nombrecompleto, fechanacimiento from votantesantiguos 
        order by fechanacimiento;
    cursor c2 is select nombrecompleto, fechanacimiento from votantesantiguos 
        order by fechanacimiento;
    n_length1 number := 0;
    n_length2 number := 0;
    s_name1 varchar2(20);
    s_name2 varchar2(20);
    flag number :=0;
BEGIN
    for num_row in c loop
        s_name1 := substr(num_row.nombrecompleto, 1, instr(num_row.nombrecompleto, ' '));
        n_length1 := length(s_name1)-1;
        dbms_output.put_line(num_row.nombrecompleto||' tiene mas letras que los siguientes mas jovenes:');
        for num_2 in c2 loop
            s_name2 := substr(num_2.nombrecompleto, 1, instr(num_2.nombrecompleto, ' '));
            n_length2 := length(s_name2)-1;
            if n_length1 > n_length2 
                and num_2.fechanacimiento > num_row.fechanacimiento  
                then dbms_output.put_line(num_2.nombrecompleto);
                flag := 1;
            end if;
        end loop;
        if flag = 0 then 
            dbms_output.put_line('Nadie cumple esta condicion');
        end if;
        flag := 0;
        DBMS_OUTPUT.NEW_LINE;
    end loop;
    
END;

