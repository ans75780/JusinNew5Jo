// Frame128.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Frame128.h"
#include "MainGame.h"
#include "TimeMgr.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HWND	  g_hWnd;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// 현재 윈도우 창을 만들기 위한 창 속성, 스타일을 지정하는 함수
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// 메모리에 할당되는 실체, 즉 객체
                     _In_opt_ HINSTANCE hPrevInstance,	// 전에 실행되었던 인스턴스의 핸들 값, 없을 경우 null, 호환성을 위해 존재할 뿐 우리가 사용할 일 없음
                     _In_ LPWSTR    lpCmdLine,			// LP는 포인터를 뜻함, LPTSTR 문자열 포인터를 의미, TSTR: 유니코드, 아스키코드 모드 호환
                     _In_ int       nCmdShow)			// 실행한 창의 스타일을 지정하는 인자값에 해당
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAME128, szWindowClass, MAX_LOADSTRING);

    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAME128));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame*	pMainGame = new CMainGame;

	if (nullptr != pMainGame)
		pMainGame->Initialize();
    TIMEMANAGER->Init();
	//DWORD dwTime = GetTickCount();	//958
		  
	while (true)
	{
		// PM_REMOVE : 메세지 읽어옴과 동시에 메시지 큐에서 메시지를 제거하는 옵션
		// PM_NOREMOVE : 메세지 큐에 메세지가 존재하는지만 파악, 메시지를 읽어오려면 GetMessage함수를 다시 호출

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))		// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해주는 함수
			{
				TranslateMessage(&msg);	// getmessage에서 꺼내온 메시지를 가공한다.
				DispatchMessage(&msg);	// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램이 알수 있는 메세지로 변환하는 함수(->wndProc로 전달)
			}
		}	
		else
		{
			// 우리가 만든 update 또는 render 함수를 실시간으로 호출

			// GetDC();
			// GetAsyncKeyState()

				// 1024 + 10		980
			//해당 코드는 타이머 클래스를 만들기 전에 사용했음
            /*
            if (dwTime < GetTickCount())
			{
				pMainGame->Update();
				pMainGame->Late_Update();
				pMainGame->Render();

				//1024
				dwTime = GetTickCount();
			}	
            */
            TIMEMANAGER->Update(60.f);
            pMainGame->Update();
            pMainGame->Late_Update();
            pMainGame->Render();

			/*pMainGame->Update();
			pMainGame->Late_Update();
			pMainGame->Render();*/
		}
	}

	if (nullptr != pMainGame)
	{
		/*delete pMainGame;
		pMainGame = nullptr;*/

		Safe_Delete(pMainGame);
	}


    return (int) msg.wParam;
} 



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAME128));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	RECT	rc{ 0, 0 , WINCX, WINCY };

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 출력 영역을 조절해주는 함수

   // rc = rc사이즈 + 기본 창 옵션 사이즈 + 메뉴 바 사이즈 고려 여부 
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, // 정의한 윈도우 클래스의 전달할 이름을 그대로 넣어준다
	   szTitle, // 윈도우 창 상단의 이름을 나타낼 문자열
	   WS_OVERLAPPEDWINDOW, // 만들고자 하는 윈도우 창의 형태를 지정, 기본값 옵션
       200, 200,	// 순서대로 x,y 값, 윈도우 창의 생성하는 위치
	   rc.right - rc.left, rc.bottom - rc.top,	// 생성할 윈도우 창의 가로, 세로 사이즈
	   nullptr, 
	   nullptr, 
	   hInstance, 
	   nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;	
		}
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(g_hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
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

// 정보 대화 상자의 메시지 처리기입니다.
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
