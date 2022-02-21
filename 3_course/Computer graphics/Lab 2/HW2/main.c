#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#pragma comment (lib, "opengl32.lib")

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;
    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          800,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
            //glRotatef(theta, 0.0f, 0.0f, 1.0f);

            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.81f, 0.39f, 0.21f);
                //Фон кота
                glVertex2f(-1, 0.783);
                glVertex2f(-1, -0.783);
                glVertex2f(1, -0.783);
                glVertex2f(1, 0.783);
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 1.0f, 1.0f);
                //Фон кота
                glVertex2f(-0.96, 0.783);
                glVertex2f(-0.96, -0.783);
                glVertex2f(0.96, -0.783);
                glVertex2f(0.96, 0.783);
            glEnd();

            void DrawCircle(float transX, float transY, float *pRgb, float size)
            {
                glBegin(GL_TRIANGLE_FAN);
                glColor3f(pRgb[0], pRgb[1], pRgb[2]);

                float points = 50;
                float x, y;
                for (float i = -1; i < points; i++ )
                {
                    x = (sin((M_PI * 2 / points)*i)/size)+transX;
                    y = (cos((M_PI * 2 / points)*i)/size)+transY;
                    glVertex2f(x, y);
                }

                glEnd();
            };


            float rgb[3] = {0.81f, 0.39f, 0.21f};

            //body
            DrawCircle(0, 0, &rgb, 2.5);

            // head
            rgb[0] = 0.79f;
            rgb[1] = 0.39f;
            rgb[2] = 0.21f;
            DrawCircle(0.4, 0.3, &rgb, 3.5);

            //nose
            rgb[0] = 0.15f;
            rgb[1] = 0.15f;
            rgb[2] = 0.15f;
            DrawCircle(0.4, 0.25, &rgb, 34.0);

            // eyes
            rgb[0] = 1.0f;
            rgb[1] = 1.0f;
            rgb[2] = 1.0f;
            DrawCircle(0.5, 0.4, &rgb, 16.5);
            DrawCircle(0.3, 0.4, &rgb, 16.5);

            rgb[0] = 0.0f;
            rgb[1] = 0.0f;
            rgb[2] = 0.0f;
            DrawCircle(0.48, 0.38, &rgb, 50.5);
            DrawCircle(0.28, 0.38, &rgb, 50.5);

            rgb[0] = 1.0f;
            rgb[1] = 1.0f;
            rgb[2] = 1.0f;
            DrawCircle(0.475, 0.375, &rgb, 170.5);
            DrawCircle(0.275, 0.375, &rgb, 170.5);

            void DrawSemicircle(float transX, float transY, float *pRgb, int size, float rotate)
            {
                glLoadIdentity();
                glRotatef(rotate, 0.0f, 0.0f, 1.0f);
                glBegin(GL_POLYGON);
                glColor3f(pRgb[0], pRgb[1], pRgb[2]);

                float points = 50;
                float x, y;
                for (float i = -1; i < points; i++ )
                {
                    x = (sin((M_PI / points)*i)/size)+transX;
                    y = (cos((M_PI / points)*i)/size)+transY;
                    glVertex2f(x, y);
                }

                glEnd();
            }

            //tail

            rgb[0] = 0.87f;
            rgb[1] = 0.39f;
            rgb[2] = 0.21f;
            DrawSemicircle(0, 0.6, &rgb, 3, 80.0);

            //legs
            rgb[0] = 0.15f;
            rgb[1] = 0.15f;
            rgb[2] = 0.15f;
            DrawSemicircle(-0.40, 0.3, &rgb, 6.0, 7.0);
            DrawSemicircle(-0.40, -0.35, &rgb, 6.0, 0.0);
            rgb[0] = 0.0f;
            rgb[1] = 0.0f;
            rgb[2] = 0.0f;
            DrawSemicircle(-0.5, 0.15, &rgb, 6.0, 0.0);
            DrawSemicircle(-0.45, -0.25, &rgb, 6.0, -7.0);


            void DrawLeafFlower(float transX, float transY, float size, float rotate)
            {
                glLoadIdentity();
                float points = 50;
                float x, y;
                float temp_y[5] = {0.07f, 0.1f, 0.14f, 0.055f, 0.12f};
                float temp_x[5] = {-0.04f, 0.04f, 0.0f, 0.02f, -0.04f};

                glRotatef(rotate, 0.0f, 0.0f, 1.0f);
                glScalef(size, size, 1);
                glBegin(GL_POLYGON);
                glColor3f(0.87, 0.6, 0.77);

                for(int j = 0; j < 5; j++)
                {
                    for (float i = -1; i < points; i++ )
                    {
                        x = (sin((M_PI * 2 / points)*i)/30)+transX+temp_y[j];
                        y = (cos((M_PI * 2 / points)*i)/30)+transY+temp_x[j];
                        glVertex2f(x, y);
                    }


                }
                 glEnd();
            }

            void DrawFlower(float transX, float transY, float size, float rotate)
            {
                glLoadIdentity();
                float points = 50;
                float x, y, r;

                glRotatef(rotate, 0.0f, 0.0f, 1.0f);
                glBegin(GL_POLYGON);

                glColor3f(1.0, 0.0, 0.0);

                for (float fi = 0.0; fi < 2*M_PI; fi+=0.01 )
                {
                    r = (sin(fi*2.5)*cos(fi*2.5));
                    x = ((r * cos(fi))/(size*5)) + transX;
                    y = ((r * sin(fi))/(size*5)) + transY;
                    glVertex2f(x, y);
                }

                glEnd();

                glBegin(GL_POLYGON);

                glColor3f(0.9, 0.64, 0.58);

                for (float i = -1; i < points; i++ )
                {
                    x = (sin((M_PI * 2 / points)*i)/(size*30)) + transX;
                    y = (cos((M_PI * 2 / points)*i)/(size*30)) + transY;
                    glVertex2f(x, y);
                }

                glEnd();
            }

            //Flower
            DrawLeafFlower(-0.7, 0.6, 1.0, 0.0);
            DrawFlower(-0.6, 0.6, 2.0, 0.0);
            DrawLeafFlower(-1.43, 0.74, 0.5, -20.0);
            DrawFlower(-0.67, 0.37, 4.0, -20.0);

            DrawLeafFlower(-0.3, 0.62, 0.7, 0.0);
            DrawFlower(-0.14, 0.43, 3.0, 0.0);

            DrawLeafFlower(0.46, 0.72, 0.9, 0.0);
            DrawFlower(0.5, 0.65, 2.4, 0.0);
            DrawLeafFlower(1.48, 0.87, 0.5, 20.0);
            DrawFlower(0.79, 0.435, 4.0, 20.0);

            DrawLeafFlower(1.1, 1.4, 0.5, -20.0);
            DrawFlower(0.6, 0.7, 4.0, -20.0);

            DrawLeafFlower(1.08, -0.5, 0.5, 20.0);
            DrawFlower(0.59, -0.25, 4.0, 20.0);

            DrawLeafFlower(0.9, -0.1, 0.8, -20.0);
            DrawFlower(0.8, -0.08, 2.9, -20.0);

            DrawLeafFlower(1.0, -1.7, 0.5, 10.0);
            DrawFlower(0.55, -0.85, 4.0, 10.0);

            DrawLeafFlower(-0.02, -1.06, 0.7, 0.0);
            DrawFlower(0.055, -0.74, 3.0, 0.0);
            DrawLeafFlower(0.43, -0.94, 0.7, -20.0);
            DrawFlower(0.37, -0.66, 3.0, -20.0);
            DrawLeafFlower(-0.25, -1.5, 0.5, 20.0);
            DrawFlower(-0.075, -0.75, 4.0, 20.0);

            DrawLeafFlower(-1.3, 0.0, 0.7, 30.0);
            DrawFlower(-0.84, 0.0, 3.0, 30.0);

            DrawLeafFlower(-1.48, 0.1, 0.5, 20.0);
            DrawFlower(-0.69, 0.05, 4.0, 20.0);

            DrawLeafFlower(-1.1, 0.85, 0.7, 50.0);
            DrawFlower(-0.7, 0.59, 3.0, 50.0);


            glLoadIdentity();
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_QUADS);
                //перекрывает цветочки
                glVertex2f(-1.0, -1.0);
                glVertex2f(1.0, -1.0);
                glVertex2f(1.0, -0.775);
                glVertex2f(-1.0, -0.775);
            glEnd();


            // ears
            rgb[0] = 0.15f;
            rgb[1] = 0.15f;
            rgb[2] = 0.15f;
            glLoadIdentity();
            glRotatef(25, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(0.4, 0.535);
            glVertex2f(0.4, 0.38);
            glVertex2f(0.5, 0.385);
            glEnd();

            glLoadIdentity();
            glRotatef(-25, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(0.25, 0.715);
            glVertex2f(0.35, 0.865);
            glVertex2f(0.35, 0.71);
            glEnd();


            // strips
            glLoadIdentity();
            glRotatef(25, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(-0.0, 0.4);
            glVertex2f(-0.1, 0.395);
            glVertex2f(-0.05, 0.05);
            glEnd();
            glLoadIdentity();
            glRotatef(15, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(0.0, 0.4);
            glVertex2f(0.1, 0.395);
            glVertex2f(0.05, 0.05);
            glEnd();
            glLoadIdentity();
            glRotatef(0.0, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(0.05, 0.4);
            glVertex2f(0.15, 0.38);
            glVertex2f(0.1, 0.05);
            glEnd();

            glLoadIdentity();
            glRotatef(25, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(-0.5, 0.675);
            glVertex2f(-0.6, 0.66);
            glVertex2f(-0.55, 0.45);
            glEnd();
            glLoadIdentity();
            glRotatef(-10, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(-0.65, 0.33);
            glVertex2f(-0.75, 0.305);
            glVertex2f(-0.65, 0.1);
            glEnd();
            glLoadIdentity();
            glRotatef(-25, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(-0.55, 0.18);
            glVertex2f(-0.65, 0.17);
            glVertex2f(-0.55, -0.05);
            glEnd();


            // mustache
            glLoadIdentity();
            glRotatef(15, 0.0f, 0.0f, 1.0f);
            glBegin(GL_POLYGON);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(0.1, 0.13);
            glVertex2f(0.1, 0.15);
            glVertex2f(0.8, 0.15);
            glVertex2f(0.8,0.13);
            glEnd();
            glLoadIdentity();
            glRotatef(-15, 0.0f, 0.0f, 1.0f);
            glBegin(GL_POLYGON);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(-0.0, 0.33);
            glVertex2f(-0.0, 0.35);
            glVertex2f(0.7, 0.35);
            glVertex2f(0.7,0.33);
            glEnd();
            glLoadIdentity();
            glRotatef(0, 0.0f, 0.0f, 1.0f);
            glBegin(GL_POLYGON);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glVertex2f(0.05, 0.245);
            glVertex2f(0.05, 0.265);
            glVertex2f(0.75, 0.265);
            glVertex2f(0.75,0.245);
            glEnd();



            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
        }


    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

