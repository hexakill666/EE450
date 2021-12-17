#pragma once
#include<netinet/in.h>
#include<string>

using namespace std;

class TCPClient{
    private:
        int clientSocket;
        sockaddr_in serverAddress;

    public:
        TCPClient(int serverPort);
        ~TCPClient();
        int createSocket();
        void connectSocket(int clientSocket);
        int sendMessage(int socket, string& message);
        int receiveMessage(int socket, char* buffer, int bufferSize);
        void closeSocket(int socket);
};