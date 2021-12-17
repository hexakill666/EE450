#include"udpclient.h"
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

/**
 * close all sockets when the object is released
 */
UDPClient::~UDPClient(){
    closeSocket(clientSocket);
}

/**
 * initialize a UDP client
 */
UDPClient::UDPClient(int port){
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(port);
}

/**
 * create a socket
 */
int UDPClient::createSocket(){
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(clientSocket < 0){
        cout << "fail to create a socket" << endl;
        exit(EXIT_FAILURE);
    }
    return clientSocket;
}

/**
 * send a message
 */
int UDPClient::sendMessage(int socket, string& message){
    return sendto(socket, message.c_str(), message.size(), 0, (struct sockaddr *) &serverAddress, sizeof(sockaddr_in));
}

/**
 * receive a message
 */
int UDPClient::receiveMessage(int socket, char* buffer, int bufferSize){
    memset(buffer, 0, bufferSize);
    socklen_t socketSize = sizeof(sockaddr_in);
    return recvfrom(socket, buffer, bufferSize, 0, (struct sockaddr *) &serverAddress, &socketSize);
}

/**
 * close a socket
 */
void UDPClient::closeSocket(int socket){
    close(socket);
}