#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
int main()
{
    int sd;
    struct sockaddr_in servaddr;
    char sendBuffer[8000],recvBuffer[8000];
    pid_t cpid;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(9652);
    /*Creating a socket, assigning IP address and port number for that socket*/
    sd=socket(AF_INET,SOCK_STREAM,0);
    /*Connect establishes connection with the server using server IP address*/
    connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    /*Fork is used to create a new process*/
    cpid=fork();
    if(cpid==0)
    {
        while(1)
        {
            bzero(&sendBuffer,sizeof(sendBuffer));
            printf("\nType a message here ...\n");
            /*This function is used to read from server*/
            fgets(sendBuffer,80000,stdin);
            
            /*Send the message to server*/
            send(sd,sendBuffer,strlen(sendBuffer)+1,0);
            printf("\nMessage sent!\n");
            
        }
    }
    else
    {
        while(1)
        {      
            bzero(&recvBuffer,sizeof(recvBuffer));
            /*Receive the message from server*/
            recv(sd,recvBuffer,sizeof(recvBuffer),0);
            printf("\nSERVER : %s\n",recvBuffer);
        }
    }
    return 0;
}   