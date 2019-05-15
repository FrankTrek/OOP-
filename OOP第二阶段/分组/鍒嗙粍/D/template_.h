#pragma once
#include "Graph.h"
#include <vector>
#include <string>


template<class T>
void Graph::ininode(std::string a, const std::vector<std::string>& b){
    std::vector<Node*> c;           //之后传入对应Node中的children
    for(std::string s : b){
        c.push_back(graph[s]);
    }
    graph[a] = new T(a, c, this);
    nodes.push_back(graph[a]); 
}
