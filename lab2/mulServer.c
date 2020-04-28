
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int sock;
struct sockaddr_in addr;

int mul_port =48660;
int mul_port2 = 48661;


int servRes;

int main()
{
	printf("Сервер возведения в квадрат запущен в работу!\n");
	recvFromServer(mul_port);		
    return EXIT_SUCCESS; 
}

void recvFromServer(int port){
	
	int result;
	
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	perror("socket");
	
	addr.sin_family = AF_INET;	
	addr.sin_port = htons(port);	
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int opt = 1;
	setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));
	perror("setsockopt");
		
	int bi = bind(sock, (struct sockaddr *)&addr, sizeof(addr));	
	perror("bind");
		
	int l = listen(sock,5);	
	perror("listen");
	
	int ac = accept(sock, NULL, NULL);			
	perror("accept");
	
						
	int r = recv(ac, &result, sizeof(result), 0);
	perror("recv");
					
	printf("Пришло число: %d \n",result);
	
	result *= result;
	printf("Квадрат: %d \n",result);
	
	printf("Сервер возвёл в квадрат!\n");
	
	int s = send(ac, &result, sizeof(result), 0);
	perror("send");
	
	printf("Отправил число: %d \n",result);
	
	//-----------------------------------------------
	
	
	r = recv(ac, &result, sizeof(result), 0);
	perror("recv");
					
	printf("Пришло число: %d \n",result);
	
	result *= result;
	printf("Квадрат: %d \n",result);
	
	printf("Сервер возвёл в квадрат!\n");
	
	s = send(ac, &result, sizeof(result), 0);
	perror("send");
	
	printf("Отправил число: %d \n",result);
			
	close(sock);		
	//error("close");
	
	}
