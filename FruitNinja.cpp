#include "framework.h"
#include "FruitNinja.h"
#include <vector>
#define MAX_LOADSTRING 100

struct ball {
    float x, y, radius;
    float xspeed, yspeed;
};

std::vector<ball> balls;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
INT BOARD_SIZE = 1000;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRUITNINJA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRUITNINJA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
       
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRUITNINJA));
    wcex.hCursor = LoadCursor(nullptr, MAKEINTRESOURCE(IDC_FRUITNINJA));
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FRUITNINJA);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_FRUITNINJA));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    
    WINDOWPLACEMENT wp;
    RECT rc = {0,0,400,300};
    RECT prevrc;
    hInst = hInstance;
    int xPos = (GetSystemMetrics(SM_CXSCREEN));
    int yPos = (GetSystemMetrics(SM_CYSCREEN));

    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    
    HWND hWnd = CreateWindowW(szWindowClass, L"FruitNinja", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX,// removing min/max
        0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);
    HWND hWnd1;
    //SetParent(hWnd1, hWnd);
    //hWnd1 = CreateWindowEx(szWindowClass);
    if (!hWnd)
    {
        return FALSE;
    }
    //GetClientRect(hWnd, &rc);
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    //SetWindowPlacement(hWnd,&wp);
    
    SetWindowPos(hWnd, HWND_TOPMOST, xPos / 2 - width / 2, yPos / 2 - height / 2, rc.right - rc.left, rc.bottom - rc.top, FALSE); // Setting window to topmost
    //MoveWindow(hWnd,xPos / 2 - width / 2,yPos / 2 - height / 2, rc.right - rc.left, rc.bottom - rc.top, TRUE);
    for (int i = 0; i < balls.size(); i++) {
        balls[i].x += balls[i].xspeed;
        balls[i].y += balls[i].yspeed;
    }
   
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hWnd);
    RECT ballrc = { 0,0,40,40 };
    //Ellipse(hdc, ballrc.left, ballrc.top, ballrc.right, ballrc.bottom);
    RECT rc = { 0,0,0,0 };
    RECT rc1 = { 0,0,400,300 };
    RECT rc2 = { 0,0,600,500 };
    RECT rc3 = { 0,0,800,600 };
    
    static HCURSOR cursor = NULL;
    static HICON icon = NULL;
    
    int xPos = (GetSystemMetrics(SM_CXSCREEN));
    int yPos = (GetSystemMetrics(SM_CYSCREEN));

    int width1 = rc1.right - rc1.left;
    int height1 = rc1.bottom - rc1.top;
    int width2 = rc2.right - rc2.left;
    int height2 = rc2.bottom - rc2.top;
    int width3 = rc3.right - rc3.left;
    int height3 = rc3.bottom - rc3.top;
   
    POINT ptOld; POINT pt;
      
    
    GetCursorPos(&ptOld);
    
    UINT uRes1 = SetTimer(hWnd, IDT_TRANPARENCY, 3000, (TIMERPROC)NULL);
    UINT uRes2 = SetTimer(hWnd, IDT_GAMEDURATION, 4000, (TIMERPROC)NULL);
    
    HMENU mainMenu = GetMenu(hWnd);
    WINDOWPLACEMENT wp = { sizeof(WINDOWPLACEMENT),WPF_ASYNCWINDOWPLACEMENT, SW_RESTORE, {rc1.right - rc1.left,rc1.bottom - rc1.top}, 12, 12 };
    //SetWindowPlacement(hWnd, &wp);
   switch (message)
    {

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
       
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_NEWGAME:
            KillTimer(hWnd, IDT_GAMEDURATION);
            SetTimer(hWnd, IDT_GAMEDURATION, 4000, (TIMERPROC)NULL);
            
        case IDM_SMALL:
            rc = { 0,0,400,300 };
            AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
            SetWindowPos(hWnd, HWND_TOPMOST, xPos / 2 - width1 / 2, yPos / 2 - height1 / 2, rc.right - rc.left, rc.bottom - rc.top, FALSE);
            CheckMenuItem(mainMenu,IDM_SMALL,MFS_CHECKED);
            CheckMenuItem(mainMenu, IDM_MEDIUM, MFS_UNCHECKED);
            CheckMenuItem(mainMenu, IDM_BIG, MFS_UNCHECKED);
            break;
        case IDM_MEDIUM:
            rc = { 0,0,600,500 };
            AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
            SetWindowPos(hWnd, HWND_TOPMOST, xPos / 2 - width2 / 2, yPos / 2 - height2 / 2, rc.right - rc.left, rc.bottom - rc.top, FALSE);
            CheckMenuItem(mainMenu, IDM_MEDIUM, MFS_CHECKED);
            CheckMenuItem(mainMenu, IDM_SMALL, MFS_UNCHECKED);
            CheckMenuItem(mainMenu, IDM_BIG, MFS_UNCHECKED);
            break;
        case IDM_BIG:
            rc = { 0,0,800,600 };
            AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
            SetWindowPos(hWnd, HWND_TOPMOST, xPos / 2 - width3 / 2, yPos / 2 - height3 / 2, rc.right - rc.left, rc.bottom - rc.top, FALSE);
            CheckMenuItem(mainMenu, IDM_BIG, MFS_CHECKED);
            CheckMenuItem(mainMenu, IDM_SMALL, MFS_UNCHECKED);
            CheckMenuItem(mainMenu, IDM_MEDIUM, MFS_UNCHECKED);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            
        }
    }
    return 0;
    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        HDC hdc1 = BeginPaint(hWnd, &ps);
        HDC hdc2 = BeginPaint(hWnd, &ps);
        HPEN pen = CreatePen(PS_NULL, 0, RGB(100, 100, 100));

        HPEN oldPen = (HPEN)SelectObject(hdc1, pen);

        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc1, brush);

        for (int i = 0; i < BOARD_SIZE; i += 100) {
            for (int j = 0; j < BOARD_SIZE; j += 100) {
                Rectangle(hdc1, j, i, 50 + j, 50 + i);
                Rectangle(hdc1, 50 + j, i + 50, 100 + j, 100 + i);
            }
        }
        DeleteObject(brush);
        
        HBRUSH brush1 = CreateSolidBrush(RGB(0, 255, 0));
        HBRUSH oldBrush1 = (HBRUSH)SelectObject(hdc2, brush);
        /*for (float k = 0; k < balls.size(); k++) {
            Ellipse(hdc2, balls[k].x - balls[k].radius, balls[k].y - balls[k].radius,
                balls[k].x + balls[k].radius, balls[k].y + balls[k].radius);
        }*/
        //Ellipse(hdc2, 10,20,30,40 );
       // Ellipse(hdc2, ballrc.left, ballrc.top, ballrc.right, ballrc.bottom);

    }
    break;

    case WM_TIMER:
        
        /*if (wParam == IDT_TRANPARENCY) {
            GetCursorPos(&pt);
            /// Set to semitransparent after not moving the cursor for 3 seconds
            if ((pt.x == ptOld.x) && (pt.y == ptOld.y))
            {
                SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
                SetLayeredWindowAttributes(hWnd, 0, (255 * 70) / 100, LWA_ALPHA);
                SetCapture(hWnd);
                
            }
            
        }
        if (wParam == IDT_GAMEDURATION) {
            GetForegroundWindow();
            SetForegroundWindow(hWnd);
        }*/
        switch (wParam){
        case IDT_TRANPARENCY:
            GetCursorPos(&pt);
            /// Set to semitransparent after not moving the cursor for 3 seconds
            if ((pt.x == ptOld.x) && (pt.y == ptOld.y))
            {
                SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
                SetLayeredWindowAttributes(hWnd,0, (255 * 70) / 100, LWA_ALPHA);
                SetCapture(hWnd);
                return 0;
            }
        case IDT_GAMEDURATION:
            GetForegroundWindow();
            SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd,  WS_EX_LAYERED));
            SetLayeredWindowAttributes(hWnd, 0x0000FF00, (255 * 70) / 100, LWA_ALPHA);
            SetForegroundWindow(hWnd);
            return 0;
            }
        //ballrc.top -= 10;
       
    break;
    case WM_MOUSEMOVE:
        
        SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), RGB(2, 250, 250));
        ReleaseDC(hWnd, hdc);
        if(ReleaseCapture() == TRUE)
            SetLayeredWindowAttributes(hWnd, 0, (255 * 100) / 100, LWA_ALPHA);
        break;
    case WM_CREATE:
        
        cursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_FRUITNINJA));
        
        icon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_FRUITNINJA));
        SendMessage(hWnd, WM_GETICON, ICON_SMALL, (LPARAM)icon);
        SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
      
        return 0;
    case WM_SETCURSOR:
        SetCursor(cursor);
         return TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        GetWindowRect(hWnd,&rc);
        KillTimer(hWnd, IDT_TRANPARENCY);
        GetWindowPlacement(hWnd,&wp);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
       
    }
    return 0;
}

//// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}



