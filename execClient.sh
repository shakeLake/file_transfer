#!/bin/bash
cmake .
clear
cd client
make
./startClient "/home/mark/Desktop/11.jpg"