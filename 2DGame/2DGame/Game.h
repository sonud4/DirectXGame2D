#ifndef _GAME_H_
#define _GAME_H_

#include <Windows.h>

//***’è”***
#define SCREEN_WIDTH (960)		//‰æ–Ê‰¡•
#define SCREEN_HEIGHT (540)		//‰æ–Êc•

HRESULT Init(HWND hWnd, UINT widht, UINT height);
void Uninit();
void Updata();
void Draw();


#endif	//_GAME_H_
