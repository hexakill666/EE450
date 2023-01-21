#include"iohandler.h"
#include<iostream>
#include<fstream>
#include<unordered_set>

using namespace std;

/**
 * read the edgelist.txt
 */
unordered_map<string, vector<string>> IOHandler::readEdge(){
    string source, dest;
    ifstream input("edgelist.txt");
    unordered_map<string, vector<string>> graph;

    if(!input.is_open()){
        cout << "cannot open edgelist.txt file" << endl;
        exit(EXIT_FAILURE);
    }

    while(input >> source >> dest){
        if(graph.find(source) == graph.end()){
            vector<string> valueList;
            graph[source] = valueList;
        }
        if(graph.find(dest) == graph.end()){
            vector<string> valueList;
            graph[dest] = valueList;
        }
        graph[source].push_back(dest);
        graph[dest].push_back(source);
    }
    input.close();

    return graph;
}

/**
 * read the scores.txt
 */
unordered_map<string, int> IOHandler::readScore(){
    string name;
    int score;
    ifstream input("scores.txt");
    unordered_map<string, int> scoreMap;

    if(!input.is_open()){
        cout << "cannot open scores.txt file" << endl;
        exit(EXIT_FAILURE);
    }

    while(input >> name >> score){
        scoreMap[name] = score;
    }
    input.close();

    return scoreMap;
}

/**
 * convert graph to graphStr
 */
string IOHandler::getGraphStr(unordered_map<string, vector<string>>& graph){
    string graphStr;
    string chainDelimiter = ">";
    string nodeDelimiter = "_";

    for(unordered_map<string, vector<string>>::iterator iter = graph.begin(); iter != graph.end(); ){
        graphStr += (*iter).first + chainDelimiter;
        for(int a = 0; a < graph[(*iter).first].size(); a++){
            graphStr += graph[(*iter).first][a];
            if(a != graph[(*iter).first].size() - 1){
                graphStr += chainDelimiter;
            }
        }
        if(++iter != graph.end()){
            graphStr += nodeDelimiter;
        }
    }

    return graphStr;
}

/**
 * convert score to scoreStr
 */
string IOHandler::getScoreStr(unordered_map<string, int>& scoreMap){
    string scoreStr;
    string nodeDelimiter = "_";

    for(unordered_map<string, int>::iterator iter = scoreMap.begin(); iter != scoreMap.end(); ){
        scoreStr += (*iter).first + nodeDelimiter + to_string((*iter).second);
        if(++iter != scoreMap.end()){
            scoreStr += nodeDelimiter;
        }
    }

    return scoreStr;
}

/**
 * parse client string, return a list of names.
 */
vector<string> IOHandler::parseClientStr(string& nameStr){
    string nodeDelimiter = "_";
    vector<string> nameList;
    int nameIndex = 0, findIndex = 0;
    while((findIndex = nameStr.find(nodeDelimiter, nameIndex)) > 0){
        nameList.push_back(nameStr.substr(nameIndex, findIndex - nameIndex));
        nameIndex = findIndex + 1;
    }
    nameList.push_back(nameStr.substr(nameIndex));
    return nameList;
}

/**
 * parse the result string
 */
pair<vector<string>, double> IOHandler::parseResultStr(string& resultStr){
    string nodeDelimiter = "_";
    vector<string> infoList;
    int nameIndex = 0, nodeIndex = 0;
    while((nodeIndex = resultStr.find(nodeDelimiter, nameIndex)) > 0){
        string path = resultStr.substr(nameIndex, nodeIndex - nameIndex);
        infoList.push_back(path);
        nameIndex = nodeIndex + 1;
    }
    double compatibility = stod(resultStr.substr(nameIndex));
    return make_pair(infoList, compatibility);
}