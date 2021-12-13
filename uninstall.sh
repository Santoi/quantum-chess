#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi
rm -rf /usr/local/share/quantum_chess
rm /usr/local/bin/quantum_chess_server
rm /usr/local/bin/quantum_chess
rm /usr/local/bin/__quantum_chess_server
rm /usr/local/bin/__quantum_chess
rm /usr/share/applications/quantum_chess.desktop
