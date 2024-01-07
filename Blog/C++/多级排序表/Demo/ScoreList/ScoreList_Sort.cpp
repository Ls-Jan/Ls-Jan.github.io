#include"ScoreList_Sort.h"
#include<algorithm>



ScoreList_Sort::ScoreList_Sort() {
	this->__isValid = false;
}

int ScoreList_Sort::Length(){
	return this->__array.size();
}

void ScoreList_Sort::SetPriorityList(std::vector<Subject> prioritylst) {
	this->__prioritylst = prioritylst;
	this->__isValid = false;
}

bool ScoreList_Sort::InsertRecord(Score* score) {
	auto id = score->studentID;
	if (this->__IDs.find(id) == this->__IDs.end()) {
		this->__isValid = false;
		this->__IDs.insert(id);
		this->__array.push_back(score);
		return true;
	}
	return false;
}

bool ScoreList_Sort::EraseRecord(Score* score) {
	this->__isValid = false;
	auto id = score->studentID;
	if (this->__IDs.find(id) == this->__IDs.end()) {
		for (auto iter = this->__array.begin(); iter != this->__array.end(); ++iter) {
			if (*iter == score) {
				this->__array.erase(iter);
				this->__IDs.erase(id);
				break;
			}
		}
	}
	return true;
}

Score* ScoreList_Sort::PopRecord() {
	this->__isValid = false;
	Score* s = nullptr;
	if (this->__array.size() > 0) {
		s = this->__array.back();
		this->__array.pop_back();
		this->__IDs.erase(s->studentID);
	}
	return s;
}

Score* ScoreList_Sort::Start(bool reversed) {
	this->__isValid = this->__array.size() != 0;

	//lambda闭包救我狗命，虽然可以使用functional库中的bind来绑定函数，只不过有一些麻烦
	std::sort(this->__array.begin(), this->__array.end(), [this,&reversed](Score* left, Score* right) {
		auto rst =left->CompWith(*right, this->__prioritylst);
		if (rst == 0)
			return false;
		return reversed ?rst < 0 :rst>0;
		});

	this->__iter = this->__array.begin();
	if (this->__isValid) {
		return *this->__iter;
	}
	return nullptr;
}

Score* ScoreList_Sort::Next() {
	if (this->__isValid) {
		if (++this->__iter != this->__array.end()) {
			return *this->__iter;
		}
		this->__isValid = false;
	}
	return nullptr;
}
