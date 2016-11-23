#include "lib/rio.h"
#include "lib/inopen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifndef MAXLINE
#define MAXLINE 1024
#endif

void echo(int connfd);

int main(int argc, char **argv)
{
	int listenfd, connfd, port;
	unsigned int clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;

	if (argc != 2) {
		fprintf(stderr, "%s <port>\n", argv[0]);
		exit(0);
	}
	port = atoi(argv[1]);

	listenfd = open_listenfd(port);
	for (;;) {
		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd,
				(struct sockaddr *)&clientaddr.sin_addr.s_addr,
				&clientlen);
		hp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
				sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		if (hp != NULL) {
			haddrp = inet_ntoa(clientaddr.sin_addr);
			printf("server connected to %s (%s)\n",
					hp->h_name, haddrp);
		}

		echo(connfd);
		close(connfd);
	}
	exit(0);
}

void echo(int connfd)
{
	size_t n;
	char buf[MAXLINE];
	rio_t rio;

	rio_readinitb(&rio, connfd);
	while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
		rio_writen(STDOUT_FILENO, buf, n);
		sprintf(buf, "server recieved %lu bytes\n", n);
		n = strlen(buf);
		rio_writen(connfd, buf, n);
	}
}
