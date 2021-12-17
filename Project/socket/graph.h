#pragma once
#include<unordered_map>
#include<unordered_set>
#include<vector>

using namespace std;

class Graph{
    public:
        unordered_map<string, int> getNodeIdMap(string& graphStr);
        unordered_map<string, vector<string>> parseGraphStr(string& graphStr);
        unordered_map<string, int> parseScoreStr(string& scoreStr);
        double getWeight(unordered_map<string, int>& scoreMap, string& source, string& dest);
        pair<vector<double>, vector<string>> dijkstra(unordered_map<string, int>& nodeIdMap, unordered_map<string, vector<string>>& graph, unordered_map<string, int>& scoreMap, string& source, string& dest);
        pair<string, string> createPath(pair<vector<double>, vector<string>>& resultPair, unordered_map<string, int>& nodeIdMap, string& source, string& dest);
};