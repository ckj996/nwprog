#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include "inopen.h"

#define LISTENQ 1024

int open_clientfd(char *hostname, int port)
{
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;

	if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1; /* check errno for cause of error */

	/* fill in the server's IP address and port */
	if ((hp = gethostbyname(hostname)) == NULL)
		return -2;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	memcpy((char *)&serveraddr.sin_addr.s_addr,
			(char *)hp->h_addr_list[0],
			hp->h_length);
	serveraddr.sin_port = htons(port);

	/* establish a connection with the server */
	if (connect(clientfd, (struct sockaddr *)&serveraddr,
				sizeof(serveraddr)) < 0)
		return -1;
	return clientfd;
}

int open_listenfd(int port)
{
	int listenfd, optval = 1;
	struct sockaddr_in serveraddr;

	/* create a socket descriptor */
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;

	/* eliminates "address already in use" error from bind */
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
				(const void *)&optval, sizeof(int)) < 0)
		return -1;

	/* listenfd will be an end point for all requests to port
	   on any IP address for this host */
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short) port);
	if (bind(listenfd, (struct sockaddr *)&serveraddr,
				sizeof(serveraddr)) < 0)
		return -1;

	/* make it a listening socket ready to accept connection requests */
	if (listen(listenfd, LISTENQ) < 0)
		return -1;
	return listenfd;
}
