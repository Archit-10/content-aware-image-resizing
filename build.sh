#!/bin/bash
set -e

g++ -std=c++17 -Iinclude src/main.cpp src/energy.cpp src/seam_carver.cpp -o seam_carver $(pkg-config --cflags --libs opencv4)

./seam_carver