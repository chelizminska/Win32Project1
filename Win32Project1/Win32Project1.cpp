// Win32Project1.cpp: определяет точку входа для приложения.
//
#define UNICODE
#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];  
// имя класса главного окна
bool is_begin = false;
int i = 0;
int clicks = 0;
int x1, x2, y1, y2;
/*int arr_x[10000];
int arr_y[10000];
int arr_pen_x[10000];
int arr_pen_y[10000];*/
int pen_points_amount = -1;
int points_amount = -1;
bool is_down = false;
bool drawing_line = false;
bool pen = false;
HWND hWnd_button_line;
HWND hWnd_button_pen;
HDC hdc2;
HBITMAP hBmp, hOldBmp;
HPEN hPen, hOldPen;
HBRUSH hBrush;
RECT rc;
int penSize;
HDC hdc;
int width, height;
POINT prept;
POINT newpt;


// Отправить объявления функций, включенных в этот модуль кода:
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int Draw(HWND hWnd, int x1, int y1, int x2, int y2);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // TODO: разместите код здесь.
	


	

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));
	MSG msg;

	HWND hWnd = CreateWindow(L"Class", L"cucu", WS_OVERLAPPEDWINDOW,
		0, 0, 500, 300, NULL, NULL, hInstance, NULL);
	//проверим создалось ли окно
	if (!hWnd)return 0;
	hWnd_button_line = CreateWindow(L"button", L"Прямые", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 10, 80, 30, hWnd, (HMENU)10000, hInstance, NULL);
	hWnd_button_pen = CreateWindow(L"button", L"Карандаш", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		100, 10, 80, 30, hWnd, (HMENU)10001, hInstance, NULL);




	






	ShowWindow(hWnd, nCmdShow);
	ShowWindow(hWnd_button_line, nCmdShow);
	ShowWindow(hWnd_button_pen, nCmdShow);


    hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rc);
	hdc2 = CreateCompatibleDC(hdc);
	width = rc.right - rc.left;
    height = rc.bottom - rc.top;
	hBmp = CreateCompatibleBitmap(hdc, width, height);
	/*hPen = CreatePen(0, penSize, RGB(0, 0, 0));
	hOldBmp = (HBITMAP)SelectObject(hdc2, hBmp);
	hOldPen = (HPEN)SelectObject(hdc2, (HGDIOBJ)hPen);
	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));*/
	//FillRect(hdc2, &rc, hBrush);

	//Line(hdc2, x1, y1, x2, y2);

	BitBlt(hdc, 0, 0, width, height, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hOldBmp);
	//SelectObject(hdc2, hOldPen);
	//DeleteObject(hBmp);
	//DeleteDC(hdc2);


	/*UpdateWindow(hWnd_button_pen);
	UpdateWindow(hWnd_button_line);
	UpdateWindow(hWnd);*/
    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   //структура для регистрации класса окон
   WNDCLASS wc;
   wc.style = 0;
   wc.lpfnWndProc = (WNDPROC)WndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;
   wc.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName = 0;
   wc.lpszClassName = L"Class";
   //регестрируем класс
   if (!RegisterClass(&wc)) return 0;
   //создать окно
   
   //Создаем кнопку
  

   

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL); //сделать текущими координаты x1, y1
	return LineTo(hdc, x2, y2);
}

BOOL Draw(HDC hdc, POINT oldPoint, POINT newPoint)
{
	MoveToEx(hdc, oldPoint.x, oldPoint.y, NULL);
	LineTo(hdc, newPoint.x, newPoint.y);
	return TRUE;
}

