#! /bin/sh
# Скрипт для сборки игры
g++ -std=c++20 demo.cpp -o demo\
    -ljsoncpp\
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio\
    -O2 -pedantic-errors -fshort-enums &&
echo "Собрано!"
