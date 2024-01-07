#pragma once
#include"ScoreList_List.h"
#include<algorithm>
ScoreList_List::ScoreList_List() {
	this->__array = new std::list<Score*>();
	this->__iter = this->__array->begin();
	this->__riter = this->__array->rbegin();
	this->__reversed = false;
	this->__isValid = false;
}

ScoreList_List::~ScoreList_List() {
	delete this->__array;
}

int ScoreList_List::Length(){
	return this->__array->size();
}

void ScoreList_List::SetPriorityList(std::vector<Subject> prioritylst) {
	this->__prioritylst = prioritylst;
	//其实这里应该使用sort函数，算了也懒得再改
	auto oldArray = this->__array;
	this->__array = new std::list<Score*>();
	for (auto i = oldArray->begin(); i != oldArray->end(); ++i)
		this->InsertRecord(*i);
	delete oldArray;
}

bool ScoreList_List::InsertRecord(Score* score) {
	auto iter = std::lower_bound(this->__array->begin(), this->__array->end(), score, [this](Score* left, Score* right) {
		auto rst = left->CompWith(*right, this->__prioritylst);
		return rst>0;
		});
	if (iter != this->__array->end()) {
		if ((*iter)->studentID == score->studentID) 
			return false;
		this->__array->insert(iter, score);
		return true;
	}
	this->__array->push_back(score);
	return true;

}

bool ScoreList_List::EraseRecord(Score* score) {
	this->__isValid = false;
	auto iter = std::lower_bound(this->__array->begin(), this->__array->end(), score, [this](Score* left, Score* right) {
		auto rst = left->CompWith(*right, this->__prioritylst);
		return rst;
		});
	if (iter != this->__array->end()) {
		this->__array->erase(iter);
	}
	return true;
}

Score* ScoreList_List::PopRecord() {
	this->__isValid = false;
	if (this->__array->size() > 0) {
		Score* s = this->__array->back();
		this->__array->pop_back();
		return s;
	}
	return nullptr;
}

Score* ScoreList_List::Start(bool reversed) {
	auto& iter = this->__iter;
	auto& riter = this->__riter;
	auto& array = this->__array;
	this->__reversed = reversed;
	this->__isValid = array->size() > 0;
	if (this->__isValid) {
		if (reversed) {
			riter = array->rbegin();
			return *riter;
		}
		else {
			iter = array->begin();
			return *iter;
		}
	}
	return nullptr;
}

Score* ScoreList_List::Next() {
	auto& iter = this->__iter;
	auto& riter = this->__riter;
	auto& array = this->__array;
	if (this->__isValid) {
		if (this->__reversed) {
			if (++riter != array->rend())
				return *riter;
		}
		else {
			if (++iter != array->end())
				return *iter;
		}
		this->__isValid = false;
	}
	return nullptr;
}
