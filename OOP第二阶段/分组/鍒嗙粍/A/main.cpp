#include "ComputationalGraph.h"
#include "Operator.h"
#include "Scalar.h"
#include <iostream>
#include <sstream>
#include <map>

ComputationalGraph CG;
int n, m;
float x;
std::string x1, x2, x3, x4, x5;

void Error()
{
	std::cout << "ERROR: Unaccepted Input" << std::endl;
}

int main()
{
	//	���������ԣ�����ֵ��
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

	//	����������
	std::cin >> n;
	while (n--)
	{
		std::cin >> x1 >> x2;
		std::cin >> x2;

		switch (x2[0])								//	���� = ���һ��string�����ݽ��м���
		{
		case('S'):	//SIN SIGMOID
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
		case('C'):	//COND
		{
			std::cin >> x3 >> x4 >> x5;
			std::vector<Node*>vc;
			vc.push_back(CG.Find(x3));
			vc.push_back(CG.Find(x4));
			vc.push_back(CG.Find(x5));
			CG.AddNode(new CondOperator(x1, vc));
			break;
		}
		case('T'):	//TANH
		{
			std::cin >> x3;
			std::vector<Node*>vc;
			vc.push_back(CG.Find(x3));
			CG.AddNode(new TanhOperator(x1, vc));
			break;
		}
		case('E'):	//EXP
		{
			std::cin >> x3;
			std::vector<Node*>vc;
			vc.push_back(CG.Find(x3));
			CG.AddNode(new ExpOperator(x1, vc));
			break;
		}
		case('L'):	//LOG
		{
			std::cin >> x3;
			std::vector<Node*>vc;
			vc.push_back(CG.Find(x3));
			CG.AddNode(new LogOperator(x1, vc));
			break;
		}
		case('P'):	//PRINT
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
			std::cin >> x3 >> x4;					//	����һ��string���������������˵��������������ͱȽ�����
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
				case('<'):	//< <=
				{
					if (x3.size() == 1)
						CG.AddNode(new LessOperator(x1, vc));
					else
						CG.AddNode(new LessEqualOperator(x1, vc));
					break;
				}
				case('>'):	//> >=
				{
					if (x3.size() == 1)
						CG.AddNode(new GreaterOperator(x1, vc));
					else
						CG.AddNode(new GreaterEqualOperator(x1, vc));
					break;
				}
				case('='):	//==
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

	//	�������
	std::cin >> n;
	while (n--)
	{
		std::getline(std::cin, x1);					//	�ȶ�ȡһ��
		while (x1.size() <= 4)						//	��Ե���һ���ַ���������4�����������Ҫ�����������е������
		{
			std::getline(std::cin, x1);				//	��������
		}
		std::stringstream fin(x1);					//	��x1��ʼ���ַ�����fin
		fin >> x1;									//	fin���ո񻮷֣���һ����������ʼ��x1
		switch (x1[0])
		{
			case('E'):
			{
				fin >> x1;
				std::vector< std::pair<std::string, float> >vc;
				if (!fin.eof())							//	��finδ����ĩβ��˵��EVAL���������˴���ֵ�����ĸ���;
				{
					fin >> m;
				}
				else
				{
					m = 0;								//	����EVAL����δ��������ֵ����������˵��û�������Ľ��
				}
				while (m--)
				{
					fin >> x2 >> x;
					vc.push_back(make_pair(x2, x));		//	���ν�����������ֵ����洢ǰ�����vc��
				}
				float tmpans = CG.Calc(x1, vc, std::cout);
				break;
			}
			case('S'):	//SETCONSTANT SETANSWER
			{
				CG.EmptyCall();							//	SET����ռλ
				int timetag = CG.GetTime();
				if (x1[3] == 'C')	//SETCONSTANT
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
	return 0;
}
