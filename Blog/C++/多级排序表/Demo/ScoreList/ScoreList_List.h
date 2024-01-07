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
	int Length();//数据大小
	void SetPriorityList(std::vector<Subject>prioritylst);//设置排序优先级
	bool InsertRecord(Score* score);//插入一条数据
	bool EraseRecord(Score* score);//移除一条数据
	Score* PopRecord();//移除最后一条数据
	Score* Start(bool reversed = false);//开始遍历，返回首条数据
	Score* Next();//获取下条数据。遍历完成后将返回nullptr
};
