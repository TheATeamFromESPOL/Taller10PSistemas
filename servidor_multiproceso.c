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

#define BUFLEN 128
#define QLEN 10 

#ifndef HOST_NAME_MAX 
#define HOST_NAME_MAX 256 
#endif

int main( int argc, char *argv[]) { 
	
	int sockfd;

	char *ip = argv[1];
	int puerto = atoi(argv[2]);

	struct sockaddr_in direccion_servidor, direccion_cliente;

	memset(&direccion_servidor, 0, sizeof(direccion_servidor));

	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(puerto);
	direccion_servidor.sin_addr.s_addr = inet_addr(ip);

	sockfd = socket(((struct sockaddr *)&direccion_servidor)->sa_family, SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("socket");	
	}

	int len = sizeof(direccion_servidor);

	if(bind(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) == -1){
		perror("bind");
	}
	
	if(listen(sockfd, 100) == -1)
		perror("listen");
	}

	int clfd, fp; 
	char buffer;
	
	pid_t pid
	int new;
	
	while(1){
		pid = fork();
		if(pid == 0){
			sigset_t set;
			sigemptyset(&set);
			sigaddset(&set,SIGTSTP);
			sigprocmask(SIG_BLOCK,&set,0);
			
			new = accept(sockfd,(struct sockaddr*)&direccion_cliente,&len);
			
			char *ruta;
			recv(new, ruta, BUFLEN,0);

			int fd = open(ruta, O_RDONLY);
		}
	}	
}
