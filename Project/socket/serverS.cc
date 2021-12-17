#include"udpclient.h"
#include"udpserver.h"
#include"numberutil.h"
#include"iohandler.h"
#include<iostream>
#include<unordered_map>
#include<unordered_set>

using namespace std;

int main(int arvc, char* argv[]){

    // server port
    int lastThreeDigit = NumberUtil::lastThreeDigit(1234567124);
    int udpPortS = 22000 + lastThreeDigit;
    int udpPortC = 24000 + lastThreeDigit;
    // score map
    unordered_map<string, int> scoreMap = IOHandler::readScore();

    // buffer
    const int bufferSize = 8192;
    char* bufferC = new char[bufferSize];

    // initialize a UDP server and client
    UDPServer* udpServerS = new UDPServer(udpPortS);
    UDPClient* udpClientC = new UDPClient(udpPortC);

    // create and bind the socket
    int udpSocketS = udpServerS->createSocket();
    udpServerS->bindSocket(udpSocketS);

    // create the socket
    int udpSocketC = udpClientC->createSocket();

    cout << "The ServerS is up and running using UDP on port " << udpPortS <<  "."  << endl;
    while (true){
        // receive the message from central
        int receiveResult = udpServerS->receiveMessage(udpSocketS, bufferC, bufferSize);
        if(receiveResult < 0){
            cout << "fail to receive a message from the server socket " << udpSocketS << endl;
            continue;
        }
        cout << "The ServerS received a request from Central to get the scores." << endl;

        // score string
        string scoreStr = IOHandler::getScoreStr(scoreMap);
        // cout << "scoreStr: " << scoreStr << endl;
        
        // send the score string to central
        int sendResult = udpClientC->sendMessage(udpSocketC, scoreStr);
        if(sendResult < 0){
            cout << "fail to send a message to the socket " << udpSocketC << endl;
            continue;
        }
        cout << "The ServerS finished sending the scores to Central." << flush;
    }
    
    // release buffer memory
    delete [] bufferC;
    // release server and client memory, and close the socket
    delete udpServerS;
    delete udpClientC;

}