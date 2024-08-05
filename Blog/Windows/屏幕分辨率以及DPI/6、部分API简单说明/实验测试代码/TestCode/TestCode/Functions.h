

#include <windows.h>
#include<shellscalingapi.h>
#include"XJ_FormatString.h"
int XJ_AlignPrint(int width, int align, const char* fmt, ...);

//所有的函数都会返回一个布尔值，可以由此决定是否将输出结果清除
namespace Functions {
	int txAlign = 0;//对齐方式，与0的大小关系分为三种情况，分别对应左中右；
	bool GetDpiForWindow(HWND hwnd, int dpiMin, int dpiMax) {
		static int txWidth = 8;
		int dpi = ::GetDpiForWindow(hwnd);
		::XJ_AlignPrint(txWidth, txAlign, "%d", dpi);
		return dpi >= dpiMin && dpi <= dpiMax;
	}

	bool GetWindowTextA(HWND hwnd, std::vector<const char*>titleKeys) {
		static int txWidth = 36;
		char title[BUFSIZ] = "";
		memset(title, sizeof(title), 0);
		::GetWindowTextA(hwnd, title, BUFSIZ);
		bool flag = titleKeys.empty();
		if (!flag) {
			for (auto t = titleKeys.begin(); t != titleKeys.end(); ++t) {
				if (strstr(title, *t) != nullptr) {
					flag = true;
					break;
				}
			}
		}
		int len = ::XJ_AlignPrint(txWidth, txAlign, "%s", title);
		if (flag && txWidth < len)
			txWidth = len + 2;
		return flag;
	}

	bool LogicalToPhysicalPoint(HWND hwnd, POINT pt) {
		static int txWidth = 16;
		POINT pto = pt;
		::LogicalToPhysicalPoint(hwnd, &pt);
		::XJ_AlignPrint(txWidth, txAlign, "(%d,%d)", pt.x, pt.y);
		return pt.x != pto.x || pt.y != pto.y;
	}

	bool LogicalToPhysicalPointForPerMonitorDPI(HWND hwnd, POINT pt) {
		static int txWidth = 16;
		POINT pto = pt;
		::LogicalToPhysicalPointForPerMonitorDPI(hwnd, &pt);
		::XJ_AlignPrint(txWidth, txAlign, "(%d,%d)", pt.x, pt.y);
		return pt.x != pto.x || pt.y != pto.y;
	}

	bool GetMonitorInfoA(HMONITOR hMonitor) {
		static int txWidth = 24;
		MONITORINFOEXA info;
		info.cbSize = sizeof(info);
		::GetMonitorInfoA(hMonitor, &info);
		auto p = &info.rcMonitor;
		::XJ_AlignPrint(txWidth, txAlign, "(%d,%d,%d,%d)", p->left, p->top, p->right, p->bottom);
		return true;
	}

	bool GetDeviceCaps(HDC hdc, const char* fmt, ...) {
		static int txWidth = 24;
		XJ_FormatString fs;
		std::vector<void*>rst;
		va_list args;
		va_start(args, fmt);
		int count = fs.Get_FormatArgsCount(fmt);
		for (auto i = 0; i < count; ++i) {
			rst.push_back(new int(::GetDeviceCaps(hdc, va_arg(args, int))));
		}
		va_end(args);

		fs.Set_Format_Ptr(fmt, rst);
		auto tx = fs.Get_String();
		int len = ::XJ_AlignPrint(txWidth, txAlign, "%s", tx);
		if (txWidth < len)
			txWidth = len + 2;
		for (auto p = rst.begin(); p != rst.end(); ++p)
			delete (int*)*p;
		return true;
	}

	bool EnumDisplaySettingsA(LPCSTR deviceName, const char* fmt, ...) {
		static int txWidth = 16;
		DEVMODEA dm;
		XJ_FormatString fs;
		std::vector<void*>ptr;
		dm.dmSize = sizeof(dm);
		dm.dmDriverExtra = 0;
		::EnumDisplaySettingsA(deviceName, ENUM_CURRENT_SETTINGS, &dm);
		va_list args;
		va_start(args, fmt);
		int count = fs.Get_FormatArgsCount(fmt);
		for (auto i = 0; i < count; ++i) {
			ptr.push_back((char*)&dm + (int)va_arg(args, void*));
		}
		va_end(args);

		fs.Set_Format_Ptr(fmt, ptr);
		auto tx = fs.Get_String();
		int len = ::XJ_AlignPrint(txWidth, txAlign, "%s", tx);
		if (txWidth < len)
			txWidth = len + 2;
		return true;
	}

	bool GetPhysicalCursorPos() {
		static int txWidth = 16;
		POINT pt;
		::GetPhysicalCursorPos(&pt);
		::XJ_AlignPrint(txWidth, txAlign, "(%d,%d)", pt.x, pt.y);
		return true;
	}

	bool GetCursorPos() {
		static int txWidth = 16;
		POINT pt;
		::GetPhysicalCursorPos(&pt);
		::XJ_AlignPrint(txWidth, txAlign, "(%d,%d)", pt.x, pt.y);
		return true;
	}

	bool GetScaleFactorForMonitor(HMONITOR hMonitor) {
		static int txWidth = 6;
		DEVICE_SCALE_FACTOR scale;
		::GetScaleFactorForMonitor(hMonitor, &scale);
		::XJ_AlignPrint(txWidth, txAlign, "%d", scale);
		return true;
	}

	bool GetDpiForMonitor(HMONITOR hMonitor) {
		static int txWidth = 12;
		UINT x, y;
		MONITOR_DPI_TYPE type[4] = {
			MDT_ANGULAR_DPI ,
			MDT_EFFECTIVE_DPI ,
			MDT_RAW_DPI ,
			MDT_DEFAULT
		};
		printf_s("  [");
		for (auto i = 0; i < sizeof(type) / sizeof(int); ++i) {
			::GetDpiForMonitor(hMonitor, type[i], &x, &y);
			::XJ_AlignPrint(txWidth, txAlign, "(%d,%d)", x, y);
		}
		printf_s("]  ");
		return true;
	}
}





