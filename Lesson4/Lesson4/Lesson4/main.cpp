#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
//CCW face:ccw- counter clock wind

void DrawSence()
{
	glClear(GL_COLOR_BUFFER_BIT);//���Ƴ���       clear background frame object buffer  �����һ֡��ǰ������
	glColor4ub(0,255,255,255);//���õ�ǰ����ɫ�ǰ�ɫ ����滭�ĵ㶼���õ�ǰ����ɫ
	glPointSize(5.0f);
	/*
	glBegin(GL_TRIANGLES );// ����������Ϊһ��������
	glVertex3f(0,0,-10.2f);//���õ���������ϵ
	glColor4ub(0,0,0,255);
	glVertex3f(5.0f,0,-10.2f);//���õ���������ϵ
	glVertex3f(5.0f,3.0f,-10.2f);//���õ���������ϵ 
	//����������ķ�������ʱ�뷽�� ���������������ʾ�������˳ʱ�뷽�����Ƿ��棬�޷���ʾ
	glEnd();
	*/
	
	/*
	glBegin(GL_TRIANGLE_STRIP );// ���һ�ŵ��������㣬���ѡ�� n+1��n+2, n+3��������Σ���1 ���1,2,3 Ȼ����˳��1��2��3����   �����ż���㣬��2   ���ѡ�� 2 3 4 ���ǻ����Ǵ�3�Ż���2�ڻ���4.
	glVertex3f(0,0,-10.2f);//���õ���������ϵ
	glColor4ub(0,0,0,255);
	glVertex3f(5.0f,0,-10.2f);//���õ���������ϵ
	glVertex3f(5.0f,3.0f,-10.2f);//���õ���������ϵ  //����������ķ�������ʱ�뷽�� ���������������ʾ�������˳ʱ�뷽�����Ƿ��棬�޷���ʾ
	glEnd();*/
	glBegin(GL_TRIANGLE_FAN );//���ε㣬�ӵ�һ��Ϊԭ�㣬��������ÿ������͵�һ�������һ�������Σ���һ�ŵ��123������������ 134������������145
	glVertex3f(0,0,-10.2f);//���õ���������ϵ
	glColor4ub(0,0,0,255);
	glVertex3f(5.0f,0,-10.2f);//���õ���������ϵ
	glVertex3f(5.0f,3.0f,-10.2f);//���õ���������ϵ 
	//����������ķ�������ʱ�뷽�� ���������������ʾ�������˳ʱ�뷽�����Ƿ��棬�޷���ʾ



	glEnd();

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
	//register window
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;//����WNDCLASSEX�Ķ���ĸ�ʽ��СΪ0
	wndClass.cbSize = sizeof(WNDCLASSEX);//�ṹ��Ĵ�С
	wndClass.cbWndExtra = 0;//����ҪΪ���ڵõ�����Ŀռ�
	wndClass.hbrBackground = NULL;//��������Ϊ�գ�����Ϊ����Ҫ��OpenGLȥ��Ⱦ��
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);//ʹ��Ĭ�ϵļ�ͷ���
	wndClass.hIcon = NULL;//Ӧ�ó����ͼ��
	wndClass.hIconSm = NULL;//������߷����ϵ�Сͼ��
	wndClass.hInstance = hInstance;//�����ʵ��
	wndClass.lpfnWndProc = RenderWindowProc;//���ڵĴ������� ���û��������¼�ͨ����������Լ�
	wndClass.lpszClassName = "OpenGLWindow";//Ҫע��Ĵ��ڵ����� �������ڵ�ʱ��ʹ��������ִ�������
	wndClass.lpszMenuName = NULL;//���ڵĲ˵�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//��ʽ  ˮƽ�ػ����ֵ�ػ� CS��CLASS_STYLE

	ATOM atom = RegisterClassEx(&wndClass);
	//create window
	HWND hwnd = CreateWindowEx(NULL,"OpenGLWindow","OpenGL Render Window",WS_OVERLAPPEDWINDOW,100,100,1280,720,NULL,NULL,hInstance,NULL);


	//opengl����Ⱦ
	HDC dc = GetDC(hwnd);//�豸����
	PIXELFORMATDESCRIPTOR pfd;//����һ���豸��ɫ�� ������ѡȡһ��opengl��Ⱦ���ظ�ʽ
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
	HGLRC rc = wglCreateContext(dc);//OpenGL��Ⱦ�豸 set opengl context complete

	wglMakeCurrent(dc,rc);//���ó�Ϊ��ǰ����Ⱦ�豸
	glClearColor(41.0f/255.0f,52.0f/255.0f,25.0f/255.0f,1.0f);//set clear color for backgroud
	//
	glMatrixMode(GL_PROJECTION);//������������project Matrix 
	gluPerspective(45.0f,800.0f/600.0f,0.1f,100.0f);//����������Ŀ��ӷ�Χ   ������ ���¼нǣ����ڵĿ��߱ȣ�����ľ��룬��Զ�ľ��룩
	glMatrixMode(GL_MODELVIEW);//	����GPU��������������modelView Matrix 
	glLoadIdentity();//���ü��� ��λ����
	glEnable(GL_CULL_FACE);// ֻ������ʾ����
	glEnable(GL_CW);//Ĭ������ʱ�������棬�������������˳ʱ��Ϊ����


	//show window
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