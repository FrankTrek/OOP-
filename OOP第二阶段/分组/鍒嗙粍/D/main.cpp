#include "Operator.h"
#include "Graph.h"
#include "template_.h"
#include <iostream>
#include <sstream>

int main(){
    Graph calgraph;
    int a, b, c;

    //输入初始变量
    std::cin >> a;                      //初始变量数量
    for(int i = 0; i < a; i++){         
        std::string input1, input2;     //名称  属性
        std::cin >> input1 >> input2;
        if(input2 == "P"){
            calgraph.iniplaceholder(input1);
        }    

        else if(input2 == "C"){
            float inputval;
            std::cin >> inputval;
            calgraph.iniconstant(input1,inputval);
        }

        else if(input2 == "V"){
            float inputval;
            std::cin >> inputval;
            calgraph.inivariable(input1,inputval);
        }
    }

    //定义新节点
    std::cin >> b;                      //新节点数量
    std::string blank;
    getline(std::cin, blank);           //b后的回车
    for(int i = 0; i < b; i++){
        std::string inputdata;
        getline(std::cin, inputdata);
        std::stringstream ss;
        ss << inputdata;
        std::vector<std::string> line;
        std::string part;
        while(ss >> part){              //拆分
            line.push_back(part);
        }
        //按照不同类型初始化Node
        if(line[2] == "SIN"){
            calgraph.ininode<Sin>(line[0], {line[3]});
        }
        else if(line[2] == "LOG"){
            calgraph.ininode<Log>(line[0], {line[3]});
        }
        else if(line[2] == "EXP"){
            calgraph.ininode<Exp>(line[0], {line[3]});
        }
        else if(line[2] == "SIGMOID"){
            calgraph.ininode<Sigmoid>(line[0], {line[3]});
        }
        else if(line[2] == "TANH"){
            calgraph.ininode<Tanh>(line[0], {line[3]});
        }
        else if(line[2] == "PRINT"){
            calgraph.ininode<Print>(line[0], {line[3]});
        }
        else if(line[2] == "COND"){
            calgraph.ininode<Cond>(line[0], {line[3], line[4], line[5]});
        }
        else if(line[3] == "+"){
            calgraph.ininode<Add>(line[0], {line[2], line[4]});
        }
        else if(line[3] == "-"){
            calgraph.ininode<Sub>(line[0], {line[2], line[4]});
        }
        else if(line[3] == "*"){
            calgraph.ininode<Mul>(line[0], {line[2], line[4]});
        }
        else if(line[3] == "/"){
            calgraph.ininode<Div>(line[0], {line[2], line[4]});
        }
        else if(line[3] == ">"){
            calgraph.ininode<Greater>(line[0], {line[2], line[4]});
        }
        else if(line[3] == ">="){
            calgraph.ininode<Greater_e>(line[0], {line[2], line[4]});
        }
        else if(line[3] == "<"){
            calgraph.ininode<Lesser>(line[0], {line[2], line[4]});
        }
        else if(line[3] == "<="){
            calgraph.ininode<Lesser_e>(line[0], {line[2], line[4]});
        }
        else if(line[3] == "=="){
            calgraph.ininode<Equal>(line[0], {line[2], line[4]});
        }
    }

    //计算操作
    std::cin >> c;                          //计算操作数量
    std::string blank2;
    getline(std::cin, blank2);              //c后的回车
    for(int i = 0; i < c; i++){
        std::string inputdata;
        getline(std::cin, inputdata);
        std::stringstream ss;
        ss << inputdata;
        std::vector<std::string> line;
        std::string part;
        while(ss >> part){
            line.push_back(part);           //拆分
        }
        //对于v型变量的操作
        if(line[0]=="SETCONSTANT"){
            calgraph.setconstant(line[1], stof(line[2]));
            calgraph.addanswers(NAN);
        }
        else if(line[0]=="SETANSWER"){
            calgraph.setanswer(line[1], stoi(line[2]));
            calgraph.addanswers(NAN);
        }
        //eval操作
        else if(line.size() >= 3){
        int num = stoi(line[2]);
        int now = 3;
        //eval中的赋值操作存入pair型的vector中
        std::vector<std::pair<std::string, float>> PHdata;
        for(int j = 0; j < num ; j++){
            auto data = make_pair(line[now], stof(line[now+1]));
            PHdata.push_back(data);
            now += 2;
        }
        calgraph.addanswers(calgraph.eval(line[1], PHdata));
        }
        else{
            std::vector<std::pair<std::string, float>> blank3 = {};
            calgraph.addanswers(calgraph.eval(line[1], blank3));
        }
    }

    return 0;
}