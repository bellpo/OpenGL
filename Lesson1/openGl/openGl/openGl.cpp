#include <windows.h>


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
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))//����Ϣ������ȡ����Ϣ��PM_REMOVEȡ������Ϣ������ȥ����Ϣ
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);//ת����Ӧ�ó�����ʶ����Ϣ��ʽ
			DispatchMessage(&msg);//�ɷ���ȥ�����ߴ��ڹ��̺���

		}

	}

	return 0;

}