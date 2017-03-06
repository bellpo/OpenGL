#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


void DrawSence()
{
	glClear(GL_COLOR_BUFFER_BIT);//绘制出来       clear background frame object buffer  清除上一帧的前景画面
	glColor4ub(255,255,255,255);//设置当前的颜色是白色 则后面画的点都是用当前的颜色
	glPointSize(5.0f);
	glBegin(GL_POINTS);//
	glVertex3f(0,0,-0.2f);//设置到世界坐标系
	glEnd();
}

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
	//register window
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;//设置WNDCLASSEX的额外的格式大小为0
	wndClass.cbSize = sizeof(WNDCLASSEX);//结构体的大小
	wndClass.cbWndExtra = 0;//不需要为窗口得到额外的空间
	wndClass.hbrBackground = NULL;//背景设置为空，是因为我们要用OpenGL去渲染的
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);//使用默认的箭头鼠标
	wndClass.hIcon = NULL;//应用程序的图标
	wndClass.hIconSm = NULL;//窗口左边方向上的小图标
	wndClass.hInstance = hInstance;//程序的实例
	wndClass.lpfnWndProc = RenderWindowProc;//窗口的处理过程 ，用户鼠标键盘事件通过这个传给自己
	wndClass.lpszClassName = L"OpenGLWindow";//要注册的窗口的名字 创建窗口的时候使用这个名字创建窗口
	wndClass.lpszMenuName = NULL;//窗口的菜单
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//方式  水平重绘和数值重绘 CS是CLASS_STYLE

	ATOM atom = RegisterClassEx(&wndClass);
	//create window
	HWND hwnd = CreateWindowEx(NULL,L"OpenGLWindow",L"OpenGL Render Window",WS_OVERLAPPEDWINDOW,100,100,1280,720,NULL,NULL,hInstance,NULL);


	//opengl的渲染
	HDC dc = GetDC(hwnd);//设备环境
	PIXELFORMATDESCRIPTOR pfd;//创建一个设备颜色表 帮我们选取一个opengl渲染像素格式
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));//清空pfd
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER|PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_TYPE_RGBA;//必选的   开启双缓冲 在运行的时候呢！计算的时候是在前景的后面计算，而是在前面的还有前景 这样不会卡
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	int pixelFormatID = ChoosePixelFormat(dc,&pfd);//选择一个颜色格式，如果不符合条件，创建不出这个 ID无效
	SetPixelFormat(dc,pixelFormatID,&pfd);
	HGLRC rc = wglCreateContext(dc);//OpenGL渲染设备 set opengl context complete

	wglMakeCurrent(dc,rc);//设置成为当前的渲染设备
	glClearColor(41.0/255.0f,52.0/255.0f,25.0/255.0f,1.0f);//set clear color for backgroud
	//
	glMatrixMode(GL_PROJECTION);//我们现在设置project Matrix 
	gluPerspective(45.0f,800.0f/600.0f,0.1f,100.0f);//设置摄像机的可视范围   参数（ 上下夹角，窗口的宽高比，最近的距离，最远的距离）
	glMatrixMode(GL_MODELVIEW);//	告诉GPU，我们现在设置modelView Matrix 
	glLoadIdentity();//设置加载 单位矩阵
	



	//show window
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
		DrawSence();


		SwapBuffers(dc);//前后缓冲区交换
	}
	return 0;
}