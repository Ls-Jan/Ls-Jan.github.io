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
	int Length();//数据大小
	void SetPriorityList(std::vector<Subject>prioritylst);//设置排序优先级
	bool InsertRecord(Score* score);//插入一条数据
	bool EraseRecord(Score* score);//移除一条数据
	Score* PopRecord();//移除最后一条数据
	Score* Start(bool reversed = false);//开始遍历，返回首条数据
	Score* Next();//获取下条数据。遍历完成后将返回nullptr
};
