#include <unistd.h>

ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

#define RIO_BUFSIZ 8192

typedef struct {
	int rio_fd;
	int rio_cnt;
	char *rio_bufp;
	char rio_buf[RIO_BUFSIZ];
} rio_t;

void rio_readinitb(rio_t *rp, int fd);

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
