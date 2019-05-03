#!/bin/bash


premake4 gmake
make

cd project
premake4 gmake 
make


