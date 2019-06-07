#include "ComputationalGraph.h"
#include "Operator.h"
#include "Scalar.h"
#include <iostream>
#include <sstream>
#include <map>
#include "Session.h"



//int n, m;
//float x;
//std::string x1, x2, x3, x4, x5;

void Error()
{
    std::cout << "ERROR: Unaccepted Input" << std::endl;
}

int main()
{
    
    ComputationalGraph CG;
    CG.workstage1();
    CG.workstage2();
    CG.workstage3();
    
    
    /*
     std::vector<std::vector<int>>  a = {{1,2,3},{7,7,4}};
     std::vector<int>   b = {1,3,4};
     
     Tensor test(a);
     Tensor test2(b);
     test.Print();
     test = test-test2;
     test.Print();
     //test=test.reshape({3,4});
     
     //test.Print();
     //test = test.transposition();
     //test.Print();
     //(test2*test).Print();
     */
    //    输入结点属性（和数值）
    /*
     std::cin >> n;
     while (n--)
     {
     std::cin >> x1 >> x2;
     switch (x2[0])
     {
     case('P'):
     {
     CG.AddNode(new Placeholder(x1));
     break;
     }
     case('C'):
     {
     std::cin >> x;
     CG.AddNode(new Constant(x1, x));
     break;
     }
     case('V'):
     {
     std::cin >> x;
     CG.AddNode(new Variable(x1, x));
     break;
     }
     default:
     {
     Error();
     }
     }
     }
     //    输入计算操作
     std::cin >> n;
     while (n--)
     {
     std::cin >> x1 >> x2;
     std::cin >> x2;
     switch (x2[0])                                //    根据 = 后第一个string的内容进行计算
     {
     case('S'):    //SIN SIGMOID
     {
     std::cin >> x3;
     std::vector<Node*>vc;
     vc.push_back(CG.Find(x3));
     if (x2[2] == 'N')
     CG.AddNode(new SinOperator(x1, vc));
     else if (x2[2] == 'G')
     CG.AddNode(new SigmoidOperator(x1, vc));
     else
     Error();
     break;
     }
     case('C'):    //COND
     {
     std::cin >> x3 >> x4 >> x5;
     std::vector<Node*>vc;
     vc.push_back(CG.Find(x3));
     vc.push_back(CG.Find(x4));
     vc.push_back(CG.Find(x5));
     CG.AddNode(new CondOperator(x1, vc));
     break;
     }
     case('T'):    //TANH
     {
     std::cin >> x3;
     std::vector<Node*>vc;
     vc.push_back(CG.Find(x3));
     CG.AddNode(new TanhOperator(x1, vc));
     break;
     }
     case('E'):    //EXP
     {
     std::cin >> x3;
     std::vector<Node*>vc;
     vc.push_back(CG.Find(x3));
     CG.AddNode(new ExpOperator(x1, vc));
     break;
     }
     case('L'):    //LOG
     {
     std::cin >> x3;
     std::vector<Node*>vc;
     vc.push_back(CG.Find(x3));
     CG.AddNode(new LogOperator(x1, vc));
     break;
     }
     case('P'):    //PRINT
     {
     std::cin >> x3;
     if (CG.Find(x3) != NULL)
     {
     std::vector<Node*>vc;
     vc.push_back(CG.Find(x3));
     CG.AddNode(new PrintOperator(x1, vc, std::cout));
     }
     else
     {
     Error();
     }
     break;
     }
     default:
     {
     std::cin >> x3 >> x4;                    //    若第一个string不满足上述情况，说明进行四则运算和比较运算
     if (CG.Find(x2) != NULL && CG.Find(x4) != NULL)
     {
     std::vector<Node*>vc;
     vc.push_back(CG.Find(x2));
     vc.push_back(CG.Find(x4));
     switch (x3[0])
     {
     case('+'):
     {
     CG.AddNode(new PlusOperator(x1, vc));
     break;
     }
     case('-'):
     {
     CG.AddNode(new MinusOperator(x1, vc));
     break;
     }
     case('*'):
     {
     CG.AddNode(new MultipleOperator(x1, vc));
     break;
     }
     case('/'):
     {
     CG.AddNode(new DivisionOperator(x1, vc));
     break;
     }
     case('<'):    //< <=
     {
     if (x3.size() == 1)
     CG.AddNode(new LessOperator(x1, vc));
     else
     CG.AddNode(new LessEqualOperator(x1, vc));
     break;
     }
     case('>'):    //> >=
     {
     if (x3.size() == 1)
     CG.AddNode(new GreaterOperator(x1, vc));
     else
     CG.AddNode(new GreaterEqualOperator(x1, vc));
     break;
     }
     case('='):    //==
     {
     CG.AddNode(new EqualOperator(x1, vc));
     break;
     }
     default:
     {
     Error();
     }
     }
     }
     else
     {
     Error();
     }
     }
     }
     }
     //    输入操作
     std::cin >> n;
     while (n--)
     {
     std::getline(std::cin, x1);                    //    先读取一行
     while (x1.size() <= 4)                        //    针对导致一行字符数不超过4的误操作（主要是针对输入空行的情况）
     {
     std::getline(std::cin, x1);                //    重新输入
     }
     std::stringstream fin(x1);                    //    用x1初始化字符串流fin
     fin >> x1;                                    //    fin按空格划分，第一部分用来初始化x1
     switch (x1[0])
     {
     case('E'):
     {
     fin >> x1;
     std::vector< std::pair<std::string, float> >vc;
     if (!fin.eof())                            //    若fin未读到末尾，说明EVAL操作给出了待赋值变量的个数;
     {
     fin >> m;
     }
     else
     {
     m = 0;                                //    否则，EVAL操作未给出待赋值变量个数，说明没有依赖的结点
     }
     while (m--)
     {
     fin >> x2 >> x;
     vc.push_back(make_pair(x2, x));        //    依次将依赖结点和其值加入存储前序结点的vc中
     }
     float tmpans = CG.Calc(x1, vc, std::cout);
     break;
     }
     case('S'):    //SETCONSTANT SETANSWER
     {
     CG.EmptyCall();                            //    SET操作占位
     int timetag = CG.GetTime();
     if (x1[3] == 'C')    //SETCONSTANT
     {
     fin >> x2 >> x;
     if (CG.Find(x2) != NULL) {
     CG.Find(x2)->SetValue(x, timetag);
     }
     }
     else  //SETANSWER
     {
     int xx;
     fin >> x2 >> xx;
     float tmpvalue = CG.GetPreviousAnswer(xx);
     CG.Find(x2)->SetValue(tmpvalue, timetag);
     }
     break;
     }
     default:
     {
     Error();
     }
     }
     }
     */
    return 0;
}
