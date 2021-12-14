#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi
# Compilation
rm -rf build
mkdir -p build
cd build
cmake ..
make

# Resources
cd ..
mkdir /usr/local/share/quantum_chess -p
cp -r resources /usr/local/share/quantum_chess/
cp -r boards /usr/local/share/quantum_chess/
cp -r config_files /usr/local/share/quantum_chess/

# Binaries
cp build/src/server/server /usr/local/bin/__quantum_chess_server
cp build/src/client/client /usr/local/bin/__quantum_chess
cp installer/quantum_chess /usr/local/bin/quantum_chess
cp installer/quantum_chess_server /usr/local/bin/quantum_chess_server
cp installer/quantum_chess.desktop /usr/share/applications/quantum_chess.desktop
chmod +x /usr/local/bin/quantum_chess
chmod +x /usr/local/bin/quantum_chess_server

rm -rf build





