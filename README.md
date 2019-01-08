# command_line_group_chat
Simple command line group chat application. Implements the UDP Socket protocol and is able to host 256 unique clients 

NOTE:
## The server is hard coded to run of the port 8080

The server code is in c
To compile
gcc server_final.c -o server.out

To run 
./server.out


The client code uses threads so is CPP
To compile
g++ client_final.cpp -std=c++11 -pthread -o client.out

To Run 
./client.out < Unique port no of the client>
