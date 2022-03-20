#!/bin/bash
cmake .
clear
cd server
make
./startServer