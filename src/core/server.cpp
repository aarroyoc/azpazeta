#include <stdio.h>
#include "server.hpp"
/* Server for logical operations, input/output operations goes to client. Works in WinSockets and Berkely Sockets */
static const char blue[]="\e[1;34m"; //Status and Info messages
static const char black[]="\e[0m"; //Long messages
static const char red[]="\e[0;31m"; //Error messages
static const char green[]="\e[0;32m"; //Sucessfully messages
static const char yellow[]="\e[0;33m"; //Warning messages
bool ipv6=false; //IPv6 enabled
bool af_unix=false; //AF_UNIX instead AF_INET, for Single Player
SOCKET sock_server, sock_client[100];
int user=0;
struct sockaddr_in6 client6;
struct sockaddr client4;
socklen_t long_client;

int main(int argc, char* argv[])
{
	blueprintf("[STATUS] Starting Azpazeta Server 2.0 Juno");
	char message[1024]="[STATUS] Running ";
	strcat(message,AZP_SOCK_TYPE);
	blueprintf(message);
	if(argc==2)
	{
		if(strcmp(argv[1],"ipv6")==0)
		{
			ipv6=true;
			blueprintf("[INFO] IPv6 Enabled");
		}
		if(strcmp(argv[1],"ipv4")==0)
		{
			ipv6=false;
			blueprintf("[INFO] IPv6 Disabled");
		}
		if(strcmp(argv[1],"unix")==0)
		{
			af_unix=true;
			blueprintf("[INFO] AF_UNIX instead AF_INET");
			blueprintf("[INFO] IPv6 Disabled");
		}

	}
	#ifdef WIN32
	StartWinSock();
	#else
	StartBerkely();
	#endif
	return 0;
}

