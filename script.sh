#!/bin/bash

for i in {1..200} 
do
	for j in {0..49}
	do
		./cliente 127.0.0.1 45343 archivos_aleatorios/archivo$j archivo$j
	done
done
