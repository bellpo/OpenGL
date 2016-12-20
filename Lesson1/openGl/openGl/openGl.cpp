#include <windows.h>


LRESULT CALLBACK RenderWindowProc(HWND hwnd, UINT  msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_QUIT://收到退出的消息
		PostQuitMessage(0);//在WinMain的循环中会受到退出消息
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
	}

}



INT WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
	WNDCLASSEX wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;//背景设置为空，是因为我们要用OpenGL去渲染的
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);//使用默认的箭头鼠标
	wndClass.hIcon = NULL;//应用程序的图标
	wndClass.hIconSm = NULL;//窗口左边方向上的小图标
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = RenderWindowProc;//窗口的处理过程 ，用户鼠标键盘事件通过这个传给自己
	wndClass.lpszClassName = L"OpenGLWindow";//要注册的窗口的名字 创建窗口的时候使用这个名字创建窗口
	wndClass.lpszMenuName = NULL;//窗口的菜单
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//方式  水平重绘和数值重绘 CS是CLASS_STYLE

	ATOM atom = RegisterClassEx(&wndClass);

	HWND hwnd = CreateWindowEx(NULL,L"OpenGLWindow",L"OpenGL Render Window",WS_OVERLAPPEDWINDOW,100,100,800,600,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd,SW_SHOW);//#define SW_HIDE             0
	//#define SW_SHOWNORMAL       1
	//#define SW_NORMAL           1
	//#define SW_SHOWMINIMIZED    2
	//#define SW_SHOWMAXIMIZED    3
	//#define SW_MAXIMIZE         3
	//#define SW_SHOWNOACTIVATE   4
	//#define SW_SHOW             5
	UpdateWindow(hwnd);
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))//从消息队列中取出消息，PM_REMOVE取完后从消息队列中去除消息
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);//转换成应用程序认识的消息格式
			DispatchMessage(&msg);//派发出去，告诉窗口过程函数

		}

	}

	return 0;

}