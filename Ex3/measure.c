#include <sys/socket.h>
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h> 
#include <errno.h>
#include <string.h> 
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

// gist: In this class we want to recive the data we have sent. The process is:
// Step 1: creat and set a socket
// Step 2: Binding the socket with an ip to this port and listen.
// Step 3: Recive the data and take notes.

#define Size 1024
#define port 9090
#define fileSize 1048576
#define mb100 104857600 //Allocate 100 MB memory block 

int reciveTheData(int serverSocket, char* buffer,struct sockaddr_in INFO);
int gettingTheData(int serverSocket, char* buffer,struct sockaddr_in serverInfo );
//int setSockOpt(int socket , char * buffer);
int createSocket();

int recevier_chakesum(int c[mb100],int s, int scheck)
{
    int checksum,sum=0;
    for (int i ; i<mb100; i++)
    {
        sum+=c[i];
    }
    sum=sum+scheck;
    checksum=~sum;
    printf("Reciver checksum is:%d",checksum);
    return checksum;
}

int createSocket(){
    // Create a socket lisener.
    // Returns zero if the creation was secssesuful and -1 if not.
    int sock = -1;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        perror("Creation failed!\n");
        return -1;
    }
    printf("Socket created!\n");
    return sock;
}

//int setSockOpt(int socket , char * buffer){
    // Taken from the instruction to the assigment 
    // Specify the wanted socket option name.
    
    //strcpy(buffer, "reno"); if will be problem its here
  //  socklen_t length = sizeof(buffer);
  //  int socketOpt = setsockopt(socket, IPPROTO_TCP, TCP_CONGESTION, buffer, length);
   // if (socketOpt != 0) {
  //      perror("Set failed:\n");
  //      return -1;
  //  }
  //  if (getsockopt(socket, IPPROTO_TCP, TCP_CONGESTION, buffer, &length) != 0) {
  //      perror("getsockopt"); 
  //      return -1; 
  //  } 
 //   printf("Set sucsseded! Algorithm changed to: %s\n", buffer);
  //  return socketOpt;
//}

int gettingTheData(int serverSocket, char* buffer,struct sockaddr_in serverInfo ){
    
    // This part taken from the tirgul slideshow("Packet Sniffing and Spoofing", page 16).
    bzero(&serverInfo, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(port);
    
    //Binding the socket with an ip to this port
    int binding = bind(serverSocket, (struct sockaddr *)&serverInfo,  sizeof(serverInfo));
    if(binding == -1){
        perror("Binding faild!\n");
        close(serverSocket);
        return -1;
    }
    printf("Bind was sucssesful!\n");

    reciveTheData(serverSocket, buffer,serverInfo,0);

    return 0;
}

int reciveTheData(int serverSocket, char* buffer,struct sockaddr_in INFO){
    char buf[1024];
    socklen_t length = sizeof(buf);
    if (getsockopt(serverSocket, IPPROTO_TCP, TCP_CONGESTION, buf, &length) != 0) { 
        perror("getsockopt");
        return -1;
    }
    // struct sockaddr_in clientInfo;
    double totalTime = 0;
    int currentRecived = 0;
    int totalBytesRecived = 0;
    socklen_t InfoLen = sizeof(INFO);
//    Await a connection on socket FD.
//    When a connection arrives, open a new socket to communicate with it

    int currSocket = accept(serverSocket, (struct sockaddr *)&INFO, &InfoLen);
    if (currSocket == -1){
        printf("Accept failed!\n");
        close(serverSocket);
        return -1;
    }
    printf("Accept was a sucsses!\n");
    
    // Start measuring time
    clock_t start = clock();
    // Reciving the data from client
    int currentData = 1;
    while(currentData = recv(currSocket, buffer, sizeof(buffer), 0) > 0 ) {
        totalBytesRecived += currentData;
    }
    // Print eror if something went wrong
    if (totalBytesRecived < 0){
        perror("Receiving failed!\n");
    }else if(totalBytesRecived == 0){
        printf("No messages are available to be received!\n");
    }else{
        printf("Recv was sucssesful!\n");
    }
    // Stop timer
    clock_t end = clock();
    if(recevier_chakesum(buffer,0,1) == 0){ // insted the 1 we neet to put ther ruslt of the chake sum from the sender.
        printf("The data is ok!\n");
        totalTime = (double)(end - start) / CLOCKS_PER_SEC;
    }
    // Store the new info so we can get the averege at the end
    if (currentData < 0){
        perror("Receiving");
    }
    
    
    
    currentRecived += 1;
    close(currSocket);

printf("The time is:  %f\n", totalTime);

}

int main(int argc, char const *argv[]){
    char buffer[mb100] = {0};
    // Open socket and get the first 5 sends
    int serverSocket = createSocket();
    int enableReuse = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enableReuse, sizeof(enableReuse)) < 0) { 
        printf("Set faild error code : %d", errno);
    }
    struct sockaddr_in serverInfo,cientInfo;
    int getData = gettingTheData(serverSocket, buffer,serverInfo);
    
    // Change the cc algorithm
  //  int set = setSockOpt(serverSocket,buffer);
    // Now get the last 5 sends
    int getData2 = reciveTheData(serverSocket,buffer,cientInfo);
    
    close(serverSocket);
    return 0;
}


