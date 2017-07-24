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

int main( int argc, char *argv[]) { 

	int sockfd;
	
	char *ip = argv[1];
	int puerto = atoi(argv[2]);
	char *ruta = argv[3];
	char *archivo = argv[4];


	struct sockaddr_in direccion_cliente;

	memset(&direccion_cliente, 0, sizeof(direccion_cliente));

	direccion_cliente.sin_family = AF_INET;
	direccion_cliente.sin_port = htons(puerto);
	direccion_cliente.sin_addr.s_addr = inet_addr(ip);

	sockfd = socket(direccion_cliente.sin_family, SOCK_STREAM, 0);
	connect(sockfd, (struct sockaddr *)&direccion_cliente, sizeof(direccion_cliente));

	send(sockfd,ruta,strlen(ruta),0);

	int fd = open(archivo,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);

	int n; 
	char *buf;
	buf=(char*)malloc(BUFLEN*sizeof(char*));

	while ((n = recv(sockfd, buf, BUFLEN, 0)) > 0){
		write(fd, buf, n);
		memset(buf,0,1);
	}
	if (n < 0)
		printf(" recv error");
	
	close(fd);
	close(sockfd);
}
