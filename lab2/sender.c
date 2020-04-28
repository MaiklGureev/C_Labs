
 
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
#include <stdio.h>

int sock;
struct sockaddr_in addr;

int a = 3;
int b = 4;
int sumRes,sqrtRes;


int mul_port =48660;
int sum_port = 48661;
int sqrt_port=48662;


int main()
{
    printf("Клиент для расчёта гипотенузы запущен в работу!\n");
     
    printf("Введите катеты: \n");
    scanf("%d", &a);
    scanf("%d", &b);
    
	system("gnome-terminal -- ./mulServer");
	system("gnome-terminal -- ./sumServer");
	system("gnome-terminal -- ./sqrtServer");
	
	printf("--- Возведение катетов в квадрат---\n");
	sendOnServer1(mul_port,a,b);
	
	printf("--- Сложение катетов ---\n");
	sumRes = sendOnServer2(sum_port,a,b);
	
	printf("--- Извлечение квадратного корня ---\n");
	sqrtRes = sendOnServer3(sqrt_port,sumRes);
	
	printf("Сервера посчитали результат!\n");
	
	printf("Ответ: %d \n",sqrtRes);
	
    return EXIT_SUCCESS; 
}

void sendOnServer1(int port, int value,int value2){
	
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	perror("socket");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	int c = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	perror("connect");
	
	int s = send(sock, &value, sizeof(value), 0);
	perror("send");
	
	printf("Отправил число: %d \n",value);	
	
	int r = recv(sock, &value, sizeof(value), 0);
	perror("recv");	
	
	printf("Пришло число: %d \n",value);
	
	a = value;
	
	//-----------------------------------------------------------
	
	s = send(sock, &value2, sizeof(value2), 0);
	perror("send");
	
	printf("Отправил число: %d \n",value2);	
	
	r = recv(sock, &value2, sizeof(value2), 0);
	perror("recv");	
	
	printf("Пришло число: %d \n",value2);
	
	b = value2;
	
	close(sock);
	perror("close");
	
	}
	
int sendOnServer2(int port, int value,int value2){
		
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	perror("socket");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	int c = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	perror("connect");
	
	int s = send(sock, &value, sizeof(value), 0);
	perror("send");
	
	printf("Отправил число: %d \n",value);	
	
	int r = recv(sock, &value, sizeof(value), 0);
	perror("recv");	
	
	
	//-----------------------------------------------------------
	
	s = send(sock, &value2, sizeof(value2), 0);
	perror("send");
	
	printf("Отправил число: %d \n",value2);	
	
	r = recv(sock, &value2, sizeof(value2), 0);
	perror("recv");	
	
	printf("Пришло число: %d \n",value2);
	
	close(sock);
	perror("close");
	
	return value2;
}

int sendOnServer3(int port, int value){
	
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	perror("socket");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	int c = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	perror("connect");
	
	int s = send(sock, &value, sizeof(value), 0);
	perror("send");
	
	printf("Отправил число: %d \n",value);		
	
	int r = recv(sock, &value, sizeof(value), 0);
	perror("recv");	
	
	printf("Пришло число: %d \n",value);
	
	close(sock);
	perror("close");
	
	return value;
}	
