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
#include <stdio.h>
#include <stdlib.h>
// gist: In this class we want to send the data we have in a txt file. The process is:
// Step 1: creat and set a socket
// Step 2: Connect to the server.
// Step 3: Open the file we want to send.
// Step 4: Send the data.
// Mission: invastigate the difrences between them.


//#define size 1024
#define size 1024
#define port 9090
#define serverIp "127.0.0.1"
#define fileName "100mb.txt"
#define MEGA_BYTE100 104857600 //  Allocate 100 MB memory block 

int sendingPacketWithoutSpoofing(int socket ,FILE* myfile, char* buffer);
int setTCPOpt(int socket , char * buffer);
int createSocket();
int createfile();


int* GenerateMemoryBlock()
{
    time_t t;
    // intializes random number generator
    srand((unsigned) time(&t));

   int* pBytes = malloc(sizeof(int) * MEGA_BYTE100);
   if (!pBytes){
     perror("Set failed:\n");
   }

   for( int Index = 0; Index < MEGA_BYTE100; ++Index )
   {
      pBytes[ Index ] = ( int ) rand();
   }

   return pBytes;
}

void create100MBBinaryFile()
{
    // open file.
    FILE * myfile = fopen(fileName, "rb");

    if(myfile == NULL) {
        perror("fopen faild!\n");
        return -1;
    }

   // Get data.
   int* pData = GenerateMemoryBlock();

   // Write 100 MB data 1000 times.
   for( int Index = 0; Index < 1000; ++Index )
   {fprintf(myfile,)

      myfile.write( (const int*)pData, MEGA_BYTE );
   }

   free(pData);

}
int createSocket(){
    // returns zero if the creation was secssesuful and -1 if not.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("Creation failed!\n");
        return -1;
    }
    printf("Socket created!\n");
    return sock;
}

int setTCPOpt(int socket , char * buffer){
    // Specify the wanted socket option name(we want TCP).
    socklen_t length = sizeof(buffer);
    int socketOpt = setsockopt(socket, IPPROTO_TCP, TCP_CONGESTION, buffer, strlen(buffer));
    if( socketOpt != 0) {
        perror("Set failed:\n");
        return -1;
    }
    if (getsockopt(socket, IPPROTO_TCP, TCP_CONGESTION, buffer, &length) != 0) {
        perror("Get failed:\n"); 
        return -1;
    }
    printf("Set sucsseded! Algorithm changed to: %s\n", buffer);
    return socketOpt;
}


int sendingPacketWithoutSpoofing(int socket ,FILE* myfile, char* buffer){
    
    // This part taken from the tirgul slideshow("Packet Sniffing and Spoofing", page 16).
    struct sockaddr_in dest_info;
    // memset(&dest_info, 0, sizeof(dest_info));
    bzero(&dest_info, sizeof(dest_info));
    dest_info.sin_family = AF_INET;
    // dest_info.sin_addr.s_addr = INADDR_ANY;
    dest_info.sin_port = htons(port);
    // Converts an Internet address in its standard text format into its numeric binary form.
    if(inet_pton(AF_INET, (const char*)serverIp, &dest_info.sin_addr) <= 0) { 
        printf("Converting to binary failed!\n"); 
        return -1;
    }
        
    //connecting to the server
    int connection = connect(socket, (struct sockaddr*)&dest_info, sizeof(dest_info));
    if(connection < 0){
        perror("Connectiong faild!\n");
        return -1;
    }
    printf("Connected to server!\n");

    // Openning the file we want to send
    
    myfile = fopen(fileName, "rb");

    if(myfile == NULL) {
        perror("fopen faild!\n");
        return -1;
    }

    int segmentsCounter = 0;
    int total = 0;
    int read = 0;
    bzero(buffer, size);
    printf("Start sending");
    while(read = fread(buffer, 1, sizeof(buffer), myfile) > 0 ){
        int dataSent = send(socket, buffer, read, 0);
        if (dataSent == 0 || dataSent == -1){
            printf("problem with the sed func: The buffer is full || The TCP connection is closed!");
        }else if(read > dataSent){
            printf("Only part of the data were sent\n");
        }
        segmentsCounter += 1;
        total += dataSent;
    }
    printf("%d bytes were sent by %d segments.\n", total, segmentsCounter);
    fclose(myfile);

    return 0;
}

int main(int argc, char const *argv[]){

    int numOfSends = 7;
    int currentSended = 0;
    FILE *file_Name;
    while (currentSended < numOfSends){
        char buffer[size] ={0};
        int socket = createSocket();
        int send = sendingPacketWithoutSpoofing(socket,file_Name,buffer,0);
        close(socket);
        currentSended += 1;
    }

    return 0;
}