/*void DrawLines(HWND hWnd)
{
//	HDC hdc2, hdc;
//	HBITMAP hBmp, hOldBmp;
//	HBRUSH hBrush;
	//RECT rc;

	hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rc);
	hdc2 = CreateCompatibleDC(hdc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	hBmp = CreateCompatibleBitmap(hdc, width, height);
	//hOldBmp = (HBITMAP)SelectObject(hdc2, hBmp);
	//hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	//FillRect(hdc2, &rc, hBrush);

	for (int i = 0; i < points_amount; i += 2)
	{
		Line(hdc2, arr_x[i], arr_y[i], arr_x[i + 1], arr_y[i + 1]);
	}

	//BitBlt(hdc, 0, 0, width, height, hdc2, 0, 0, SRCCOPY);
	//SelectObject(hdc2, hOldBmp);
	//DeleteObject(hBmp);
	//DeleteDC(hdc2);
}
*/
/*void DrawPoints(HWND hWnd)
{
	//HDC hdc2, hdc;
//	HBITMAP hBmp, hOldBmp;
//	HBRUSH hBrush;
//	RECT rc;

	//hdc = GetDC(hWnd);
	//GetClientRect(hWnd, &rc);
	//hdc2 = CreateCompatibleDC(hdc);
	//int width = rc.right - rc.left;
	//int height = rc.bottom - rc.top;
	//hBmp = CreateCompatibleBitmap(hdc, width, height);
	hOldBmp = (HBITMAP)SelectObject(hdc2, hBmp);
	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc2, &rc, hBrush);
	penSize = 20;
	
	for (int i = 0; i < pen_points_amount; i++)
	{
		for (int j = -(penSize / 2); j < penSize / 2; j++)
		{
			for (int k = -(penSize / 2); k < penSize / 2; k++)
				SetPixel(hdc2, arr_pen_x[i] + j, arr_pen_y[i] + k, RGB(0, 0, 0));
		}
	}
	BitBlt(hdc, 0, 0, width, height, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hOldBmp);
	DeleteObject(hBmp);
	DeleteDC(hdc2);
}*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static COLORREF color = 0x000000;

    switch (message)
    {

	case WM_LBUTTONUP:
		{
			is_down = false;
			/*if (drawing_line) {
				POINT point;
				GetCursorPos(&point);
				ScreenToClient(hWnd, &point);
	
				clicks++;
				if (clicks == 1) {
					x1 = point.x;
					y1 = point.y;
				}
				else if (clicks == 2) {
					x2 = point.x;
					y2 = point.y;
					arr_x[++points_amount] = x1;
					arr_y[points_amount] = y1;
					arr_x[++points_amount] = x2;
					arr_y[points_amount] = y2;
					clicks = 0;
				}  
			}*/
			//InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	case WM_LBUTTONDOWN:
		{
			is_down = true;
			POINT point;
			GetCursorPos(&point);
			ScreenToClient(hWnd, &point);
			prept.x = newpt.x = point.x;
			prept.y = newpt.y = point.y;
			break;
		}

	case WM_MOUSEMOVE:
		if (is_down)
		{
			hdc = GetDC(hWnd);
			hPen = CreatePen(PS_SOLID, 1, color);
			SelectObject(hdc, (HGDIOBJ)hPen);
			//switch (drawMethod)
			{
				if (drawing_line)
				{
					SetROP2(hdc, R2_NOTXORPEN);
					Draw(hdc, prept, newpt);
					newpt.x = LOWORD(lParam);
					newpt.y = HIWORD(lParam);
					SetROP2(hdc, R2_NOTXORPEN);
					Draw(hdc, prept, newpt);
				}
				

			//case METHOD_PEN:
				if (pen)
				{
					MoveToEx(hdc, prept.x, prept.y, NULL);
					newpt.x = LOWORD(lParam);
					newpt.y = HIWORD(lParam);
					prept.x = newpt.x;
					prept.y = newpt.y;
					LineTo(hdc, newpt.x, newpt.y);
				}
			}
			ReleaseDC(hWnd, hdc);
		}
		break;
    case WM_COMMAND:
        {
			if (LOWORD(wParam) == 10000)
			{
				drawing_line = true;
				pen = false;
			}
			if (LOWORD(wParam) == 10001)
			{
				drawing_line = false;
				pen = true;
			}
			break;
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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
            HDC hdc = BeginPaint(hWnd, &ps);

	//		DrawLines(hWnd);
		//	DrawPoints(hWnd);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
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


