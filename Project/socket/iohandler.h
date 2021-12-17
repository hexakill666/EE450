#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

class IOHandler{
    public:
        static unordered_map<string, vector<string>> readEdge();
        static unordered_map<string, int> readScore();
        static string getGraphStr(unordered_map<string, vector<string>>& graph);
        static string getScoreStr(unordered_map<string, int>& scoreMap);
        static vector<string> parseClientStr(string& nameStr);
        static pair<vector<string>, double> parseResultStr(string& resultStr);
};