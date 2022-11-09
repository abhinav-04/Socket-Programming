#include<stdio.h>
#include<unistd.h>
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<netdb.h> 
#include<arpa/inet.h> 
#include<string.h>
#include<stdlib.h>
int main(int asrgc,char*argv[]) 
{ 
int sd; 
char buff[1024]; 
struct sockaddr_in cliaddr,servaddr; 
socklen_t clilen; 
clilen=sizeof(cliaddr); 

           /*Socket address structure*/ 

/*TCP socket is created, an Internet socket address structure is filled with wildcard address & server’s well known port*/   
sd=socket(AF_INET,SOCK_DGRAM,0); 
if(sd<0){
    perror("Cannot open Socket");
    exit(1);
}

bzero(&servaddr,sizeof(servaddr));

servaddr.sin_family=AF_INET; 
servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
servaddr.sin_port=htons(1999);

          /*Bind function assigns a local protocol address to the socket*/
//bd=bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)); 

/*Listen function specifies the maximum number of connections that kernel should queue for this socket*/
if(bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
    perror("Cannoy open Socket");
    exit(1);
}
printf("%s","Server is running...\n");
while(1){
    bzero(&buff,sizeof(buff));
    
    if (recvfrom(sd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,&clilen)<0){
        perror("Cannot rec data");
        exit(1);
    }
    printf("Message received is : %s",buff);
    
    if (sendto(sd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,clilen)<0){
        perror("Cannot send data to client");
        exit(1);
    }
    printf("Sent data to UDP Client : %s",buff);
    
}
close(sd);
return 0;
}
