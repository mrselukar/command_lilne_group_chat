
// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1000

int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    const char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int recvlen,  n = 0 ; 
    socklen_t len = sizeof(servaddr);
  
    
    int i,clients_connected = 0 ; 
    struct sockaddr_in clients[256];  // list of clients in the group chat
   
    while(1) {
                printf("waiting on port %d\n", PORT);
                recvlen = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len); 
                printf("received %d bytes\n", recvlen);
                if (recvlen > 0) 
                    {
                        int cli_index = -1;
                        i=0;
                        for (;i<clients_connected && cli_index == -1;i++)
                        {
                            if (clients[i].sin_port == cliaddr.sin_port)
                            {
                                //Old Client found set the client index variable 
                                cli_index = i;
                            }
                        }
                        if (i == clients_connected && cli_index == -1)
                        {                        
                            // New client identified add copy the address in the clients array
                            memcpy(&clients[i], &cliaddr, sizeof (cliaddr));
                            
                            cli_index = i;
                            clients_connected++;
                        }

                        buffer[recvlen] = '\0';
                        printf("received message: \"%s\" from client %d \n", (char*)buffer, cli_index);
                        //Send this message to all the clients except the sender 
                        for (int j = 0; j < clients_connected ; j++)
                        {
                            if(j != cli_index )
                            {    
                                sendto(sockfd, (char *)buffer, MAXLINE, MSG_CONFIRM, (const struct sockaddr *) &clients[j], len); 
                            }
                            
                        }  
                    }
            }
        /* never exits */
      
    return 0; 
} 