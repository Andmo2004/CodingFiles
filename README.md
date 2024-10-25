# PRÁCTICA 1: INICIACIÓN A JAVA
![Build Status](https://img.shields.io/badge/build-passing-brightgreen) ![Version](https://img.shields.io/badge/version-1.0.0-blue)  
### Grupo 14 - GM2:
Mario Sánchez Gómez  
Ángel Moreno Fernández  
Alberto Poveda del Río  
Andrés Moros Rincón  

## Descripción
La práctica consiste en la programación de un sistema en JAVA el cuál nos permite la gestión de de reservas de pistas, en función de los diferentes tipos de eventos, además de controlar el estado y el mantenimiento de los materiales disponibles. Todo esto a través del procesamiento de los datos que guardamos en ficheros.

## Tabla de Contenidos
- [Instalación](#instalación)
- [Uso](#uso)
- [Contribución](#contribución)

## Instalación
Instrucciones para instalar el proyecto:

```bash
git clone https://github.com/masago04/ProgramacionWeb.git
```

## Uso
Para el uso del sistema, tenemos un único main `ReservasMainProgram.java` que cuando ejecutamos nos lanza a un menú el cuál nos permite acceder a todos los distintos gestores `GestionReservas.java`, `GestionPistas.java`, y `GestionUsuario` los cuales a su vez son menus que nos permiten la creación, modificación, y eliminación de datos sobre los distintos campos.

### Menu MainProgram
| Opción | Redirección |
|---------|-------------|
| 1.    | `GestionUsuario.java` |
| 2.    | `GestionReservas.java`|
| 3.    | `GestionPistas.java`  |
| 4.    | Salimos del programa  |

### Menu GestionUsuario
| Opción | Uso |
|---------|-------------|
| 1.    | Dar de alta a un usuario |
| 2.    | Modificar la información de un usuario|
| 3.    | Listar a los usuarios registrados  |
| 4.    | Volvemos al main menu  |
