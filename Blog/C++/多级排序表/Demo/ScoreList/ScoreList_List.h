#pragma once

#include"Declare.h"
#include<list>
#include<set>
class ScoreList_List :public Interface_ScoreList {
private:
	std::vector<Subject>__prioritylst;
	std::list<Score*>*__array;
	std::list<Score*>::iterator __iter;
	std::list<Score*>::reverse_iterator __riter;
	bool __reversed;
	bool __isValid;
public:
	ScoreList_List();
	~ScoreList_List();
	int Length();//���ݴ�С
	void SetPriorityList(std::vector<Subject>prioritylst);//�����������ȼ�
	bool InsertRecord(Score* score);//����һ������
	bool EraseRecord(Score* score);//�Ƴ�һ������
	Score* PopRecord();//�Ƴ����һ������
	Score* Start(bool reversed = false);//��ʼ������������������
	Score* Next();//��ȡ�������ݡ�������ɺ󽫷���nullptr
};
