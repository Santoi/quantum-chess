# Quantum Chess: Manual de Proyecto

## Repartición de tareas

### Matías Charrut

* Lógica del ajedrez y ajedrez cuántico.
* Comunicación cliente-servidor:
    * Instrucciones del juego.
    * Log de las acciones de los usuarios durante la partida.
* Diseño e implementación del Acceptor thread.
* Lobby thread del lado del servidor.
* Action thread del lado del cliente.
* Match thread del lado del servidor.
* Diseño de paquetes genéricos para enviar información a través de los sockets.

### Andrés Zambrano

* Construcción y diseño de la GUI durante el login.
* Comunicación cliente-servidor:
    * Mensajes de chat.
    * Diseño de las instrucciones.
* Implementación de los sockets y envío de paquetes.

### Santiago López

* Construcción y diseño de la GUI durante la partida:
    * Tablero con sus Tiles y Chessmen.
    * Chat multiusuario.
    * Log de movimientos.
    * Log de acciones inválidas.
* Interacción con el usuario:
    * Lectura y renderizado de entrada de texto.
    * Interacción con las piezas del tablero.
* Implementación de la conexión de los sockets a la red.
