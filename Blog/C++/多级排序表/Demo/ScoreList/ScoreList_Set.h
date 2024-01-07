#pragma once

#include"Declare.h"
#include<set>
#include<map>
class ScoreList_Set :public Interface_ScoreList {
private:
	class __Score {
	public:
		Score* __score;
		ScoreList_Set* __parent;
	public:
		__Score(Score* data, ScoreList_Set* parent);
		bool operator<(const __Score& right)const;
	};
	std::set<__Score>__array;
	std::set<__Score>::iterator __iter;
	std::set<__Score>::reverse_iterator __riter;
	std::vector<Subject> __priorityLst;
	bool __reversed;
	bool __isValid;
public:
	ScoreList_Set();
	std::vector<Subject>* GetPriorityList();//�����������ȼ�
	int Length();//���ݴ�С
	void SetPriorityList(std::vector<Subject>priorityLst);//�����������ȼ�
	bool InsertRecord(Score* score);//����һ������
	bool EraseRecord(Score* score);//�Ƴ�һ������
	Score* PopRecord();//�Ƴ����һ������
	Score* Start(bool reversed = false);//��ʼ������������������
	Score* Next();//��ȡ�������ݡ�������ɺ󽫷���nullptr
};
