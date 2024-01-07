#include "Declare.h"

int Score::CompWith(const Score& right, std::vector<Subject>& priorityLst){
	auto& left = *this;
	if (left.studentID==right.studentID)
		return 0;
	for (auto prior = priorityLst.begin(); prior != priorityLst.end(); ++prior) {
		int diff = left.score.at(*prior) - right.score.at(*prior);
		if (diff == 0)
			continue;
		return diff>0?1:-1;
	}
	return left.studentID > right.studentID?1:-1;
}
