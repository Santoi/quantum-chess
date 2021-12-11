#!/bin/bash
# Compilacion
mkdir -p build
cd build
qchess_path=`/usr/local/share/quantum_chess/`
echo "${qchess_path}"
cmake -DCMAKE_CXX_FLAGS:STRING="-DQCHESS_PATH=${qchess_path}" ..
make

# Resources
cd ..
mkdir /usr/local/share/quantum_chess -p
cp -r resources /usr/local/share/quantum_chess/
cp -r boards /usr/local/share/quantum_chess/
cp -r config_files /usr/local/share/quantum_chess/

# Binarios
cp build/src/server/server /usr/local/bin/quantum_chess_server
cp build/src/client/client /usr/local/bin/quantum_chess






