#!/bin/bash


if [ $# -eq 0 ];
then 
	echo "Too few arguments! Usage: ./compile [project]"
	exit 1

elif [ $# -eq 2 ];
then
	echo "Too much arguments! Usage: ./compile [project]"
	exit 1

else 	
	arduino-cli compile --fqbn esp32:esp32:esp32-poe-iso $1

fi
