echo "Compile script for Assignment 1 TOC"
echo "Checkinng for source code"
if [ -e "server_final.c" ]; then
	echo "Source found as server_final.c"
	gcc server_final.c -o server.out
	echo "Server Compilation done"
	
else	
	echo "Error: Source code for server not found"
fi

if [ -e "client_final.cpp" ]; then
	echo "Source found as client_final.c"
	g++ client_final.cpp -std=c++11 -pthread -o client.out
	echo "client Compilation done"
	
else	
	echo "Error: Source code for client not found"
fi
