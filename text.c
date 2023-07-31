#include <asm-generic/errno.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>

int get_line(int cfd, char* buf, int size)
{
	int i = 0;
	char c = '\0';
	int n;
	while (i < size - 1)
	{
		n = read(cfd, &c, 1);
		if(n > 0)
		{
			if(c == '\r')
			{
				buf[i] = c;
				i++;
				n = read(cfd, &c, 1);
				if((n > 0) && (c == '\n'))
				{
					buf[i] = c;
					i++;
					break;
				}
			}
			buf[i] = c;
			i++;
		}
		else 
		{
			c = '\n';
			break;
		}
	}
	buf[i] = '\0';
	if (-1 == n)
	{
		i = n;
	}
	return i;
}

int main(void)
{
	char buf[BUFSIZ];
	int fd = open("./a.text", O_RDONLY);
	int r = get_line(fd, buf, BUFSIZ);
	int i = 0;
	printf("%s  %d  %d\n",buf, r, i++);
	r = get_line(fd, buf, BUFSIZ);
	printf("%s  %d  %d\n",buf, r, i++);
	r = get_line(fd, buf, BUFSIZ);
	printf("%s  %d  %d\n",buf, r, i);
	return 0;
}