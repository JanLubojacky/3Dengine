#!/bin/bash
g++ -o eng3D engine3D.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
./eng3D