#include"udpserver.h"
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

/**
 * close all sockets when the object is released
 */
UDPServer::~UDPServer(){
    closeSocket(serverSocket);
}

/**
 * initialize a UDP server
 */
UDPServer::UDPServer(int port){
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(port);
}

/**
 * create a socket
 */
int UDPServer::createSocket(){
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(serverSocket < 0){
        cout << "fail to create a socket" << endl;
        exit(EXIT_FAILURE);
    }
    return serverSocket;
}

/**
 * bind the IP address to the socket
 */
void UDPServer::bindSocket(int serverSocket){
    if(bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(sockaddr_in)) < 0){
        cout << "fail to bind the socket " << serverSocket << endl;
        closeSocket(serverSocket);
        exit(EXIT_FAILURE);
    }
}

/**
 * send a message
 */
int UDPServer::sendMessage(int socket, string& message){
    return sendto(socket, message.c_str(), message.length(), 0, (struct sockaddr *) &clientAddress, sizeof(sockaddr_in));
}

/**
 * receive a message
 */
int UDPServer::receiveMessage(int socket, char* buffer, int bufferSize){
    memset(buffer, 0, bufferSize);
    socklen_t socketSize = sizeof(sockaddr_in);
    return recvfrom(socket, buffer, bufferSize, 0, (struct sockaddr *) &clientAddress, &socketSize);
}

/**
 * close a socket
 */
void UDPServer::closeSocket(int socket){
    close(socket);
}