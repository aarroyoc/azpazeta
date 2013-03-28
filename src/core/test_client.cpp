#include "server.hpp"

int main(int argc, char* argv[])
{

	if(argc>=2)
	{
		//char ip[]=argv[1];

	}
#ifdef IPV4_AND_HOSTNAME	
struct hostent *Host;
Host = gethostbyname ("localhost");
if (Host == NULL)
{
	printf ("Error\n");
} 
int server = socket (AF_INET, SOCK_STREAM, 0);

if (server == -1)
{
    printf ("Error\n");
} 
struct sockaddr_in Direccion;
Direccion.sin_family = AF_INET;
Direccion.sin_addr.s_addr = ((struct in_addr*)(Host->h_addr))->s_addr;
Direccion.sin_port = htons(6996);

if (connect (server, (struct sockaddr *)&Direccion,sizeof (Direccion)) == -1)
{
    printf ("Error\n");
} 
char buffer[1024];
recv(server, buffer, 1024, 0);
puts(buffer);
send(server,buffer,1024,0);
recv(server,buffer,1024,0);
puts(buffer);
#endif


#ifdef IPV6_AND_IP

int server = socket (AF_INET6, SOCK_STREAM, 0);

if (server == -1)
{
    printf ("Error\n");
} 
struct sockaddr_in6 Direccion;
Direccion.sin6_family = AF_INET6;
Direccion.sin6_port = htons(6996);
inet_pton(AF_INET6, "::1", &(Direccion.sin6_addr));

if (connect (server, (struct sockaddr *)&Direccion,sizeof (Direccion)) == -1)
{
    printf ("Error\n");
} 
char buffer[1024];
recv(server, buffer, 1024, 0);
puts(buffer);
send(server,buffer,1024,0);
recv(server,buffer,1024,0);
puts(buffer);
#endif

#define ALL_AND_HOST

#ifdef ALL_AND_HOST
struct addrinfo *result = NULL;
struct addrinfo *ptr = NULL;
struct addrinfo hints;
int server;

struct sockaddr_in  sockaddr_ipv4;
struct sockaddr_in6 sockaddr_ipv6;
bool ipv6=true;
if(argc==2)
{
	if(strcmp(argv[1],"ipv4")==0)
		ipv6=false;
	if(strcmp(argv[1],"ipv6")==0)
		ipv6=true;
}

	/*struct sockaddr_in *h;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // use AF_INET6 to force IPv6
	hints.ai_socktype = SOCK_STREAM;

	if ( (rv = getaddrinfo( "www.google.es" , "6996" , &hints , &result)) != 0) 
	{
		fprintf(stderr, "getaddrinfo:\n");
		return 1;
	}

	// loop through all the results and connect to the first we can
	for(ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{
		h = (struct sockaddr_in *) ptr->ai_addr;
		printf("IP from the host: %s\n",inet_ntoa( h->sin_addr ) );
	}
	
	freeaddrinfo(result); // all done with this structure
	*/

if(!ipv6)
{
                printf("AF_INET (IPv4)\n");
		server = socket (AF_INET, SOCK_STREAM, 0);

		if (server == -1)
		{
    		printf ("Error\n");
		} 
		sockaddr_ipv4.sin_family = AF_INET;
		sockaddr_ipv4.sin_port = htons(6996);
		inet_pton(AF_INET, "127.0.0.1", &(sockaddr_ipv4.sin_addr));
	
		if (connect (server, (struct sockaddr *)&sockaddr_ipv4,sizeof (sockaddr_ipv4)) == -1)
		{
		    printf ("Error\n");
		} 	

}else{

                printf("AF_INET6 (IPv6)\n");
		server = socket (AF_INET6, SOCK_STREAM, 0);

		if (server == -1)
		{
    		printf ("Error\n");
		} 
		sockaddr_ipv6.sin6_family = AF_INET6;
		sockaddr_ipv6.sin6_port = htons(6996);
		inet_pton(AF_INET6, "::1", &(sockaddr_ipv6.sin6_addr));
	
		if (connect (server, (struct sockaddr *)&sockaddr_ipv6,sizeof (sockaddr_ipv6)) == -1)
		{
		    printf ("Error\n");
		}
}
char buffer[1024];
recv(server, buffer, 1024, 0);
puts(buffer);
getchar();
send(server,buffer,1024,0);
recv(server,buffer,1024,0);
puts(buffer);

#endif
}
