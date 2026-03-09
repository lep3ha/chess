#!/bin/bash

currDir=$(pwd)
libDir=$currDir"/ExternalLibraries/SFML/lib"
includeDir=$currDir"/ExternalLibraries/SFML/include"

g++ ./source/main.cpp -std=c++20 -I$includeDir -I./include/ -o ./bin/ChessGame -L$libDir -lsfml-graphics -lsfml-window -lsfml-system

exit 0
# ./bin/ChessGame - executable