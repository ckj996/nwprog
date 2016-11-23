#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	struct in_addr inaddr;
	unsigned int addr;

	if (argc != 2 || sscanf(argv[1], "%x", &addr) != 1) {
		fprintf(stderr, "usage: %s <hexadecimal>\n", argv[0]);
	} else {
		inaddr.s_addr = ntohl(addr);
		puts(inet_ntoa(inaddr));
	}
	return 0;
}
