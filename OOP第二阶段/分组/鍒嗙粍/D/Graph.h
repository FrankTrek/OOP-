#pragma once
#include "Node.h"
#include <map>
#include <utility>
#include <cmath>
#include <vector>

class Node;

class Graph{
private:
    std::vector<Node*> caleds;          //已经计算过的节点
    std::vector<Node*> nodes;           //图中所有节点
    std::map<std::string, Node*> graph;  //名称所对应节点
    std::string error;                  //报错类型（如果有）
    std::vector<float> answers;         //之前输出操作的结果
    bool haserror=false;                //是否报错
public:
    void addanswers(float);
    Graph(){}
    template <class T>
    void ininode(std::string, const std::vector<std::string>&);
    void iniplaceholder(std::string);
    void iniconstant(std::string, float);
    void inivariable(std::string, float);
    void setconstant(std::string, float);
    void setanswer(std::string, int);
    float eval(std::string,std::vector<std::pair<std::string, float>>);
    void errorthrow(std::string);
    std::map<std::string,Node*>& getmap();
    ~Graph(){
        for(auto i : nodes){
            delete i;
        }
    }
    friend Node;
};