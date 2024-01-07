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
	std::vector<Subject>* GetPriorityList();//返回排序优先级
	int Length();//数据大小
	void SetPriorityList(std::vector<Subject>priorityLst);//设置排序优先级
	bool InsertRecord(Score* score);//插入一条数据
	bool EraseRecord(Score* score);//移除一条数据
	Score* PopRecord();//移除最后一条数据
	Score* Start(bool reversed = false);//开始遍历，返回首条数据
	Score* Next();//获取下条数据。遍历完成后将返回nullptr
};
