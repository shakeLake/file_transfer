#!/bin/bash
cmake .
clear
cd client
make
./startClient "/home/mark/Desktop/data/geass/test/photo_2022-01-06_14-19-40.jpg"