# Quantum Chess: Manual de Proyecto

## Integrantes

**Santiago Lopez** - 100566

**Matías Charrut** - 101137

**Andrés Zambrano** - 105500

## Repartición de tareas

### Matías Charrut

* Lógica del ajedrez y ajedrez cuántico.
* Comunicación cliente-servidor:
    * Instrucciones del juego.
    * Log de las acciones de los usuarios durante la partida.
* Diseño e implementación del Acceptor thread.
* Lobby thread del lado del servidor.
* Thread de conexión del cliente.
* Action thread del lado del cliente.
* Match thread del lado del servidor.
* Diseño de paquetes genéricos para enviar información a través de los sockets.
* Diseño de pantalla de help.

### Andrés Zambrano

* Construcción y lógica del Log in.
    * Botones.
* Comunicación cliente-servidor:
    * Mensajes de chat.
    * Diseño de las instrucciones.
* Implementación de los sockets y envío de paquetes.
* Rendición y salida de partida.
* Lógica de pantalla de help.
* Sonidos.

### Santiago López

* Construcción y diseño de la GUI durante la partida:
    * Tablero con sus Tiles y Chessmen.
    * Chat multiusuario.
    * Log de movimientos.
    * Log de acciones inválidas.
* Construcción y diseño de la GUI durante el Log In:
    * Entradas de texto.
* Interacción con el usuario:
    * Lectura y renderizado de entrada de texto.
    * Interacción con las piezas del tablero.
    * Feedback del tablero.
* Implementación de la conexión de los sockets a la red.

## Inconvenientes encontrados

Uno de los inconvenientes encontrados fue la entrada de texto en SDL, ya que esta libreria no posee ningun tipo de soporte para esto (más que el mapeo del teclado). Se debió dedicarle tiempo a esta tarea pero se obtuvieron resultados satifactorios.

Otro inconveniente fue la lógica del entrelazamiento del ajedrez cuántico. Se barajaron varios métodos que fueron descartados a distintos niveles de desarrollo, el último luego de varios días de trabajo. Finalmente se decantó por el método actual el cual fue muy sencillo de programa y debuggear.

## Análisis de puntos pendientes

Varias aspectos del juegos estaban planeados para ser agregados, no quedando finalmente por temas de tiempo. Entre ellos:

* Partidas con reloj
* Coronación
* Movimiento del peón pasado
* Posibilidad de poder salir de partidas y volver al Log In sin cerrar el programa.
* Entrelazamiento entre más de dos piezas.
* Visualización de información de piezas, especialmente para la probabilidad, ya que esta puede ser muy pequeña y no llegar a verse debido a la GUI.


## Herramientas

Se listan las herramientas utilizadas:

* CLion
* Git
* GitHub
* gdb, gcc, g++
* valgrind
* CMake
* Cpplint
* Cppcheck
* Visual Studio Code
* GIMP
* Adobe Photoshop
* Oracle VirtualBox
* Oracle Cloud Infraestructure
* Tiburoncin
* Notion
* Draw.io
* PlantUML

## Conclusiones

Se puede concluir, que se alcanzaron los objetivos requeridos y se superaron en ciertos aspectos. 

El desarrollo del trabajo práctico sirvió como una buena manera de afianzar los conocimientos adquiridos durante la cursada de la materia y de sumar nuevos conocimientos, tales como manejo de SDL, CMake, entre otros.