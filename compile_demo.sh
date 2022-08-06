#!/bin/bash
g++ -o demo demo.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
./demo