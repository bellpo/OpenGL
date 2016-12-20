#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


void DrawSence()
{
	glClear(GL_COLOR_BUFFER_BIT);//���Ƴ���       clear background frame object buffer  �����һ֡��ǰ������
	/*
	glPointSize(20.0f);
	glEnable(GL_POINT_SMOOTH);//�ѵ㻭Բ��  ��Ϊ�е����Կ����� ����Ҫ���������д���
	glEnable(GL_BLEND);   //��Ҫ�򿪶��ز���
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POINTS);//����GPU��Ҫ��ʼ������   ��ס ������POINTS����   �������� �������εĸ��� �������� �������εĸ���
	glColor4ub(255,255,255,255);
	glVertex3f(3.0f,0.0f,-10.0f);//�����λ�� Ĭ���۾�λ����0,0,0λ�� ����Z��ĸ���������Ϊ-10.0f
	glVertex3f(0.0f,0.0f,-10.0f);
	glVertex3f(-3.0f,0.0f,-10.f);
	glEnd();
	*/
	glLineWidth(5.0f);//�����ߵĿ��
	
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
	case WM_QUIT://�յ��˳�����Ϣ
		PostQuitMessage(0);//��WinMain��ѭ���л��ܵ��˳���Ϣ
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
	wndClass.hbrBackground = NULL;//��������Ϊ�գ�����Ϊ����Ҫ��OpenGLȥ��Ⱦ��
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);//ʹ��Ĭ�ϵļ�ͷ���
	wndClass.hIcon = NULL;//Ӧ�ó����ͼ��
	wndClass.hIconSm = NULL;//������߷����ϵ�Сͼ��
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = RenderWindowProc;//���ڵĴ������ ���û��������¼�ͨ����������Լ�
	wndClass.lpszClassName = L"OpenGLWindow";//Ҫע��Ĵ��ڵ����� �������ڵ�ʱ��ʹ��������ִ�������
	wndClass.lpszMenuName = NULL;//���ڵĲ˵�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//��ʽ  ˮƽ�ػ����ֵ�ػ� CS��CLASS_STYLE

	ATOM atom = RegisterClassEx(&wndClass);
	HWND hwnd = CreateWindowEx(NULL,L"OpenGLWindow",L"OpenGL Render Window",WS_OVERLAPPEDWINDOW,100,100,800,600,NULL,NULL,hInstance,NULL);


	//opengl����Ⱦ
	HDC dc = GetDC(hwnd);//�豸����
	PIXELFORMATDESCRIPTOR pfd;//����һ���豸��ɫ��
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));//���pfd
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER|PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_TYPE_RGBA;//��ѡ��   ����˫���� �����е�ʱ���أ������ʱ������ǰ���ĺ�����㣬������ǰ��Ļ���ǰ�� �������Ῠ
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	int pixelFormatID = ChoosePixelFormat(dc,&pfd);//ѡ��һ����ɫ��ʽ���������������������������� ID��Ч
	SetPixelFormat(dc,pixelFormatID,&pfd);

	HGLRC rc = wglCreateContext(dc);//OpenGL��Ⱦ�豸
	wglMakeCurrent(dc,rc);//���ó�Ϊ��ǰ����Ⱦ�� ��
	glClearColor(41.0/255.0f,52.0/255.0f,25.0/255.0f,1.0f);

	//
	glMatrixMode(GL_MODELVIEW);//	����GPU��������������modelView Matrix 
	glLoadIdentity();//���ü��� ��λ����
	glMatrixMode(GL_PROJECTION);//������������project Matrix 
	glLoadIdentity();//���ü��� ��λ����
	gluPerspective(45.0f,800.0f/600.0f,0.1f,100.0f);//����������Ŀ��ӷ�Χ   ������ ���¼нǣ����ڵĿ�߱ȣ�����ľ��룬��Զ�ľ��룩




	ShowWindow(hwnd,SW_SHOW);   //#define SW_HIDE 0                  //#define SW_SHOW 5
	UpdateWindow(hwnd);
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))//����Ϣ������ȡ����Ϣ��PM_REMOVEȡ������Ϣ������ȥ����Ϣ
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);//ת����Ӧ�ó�����ʶ����Ϣ��ʽ
			DispatchMessage(&msg);//�ɷ���ȥ�����ߴ��ڹ��̺���
		}
		DrawSence();


		SwapBuffers(dc);//ǰ�󻺳�������
	}
	return 0;
}