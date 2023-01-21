#include"tcpserver.h"
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

/**
 * close all sockets when the object is released
 */
TCPServer::~TCPServer(){
    closeSocket(serverSocket);
    for(int a = 0; a < clientSocket.size(); a++){
        closeSocket(clientSocket[a]);
    }
}

/**
 * initialize a TCP server
 */
TCPServer::TCPServer(int port, int backlog){
    this->backlog = backlog;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(port);
}

/**
 * create a socket
 */
int TCPServer::createSocket(){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0){
        cout << "fail to create a socket" << endl;
        exit(EXIT_FAILURE);
    }
    return serverSocket;
}

/**
 * bind the IP address to the socket
 */
void TCPServer::bindSocket(int serverSocket){
    if(bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(sockaddr_in)) < 0){
        cout << "fail to bind the socket " << serverSocket << endl;
        closeSocket(serverSocket);
        exit(EXIT_FAILURE);
    }
}

/**
 * listen to the socket
 */
void TCPServer::listenSocket(int serverSocket){
    if(listen(serverSocket, backlog) < 0){
        cout << "fail to listen the socket " << serverSocket << endl;
        closeSocket(serverSocket);
        exit(EXIT_FAILURE);
    }
}

/**
 * accept a socket
 */
int TCPServer::acceptSocket(int serverSocket){
    socklen_t socketSize = sizeof(sockaddr_in);
    int childSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &socketSize);
    if(childSocket > 0){
        clientSocket.push_back(childSocket);
    }
    return childSocket;
}

/**
 * send a message
 */
int TCPServer::sendMessage(int socket, string& message){
    return send(socket, message.c_str(), message.length(), 0);
}

/**
 * receive a message
 */
int TCPServer::receiveMessage(int socket, char* buffer, int bufferSize){
    memset(buffer, 0, bufferSize);
    return recv(socket, buffer, bufferSize, 0);
}

/**
 * close a socket
 */
void TCPServer::closeSocket(int socket){
    close(socket);
}