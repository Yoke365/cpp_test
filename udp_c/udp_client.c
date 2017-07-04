#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>

#define rport 4567
#define rip "127.0.0.1"

int main()
{
	int s,len;
	struct sockaddr_in addr;
	int addr_len;
	char msg[256];
	int i=0;

	if((s=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("error");
		exit(1);
	}
	else
	{
		printf("socket created.\n");
		printf("socket id: %d\n",s);
		printf("romote ip: %s\n",rip);
		printf("remote port: %d\n",rport);
	}

	len=sizeof(struct sockaddr_in);
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(rport);
	addr.sin_addr.s_addr=inet_addr(rip);

	while(1)
	{
		bzero(msg,sizeof(msg));
		len=read(STDIN_FILENO,msg,sizeof(msg));
		sendto(s,msg,len,0,&addr,addr_len);
		printf("\nInput message: %s\n",msg);
		len=recvfrom(s,msg,sizeof(msg),0,&addr,&addr_len);

		printf("%d :",i);
		i++;
		printf("received message: %s \n",msg);
	}
	return 0;
}
