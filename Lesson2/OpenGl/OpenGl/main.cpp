#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


void DrawSence()
{
	glClear(GL_COLOR_BUFFER_BIT);//绘制出来       clear background frame object buffer  清除上一帧的前景画面
	/*
	glPointSize(20.0f);
	glEnable(GL_POINT_SMOOTH);//把点画圆了  因为有的人显卡不行 所以要加下面两行代码
	glEnable(GL_BLEND);   //需要打开多重采样
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POINTS);//告诉GPU我要开始画点了   记住 这里是POINTS复数   画三角形 是三角形的复数 画正方形 是正方形的复数
	glColor4ub(255,255,255,255);
	glVertex3f(3.0f,0.0f,-10.0f);//画点的位置 默认眼睛位置在0,0,0位置 看向Z轴的负方向！所以为-10.0f
	glVertex3f(0.0f,0.0f,-10.0f);
	glVertex3f(-3.0f,0.0f,-10.f);
	glEnd();
	*/
	glLineWidth(5.0f);//设置线的宽度
	
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,-10.0f);
	glVertex3f(3.0f,0.0f,-10.f);

	glVertex3f(3.0f,2.0f,-10.0f);
	glVertex3f(-3.0f,0.0f,-10.f);
	glEnd();
	

	/*
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f,0.0f,-10.0f);
	glVertex3f(3.0f,0.0f,-10.f);
	glVertex3f(3.0f,3.0f,-10.f);
	glEnd();*/

	/*
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,0.0f,-10.0f);
	glVertex3f(3.0f,0.0f,-10.f);
	glVertex3f(3.0f,3.0f,-10.f);
	glEnd();*/

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
	pfd.dwFlags = PFD_DOUBLEBUFFER|PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_TYPE_RGBA;//必选的   开启双缓冲 在运行的时候呢！计算的时候是在前景的后面计算，而是在前面的还有前景 这样不会卡
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	int pixelFormatID = ChoosePixelFormat(dc,&pfd);//选择一个颜色格式，如果不符合条件，创建不出这个 ID无效
	SetPixelFormat(dc,pixelFormatID,&pfd);

	HGLRC rc = wglCreateContext(dc);//OpenGL渲染设备
	wglMakeCurrent(dc,rc);//设置成为当前的渲染设 备
	glClearColor(41.0/255.0f,52.0/255.0f,25.0/255.0f,1.0f);

	//
	glMatrixMode(GL_MODELVIEW);//	告诉GPU，我们现在设置modelView Matrix 
	glLoadIdentity();//设置加载 单位矩阵
	glMatrixMode(GL_PROJECTION);//我们现在设置project Matrix 
	glLoadIdentity();//设置加载 单位矩阵
	gluPerspective(45.0f,800.0f/600.0f,0.1f,100.0f);//设置摄像机的可视范围   参数（ 上下夹角，窗口的宽高比，最近的距离，最远的距离）




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