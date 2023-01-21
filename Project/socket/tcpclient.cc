#include"tcpclient.h"
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

/**
 * close all sockets when the object is released
 */
TCPClient::~TCPClient(){
    closeSocket(clientSocket);
}

/**
 * initialize a TCP client
 */
TCPClient::TCPClient(int serverPort){
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(serverPort);
}

/**
 * create a socket
 */
int TCPClient::createSocket(){
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
        cout << "fail to create a socket" << endl;
        exit(EXIT_FAILURE);
    }
    return clientSocket;
}

/**
 * connect to a socket
 */
void TCPClient::connectSocket(int clientSocket){
    if(connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
        cout << "fail to connect the server from socket " << clientSocket << endl;
        closeSocket(clientSocket);
        exit(EXIT_FAILURE);
    }
}

/**
 * send a message
 */
int TCPClient::sendMessage(int socket, string& message){
    return send(socket, message.c_str(), message.length(), 0);
}

/**
 * receive a message
 */
int TCPClient::receiveMessage(int socket, char* buffer, int bufferSize){
    memset(buffer, 0, bufferSize);
    return recv(socket, buffer, bufferSize, 0);
}

/**
 * close a socket
 */
void TCPClient::closeSocket(int socket){
    close(socket);
}