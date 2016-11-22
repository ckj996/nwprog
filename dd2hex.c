#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	struct in_addr inaddr;
	unsigned int addr;

	if (argc != 2 || !inet_aton(argv[1], &inaddr)) {
		fprintf(stderr, "Useage: %s <dotted-decimal>\n", argv[0]);
	} else {
		addr = htonl(inaddr.s_addr);
		printf("0x%08x\n", addr);
	}
	return 0;
}
