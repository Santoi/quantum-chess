# Quantum Chess
## Taller de Programación I

**Matías Charrut** - 101137

**Santiago Lopez** - 100566

**Andrés Zambrano** - 105500

[Link al repositorio](https://github.com/santoi/quantum-chess)

## Ejecucion

### Dependencias
* Git
* Make
* CMake
* gcc
* g++
* SDL2 (paquetes ```libsdl2-dev```, ```libsdl2-mixer-dev```, ```libsdl2-ttf-dev```, ```libsdl2-image-dev```)
* Valgrind (solo si se desea correr con el mismo)

### Compilación
Para compilar, en una consola se debe clonar el resositorio utilizando
    
    git clone --recurse-submodules git@github.com:Santoi/quantum-chess

y luego ejecutar la compilación usando el script de bash.

    bash build.sh

### Ejecución del servidor
Para ejecutar el server, se debe ejecutar la siguiente linea, donde ```port``` es el puerto en el que se abrirá el server y ```config_file``` el archivo de configuración del tablero, el cual debe estar ubicado en ```boards/``` (solo el nombre del archivo, sin esta primera carpeta). Si no se explicita este último parámetro, se utilizara el archivo ```default.txt```.

    bash server.sh <port> [config_file]

### Ejecución del cliente

Para ejecutar el cliente, se debe ejecutar la siguiente linea, donde ```host``` es el host donde se encuentra corriendo el server y ```port``` el puerto.

    bash client.sh <host> <port>

### Ejecución de tests y valgrind

Para ejecutar los tests se debe correr la siguiente linea, para ello se debe tener instalado Valgrind.

    bash valtest.sh

Para ejecutar el servidor o el cliente con Valgrind, se ejecuta de la misma manera detallada en la sección anterior pero con los scripts

        bash valserver.sh <port> [config_file]
        bash valclient.sh <host> <port>

### Limpieza de build

Para limpiar la build, simplemente se debe borrar la carpeta ```build``` con

    rm -r build

## Archivo de configuración

El archivo de configuracion permite cargar tableros pre-definidos. Esto es para el server, por lo que un server inicializado con un archivo, lo usará para todas sus partidas.

 Los archivos de configuración deben ser guardados en texto plano en la carpeta ```boards/```.

Cada pieza debe ser colocada en una línea distinta, teniendo la siguiente forma:
    
    <CHESSMAN><POS_X><POS_Y><COLOR>

donde:

* ```CHESSMAN``` es un caracter que representa a la pieza que se coloca (este caracter es la inicial del nombre de la pieza en inglés, excepto para el caballo que es representado por ```H```).
* ```POS_X``` es la posición en x, caracter de A a H.
* ```POS_Y``` es la posicion en y, número de 1 a 8.
* ```COLOR``` es un caracter que representa el color de la pieza, ```W``` para blancas y ```B``` para negras.

Las lineas en blanco son ignoradas y se pueden insertar comentarios utilizando ```#``` como primer caracter de la linea.