#include <sys/types.h>          /* some systems still require this */
#include <sys/stat.h>
#include <stdio.h>              /* for convenience */
#include <stdlib.h>             /* for convenience */
#include <stddef.h>             /* for offsetof */
#include <string.h>             /* for convenience */
#include <unistd.h>             /* for convenience */
#include <signal.h>             /* for SIG_ERR */ 
#include <netdb.h> 
#include <errno.h> 
#include <syslog.h> 
#include <sys/socket.h> 
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/resource.h>

#define BUFRUTA 1000
#define BUFLEN 128
#define QLEN 10 

#ifndef HOST_NAME_MAX 
#define HOST_NAME_MAX 256 
#endif

int sockfd;
pid_t hue;

void catchSignal(int senial){
	close(sockfd);
	printf("\nCierre de socket.\nCierre de Servidor");
	exit(1);
}

int main( int argc, char *argv[]) {

	char *ip = argv[1];
	int puerto = atoi(argv[2]);

	struct sockaddr_in direccion_servidor, direccion_cliente;

	memset(&direccion_servidor, 0, sizeof(direccion_servidor));

	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(puerto);
	direccion_servidor.sin_addr.s_addr = inet_addr(ip);

	sockfd = socket(((struct sockaddr *)&direccion_servidor)->sa_family, SOCK_STREAM, 0);

	if(sockfd == -1)
		perror("socket");	

	unsigned int len = sizeof(direccion_servidor);

	if(bind(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) == -1)
		perror("bind");
	
	if(listen(sockfd, 100) == -1)
		perror("listen");
	
	pid_t pid;
	int new = 0;
	
	while(1){	
		new = accept(sockfd,(struct sockaddr*)&direccion_cliente,&len);
		
		pid = fork();
		if(pid == 0){
			char *ruta;
			char *archivo;

			ruta=(char*)malloc(BUFRUTA*sizeof(char*));

			recv(new, ruta, BUFRUTA,0);

			int fd = open(ruta, O_RDONLY);
			
			//int tam;
			//tam = read(fd,archivo,BUFLEN);
			while(read(fd,&archivo,BUFLEN)!=0){
				send(new,&archivo,BUFLEN,0);
			}
			
			close(fd);
			close(new);
		}else if (pid<0){
			printf("No hay hijo.");
		}else{
			signal(SIGINT,catchSignal);
			close(new);
		}
	}
}
