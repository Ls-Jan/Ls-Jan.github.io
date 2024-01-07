#include<algorithm>
#include<list>
#include<vector>
#include<string>

int main() {
	std::list<int>lst = { 9,7,5,3,1 };
	lst.sort();//排序与否都将对查找结果造成直接影响

	//std::vector<int>lst = { 9,7,5,3,1 };
	//std::sort(lst.begin(), lst.end());//排序与否都将对查找结果造成直接影响

	std::vector<int>test = { 3,4,5,6,7};
	for (auto i = lst.begin(); i != lst.end(); ++i)
		printf_s("%d ", *i);
	printf_s("\n\n");
	for (auto i = test.begin(); i != test.end(); ++i) {
		printf_s("test:%d\n",*i);
		printf_s("binary_search:%d\n", std::binary_search(lst.begin(), lst.end(), *i));
		{
			auto iter = std::lower_bound(lst.begin(), lst.end(), *i);
			printf_s("  lower_bound:%s\n", iter == lst.end()?"-":std::to_string(*iter).data());
		}
		{
			auto iter = std::upper_bound(lst.begin(), lst.end(), *i);
			printf_s("  upper_bound:%s\n", iter == lst.end()?"-":std::to_string(*iter).data());
		}
		printf_s("\n");
	}
	return 0;
}
