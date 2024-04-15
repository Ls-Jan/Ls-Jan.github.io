
#include<stdio.h>

class A {
public:
	A(bool isPublic = true) {
		if (isPublic)
			this->Print("aaa");
		else 
			this->__Print("aaa");
	}
public:
	virtual void Print(const char* ch) {
		printf_s(">>>[PUBLIC]A-%s\n", ch);
	}
private:
	virtual void __Print(const char* ch) {
		printf_s(">>>[PRIVATE]A-%s\n", ch);
	}
};

class B :public A {
public:
	B(bool isPublic=true) :A(isPublic) {
		if (isPublic)
			this->Print("bbb");
		else
			this->__Print("bbb");
	}
public:
	virtual void Print(const char* ch) {
		printf_s(">>>[PUBLIC]B-%s\n", ch);
	}
private:
	virtual void __Print(const char* ch) {
		printf_s(">>>[PRIVATE]B-%s\n", ch);
	}
};

int main() {
	bool flags[] = { false,true };
	bool flag = false;
	printf_s("It's C++\n");
	for (auto i = 0; i < 2; ++i) {
		flag = flags[i];
		printf_s("\nisPublic=%s\n", flag ? "True" : "False");
		B b(flag);
	}
	return 0;
}
