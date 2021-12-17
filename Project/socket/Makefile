permit = sudo
cc = g++
flag = -std=c++11


all : clientA.o clientB.o serverT.o serverS.o serverP.o central.o tcpclient.o tcpserver.o udpclient.o udpserver.o numberutil.o iohandler.o graph.o
	$(permit) $(cc) $(flag) clientA.o tcpclient.o numberutil.o iohandler.o -o clientA
	$(permit) $(cc) $(flag) clientB.o tcpclient.o numberutil.o iohandler.o -o clientB
	$(permit) $(cc) $(flag) serverT.o udpclient.o udpserver.o numberutil.o iohandler.o -o serverT
	$(permit) $(cc) $(flag) serverS.o udpclient.o udpserver.o numberutil.o iohandler.o -o serverS
	$(permit) $(cc) $(flag) serverP.o udpclient.o udpserver.o numberutil.o iohandler.o graph.o -o serverP
	$(permit) $(cc) $(flag) central.o tcpserver.o udpclient.o udpserver.o numberutil.o iohandler.o -o serverC
	$(permit) chmod -R 777 *

clientA.o : clientA.cc
	$(permit) $(cc) $(flag) -c clientA.cc

clientB.o : clientB.cc
	$(permit) $(cc) $(flag) -c clientB.cc

serverT.o : serverT.cc
	$(permit) $(cc) $(flag) -c serverT.cc

serverS.o : serverS.cc
	$(permit) $(cc) $(flag) -c serverS.cc

serverP.o : serverP.cc
	$(permit) $(cc) $(flag) -c serverP.cc

central.o : central.cc
	$(permit) $(cc) $(flag) -c central.cc

tcpclient.o : tcpclient.cc
	$(permit) $(cc) $(flag) -c tcpclient.cc

tcpserver.o : tcpserver.cc
	$(permit) $(cc) $(flag) -c tcpserver.cc

udpclient.o : udpclient.cc
	$(permit) $(cc) $(flag) -c udpclient.cc

udpserver.o : udpserver.cc
	$(permit) $(cc) $(flag) -c udpserver.cc

numberutil.o : numberutil.cc
	$(permit) $(cc) $(flag) -c numberutil.cc

iohandler.o : iohandler.cc
	$(permit) $(cc) $(flag) -c iohandler.cc

graph.o : graph.cc
	$(permit) $(cc) $(flag) -c graph.cc

test : test.cc iohandler.o graph.o
	$(permit) $(cc) $(flag) test.cc iohandler.o graph.o -o test

clean:
	$(permit) rm -rf *.o *.out clientA clientB serverT serverS serverP serverC test