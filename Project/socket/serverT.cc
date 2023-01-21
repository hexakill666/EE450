#include"udpclient.h"
#include"udpserver.h"
#include"numberutil.h"
#include"iohandler.h"
#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

int main(int arvc, char* argv[]){

    // server pot
    int lastThreeDigit = NumberUtil::lastThreeDigit(1234567124);
    int udpPortT = 21000 + lastThreeDigit;
    int udpPortC = 24000 + lastThreeDigit;
    // topology map
    unordered_map<string, vector<string>> graph = IOHandler::readEdge();

    // buffer
    const int bufferSize = 8192;
    char* bufferC = new char[bufferSize];

    // initialize a UDP server and client
    UDPServer* udpServerP = new UDPServer(udpPortT);
    UDPClient* udpClientC = new UDPClient(udpPortC);

    // create and bind the socket
    int udpSocketP = udpServerP->createSocket();
    udpServerP->bindSocket(udpSocketP);

    // create the socket
    int udpSocketC = udpClientC->createSocket();

    cout << "The ServerT is up and running using UDP on port " << udpPortT << "." << endl;
    while (true){
        // receive the message from central
        int receiveResult = udpServerP->receiveMessage(udpSocketP, bufferC, bufferSize);
        if(receiveResult < 0){
            cout << "fail to receive a message from the server socket " << udpSocketP << endl;
            continue;
        }
        cout << "The ServerT received a request from Central to get the topology." << endl;

        // graph string
        string graphStr = IOHandler::getGraphStr(graph);
        // cout << "graphStr: " << graphStr << endl;

        // send the graph string to central
        int sendResult = udpClientC->sendMessage(udpSocketC, graphStr);
        if(sendResult < 0){
            cout << "fail to send a message to the socket " << udpSocketC << endl;
            continue;
        }
        cout << "The ServerT finished sending the topology to Central." << flush;
    }
    
    // release buffer memory
    delete [] bufferC;
    // release server and client memory, and close the socket
    delete udpServerP;
    delete udpClientC;

}