#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include "Game.h"

#pragma comment(lib,"winmm.lib")

//プロトタイプ宣言
LRESULT CALLBACK WndProc(
	HWND   hwnd,
	UINT   message,
	WPARAM wParam,
	LPARAM lParam
);

//エントリポイント
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	//***変数宣言***
	//ウィンドウクラス情報を設定する構造体
	WNDCLASSEX wcex;
	//作成したウィンドウのハンドル
	HWND	   hWnd;
	MSG		   message;

	//***ウィンドウクラス情報の設定***
	ZeroMemory(&wcex, sizeof(wcex));
	//作成するウィンドウと紐づけ
	wcex.hInstance = hInstance;
	//ウィンドウクラス情報を識別する名前
	wcex.lpszClassName = "Class Name";
	//ウィンドウプロシージャの指定
	wcex.lpfnWndProc = WndProc;
	//ウィンドウのスタイル指定
	wcex.style = CS_CLASSDC;
	//構造体のサイズを設定
	wcex.cbSize = sizeof(WNDCLASSEX);
	//タスクバーに表示するアイコンを指定
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//16*16サイズのアイコン
	wcex.hIconSm = wcex.hIcon;
	//カーソル設定
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//背景の指定
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//ウィンドウクラス情報の登録
	if (RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			"ウィンドウクラスの情報登録に失敗",
			"error",
			MB_OK | MB_ICONERROR);
		return 0;
	}

	//***ウィンドウの作成***
	hWnd = CreateWindowEx(
		//ウィンドウのスタイルを追加指定
		WS_EX_OVERLAPPEDWINDOW,
		//ウィンドウ作成の為のウィンドウクラスを指定
		wcex.lpszClassName,
		//キャプション部分に表示する名前
		"test",
		//基本のウィンドウスタイル
		WS_CAPTION | WS_SYSMENU,
		//ウィンドウの表示位置X
		CW_USEDEFAULT,
		//ウィンドウの表示位置Y
		CW_USEDEFAULT,
		//ウィンドウの横幅
		SCREEN_WIDTH,
		//ウィンドウの縦幅
		SCREEN_HEIGHT,
		//親ウィンドウの指定
		HWND_DESKTOP,
		//メニューの指定
		NULL,
		//ウィンドウを紐づけるアプリケーション
		hInstance,
		NULL
	);

	//***ウィンドウの表示***
	ShowWindow(
		hWnd,		//表示するウィンドウ
		nCmdShow	//表示方法
	);
	//ウィンドウの中身をリフレッシュ
	UpdateWindow(hWnd);

	//初期化
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

	//時間計測の制度を指定
	timeBeginPeriod(1);		//1m秒間隔

	//FPS制御の初期化
	int fpsCount = 0;	
	//計測開始時間
	DWORD countStartTime = timeGetTime();
	//前回の実行時間
	DWORD preExecTime = countStartTime;

	//---ウィンドウの管理---
	while (1) {

		//OSで発生したメッセージをキューに受け取る
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
			//キューに溜まったメッセージを取り出す
			if (!GetMessage(&message, NULL, 0, 0)) {
				break;
			}
			else {
				//受け取ったメッセージをウィンドウプロシージャに送信
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else {
			//FPSの制御
			DWORD nowTime = timeGetTime();		//現在の時刻
			//1秒経過したか判定
			if (nowTime - countStartTime >= 1000)
			{
				char fpsText[20];
				sprintf(fpsText, "FPS:%d", fpsCount);
				SetWindowText(hWnd, fpsText);
				//次の１秒間の計測準備
				countStartTime = nowTime;
				fpsCount = 0;
			}

		}
	}
	
	//===終了時の処理===
	timeEndPeriod(1);		//時間計測の制度を戻す
	//Uninit();
	//ウィンドウクラス情報の登録解除
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(
	HWND   hWnd,
	UINT   message,
	WPARAM wParam,
	LPARAM lParam
)
{
	// 受け取ったメッセージごとに処理
	switch (message)
	{
		// ウィンドウを閉じた
	case WM_DESTROY:
		// WM_Quitメッセージ
		// プログラムを完全終了させる命令
		PostQuitMessage(0);
		break;

		//[×]が押された
	case WM_CLOSE:
		//#ifndef _DEBUG
		if (IDNO == MessageBox(hWnd, "終了しますか？", "確認", MB_YESNO))
		{
			// ウィンドウプロシージャの
			// 途中でreturnを呼び出すと
			// 通常の動作を行わなくなる
			return 0;
		}
		//#endif
		break;
	}

	// 他のメッセージは
	// 基本の処理を行わせる
	return DefWindowProc(
		hWnd, message,
		wParam, lParam
	);
}