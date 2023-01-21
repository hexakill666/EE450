#pragma once
#include<netinet/in.h>
#include<string>

using namespace std;

class UDPServer{
    private:
        int serverSocket;
        sockaddr_in serverAddress, clientAddress;
        
    public:
        UDPServer(int port);
        ~UDPServer();
        int createSocket();
        void bindSocket(int serverSocket);
        int sendMessage(int socket, string& message);
        int receiveMessage(int socket, char* buffer, int bufferSize);
        void closeSocket(int socket);
};