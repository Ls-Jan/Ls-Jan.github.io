
#include <string.h>  
#include <stdarg.h>
#include<vector>

/// ������������Ϊ������ִ���ʽ����
/// ��ͨ�����ִ���ʽ����ͬ���ǣ�Set_Format����Ĳ�����ָ���������ֵ��
/// ��˸�ʽ����Ϊ���Ƴٵ�Get_String�н��еģ�������һ���̶ȵļ���/��̹��ܡ�
/// ����ر�֤��Set_Format�д����ָ���ڵ���Get_Stringʱ����Ȼ��Ч���������ֲ��ɲ�Ľ����
class XJ_FormatString {
private:
	std::vector<void*>args;
	std::vector<int>pst;
	const char* fmt = nullptr;
	char* tx = nullptr;
	int bufSize = 0;
private:
	int __Set_fmt_pst(const char* fmt, bool doNotAlter = false) {
		int weight = 1;
		int count = 0;
		std::vector<int>pst;
		for (auto p = fmt; *p != '\0'; ++p) {//ͳ�Ƶ�����%����������¼��Ӧλ��
			if (*p == '%') {
				count += weight;
				if (weight > 0)
					pst.push_back(p - fmt);
				else
					pst.pop_back();
				weight = -weight;
			}
			else {
				weight = 1;
			}
		}
		if (!doNotAlter) {
			this->pst = pst;
			this->fmt = fmt;
		}
		return count;
	}
	void __Set_args(va_list args, int count) {
		this->args.clear();
		this->args.push_back((void*)"");
		for (auto i = 0; i < count; ++i) {
			this->args.push_back(va_arg(args, void*));
		}
		va_end(args);
	}
public:
	XJ_FormatString() {
		this->tx = new char[1];
		Set_BufSize(BUFSIZ);
	}
	~XJ_FormatString() {
		delete[] this->tx;
	}
	void Set_BufSize(int size) {
		delete[] this->tx;
		this->tx = new char[size];
		this->bufSize = size;
		memset(this->tx, 0, size);
	}
	void Set_Format(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		int count = this->__Set_fmt_pst(fmt);
		this->__Set_args(args, count);
		va_end(args);
	}
	void Set_Format_Va(const char* fmt, va_list args) {
		int count = this->__Set_fmt_pst(fmt);
		this->__Set_args(args, count);
	}
	void Set_Format_Ptr(const char* fmt, std::vector<void*>args) {
		int count = this->__Set_fmt_pst(fmt);
		this->args = args;
		this->args.insert(this->args.begin(), (void*)"");
	}
	const char* Get_String() {
		int count = this->bufSize;
		int len = strnlen_s(this->fmt, BUFSIZ) + 1;
		char* fmt = new char[len];
		memcpy(fmt, this->fmt, len);

		auto f = fmt;
		auto t = this->tx;
		auto a = this->args.begin();
		for (auto p = this->pst.begin(); p != this->pst.end(); ++p, ++a) {
			fmt[*p] = '\0';
			len = vsprintf_s(t, count, f, (char*)(*a));
			f = fmt + *p;
			t += len;
			count -= len;
			fmt[*p] = '%';
		}
		vsprintf_s(t, count, f, (char*)(*a));
		delete[] fmt;
		return this->tx;
	}
	int Get_FormatArgsCount(const char* fmt) {//ͳ���ִ��е�����%����
		int weight = 1;
		int count = 0;
		for (auto p = fmt; *p != '\0'; ++p) {
			if (*p == '%') {
				count += weight;
				weight = -weight;
			}
			else {
				weight = 1;
			}
		}
		return count;
	}
};

