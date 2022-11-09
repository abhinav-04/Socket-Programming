#include<stdio.h> 
#include<string.h> 
#include<sys/socket.h> 
#include<sys/types.h> 
#include<unistd.h> 
#include<netinet/in.h> 
#include<netdb.h> 
#include<arpa/inet.h> 
#include<stdlib.h>
int main(int argc,char * argv[]) 
{ 
int sd; 
char buff[1024]; 
struct sockaddr_in cliaddr,servaddr; 
socklen_t len;
len = sizeof(servaddr);
	/*This function looks up a hostname and it returns a pointer to a hostent  
           structure that contains all the IPV4 address*/   


           /*Creating a socket, assigning IP address and port number for that socket*/ 
sd = socket(AF_INET,SOCK_DGRAM,0); 

bzero(&servaddr,sizeof(servaddr));

/*Socket address structure*/
servaddr.sin_family = AF_INET; 
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(1999); 

            /*Connect establishes connection with the server using server IP address*/
//cd=connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)); 
while(1) { 
    printf("Enter the message: \n"); 
    bzero(buff,sizeof(buff));
    /*Reads the message from standard input*/
    fgets(buff,sizeof(buff),stdin); 
    if (sendto(sd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,len)<0){
        perror("Cannot send data to client");
        exit(1);
    }
    printf("Sent data to UDP Server : %s",buff);
    bzero(buff,sizeof(buff));
    
    if (recvfrom(sd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,&len)<0){
        perror("Cannot rec data");
        exit(1);
    }
    printf("Received data from server : %s",buff);
                 /*Send function is used on client side to send data given by user on client
                 side to the server*/                          
     
} 
close(sd);
return 0;
}