#include"udpclient.h"
#include"udpserver.h"
#include"tcpserver.h"
#include"numberutil.h"
#include"iohandler.h"
#include<iostream>

using namespace std;

int main(int argc, char* argv[]){

    // all ports
    int lastThreeDigit = NumberUtil::lastThreeDigit(1234567124);
    int tcpPortA = 25000 + lastThreeDigit;
    int tcpPortB = 26000 + lastThreeDigit;
    int udpPortT = 21000 + lastThreeDigit;
    int udpPortS = 22000 + lastThreeDigit;
    int udpPortP = 23000 + lastThreeDigit;
    int udpPortC = 24000 + lastThreeDigit;

    // buffer
    const int bufferSize = 8192;
    char* bufferA = new char[bufferSize];
    char* bufferB = new char[bufferSize];
    char* bufferT = new char[bufferSize];
    char* bufferS = new char[bufferSize];
    char* bufferP = new char[bufferSize];

    // initializtion
    TCPServer* tcpServerA = new TCPServer(tcpPortA, 10);
    TCPServer* tcpServerB = new TCPServer(tcpPortB, 10);
    UDPClient* udpClientT = new UDPClient(udpPortT);
    UDPClient* udpClientS = new UDPClient(udpPortS);
    UDPClient* udpClientP = new UDPClient(udpPortP);
    UDPServer* udpServerC = new UDPServer(udpPortC);

    // create, bind and listen to the socket
    int tcpSocketA = tcpServerA->createSocket();
    tcpServerA->bindSocket(tcpSocketA);
    tcpServerA->listenSocket(tcpSocketA);

    // create, bind and listen to the socket
    int tcpSocketB = tcpServerB->createSocket();
    tcpServerB->bindSocket(tcpSocketB);
    tcpServerB->listenSocket(tcpSocketB);

    // create the socket
    int udpSocketT = udpClientT->createSocket();
    int udpSocketS = udpClientS->createSocket();
    int udpSocketP = udpClientP->createSocket();

    // create and bind the socket
    int udpSocketC = udpServerC->createSocket();
    udpServerC->bindSocket(udpSocketC);
    
    // message
    string messageClient;
    string messageA;
    string messageB;
    string messageT;
    string messageS;
    string messageP;
    
    cout << "The Central server is up and running." << endl;
    while(true){
        // accept clientA
        int childSocketA = tcpServerA->acceptSocket(tcpSocketA);
        if(childSocketA < 0){
            cout << "fail to accept a socket from the server socket " << tcpSocketA << endl;
            continue;
        }
        // receive the message from clientA
        int receiveResultA = tcpServerA->receiveMessage(childSocketA, bufferA, bufferSize);
        if(receiveResultA < 0){
            cout << "fail to receive a message from the child socket " << childSocketA << endl;
            continue;
        }
        // clientA message
        messageA = bufferA;
        cout << "The Central server received input=" << bufferA << " from the client using TCP over port " << tcpPortA << "." << endl;


        // accept clientB
        int childSocketB = tcpServerB->acceptSocket(tcpSocketB);
        if(childSocketB < 0){
            cout << "fail to accept a socket from the server socket " << tcpSocketB << endl;
            continue;
        }
        // receive the message from clientB
        int receiveResultB = tcpServerB->receiveMessage(childSocketB, bufferB, bufferSize);
        if(receiveResultB < 0){
            cout << "fail to receive a message from the child socket " << childSocketB << endl;
            continue;
        }
        // clientB message
        messageB = bufferB;
        string messageBPrint = messageB.find("_") == string::npos ? messageB : messageB.substr(0, messageB.find("_")) + " " + messageB.substr(messageB.find("_") + 1);
        cout << "The Central server received input=" << messageBPrint << " from the client using TCP over port " << tcpPortB << "." << endl;


        // client message
        messageClient = messageA + "_" + messageB;
        vector<string> resultList;
        vector<string> nameList = IOHandler::parseClientStr(messageClient);
        for(int a = 1; a < nameList.size(); a++){
            messageClient = nameList[0] + "_" + nameList[a];
            // send client message to serverT
            int sendResultT = udpClientT->sendMessage(udpSocketT, messageClient);
            if(sendResultT < 0){
                cout << "fail to send a message to the socket " << udpSocketT << endl;
                continue;
            }
            cout << "The Central server sent a request to Backend-Server T." << endl;
            // receive the message from serverT
            int receiveResultT = udpServerC->receiveMessage(udpSocketC, bufferT, bufferSize);
            if(receiveResultT < 0){
                cout << "fail to receive a message from the socket " << udpSocketC << endl;
                continue;
            }
            // serverT message
            messageT = bufferT;
            // cout << "messageT: " << messageT << endl;
            cout << "The Central server received information from Backend-Server T using UDP over port " << udpPortC << "." << endl;


            // send serverT messge to serverS
            int sendResultS = udpClientS->sendMessage(udpSocketS, messageT);
            if(sendResultS < 0){
                cout << "fail to send a message to the socket " << udpSocketS << endl;
                continue;
            }
            cout << "The Central server sent a request to Backend-Server S." << endl;
            // receive the message from serverS
            int receiveResultS = udpServerC->receiveMessage(udpSocketC, bufferS, bufferSize);
            if(receiveResultS < 0){
                cout << "fail to receive a message from the socket " << udpSocketC << endl;
                continue;
            }
            // serverS message
            messageS = bufferS;
            // cout << "messageS: " << messageS << endl;
            cout << "The Central server received information from Backend-Server S using UDP over port " << udpPortC << "." << endl;


            // send client message to serverP
            int sendResultPClient = udpClientP->sendMessage(udpSocketP, messageClient);
            if(sendResultPClient < 0){
                cout << "fail to send a message to the socket " << udpSocketP << endl;
                continue;
            }
            // send serverT message to serverP
            int sendResultPT = udpClientP->sendMessage(udpSocketP, messageT);
            if(sendResultPT < 0){
                cout << "fail to send a message to the socket " << udpSocketP << endl;
                continue;
            }
            // send serverS message to serverP
            int sendResultPS = udpClientP->sendMessage(udpSocketP, messageS);
            if(sendResultPS < 0){
                cout << "fail to send a message to the socket " << udpSocketP << endl;
                continue;
            }
            cout << "The Central server sent a processing request to Backend-Server P." << endl;
            // receive the message from serverP
            int receiveResultP = udpServerC->receiveMessage(udpSocketC, bufferP, bufferSize);
            if(receiveResultP < 0){
                cout << "fail to receive a message from the socket " << udpSocketC << endl;
                continue;
            }
            // serverP message
            messageP = bufferP;
            // cout << "messageP: " << messageP << endl;
            cout << "The Central server received the results from backend server P." << endl;
            
            
            resultList.push_back(messageP);
        }


        // result string
        string resultStr;
        for(int a = 0; a < resultList.size(); a++){
            resultStr += resultList[a];
            if(a != resultList.size() - 1){
                resultStr += "+";
            }
        }
        resultStr += resultList.size() < 2 ? "+NOINPUT" : "";


        // send serverP message to clientA
        int sendResultA = tcpServerA->sendMessage(childSocketA, resultStr);
        if(sendResultA < 0){
            cout << "fail to send a message to the socket " << childSocketA << endl;
            continue;
        }
        cout << "The Central server sent the results to client A." << endl;
        // send serverP message to clientB
        int sendResultB = tcpServerB->sendMessage(childSocketB, resultStr);
        if(sendResultB < 0){
            cout << "fail to send a message to the socket " << childSocketB << endl;
            continue;
        }
        cout << "The Central server sent the results to client B." << flush;
    }

    // release buffer memeory
    delete [] bufferA;
    delete [] bufferB;
    delete [] bufferT;
    delete [] bufferS;
    delete [] bufferP;
    // release server and client memeory, and close all sockets
    delete tcpServerA;
    delete tcpServerB;
    delete udpClientT;
    delete udpClientS;
    delete udpClientP;
    delete udpServerC;

}