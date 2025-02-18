Cómo jugar: 
- Una vez seleccionada la opción jugar debe ingresar los nombres de todos los jugadores que vayan a jugar, terminando la carga al escribir la palabra "listo"
- Una vez cargados los nombres verá el orden en que jugarán los jugadores y sus puntajes actuales. Seguido a esto se le preguntará al primer jugador si esta listo y debe ingresar una "s" si lo esta
- A partir de ahi iniciaran las rondas de cada jugador determinadas por el archivo de configuracion, en la que cada vez que sea el turno del jugador para hacer su jugada debe ingresar el número de columna, apretar enter, ingresar la fila y apretar enter de nuevo.

*Si quiere cambiar la cantidad de rondas que juega cada jugador debe modificar el archivo de de texto config.txt*



Descripción   | Salida esperada | Salida obtenida 
------------- | -------------   | -------------
Se quiere probar que es lo que pasaría si se inserta un número de columna invalido    | Se espera que el sistema muestra un mensaje de “Posición invalida” y pide volver a ingresar columna y fila   | ![](https://github.com/Lautaro307/ArgProg23/blob/main/image.png) 
Se quiere probar que es lo que pasaría si se intenta elegir un lugar ocupado del tablero  | Se espera que el sistema muestra un mensaje de “Posición invalida” y pide volver a ingresar columna y fila  |  ![](https://github.com/Lautaro307/ArgProg23/blob/main/ab.PNG)
Se quiere probar que es lo que pasaría si las primeras dos jugadas del usuario son 1-1 y 2-2  | Se espera que la máquina en su turno pone su ficha en el 0-0  |  ![](https://github.com/Lautaro307/ArgProg23/blob/main/ab.PNG)
Se quiere probar que es lo que pasaría si se llena todo el tablero sin que nadie gane  | Se espera que el sistema muestra un mensaje de empate y espere a que el usuario aprete algún botón para arrancar otra partida (en caso de que tenga que venir otra partida)   |  ![](https://github.com/Lautaro307/ArgProg23/blob/main/ac.PNG)
Se quiere probar que es lo que pasaría si se ingresan 3 números cuando al usuario se le pide la columna y fila para su jugada   | Se espera que el sistema muestra un mensaje de “Posición invalida” y pide volver a ingresar columna y fila   |  ![](https://github.com/Lautaro307/ArgProg23/blob/main/ad.PNG)
Se quiere probar que es lo que pasaría si se ingresan letras cuando se pide ingresar columna y fila   | Se espera que el sistema muestre un mensaje de “Posición invalida” y pide volver a ingresar columna y fila  |  ![](https://github.com/Lautaro307/ArgProg23/blob/main/ae.PNG)
Se quiere probar que es lo que pasaría si el usuario esta por ganar de dos formas distintas   | Se espera que la máquina impida solo una de las formas de ganar   |  ![](https://github.com/Lautaro307/ArgProg23/blob/main/af.PNG) La maquina puso su ficha en 0-1
Se quiere probar que es lo que pasaria si el archivo dice que cada jugador juegue 0 partidas  | Se espera que el programa vuelva al menú  |  ![](
