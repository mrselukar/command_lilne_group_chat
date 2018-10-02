
// Client side implementation  
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <thread> 
#include <chrono>
using namespace std; 
#define MAXLINE 1000
typedef struct sockaddr_in sadr; 

void ip_scanner(int* sockfd_ptr, sadr* cliaddr);

  
void server_listner(int* sockfd_ptr,int PORT, int CLI_PORT)
{	
	//declaring server address
    struct sockaddr_in     servaddr, cliaddr; 
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    
    // Filling clients information 
    cliaddr.sin_family = AF_INET; 
    cliaddr.sin_port = htons(CLI_PORT); 
    cliaddr.sin_addr.s_addr = INADDR_ANY; 
    
    // Binding the socket to the client address
    if ( bind(*sockfd_ptr, (const struct sockaddr *)&cliaddr, sizeof(cliaddr) ) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    int n;
    socklen_t len = sizeof(servaddr);
    char buffer[MAXLINE]; 
 	//Starting the input scanner thread
    thread th2(ip_scanner, sockfd_ptr, &servaddr); 

    while(1)
    {
        //Listinig for messages from the server if received then printing them
        n = recvfrom(*sockfd_ptr, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, (struct sockaddr *) &servaddr, 
                    &len);

        if( n > 0)
        {             
            buffer[n] = '\0'; 
            printf("%s", buffer); 
            
        }
    }
 } 


void ip_scanner(int* sockfd_ptr, sadr* servaddr_ptr)
{
    int n, len, sockfd = *sockfd_ptr; 
    char buffer[MAXLINE]; 
    char message[MAXLINE-100];
    struct sockaddr_in     servaddr = *servaddr_ptr;

    // Initialisation 
    char temp[MAXLINE];
    printf("Enter User-name\n");
    scanf("%s",temp);
    printf("===============================================================\n");
    strcat(temp," :\t");
    char saved_name[MAXLINE];
    strcpy(saved_name,temp);
    strcpy(buffer,temp);
    strcat(buffer," Joined \0");

    
    while(1)
    {
    	// Scans for input and once the i/p is given sends it to the server
    	// adds the clients user name at the start of the message
        fgets(message,MAXLINE-100, stdin);
        strcat(temp,message);
        strcat(buffer, temp);    
        sendto(*sockfd_ptr, (const char *)buffer, strlen(buffer), 
            MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
       
        buffer[0] = '\0';
        strcpy(temp,saved_name);
    }
}

// Driver code 
int main(int argc, char ** argv) { 
    int sockfd; 
	if( argc != 2)
	{
		perror("ERROR: No Port addr specified \n");
		exit(EXIT_FAILURE);
	} 

    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    
    thread th1(server_listner, &sockfd, 8080, atoi(argv[0]));
    

    th1.join(); 
  
    return 0; 
} 
