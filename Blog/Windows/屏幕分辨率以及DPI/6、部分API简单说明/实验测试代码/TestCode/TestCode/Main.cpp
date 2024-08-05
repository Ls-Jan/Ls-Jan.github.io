
// ����˵����Ϊ��ʹ��������������ԭ����500�еĵ��ļ�������в�֣�
// ���ڲ��ٺ�������ֱ��д����ͷ�ļ��У��ⲻ��һ�ݹ淶�Ĵ��룻
// ���ټ�������cpp�ļ���Ϊ�˱��⸴�ӻ���
// ��Ϊ���ʾ�����������ڲ���API�ģ�����д�Ĺ��ڷ��ӣ�


#include"Functions.h"

BOOL CALLBACK EnumWindowsProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
) {
	bool flag = true;
	flag = flag && (Functions::GetWindowTextA(hwnd, { "explorer" }) || false);
	flag = flag && (Functions::GetDpiForWindow(hwnd, 0, INT_MAX) || true);
	flag = flag && (Functions::LogicalToPhysicalPoint(hwnd, { 200,200 }) || true);
	flag = flag && (Functions::LogicalToPhysicalPointForPerMonitorDPI(hwnd, { 200,200 }) || true);
	if (flag) {
		//HDC hdc = GetWindowDC(hwnd);
		//printf_s("%d,%d\n", GetDeviceCaps(hdc, HORZRES), GetDeviceCaps(hdc, VERTRES));//��GetDeviceCaps���봰��HDC�Ľ���ʹ�������HDC����Ϊһ��
		//ReleaseDC(hwnd, hdc);
		printf_s("\n");
	}
	else
		printf("\33[2K\r");
	return TRUE;
}

BOOL MonProc(
	HMONITOR hMonitor,
	HDC hDC,
	LPRECT pRect,
	LPARAM pExtra
) {
	bool flag = true;
	::XJ_AlignPrint(24, 0, "(%d,%d,%d,%d)", pRect->left, pRect->top, pRect->right, pRect->bottom);
	flag = flag && (Functions::GetMonitorInfoA(hMonitor) || true);
	flag = flag && (Functions::GetScaleFactorForMonitor(hMonitor) || true);
	flag = flag && (Functions::GetDpiForMonitor(hMonitor) || true);
	if (flag)
		printf_s("\n");
	else
		printf("\33[2K\r");
	return TRUE;
}

void EnumDisplayDevicesProc(
	LPCSTR deviceName
) {
	bool flag = true;
	auto hdc = CreateDCA("DISPLAY", deviceName, NULL, NULL);
	flag = flag && (Functions::GetDeviceCaps(hdc, "[(%d,%d)  (%d,%d)]", HORZSIZE, VERTSIZE, HORZRES, VERTRES) || true);
	flag = flag && (Functions::EnumDisplaySettingsA(deviceName, "%d,%d", &DEVMODEA::dmPelsWidth, &DEVMODEA::dmPelsHeight) || true);
	if (flag)
		printf_s("\n");
	else
		printf("\33[2K\r");
	DeleteDC(hdc);
}




int main() {
	bool flag_HWND = false;
	bool flag_HDC = false;
	bool flag_HMONITOR = false;
	bool flag_SystemParametersInfo = false;
	bool flag_GetSystemMetrics = false;
	bool flag_GetCursorPos = false;
	bool flag_Other = false;

	flag_HWND = true;
	flag_HDC = true;
	flag_HMONITOR = true;
	flag_SystemParametersInfo = true;
	flag_GetSystemMetrics = true;
	flag_GetCursorPos = true;
	flag_Other = true;

	printf_s("SetProcessDPIAware()\n"); SetProcessDPIAware();
	//printf_s("SetThreadDpiAwarenessContext(V1)\n"); SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
	//printf_s("SetThreadDpiAwarenessContext(V2)\n"); SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	if (true) {
		if (flag_SystemParametersInfo) {
			printf_s(">>>SystemParametersInfoA\n");
			RECT rect;
			SystemParametersInfoA(SPI_GETWORKAREA, 0, &rect, 0);
			::XJ_AlignPrint(24, 0, "(%d,%d,%d,%d)", rect.left, rect.top, rect.right, rect.bottom);
			printf_s("\n\n");
		}

		if (flag_GetSystemMetrics) {
			printf_s(">>>GetSystemMetrics\n");
			::XJ_AlignPrint(24, 0, "(%d,%d)", GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN));
			::XJ_AlignPrint(24, 0, "(%d,%d)", GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			::XJ_AlignPrint(24, 0, "(%d,%d)", GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));
			::XJ_AlignPrint(24, 0, "(%d,%d)", GetSystemMetrics(SM_XVIRTUALSCREEN), GetSystemMetrics(SM_YVIRTUALSCREEN));
			printf_s("\n\n");
		}

		if (flag_GetCursorPos) {
			printf_s(">>>GetCursorPos\n");
			Functions::GetCursorPos();
			Functions::GetPhysicalCursorPos();
			printf_s("\n\n");
		}

		if (flag_Other) {
			//HWND hwnd = GetDesktopWindow();
			//HDC hdc = GetDC(hwnd);
			//HDC hdc = GetWindowDC(hwnd);
			//ReleaseDC(hwnd, hdc);
			printf_s("\n\n");
		}
		printf_s("\n\n");
	}

	if (flag_HWND) {
		printf_s(">>>HWND:    GetWindowTextA  GetDpiForWindow  LogicalToPhysicalPoint  LogicalToPhysicalPointForPerMonitorDPI\n");
		EnumWindows(EnumWindowsProc, NULL);
		printf_s("\n\n");
	}

	if (flag_HDC) {
		printf_s(">>>HDC:    GetDeviceCaps  EnumDisplaySettingsA\n");
		DISPLAY_DEVICEA dd;
		dd.cb = sizeof(dd);
		for (auto index = 0; EnumDisplayDevicesA(NULL, index, &dd, 0); ++index) {
			if ((dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) == DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
				EnumDisplayDevicesProc(dd.DeviceName);
			}
		}
		EnumDisplayDevicesProc(nullptr);
		printf_s("\n\n");
	}

	if (flag_HMONITOR) {
		printf_s(">>>HMONITOR:    RECT  GetMonitorInfoA  GetScaleFactorForMonitor  GetDpiForMonitor\n");
		int sleepTime = 3000;
		int loopCount = 1;
		for (auto i = 0; ; ) {
			EnumDisplayMonitors(NULL, NULL, (MONITORENUMPROC)MonProc, NULL);
			if (++i >= loopCount)
				break;
			Sleep(sleepTime);
		}
		printf_s("\n\n");
	}

	return 0;
}

