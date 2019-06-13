#ifndef NODE_H
#define NODE_H

#include<vector>
#include<string>

const float Epsi = 1e-7;

template <typename T>
class Node {
private:
	int Time;
	std::string Name;
	T Value;
    //add by Cai on 6.6
    T gradi=0;
    //
protected:
	std::vector<Node*> Pre;		//Pre: ����ĳ����Value������ǰ����
public:
    Node(){
        Name = "";
        Value = 0;
        Time = 0;
        Pre.clear();
    }
	Node(const std::string& InitName, const T& InitValue, const int& InitTime)
    {
        Name = InitName;
        Value = InitValue;
        Time = InitTime;
        Pre.clear();
    }
	T Calc(const int& CurTime, std::string& ErrorSignal)
    {
        SetGradi(0);
        if (Time == CurTime)                    //    ������Ӧ��ʱ����ڵ�ǰʱ�䣬����ֱ�ӷ���Value;
        {
            return Value;
        }
        
        Time = CurTime;
        Value = this->Solve(ErrorSignal);        //    �������¼���
        return Value;
    }//	����ĳһ����ֵ
    void SetValue(const T& Input, const int& CurTime){
        Value = Input;
        Time = CurTime;
    }						//	Ϊ��㸳ֵ
    std::string GetName(){
        return Name;
    }														//	��ý����
    T GetValue(){
        return Value;
    }																//	��ý��ֵ
    //
    T GetGradi (){
        return gradi;
    }
    void SetGradi (T G){
        gradi= G;
    }
    //
    
    int GetTime(){
        return Time;
    }																	//	��ý���ʱ����
	virtual T Solve(std::string&ErrorSignal) = 0;									//	���麯������������������д����: ���в�ͬ����������ļ���
    
    //add by Cai on 6.6
    virtual void Backward(T ,std::string&ErrorSignal) = 0;
    //
    virtual ~Node() {}															//	������������
};

#endif
