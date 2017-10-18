
/**
 * Como argumentos recibe el nombre del servidor (localhost en nuestro caso)
 * y el número de puerto en el que debe realizar la conexión
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <netdb.h>

using namespace std;


int main(int argc, char const* argv[]) {
	int sockfd, newSockFd, portNumber, i;
	struct hostent* server;
	char buffer[256];
	struct sockaddr_in servAddr;
	portNumber = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		cerr << "Error creating socket file descriptor" << endl;
		exit(-1);
	}
	server = gethostbyname(argv[1]); // Dirección del servidor
	if (server == NULL) {
		cerr << "Error trying to get hostbyname for server" << endl;
		exit(-1);
	}
	bzero((char*)& servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)& servAddr.sin_addr.s_addr, server->h_length);
	servAddr.sin_port = htons(portNumber);
	if (connect(sockfd, (struct sockaddr*)& servAddr, sizeof(servAddr)) < 0) {
		cerr << "Errory trying to connect to server" << endl;
		exit(-1);
	}
	cout << "Introduzca el mensaje: \n>";
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	i = write(sockfd, buffer, strlen(buffer));
	if (i < 0) {
		cerr << "Couldn't be able to write in the socket" << endl;
		exit(-1);
	}
	close(sockfd);
	return 0;
}