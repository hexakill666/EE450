#pragma once
#include<netinet/in.h>
#include<string>
#include<vector>

using namespace std;

class TCPServer{
    private:
        int serverSocket;
        vector<int> clientSocket;
        int backlog;
        sockaddr_in serverAddress, clientAddress;
        
    public:
        TCPServer(int port, int backlog);
        ~TCPServer();
        int createSocket();
        void bindSocket(int serverSocket);
        void listenSocket(int serverSocket);
        int acceptSocket(int serverSocket);
        int sendMessage(int socket, string& message);
        int receiveMessage(int socket, char* buffer, int bufferSize);
        void closeSocket(int socket);
};