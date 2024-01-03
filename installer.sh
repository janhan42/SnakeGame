#!/bin/bash

git clone https://github.com/janhan42/SnakeGame.git
cd SnakeGame
bash -c "$(curl -fsSL https://raw.githubusercontent.com/janhan42/SFML-installer/master/installer.sh)"
mkdir .OBJ
make
./SnakeGame
