// i use the website https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/ for help

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// uncludes for the server and client
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h> // inet_addr()
#include <stdlib.h>
#include <strings.h> // bzero()
#define MAX 1024
#define SA struct sockaddr


// declrisons on th funcsions
int server(int p);
int client(char *  x , int y);
void funcserver(int x);
void funcclient(int y);

int main(int argc, char* argv[]) {
    
    if (strcmp(argv[1],"nc")==0){
        if (argc != 4){
       
        printf("its need to be in the formet ./mync nc <ip> <port>");
        exit(1);}
        
        
        char * IP = argv[2];
        client(IP,argv[3]);}
    
    if (strcmp(argv[1],"nc-L")==0){
         if (argc != 3)
    {
        printf("its need to be in the formet ./mync nc-L <port>");
        exit(1);
    }
        server(argv[2]);}
    
    if((strcmp(argv[1],"nc")==-1) && (strcmp(argv[1],"nc-L")==-1)){
    
        printf("it is not a valid commend");
        exit(1);}
    return 0;}


    int client(char * ip, int port){
         int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
 
    // function for chat
    funcclient(sockfd);
 
    // close the socket
    close(sockfd);

        return 0;
    }

    void funcclient(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
    }
}

    int server(int port){
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // Function for chatting between client and server
    funcserver(connfd);
   
    // After chatting close the socket
    close(sockfd);

    return 0; 
    }

    // Function designed for chat between client and server.
void funcserver(int connfd){
    char buff[MAX];
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
        // read the message from client and copy it in buffer
        int x = read(connfd, buff, sizeof(buff));
        printf("%s",buff);
  
    
        

    }
    
}