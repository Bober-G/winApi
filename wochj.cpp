/// Project2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Project2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];// = { L"sdasd" };            // the main window class name

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
    LoadStringW(hInstance, IDC_PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT2));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    

   hInst = hInstance; // Store instance handle in our global variable
   int xPos = (GetSystemMetrics(SM_CXSCREEN));
   int yPos = (GetSystemMetrics(SM_CYSCREEN));
  
   HWND hWnd = CreateWindowW(szWindowClass, L"FruitNinja", WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX,
       xPos/2, yPos/2 ,400, 300 , nullptr, nullptr, hInstance, nullptr);
    
   if (!hWnd)
   {
      return FALSE;
   }

   RECT rc;
 
   GetClientRect(hWnd, &rc);
   rc.right = 300;
   rc.bottom = 400;
   
   int width = rc.right - rc.left;
   int height = rc.bottom - rc.top;
    
   
   SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
   MoveWindow(
       hWnd,
       xPos /2 - width/2, 
       yPos/2  - height / 2 ,
       rc.right - rc.left,
       rc.bottom - rc.top,
       FALSE
   );
   //ModifyStyle(0, WS_MAXIMIZEBOX, SWP_FRAMECHANGED);
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
   static HCURSOR cursor = NULL;
    switch (message)
    {
    
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {

        PAINTSTRUCT ps;
        HDC hdc1 = BeginPaint(hWnd, &ps);

        HPEN pen = CreatePen(PS_NULL, 0, RGB(100, 100, 100));

        HPEN
            oldPen = (HPEN)SelectObject(hdc1, pen);

        HBRUSH
            brush = CreateSolidBrush(RGB(0, 0, 0));

        HBRUSH
            oldBrush = (HBRUSH)SelectObject(hdc1, brush);
        for (int i = 0; i < 400; i += 100) {
            Rectangle(hdc1, 0,  i, 50, 50 + i);
            Rectangle(hdc1, 50, 50 + i, 100, 100 + i);
            Rectangle(hdc1, 100, i, 150, 50 + i);
            Rectangle(hdc1, 150, 50 + i, 200, 100 + i);
            Rectangle(hdc1, 200, i, 250, 50 + i);
            Rectangle(hdc1, 250, 50 + i, 300, 100 + i);
        }

       
        SelectObject(hdc1, oldPen);
        DeleteObject(pen);
         SelectObject(hdc1, oldBrush);
        DeleteObject(brush);
        EndPaint(hWnd, &ps);
        }
        break;
        
    case WM_GETMINMAXINFO:
         {
             MINMAXINFO * minMaxInfo = (MINMAXINFO*)lParam;
             minMaxInfo -> ptMaxSize.x = minMaxInfo -> ptMaxTrackSize.x = 300;
             minMaxInfo -> ptMaxSize.y = minMaxInfo -> ptMaxTrackSize.y = 400;
             }
        break;

    //case WM_CREATE:
    //{
    //    HINSTANCE hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
    //    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    //    //_ASSERTE(hIcon != 0);
    //    SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    //    return 0;
    //}
   
    
    case WM_CREATE:
         cursor = LoadCursor(NULL, IDC_NO);
         break;
     case WM_SETCURSOR:
         SetCursor(cursor);
         return TRUE;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
