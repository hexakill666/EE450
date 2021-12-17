#pragma once
#include<netinet/in.h>
#include<string>

using namespace std;

class UDPClient{
    private:
        int clientSocket;
        sockaddr_in serverAddress;
        
    public:
        UDPClient(int port);
        ~UDPClient();
        int createSocket();
        int sendMessage(int socket, string& message);
        int receiveMessage(int socket, char* buffer, int bufferSize);
        void closeSocket(int socket);
};