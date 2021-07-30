
All: server.o client.o

server.o:
	g++ -std=c++11 -o Server Server.cpp -pthread
client.o: 
	g++ -std=c++11 -o Client Client.cpp -pthread
