#include "ComputationalGraph.h"
#include "Scalar.h"
#include "Operator.h"
#include <iomanip>
#include <string>
#include <utility>
#include <sstream>
ComputationalGraph::ComputationalGraph()
{
    NodeMap.clear();
    PreAnswer.clear();
    NodeAddress.clear();
    TimeTag = 0;
}

//    陋脪碌鈭毬德甭垶潞鈭喢€鈥灻暵郝灯捖犅甭衡€奥泵嵚郝?
int ComputationalGraph::GetTime()
{
    return TimeTag;
}

//    鈭徦樏︹€何┞仿碘€炩垰藲鈥斺垶鈥欌€溑撯€♀€澛段┞仿碘€?
Node* ComputationalGraph::Find(const std::string& NodeName)
{
    if (NodeMap.find(NodeName) == NodeMap.end())    return NULL;
    else return NodeMap[NodeName];
}

//    陋脪碌鈭毬碘亜 Index 鈭徦嗏墹鸥鈼娝溌灯捖ワ？鈭炩垙
float ComputationalGraph::GetPreviousAnswer(const int& Index)
{
    return PreAnswer[Index - 1];
}

//    艙脷潞鈭喢€鈥灻暵好封€撯€標喢兠屸€撀┞仿碘€?
void ComputationalGraph::AddNode(Node* NewNode)
{
    NodeMap[NewNode->GetName()] = NewNode;
    NodeAddress.push_back(NewNode);
}

//    聽鈥扳墺藛鈭傗€樷€澛堵灯捖ッ屌捗涒€撯増艙垄
void ComputationalGraph::ErrorPrint(std::ostream& OutStream)
{
    OutStream << "ERROR: " << ErrorSignal << std::endl;
}

//  潞鈭喢€鈥炍┞仿碘€灻仿碘墹垄聽鈥扳墺藛拢庐陋脷聽鈥扳墺藛楼脤艗脹鈥撯増艙垄拢漏
float ComputationalGraph::Calc(const std::string& NodeName, const std::vector< std::pair<std::string, float> >& InitNode, std::ostream& OutStream)
{
    TimeTag++;                            //    鈭徛糕€撀犅甭衡€奥泵嵚郝?
    for (auto it : InitNode)
    {
        NodeMap[it.first]->SetValue(it.second, TimeTag);
    }
    ErrorSignal.clear();
    float tmpans = NodeMap[NodeName]->Calc(TimeTag, ErrorSignal);
    if (ErrorSignal.size() != 0)
    {
        PreAnswer.push_back(0);            //    碌卤茠鈮モ垙藛鈮づ糕棅藴聽蟺ErrorSignal鈭懧糕€櫬Ｂㄅ掞瑏楼铮库垶鈭徛Ｂㄢ€濃垰0鈥櫬号捖?
        this->ErrorPrint(OutStream);    //    鈮ぢ⒙犫€扳墺藛楼脤艗脹鈥撯増艙垄;
        return 0;                        //    鈭懧德?
    }
    PreAnswer.push_back(tmpans);
    OutStream.setf(std::ios::fixed);
    OutStream << std::setprecision(4) << tmpans << std::endl;
    return tmpans;
}

//    潞芦卢潞 SETCONSTANT 鈭?SETANSWER 鈮づ糕棅藴
void ComputationalGraph::EmptyCall()
{
    PreAnswer.push_back(0);                //    碌卤茠鈮モ垙藛鈮づ糕棅藴艗鈩ET鈮づ糕棅藴聽卤拢篓艗铿伮犫€扳墺藛拢庐楼铮库垶鈭徛Ｂ┞Ｂㄢ€濃垰0鈥櫬号捖?
    TimeTag++;
}

//    艗藛蟺蟺潞鈭喢€鈥灻暵?

//

//Add by Cai on 5.22



void ComputationalGraph::workstage1() {
    std::string ini;
    std::getline(std::cin,ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[1]=="P") {
            AddNode(new Placeholder(info[0]));
        }
        else if (info[1]=="C") {
            AddNode(new Constant(info[0],std::stof(info[2])));
        }
        else if (info[1]=="V") {
            AddNode(new Variable(info[0],std::stof(info[2])));
        }
        else {
            std::cout << "ERROR: Unaccepted Input" << std::endl;
        }
    }
}

void ComputationalGraph::workstage2() {
    std::string ini;
    getline(std::cin, ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[2]=="+")                 //涓哄姞娉?
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new PlusOperator(info[0],vs));
        }
        else if(info[2]=="-")                 //涓轰箻娉?
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MinusOperator(info[0],vs));
        }
        else if(info[2]=="*")            //涓哄噺娉?
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MultipleOperator(info[0],vs));
        }
        else if(info[2]=="/")
        {
            //Div(info[0], info[1], info[3]);
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new DivisionOperator(info[0],vs));
        }
        else if(info[2]=="<")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessOperator(info[0],vs));
        }
        else if(info[2]=="<=")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessEqualOperator(info[0],vs));
        }
        else if(info[2]==">")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterOperator(info[0],vs));
        }
        else if(info[2]==">=")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterEqualOperator(info[0],vs));
        }
        else if(info[2]=="==")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterEqualOperator(info[0],vs));
        }
        else if(info[2]=="==")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new EqualOperator(info[0],vs));
        }
        else if(info[1]=="SIN")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SinOperator(info[0],vs));
        }
        else if(info[1]=="LOG")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new LogOperator(info[0],vs));
        }
        else if(info[1]=="TANH")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new TanhOperator(info[0],vs));
        }
        else if(info[1]=="EXP")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new ExpOperator(info[0],vs));
        }
        else if(info[1]=="SIGMOID")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SigmoidOperator(info[0],vs));
        }
        else if(info[1]=="PRINT" || info[1] == "Print")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new PrintOperator(info[0],vs,std::cout));
        }
        else if(info[1]=="COND")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            vs.push_back(Find(info[4]));
            AddNode(new CondOperator(info[0],vs));
        }
        else if(info[1]=="ASSERT")
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new AssertOperator(info[0],vs));
        }
        else if(info[1]=="BIND")            //涓哄噺娉?
        {
            std::vector<Node*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            AddNode(new BindOperator(info[0],vs));
        }
    }
}

void ComputationalGraph::workstage3() {
    std::string ini;
    getline(std::cin, ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[0]=="EVAL") {
            int m=info.size()-3;
            std::vector< std::pair<std::string, float> >vc;
            for(int i=0;i<m;i+=2) {
                vc.push_back(std::make_pair(info[3+i], std::stof(info[4+i])));
            }
            Calc(info[1], vc, std::cout);
            
        }
        else if (info[0]=="SETANSWER") {
            EmptyCall();
            int timetag=GetTime();
            Find(info[1])->SetValue(PreAnswer[std::stoi(info[2])-1], timetag);
            
        }
        else if (info[0]=="SETCONSTANT") {
            EmptyCall();
            int timetag=GetTime();
            Find(info[1])->SetValue(std::stof(info[2]), timetag);
        }

    }
}


//End Add


ComputationalGraph::~ComputationalGraph()
{
    //    鈥γ︹墺藵NodeAddress驴脭鈭毭糕垙藛惟路碌鈥灻封垙鈥櫭幟封垙艙脷碌茠茠鈦劼ッ?
    for (auto it : NodeAddress)
    {
        delete it;
    }
    NodeMap.clear();
    NodeAddress.clear();
    PreAnswer.clear();
}
