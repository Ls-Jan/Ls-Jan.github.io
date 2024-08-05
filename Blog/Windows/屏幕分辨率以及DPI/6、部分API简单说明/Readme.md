


以下内容是根据本机win10经过测试得出的个人总结。

说明：没有直接手段获取屏幕DPI和适宜DPI，win10以后才能直接获取软件DPI和窗口DPI，但是软件DPI并没有多大用途。


<br>

# 有效API

- <**winVista**>[``SetProcessDPIAware``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-setprocessdpiaware)：设置进程DPI感知模式为静态感知。

- <**win10**>[``SetProcessDpiAwarenessContext``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-setprocessdpiawarenesscontext)：设置进程DPI感知模式，该API仅win10及以后版本可用。

- <**win10**>[``SetThreadDpiAwarenessContext``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-setthreaddpiawarenesscontext)：设置当前线程的DPI感知模式，该API仅win10及以后版本可用。

- <**win10**>[``GetDpiForSystem``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getdpiforsystem)：获取软件DPI，该API仅win10及以后版本可用。实际上由于软件DPI并没有什么作用，该API的存在价值甚至不如``GetDpiForWindow``。

- <**win10**>[``GetDpiForWindow``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getdpiforwindow)：获取指定窗口``HWND``的窗口DPI，该API仅win10及以后版本可用。==GetDpiForWindow的返回值与目标窗口的DPI感知模式有关==，此不赘述。

- [``CreateDC``](https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-createdca)：==CreateDC可以获取监视器的``HDC``==，调用方式为``CreateDC(TEXT("DISPLAY"), DeviceName, NULL, NULL)``，``DeviceName``需使用``EnumDisplayDevices``获取，实测``DeviceName``为空时返回的是主监视器的``HDC``。

- [``MonitorFromPoint``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-monitorfrompoint)和[``MonitorFromRect``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-monitorfromrect)：获取指定坐标所在的屏幕``HMONITOR``，依赖当前程序所设置的DPI模式，即仅在DPI动态感知下才能获取到准确无误的结果。

- [``EnumDisplayMonitors``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-enumdisplaymonitors)：该函数需要一个回调函数[``MONITORENUMPROC``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nc-winuser-monitorenumproc)，调用方式是``EnumDisplayMonitors(NULL, NULL, (MONITORENUMPROC)MonProc, NULL)``。==EnumDisplayMonitors可以获取到监视器的``HMONITOR``以及监视器的虚拟屏幕矩形坐标==。

- [``GetMonitorInfo``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getmonitorinfoa)：==传入监视器的``HMONITOR``即可获取对应的虚拟屏幕矩形坐标==，需要使用到结构体[``MONITORINFO``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-monitorinfo)，该结构体的属性``rcMonitor``存储虚拟屏幕矩形坐标。

