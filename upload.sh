#!/bin/bash

if [$# -eq 1]
then
	echo "Too few arguments! Usage: ./upload [project] ar/es"
	exit 1


elif [$# -eq 2]
then
	echo "Too much arguments! Usage: ./upload [project] ar/es"
	exit 1	
	
else 

	raw=$(arduino-cli board list | grep /dev/)
	
	port=$(echo $raw | cut -d " " -f 1)

	echo "$port"	
		
	if [[ "$port" ]];
	then 
		arduino-cli upload -p $port --fqbn esp32:esp32:esp32-poe-iso $1
	fi
fi
		
