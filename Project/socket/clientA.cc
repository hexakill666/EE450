#include"tcpclient.h"
#include"numberutil.h"
#include"iohandler.h"
#include<iostream>
#include<limits>
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){

    // server port
    int tcpPortC = 25000 + NumberUtil::lastThreeDigit(1234567124);
    // input
    string message = argv[1];
    
    // buffer
    const int bufferSize = 8192;
    char* bufferC = new char[bufferSize];

    // initialize a TCP client
    TCPClient* tcpClientC = new TCPClient(tcpPortC);
    // create a socket
    int clientSocket = tcpClientC->createSocket();
    // connect a socket
    tcpClientC->connectSocket(clientSocket);


    cout << "The client is up and running." << endl;
    // send the input to central
    int sendResult = tcpClientC->sendMessage(clientSocket, message);
    if(sendResult < 0){
        cout << "fail to send a message from socket " << clientSocket << endl;
        exit(EXIT_FAILURE);
    }
    cout << "The client sent " << message << " to the Central server." << endl;
    

    // receive the result string from central
    int receiveResult1 = tcpClientC->receiveMessage(clientSocket, bufferC, bufferSize);
    if(receiveResult1 < 0){
        cout << "fail to receive a message from socket " << clientSocket << endl;
        exit(EXIT_FAILURE);
    }
    string resultStr = bufferC;
    // cout << "resultStr: " << resultStr << endl;


    // seperate the result string
    int index = resultStr.find("+");
    string resultPairStr1 = resultStr.substr(0, index);
    string resultPairStr2 = resultStr.substr(index + 1);
    // parse result string
    pair<vector<string>, double> resultPair1 = IOHandler::parseResultStr(resultPairStr1);
    // if it has no path
    if(resultPair1.second == numeric_limits<double>::max()){
        cout << "Found no compatibility for " << resultPair1.first[0] << " and " << resultPair1.first[1] << endl;
    }
    // if it has a path
    else{
        cout << "Found compatibility for " << resultPair1.first[0] << " and " << resultPair1.first[1] << ":" << endl;
        cout << resultPair1.first[2] << endl;
        cout << "Matching Gap : " << fixed << setprecision(2) << resultPair1.second;
    }
    // if clientB has the second input
    if(resultPairStr2 != "NOINPUT"){
        // parse result string
        pair<vector<string>, double> resultPair2 = IOHandler::parseResultStr(resultPairStr2);
        // if it has no path
        if(resultPair2.second == numeric_limits<double>::max()){
            cout << "Found no compatibility for " << resultPair2.first[0] << " and " << resultPair2.first[1] << endl;
        }
        // if it has a path
        else{
            cout << "Found compatibility for " << resultPair2.first[0] << " and " << resultPair2.first[1] << ":" << endl;
            cout << resultPair2.first[2] << endl;
            cout << "Matching Gap : " << fixed << setprecision(2) << resultPair2.second;
        }
    }

    // release buffer memoery
    delete [] bufferC;
    // release TCP client memory, and close the socket
    delete tcpClientC;

}