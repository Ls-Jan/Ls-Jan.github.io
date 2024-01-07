
#include"ScoreList_Set.h"


ScoreList_Set::__Score::__Score(Score* score,ScoreList_Set*parent) {
	this->__score = score;
	this->__parent = parent;
}

bool ScoreList_Set::__Score::operator<(const __Score& right)const {
	auto rst=this->__score->CompWith(*right.__score, *this->__parent->GetPriorityList());
	if (rst==0)//�ܾ�����idһ�µ�����
		return false;
	return rst>0;
}


ScoreList_Set::ScoreList_Set() {
	this->__iter = this->__array.begin();
	this->__riter = this->__array.rbegin();
	this->__reversed = false;
	this->__isValid = false;
}

int ScoreList_Set::Length() {
	return this->__array.size();
}

std::vector<Subject>* ScoreList_Set::GetPriorityList() {//��ȡ�������ȼ�
	return &this->__priorityLst;
}

void ScoreList_Set::SetPriorityList(std::vector<Subject>priorityLst) {//�����������ȼ�
	this->__priorityLst = priorityLst;
	std::vector<Score*>lst;
	for (auto iter = this->__array.begin(); iter != this->__array.end(); ++iter)
		lst.push_back(iter->__score);
	this->__array.clear();
	for (auto iter = lst.begin(); iter != lst.end(); ++iter)
		this->__array.insert(__Score(*iter,this));
	this->__isValid =false;
}

bool ScoreList_Set::InsertRecord(Score* score) {//����һ������
	auto rst = this->__array.insert(__Score(score, this));
	this->__isValid = false;
	return rst.second;
}

bool ScoreList_Set::EraseRecord(Score* score) {//�Ƴ�һ������
	this->__array.erase(__Score(score,this));
	this->__isValid = false;
	return true;
}

Score* ScoreList_Set::PopRecord() {//�Ƴ����һ������
	auto iter = this->__array.rbegin();
	if (iter == this->__array.rend())
		return nullptr;
	auto s = iter->__score;
	this->__array.erase(*iter);
	this->__isValid = false;
	return s;
}

Score* ScoreList_Set::Start(bool reversed) {//��ʼ������������������
	this->__reversed = reversed;
	this->__isValid = this->__array.size()>0;
	if (this->__isValid) {
		if (reversed) {
			this->__riter = this->__array.rbegin();
			return this->__riter->__score;
		}
		else {
			this->__iter = this->__array.begin();
			return this->__iter->__score;
		}
	}
	return nullptr;
}

Score* ScoreList_Set::Next() {//��ȡ�������ݡ�������ɺ󽫷���nullptr
	if (this->__isValid) {
		if (this->__reversed) {
			if (++this->__riter != this->__array.rend()) {
				return this->__riter->__score;
			}
		}
		else {
			if (++this->__iter != this->__array.end()) {
				return this->__iter->__score;
			}
		}
		this->__isValid = false;
	}
	return nullptr;
}


