#pragma once

#include<map>
#include<vector>

enum class Subject {//��Ŀ
	English,//Ӣ��
	Chinese,//����
	Math,//��ѧ
};

struct Score {//������Ϣ
	unsigned studentID;
	std::map<Subject, unsigned>score;
	int CompWith(const Score& right, std::vector<Subject>&priorityLst);//����Ȩ�ؽ��бȽ�(���ڽ�����1��С����-1����idһ��ʱ����0����scoreֵ��һ��ʱ������idֵ��С���бȽ�
};


class Interface_ScoreList {
public:
	virtual int Length() = 0;//���ݴ�С
	virtual void SetPriorityList(std::vector<Subject>priorityLst) = 0;//�����������ȼ�
	virtual bool InsertRecord(Score* score) = 0;//����һ������
	virtual bool EraseRecord(Score* score) = 0;//�Ƴ�һ������
	virtual Score* PopRecord() = 0;//�Ƴ����һ������
	virtual Score* Start(bool reversed = false) = 0;//��ʼ������������������
	virtual Score* Next() = 0;//��ȡ�������ݡ�������ɺ󽫷���nullptr
};

