all: servidor cliente archivos

servidor: servidor_multiproceso.c 
	gcc -Wall -g $^ -o $@

cliente: cliente.c 
	gcc -Wall $^ -o $@

archivos: aleatorio.py
	mkdir archivos_aleatorios
	chmod 755 aleatorio.py
	./aleatorio.py

clean:
	rm -rf cliente servidor
	rm -rf ./archivos_aleatorios/*
	rmdir archivos_aleatorios
