

#include"ScoreList_Set.h"
#include"ScoreList_Sort.h"
#include"ScoreList_List.h"

//class ScoreList :public ScoreList_Set {};
class ScoreList :public ScoreList_Sort {};
//class ScoreList :public ScoreList_List {};



#include<random>

int main() {
	srand(1);
	ScoreList lst;
	//��������
	for (auto i = 0; i < 15; ++i) {
		Score* s = new Score();
		s->studentID = i%10;//�����ظ�����
		s->score[Subject::English] = rand() % 3;
		s->score[Subject::Chinese] = rand() % 3;
		s->score[Subject::Math] = rand() % 3;
		lst.InsertRecord(s);
	}
	//��������
	lst.SetPriorityList({ Subject::English,Subject::Math,Subject::Chinese });
	for (auto s = lst.Start(true); s != nullptr; s = lst.Next())
		printf_s("%.2d    %.2d, %.2d, %.2d\n", s->studentID, s->score[Subject::English], s->score[Subject::Math], s->score[Subject::Chinese]);
	printf_s("\n\n");
	lst.SetPriorityList({ Subject::Math,Subject::Chinese,Subject::English });
	for (auto s = lst.Start(); s != nullptr; s = lst.Next())
		printf_s("%.2d    %.2d, %.2d, %.2d\n", s->studentID, s->score[Subject::English], s->score[Subject::Chinese], s->score[Subject::Math]);
	for (auto s = lst.PopRecord(); s != nullptr; s = lst.PopRecord())
		delete s;

	return 0;
}
