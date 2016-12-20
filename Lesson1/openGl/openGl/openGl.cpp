#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib,"opengl32.lib")

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

	
	//opengl的渲染
	HDC dc = GetDC(hwnd);//设备环境
	PIXELFORMATDESCRIPTOR pfd;//创建一个设备颜色表
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));//清空pfd
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER|PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_TYPE_RGBA;//必选的
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	int pixelFormatID = ChoosePixelFormat(dc,&pfd);//选择一个颜色格式，如果不符合条件，创建不出这个 ID无效
	SetPixelFormat(dc,pixelFormatID,&pfd);

	HGLRC rc = wglCreateContext(dc);//OpenGL渲染设备
	wglMakeCurrent(dc,rc);//设置成为当前的渲染设 备
	glClearColor(41.0/255.0f,41.0/255.0f,121.0/255.0f,1.0f);
	

	ShowWindow(hwnd,SW_SHOW);   //#define SW_HIDE 0                  //#define SW_SHOW 5
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
		glClear(GL_COLOR_BUFFER_BIT);//绘制出来
		SwapBuffers(dc);//前后缓冲区交换
	}
	return 0;
}