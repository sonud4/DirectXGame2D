#include<Windows.h>
#include<stdio.h>

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
	MSG		   messsage;

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
}