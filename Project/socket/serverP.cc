#include"udpclient.h"
#include"udpserver.h"
#include"numberutil.h"
#include"iohandler.h"
#include"graph.h"
#include<iostream>
#include<limits>

using namespace std;

int main(int arvc, char* argv[]){

    // server port
    int lastThreeDigit = NumberUtil::lastThreeDigit(1234567124);
    int serverPort = 23000 + lastThreeDigit;
    int udpPortC = 24000 + lastThreeDigit;

    // buffer
    const int bufferSize = 8192;
    char* bufferC = new char[bufferSize];

    // initialize a UDP server
    UDPServer* udpServerP = new UDPServer(serverPort);
    UDPClient* udpClientC = new UDPClient(udpPortC);

    // create and bind the socket
    int udpPortP = udpServerP->createSocket();
    udpServerP->bindSocket(udpPortP);

    // create the socket
    int udpSocketC = udpClientC->createSocket();

    Graph graph;
    string messageClient, graphStr, scoreStr;
    cout << "The ServerP is up and running using UDP on port " << serverPort << "." << endl;
    while (true){
        // receive the message from central
        int receiveResult1 = udpServerP->receiveMessage(udpPortP, bufferC, bufferSize);
        if(receiveResult1 < 0){
            cout << "fail to receive a message from the server socket " << udpPortP << endl;
            continue;
        }
        // client message
        messageClient = bufferC;
        // receive the message from central
        int receiveResult2 = udpServerP->receiveMessage(udpPortP, bufferC, bufferSize);
        if(receiveResult2 < 0){
            cout << "fail to receive a message from the server socket " << udpPortP << endl;
            continue;
        }
        // graph string
        graphStr = bufferC;
        // receive the message from central
        int receiveResult3 = udpServerP->receiveMessage(udpPortP, bufferC, bufferSize);
        if(receiveResult3 < 0){
            cout << "fail to receive a message from the server socket " << udpPortP << endl;
            continue;
        }
        // score string
        scoreStr = bufferC;
        cout << "The ServerP received the topology and score information." << endl;


        string resultStr;
        string nodeDelimiter = "_";
        // name list
        vector<string> nameList = IOHandler::parseClientStr(messageClient);
        // node id map
        unordered_map<string, int> nodeIdMap = graph.getNodeIdMap(graphStr);
        // graph map
        unordered_map<string, vector<string>> graphMap = graph.parseGraphStr(graphStr);
        // score map
        unordered_map<string, int> scoreMap = graph.parseScoreStr(scoreStr);
        // find the shortest path
        pair<vector<double>, vector<string>> resultPair = graph.dijkstra(nodeIdMap, graphMap, scoreMap, nameList[0], nameList[1]);
        // create path string
        pair<string, string> pathPair = graph.createPath(resultPair, nodeIdMap, nameList[0], nameList[1]);
        // get result string
        resultStr = nameList[0] + nodeDelimiter + nameList[1] + nodeDelimiter + pathPair.first + nodeDelimiter + pathPair.second + nodeDelimiter + to_string(resultPair.first[nodeIdMap[nameList[1]]]);
        // cout << "resultStr: " << resultStr << endl;


        // send result string to central
        int sendResult = udpClientC->sendMessage(udpSocketC, resultStr);
        if(sendResult < 0){
            cout << "fail to send a message to the socket " << udpSocketC << endl;
            continue;
        }
        cout << "The ServerP finished sending the results to the Central." << flush;
    }
    
    // release buffer memory
    delete [] bufferC;
    // release server and client memory, and close the socket
    delete udpServerP;
    delete udpClientC;

}