#include"graph.h"
#include<math.h>
#include<queue>
#include<limits>
#include<iostream>

using namespace std;

/**
 * based on the graph string, create a node id map
 */
unordered_map<string, int> Graph::getNodeIdMap(string& graphStr){
    string chainDelimiter = ">";
    string nodeDelimiter = "_";
    unordered_map<string, int> nodeIdMap;
    vector<string> nodeChain;
    
    int nameIndex = 0, nodeIndex = 0;
    while((nodeIndex = graphStr.find(nodeDelimiter, nameIndex)) > 0){
        nodeChain.push_back(graphStr.substr(nameIndex, nodeIndex - nameIndex));
        nameIndex = nodeIndex + 1;
    }
    nodeChain.push_back(graphStr.substr(nameIndex));

    int id = 0;
    for(string chain : nodeChain){
        string name;
        int chainIndex = 0, nameIndex = 0;
        while((chainIndex = chain.find(chainDelimiter, nameIndex)) > 0){
            name = chain.substr(nameIndex, chainIndex - nameIndex);
            if(!nodeIdMap.count(name)){
                nodeIdMap[name] = id++;
            }
            nameIndex = chainIndex + 1;
        }
        name = chain.substr(nameIndex);
        if(!nodeIdMap.count(name)){
            nodeIdMap[name] = id++;
        }
    }

    return nodeIdMap;
}

/**
 * based on the graphStr string, create a graphStr map
 */
unordered_map<string, vector<string>> Graph::parseGraphStr(string& graphStr){
    unordered_map<string, vector<string>> graph;
    vector<string> chainList;
    string chainDelimiter = ">";
    string nodeDelimiter = "_";

    int nameIndex = 0, nodeIndex = 0;
    while((nodeIndex = graphStr.find(nodeDelimiter, nameIndex)) > 0){
        string chain = graphStr.substr(nameIndex, nodeIndex - nameIndex);
        chainList.push_back(chain);
        nameIndex = nodeIndex + 1;
    }
    chainList.push_back(graphStr.substr(nameIndex));

    for(string chain : chainList){
        int chainIndex = 0, nameIndex = 0;
        string key;
        vector<string> nodeList;
        while((chainIndex = chain.find(chainDelimiter, nameIndex)) > 0){
            string node = chain.substr(nameIndex, chainIndex - nameIndex);
            if(key.empty()){
                key = node;
            }
            else{
                nodeList.push_back(node);
            }
            nameIndex = chainIndex + 1;
        }
        nodeList.push_back(chain.substr(nameIndex));
        graph[key] = nodeList;
    }

    return graph;
}

/**
 * parse the score string, return a score map
 */
unordered_map<string, int> Graph::parseScoreStr(string& scoreStr){
    unordered_map<string, int> scoreMap;
    string nodeDelimiter = "_";
    string name;
    int strIndex = 0, nodeIndex = 0;
    while((nodeIndex = scoreStr.find(nodeDelimiter, strIndex)) > 0){
        string str = scoreStr.substr(strIndex, nodeIndex - strIndex);
        if(name.empty()){
            name = str;
        }
        else{
            scoreMap[name] = stoi(str);
            name = "";
        }
        strIndex = nodeIndex + 1;
    }
    scoreMap[name] = stoi(scoreStr.substr(strIndex));
    return scoreMap;
}

/**
 * get the score between two names
 */
double Graph::getWeight(unordered_map<string, int>& scoreMap, string& source, string& dest){
    double s1 = scoreMap[source];
    double s2 = scoreMap[dest];
    return abs(s1 - s2) / (s1 + s2);
}

/**
 * find the shortest path
 */
pair<vector<double>, vector<string>> Graph::dijkstra(unordered_map<string, int>& nodeIdMap, unordered_map<string, vector<string>>& graph, unordered_map<string, int>& scoreMap, string& source, string& dest){
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    vector<double> distTo(nodeIdMap.size(), numeric_limits<double>::max());
    vector<string> preNode(nodeIdMap.size());
    distTo[nodeIdMap[source]] = 0.0;
    preNode[nodeIdMap[source]] = source;
    
    pq.push(make_pair(0.0, source));
    while(!pq.empty()){
        pair<double, string> p = pq.top();
        string curNode = p.second;
        double curDistFromStart = p.first;
        int curNodeId = nodeIdMap[curNode];
        pq.pop();

        if(curNode == dest){
            return make_pair(distTo, preNode);
        }
        if(curDistFromStart > distTo[curNodeId]){
            continue;
        }

        for(string nextNode : graph[curNode]){
            int nextNodeId = nodeIdMap[nextNode];
            double distToNextNode = distTo[curNodeId] + getWeight(scoreMap, curNode, nextNode);
            if(distTo[nextNodeId] > distToNextNode){
                distTo[nextNodeId] = distToNextNode;
                preNode[nextNodeId] = curNode;
                pq.push(make_pair(distToNextNode, nextNode));
            }
        }
    }

    return make_pair(distTo, preNode);
}

/**
 * based on the result, create a path string
 */
pair<string, string> Graph::createPath(pair<vector<double>, vector<string>>& resultPair, unordered_map<string, int>& nodeIdMap, string& source, string& dest){
    vector<double> distTo = resultPair.first;
    vector<string> preNodeList = resultPair.second;

    int destNodeId = nodeIdMap[dest];
    if(distTo[destNodeId] == numeric_limits<double>::max()){
        return make_pair("NOPATH", "NOPATH");
    }

    vector<string> pathList;
    string preNode = preNodeList[destNodeId];
    pathList.push_back(dest);
    while(preNode != source){
        pathList.push_back(preNode);
        int preNodeId = nodeIdMap[preNode];
        preNode = preNodeList[preNodeId];
    }
    pathList.push_back(source);

    string path1, path2;
    for(int a = pathList.size() - 1; a >= 0; a--){
        path1 += pathList[a];
        if(a != 0){
            path1 += " --- ";
        }
    }
    for(int a = 0; a < pathList.size(); a++){
        path2 += pathList[a];
        if(a != pathList.size() - 1){
            path2 += " --- ";
        }
    }

    return make_pair(path1, path2);
}