all: servidor cliente

servidor: servidor_multiproceso.c 
	gcc -Wall -g $^ -o $@

cliente: cliente.c 
	gcc -Wall $^ -o $@

clean:
	rm -rf cliente servidor
