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

	struct sockaddr_in direccion_servidor;

	memset(&direccion_servidor, 0, sizeof(direccion_servidor));

	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(puerto);
	direccion_servidor.sin_addr.s_addr = inet_addr(ip);

	sockfd = socket(((struct sockaddr *)&direccion_servidor)->sa_family, SOCK_STREAM, 0);

	bind(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor));

	listen(sockfd, 100);

	int clfd, fp; 
	char buffer;
	
	if (( clfd = accept(sockfd, NULL, NULL)) < 0) {
		syslog( LOG_ERR, "ruptimed: accept error: %s", strerror( errno));			
		exit( 1); 
	} 


	fp = open("./imagen/perro.jpg", O_RDONLY);

	while(read(fp,&buffer,sizeof(buffer))!=0){
		send(clfd, &buffer, sizeof(buffer), 0);
	}
	
	

	close( fp);
	close(clfd);
}
