#pragma once

#include<map>
#include<vector>

enum class Subject {//科目
	English,//英语
	Chinese,//国语
	Math,//数学
};

struct Score {//数据信息
	unsigned studentID;
	std::map<Subject, unsigned>score;
	int CompWith(const Score& right, std::vector<Subject>&priorityLst);//根据权重进行比较(大于将返回1，小于则-1），id一致时返回0。当score值都一致时返回以id值大小进行比较
};


class Interface_ScoreList {
public:
	virtual int Length() = 0;//数据大小
	virtual void SetPriorityList(std::vector<Subject>priorityLst) = 0;//设置排序优先级
	virtual bool InsertRecord(Score* score) = 0;//插入一条数据
	virtual bool EraseRecord(Score* score) = 0;//移除一条数据
	virtual Score* PopRecord() = 0;//移除最后一条数据
	virtual Score* Start(bool reversed = false) = 0;//开始遍历，返回首条数据
	virtual Score* Next() = 0;//获取下条数据。遍历完成后将返回nullptr
};

