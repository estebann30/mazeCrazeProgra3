# mazeCrazeProgra3
Tarea Programada 3

## Description

MazeCraze es un videojuego en 2D. El juego trata acerca de un laberinto
en el cual dos jugadores son colocados en las esquinas opuestas y el
primero en llegar al tesoro gana. Donde los jugadores se encontraran con poderes y portales los cuales les ayudaran a conseguir el tesoro, o quizas no.

## Characteristics 

Los laberintos son generados mediante un tipo de busqueda BFS o DFS de un grafo
(se puede cambiar el tipo de busqueda en la clase Catacomb).

El jugador 1 se mueve usando las teclas WASD
El jugador 2 se mueve usando las flechas

Hay diversos portales y poderes generados en zonas aleatorias del laberinto

La interfaz gráfica fue hecha en SFML


## Requisitos para correr el programa

Tener SFML instalado

Tener C++ y su compilador instalados

Tener CMake instalado

Clonar el repositorio: https://github.com/estebann30/mazeCrazeProgra3.git

## Cómo correr el programa

Abrir la carpeta principal del repositorio y en la terminal escribir make, y luego de que compile escribir ./game

## User Manual
- **First part**
1. Descargar los elementos necesarios para VScode, el compilador de c++, SFML y CMAKE.
2. Descargar el archivo donde se encuentran los archivos .cpp, los .h, y los demas archivos necesarios para correr el juego.
3. Se debe de compilar con make y ejecutar con ./game
- **Second part**
1. Al momento de ejecutar se abrira una pantalla menu donde podra escoger sobre iniciar el juego o cerrar, si inicia el juego se encontrara una ventana donde se encuentran el laberinto y los jugadores.
2. Los jugadores se mueve mediante: jugador 1 se mueve usando las teclas WASDE y jugador 2 se mueve usando las flechas
3. Se busca llegar al oponente antes que el rival.

## Photos

![fichaCon2](https://github.com/estebann30/mazeCrazeProgra3/assets/165967249/b1a7a8ae-46e4-44e2-83c5-6f0879a22749)
> El poder que hace referencia esta imagen se puede describir como obtener dos oporturnidades para moverse.

![cambioDeTurnos](https://github.com/estebann30/mazeCrazeProgra3/assets/165967249/37f3e1c7-260a-474c-b43a-7c7cf3434952)
> El poder que hacer referencia esta imagen es poder mover al personaje del oponente una vez a partir de los propios controles.

![Saltar](https://github.com/estebann30/mazeCrazeProgra3/assets/165967249/bf63c64b-b06a-4f7d-af40-b7bdac80a17d)
> El poder que hace refencia esta imagen es poder moverse sobre paredes.

![Portal](https://github.com/estebann30/mazeCrazeProgra3/assets/165967249/d02b1d8d-0824-4581-964c-f3a9d9a92d56)
> Esta imagen hacer referencia a los portales donde se movera hacia otra parte del laberinto. 

## Division de archivos
- **Chunk.cpp**
> la clase chunk representa los nodos donde los jugadores interactuan con el mapa.

- **Catacomb.cpp**
> la clase catacomb crea usando DFS o BFS un mapa de Chunks donde se desarrolla el juego y lo llena de poderes.

- **Explorer.cpp**
> la clase explorer representa a los jugadores y como interactuan con la partida.

- **Controller.cpp**
> la clase controller se encarga de efectuar los movimientos de los jugadores usando los inputs del front end.

- **Config.h**
> Parametriza los valores a cambiar

- **Game.cpp**
> Maneja las ventanas, texturas, el renderiza y los eventos.

- **CellUI.cpp**
> Maneja la textura, renderizado y colocacion de paredes.

- **MenuUI.cpp**
> Maneja la textura, renderizado, y eventos del menu.

- **WindowSizeException.cpp**
> Maneja la creacion de excepciones.

- **main.cpp**
> Maneja la ventana del menu, crea una instancia a Game para correr el juego.
>
## Autores
> Esteban Solis Alfaro C37670
> Juan Sebastian Loaiza Ospina B74200
> Jose Pablo Brenes Coto C31289
