#pragma once

#include"Declare.h"
#include<set>
class ScoreList_Sort :public Interface_ScoreList {
private:
	std::set<unsigned>__IDs;
	std::vector<Subject>__prioritylst;
	std::vector<Score*>__array;
	std::vector<Score*>::iterator __iter;
	bool __isValid;
public:
	ScoreList_Sort();
	int Length();//���ݴ�С
	void SetPriorityList(std::vector<Subject>prioritylst);//�����������ȼ�
	bool InsertRecord(Score* score);//����һ������
	bool EraseRecord(Score* score);//�Ƴ�һ������
	Score* PopRecord();//�Ƴ����һ������
	Score* Start(bool reversed = false);//��ʼ������������������
	Score* Next();//��ȡ�������ݡ�������ɺ󽫷���nullptr
};
