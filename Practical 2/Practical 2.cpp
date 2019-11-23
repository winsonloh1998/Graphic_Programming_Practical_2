#include <Windows.h>
#include <math.h>
#include <gl/GL.h>

#define WINDOW_TITLE "Practical 2"

#pragma comment (lib, "OpenGL32.lib")

int displayKey = 1;
float r = 0.0, g = 0.0, b = 0.0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == 0x31)
			displayKey = 1;
		else if (wParam == 0x32)
			displayKey = 2;
		else if (wParam == 0x33)
			displayKey = 3;
		else if (wParam == 0x34)
			displayKey = 4;
		else if (wParam == 0x25)
			//Move to Left
			glTranslatef(-0.05, 0.0, 0.0);
		else if (wParam == 0x27)
			//Move to Right
			glTranslatef(0.05, 0.0, 0.0);
		else if (wParam == 0x26)
			//Move Upwards
			glTranslatef(0.0, 0.05, 0.0);
		else if (wParam == 0x28)
			//Move Downwards
			glTranslatef(0.0, -0.05, 0.0);
		else if (wParam == 0x52) {
			r = 1.0;
			g = 0.0;
			b = 0.0;
		}
		else if (wParam == 0x47) {
			r = 0.0;
			g = 1.0;
			b = 0.0;
		}
		else if (wParam == 0x42) {
			r = 0.0;
			g = 0.0;
			b = 1.0;
		}
		else if (wParam == 0x20) {
			r = 0.0;
			g = 0.0;
			b = 0.0;
			glLoadIdentity();
		}
			
		break;

	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			//mouse wheel scrolled up
			glScalef(1.5, 1.5, 1.0);
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			//mouse wheel scrolled down
			glScalef(0.5, 0.5, 1.0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void question1() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		glVertex2f(-0.2, 0.0);
		glVertex2f(0.2, 0.0);
		glVertex2f(0.0, 0.2);
	glEnd();
}

//--------------------------------------------------------------------

float* getBinaryValue(int colorBase10) {
	if (colorBase10 > 6) {
		colorBase10 = (int)(colorBase10 / 6);
	}

	static float binCode[3];

	for (int i = 0; colorBase10 > 0; i++) {
		binCode[i] = colorBase10 % 2;
		colorBase10 = colorBase10 / 2;
	}

	return binCode;
}

void question2(int colorValue) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	float *binaryValue;
	binaryValue = getBinaryValue(colorValue);

	//Top
	glBegin(GL_POLYGON);
	glColor3f(binaryValue[0], binaryValue[1], binaryValue[2]);
	glVertex2f(-0.13, 0.18);
	glVertex2f(0.0, 0.62);
	glVertex2f(0.13, 0.18);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	binaryValue = getBinaryValue(colorValue + 1);
	//Right Upper Part
	glBegin(GL_POLYGON);
	glColor3f(binaryValue[0], binaryValue[1], binaryValue[2]);
	glVertex2f(0.23, -0.12);
	glVertex2f(0.59, 0.16);
	glVertex2f(0.13, 0.18);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	binaryValue = getBinaryValue(colorValue + 2);
	//Right Lower Part
	glBegin(GL_POLYGON);
	glColor3f(binaryValue[0], binaryValue[1], binaryValue[2]);
	glVertex2f(0.23, -0.12);
	glVertex2f(0.37, -0.58);
	glVertex2f(0.0, -0.32);


	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	binaryValue = getBinaryValue(colorValue + 3);
	//Left Lower Part
	glBegin(GL_POLYGON);
	glColor3f(binaryValue[0], binaryValue[1], binaryValue[2]);
	glVertex2f(0.0, -0.32);
	glVertex2f(-0.37, -0.58);
	glVertex2f(-0.23, -0.12);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	binaryValue = getBinaryValue(colorValue + 4);
	//Left Upper Part
	glBegin(GL_POLYGON);
	glColor3f(binaryValue[0], binaryValue[1], binaryValue[2]);
	glVertex2f(-0.23, -0.12);
	glVertex2f(-0.59, 0.16);
	glVertex2f(-0.13, 0.18);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glEnd();
}

//--------------------------------------------------------------------
void question3() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.025, 0.025);
		glVertex2f(0.025, 0.025);
		glVertex2f(0.025, -0.025);
		glVertex2f(-0.025, -0.025);
	glEnd();
}

void forQuestion3(float q3i) {
	glLoadIdentity();

	float degInRad = q3i * (3.14159 / 180);
	glTranslatef(cos(degInRad) * 0.5, sin(degInRad) * 0.5, 0.0f);
	question3();
}
//--------------------------------------------------------------------
void question4() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.05, 0.05);
		glVertex2f(0.05, 0.05);
		glVertex2f(0.05, -0.05);
		glVertex2f(-0.05, -0.05);
	glEnd();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	float q3i = 0;
	int q2i = 1;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (displayKey == 1) {
			question1();
		}else if (displayKey == 2) {
			Sleep(50);
			question2(q2i);
		}else if (displayKey == 3) {
			forQuestion3(q3i);
		}
		else if (displayKey == 4) {
			question4();
		}
		else {
			question1();
		}

		q2i++;
		q3i += 0.2;

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------


