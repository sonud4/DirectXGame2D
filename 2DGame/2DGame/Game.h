#ifndef _GAME_H_
#define _GAME_H_

#include <Windows.h>

//***�萔***
#define SCREEN_WIDTH (960)		//��ʉ���
#define SCREEN_HEIGHT (540)		//��ʏc��

HRESULT Init(HWND hWnd, UINT widht, UINT height);
void Uninit();
void Updata();
void Draw();


#endif	//_GAME_H_