- [``EnumWindows``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-enumwindows)：该函数需要一个回调函数[``EnumWindowsProc``](https://learn.microsoft.com/zh-cn/previous-versions/windows/desktop/legacy/ms633498(v=vs.85))，会遍历并获取每个窗口的``HWND``(不包括子窗口)。

- [``EnumDisplayDevices``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-enumdisplaydevicesa)：该函数可以不需要额外创建一个回调函数就能轻松遍历所有监视器，只不过获取到的[``DISPLAY_DEVICE``](https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/ns-wingdi-display_devicea)所携带的信息比较有限，倒不如说 ==EnumDisplayDevicesA只能获取到监视器的名称DISPLAY_DEVICE::DeviceName==，通常搭配``EnumDisplaySettings``使用。

- [``EnumDisplaySettings``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-enumdisplaysettingsa)：==EnumDisplaySettings可以根据监视器名称直接获取对应的物理屏幕大小而无需设置DPI感知==，通常搭配``EnumDisplayDevices``使用，调用方式为``EnumDisplaySettings(DeviceName,ENUM_CURRENT_SETTINGS,&dm)``。[``DEVMODEA``](https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/ns-wingdi-devmodea)中的``dmPelsWidth``和``dmPelsHeight``记录着物理屏幕的宽和高。


<br>


# 垃圾API
要么过时，要么返回的数据不具有参考价值(或者说返回的数据不知道能拿来干嘛)。

- <**winVista**>[``LogicalToPhysicalPoint``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-logicaltophysicalpoint)：官方说明已经明确指出，这个API(以及同类API)在win8.1起已经废弃，或者说调用了也没实际作用。

- <**win8.1**>[``LogicalToPhysicalPointForPerMonitorDPI``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-logicaltophysicalpointforpermonitordpi)：实测传入的绝大多数``HWND``不使坐标发生变化，怀疑其实用性。

- <**win8.1**>[``GetScaleFactorForMonitor``](https://learn.microsoft.com/zh-cn/windows/win32/api/shellscalingapi/nf-shellscalingapi-getscalefactorformonitor)：win8.1留下的垃圾API，实测得到的数据无意义。使用枚举[``DEVICE_SCALE_FACTOR``](https://learn.microsoft.com/zh-cn/windows/win32/api/shtypes/ne-shtypes-device_scale_factor)

- <**win8.1**>[``GetDpiForMonitor``](https://learn.microsoft.com/zh-cn/windows/win32/api/shellscalingapi/nf-shellscalingapi-getdpiformonitor)：win8.1留下的垃圾API，实测得到的数据无意义。使用枚举[``MONITOR_DPI_TYPE``](https://learn.microsoft.com/zh-cn/windows/win32/api/shellscalingapi/ne-shellscalingapi-monitor_dpi_type)

- <**win8.1**>[``SetProcessDpiAwareness``](https://learn.microsoft.com/zh-cn/windows/win32/api/shellscalingapi/nf-shellscalingapi-setprocessdpiawareness)：设置DPI感知模式，不应该使用这个函数。使用枚举[``PROCESS_DPI_AWARENESS``](https://learn.microsoft.com/zh-cn/windows/win32/api/shellscalingapi/ne-shellscalingapi-process_dpi_awareness)

- [``GetDeviceCaps``](https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-getdevicecaps)：使用索引值``HORZRES``和``VERTRES``可以获取指定屏幕的虚拟屏幕宽高,如果传入的是窗口HDC则获取到的是主屏相关信息。很明显这个只能获取虚拟屏幕宽高的API并没什么用，可以把它扔进垃圾堆里了。

- [``GetSystemMetrics``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getsystemmetrics)：获取到的像素都是基于虚拟屏幕的而不是物理屏幕。如果只谈论获取监视器信息的话这个函数的确是个垃圾函数，因为它只能获取主屏的虚拟屏幕大小。

- [``SystemParametersInfo``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-systemparametersinfoa)：该API可以获取或设置大量的系统参数。如果只谈论获取监视器信息的话这个函数的确是个垃圾函数，因为它只能获取主屏的虚拟屏幕的矩形坐标。


# 未测试API：

- <**win10**>[``SetDialogDpiChangeBehavior``](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-setdialogdpichangebehavior)：似乎和DPI动态感知v2有关？没了解，没试过。


<br>

# 参考：

- GetDeviceCaps获取的物理屏幕尺寸不是我屏幕的实际物理尺寸：[https://www.coder.work/article/1201807](https://www.coder.work/article/1201807)。
- 从外部窗口的 GetWindowRect 获取 DPI 感知正确的 RECT：[https://www.coder.work/article/552912](https://www.coder.work/article/552912)
- windows屏幕分辨率及系统缩放获取方法大全：[https://blog.csdn.net/siyacaodeai/article/details/112971964](https://blog.csdn.net/siyacaodeai/article/details/112971964)
- 使用Win32 API获得真实屏幕分辨率：[https://cloud.tencent.com/developer/ask/sof/106669398](https://cloud.tencent.com/developer/ask/sof/106669398)

