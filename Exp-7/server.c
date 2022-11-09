#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc,char *argv[]){
    int ad,sd;
    struct sockaddr_in servaddr ,cliaddr;
    socklen_t clilen;
    char recvBuffer[8000],sendBuffer[8000];
    pid_t cpid;
    
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(9652);

    sd=socket(AF_INET,SOCK_STREAM,0);
    
    bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sd,5);
    printf("%s\n","Server is running ...");
    
    ad=accept(sd,(struct sockaddr*)&cliaddr,&clilen);

    cpid=fork();
    if(cpid==0)
    {
        while(1)
        {
            bzero(&recvBuffer,sizeof(recvBuffer));
            recv(ad,recvBuffer,sizeof(recvBuffer),0);
            printf("\nCLIENT : %s\n",recvBuffer);
        }
    }
    else{
        while(1){
            bzero(&sendBuffer,sizeof(sendBuffer));
            printf("\nType a message here ...\n");
            fgets(sendBuffer,80000,stdin);
            send(ad,sendBuffer,strlen(sendBuffer)+1,0);
            printf("\nMessage sent!\n");
                }
        }       
    return 0;
}