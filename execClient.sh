#!/bin/bash
cmake .
clear
cd client
make
./startClient "/home/mark/Desktop/Effective_Modern_C__.pdf"