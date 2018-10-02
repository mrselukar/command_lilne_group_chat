echo "Executing server.out"
echo "Checkinng for executable"
if [ -e "server.out" ]; then
	echo "file found as server.out"
	echo "Executing server.out"
	echo ""
	echo "Starting SErver on port 8080: Start clients using ./client.out <Unique port no>"
	./server.out
else	
	echo "Error: Executable not found "
	echo "Check if server.out exits"
fi