void StartWinSock()
{
#ifdef WIN32
	struct sockaddr_in host;
	WSADATA wsaData;
	WORD version;

	version = MAKEWORD( 2, 2 );
	
	WSAStartup( version, &wsaData );

	if(!ipv6)
	//IPV4
	{
		int size=sizeof(sockaddr);
		sock_server=socket(AF_INET,SOCK_STREAM,0);
		if(sock_server==-1)
			redprintf("[ERROR] Azpazeta Server can't open the socket");
		else
			greenprintf("[OK] Azpazeta Server opens the socket");
		host.sin_family = AF_INET;
		host.sin_port = htons(6996);
		host.sin_addr.s_addr =INADDR_ANY;

		if (bind (sock_server,(struct sockaddr *)&host, sizeof(struct sockaddr_in)) == -1)
		{
			redprintf("[ERROR] Error while server is binding the data");
			puts(strerror(errno));
		}
		if (listen (sock_server, 1) == -1)
		{
			redprintf("[ERROR] Error while server is listening");
			puts(strerror(errno));
		}
		long_client = sizeof (client4);
	}else
	//IPV6
	{
		struct sockaddr_in6 host;

		char buffer [1024];
		int size=sizeof (client4); 
		sock_server=socket(AF_INET6,SOCK_STREAM,0);
		if(sock_server==-1)
			redprintf("[ERROR] Azpazeta Server can't open the socket");
		else
			greenprintf("[OK] Azpazeta Server opens the socket");
		host.sin6_family = AF_INET6;
		host.sin6_port = htons(6996);
		host.sin6_addr = in6addr_any;

		if (bind (sock_server,(struct sockaddr *)&host, sizeof(struct sockaddr_in6)) == -1)
		{
			redprintf("[ERROR] Error while server is binding the data");
			puts(strerror(errno));
		} 
		if (listen (sock_server, 1) == -1)
		{
			redprintf("[ERROR] Error while server is listening");
			puts(strerror(errno));
		}
		long_client = sizeof (sockaddr_in6);
	}
	//Crear un thread y tal
	DWORD threadIDArray[100];
	HANDLE threadArray[100];

	for( int i = 0; i < 10; i++){
	threadArray[i] = CreateThread(
	    NULL,
	    0,          
	    (LPTHREAD_START_ROUTINE)RegisterUser,
	    NULL,    
	    i,
	    &threadIDArray[i]);  
	}
	WaitForMultipleObjects(10, threadArray, TRUE, INFINITE);
    for (int x = 0; x < 10; x++) {
	int ret;
	if ((ret = CloseHandle(threadArray[x]) != 0)) {
	    /* The thread not closing properly */
	    x--;
	}
    }
closesocket(sock_server);
WSACleanup();

#endif
}
void StartBerkely()
{
#ifndef WIN32
fd_set descriptoresLectura;
if(!ipv6)
//IPv4
{
struct sockaddr_in host;
char buffer [1024];
int size=sizeof (client4); 
sock_server=socket(AF_INET,SOCK_STREAM,0);
if(sock_server==-1)
	redprintf("[ERROR] Azpazeta Server can't open the socket");
else
	greenprintf("[OK] Azpazeta Server opens the socket");


//memset(&host, 0, sizeof(struct sockaddr_in));
host.sin_family = AF_INET;
host.sin_port = htons(6996);
host.sin_addr.s_addr =INADDR_ANY;

if (bind (sock_server,(struct sockaddr *)&host, sizeof(struct sockaddr_in)) == -1)
{
	redprintf("[ERROR] Error while server is binding the data");
	puts(strerror(errno));
} 
if (listen (sock_server, 1) == -1)
{
    redprintf("[ERROR] Error while server is listening");
	puts(strerror(errno));
}
long_client = sizeof (client4);

}else{
//IPv6
struct sockaddr_in6 host;

socklen_t long_client;
char buffer [1024];
int size=sizeof (client4); 
sock_server=socket(AF_INET6,SOCK_STREAM,0);
if(sock_server==-1)
	redprintf("[ERROR] Azpazeta Server can't open the socket");
else
	greenprintf("[OK] Azpazeta Server opens the socket");


//memset(&host, 0, sizeof(struct sockaddr_in));
host.sin6_family = AF_INET6;
host.sin6_port = htons(6996);
host.sin6_addr = in6addr_any;

if (bind (sock_server,(struct sockaddr *)&host, sizeof(struct sockaddr_in6)) == -1)
{
	redprintf("[ERROR] Error while server is binding the data");
	puts(strerror(errno));
} 
if (listen (sock_server, 1) == -1)
{
    redprintf("[ERROR] Error while server is listening");
	puts(strerror(errno));
}
long_client = sizeof (client6);
}

//One thread per socket



pthread_t sock_hilo[100];
char* valorDevuelto=NULL;
int closing;
for(user=0;user<10;user++)
	pthread_create(&sock_hilo[user],NULL,RegisterUser,(void*)user);
for(closing=0;closing<10;closing++)
	pthread_join (sock_hilo[closing], (void **)&valorDevuelto); 
close(sock_server);






#endif
}
void MainLoop(int64_t me)
{
/*Works in the 2 types of Sockets*/
/* Un socket ya esta conectado. Se crean un hilo nuevo con listen y accept incluido */
char message[]="[OK] Azpazeta Server connection stablished";
char recvbuf[1024];
send(sock_client[me],message,sizeof(message),0);
recv(sock_client[me],recvbuf,sizeof(recvbuf),0);
greenprintf(recvbuf);
char message2[]="[OK] Waiting ";
send(sock_client[me],message2,sizeof(message2),0);
#ifdef WIN32
closesocket(sock_client[me]);
#else
close(sock_client[me]);
#endif
blueprintf("[INFO] Exit server an user");



}
void *RegisterUser (void * yo)
{ 
	int64_t me=(int64_t)yo;
	sock_client[me] = accept (sock_server,ipv6 ? (struct sockaddr *)&client6 : (struct sockaddr *)&client4,&long_client);
	if (sock_client[me] == -1)
	{
	redprintf("[ERROR] Azpazeta Server can't accept the client");
	puts(strerror(errno));
	}else{
	blueprintf("[INFO] New user connected");
	printf("Connected user number: %d\n",user);
	printf("Connected me number: %lld\n",me);
	}
	MainLoop(me);

	return NULL;
}
void blueprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",blue,message,black);

#endif
}
void redprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",red,message,black);

#endif
}
void yellowprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",yellow,message,black);

#endif
}
void greenprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",green,message,black);

#endif
}
