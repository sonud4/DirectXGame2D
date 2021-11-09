#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include "Game.h"

#pragma comment(lib,"winmm.lib")

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(
	HWND   hwnd,
	UINT   message,
	WPARAM wParam,
	LPARAM lParam
);

//�G���g���|�C���g
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	//***�ϐ��錾***
	//�E�B���h�E�N���X����ݒ肷��\����
	WNDCLASSEX wcex;
	//�쐬�����E�B���h�E�̃n���h��
	HWND	   hWnd;
	MSG		   message;

	//***�E�B���h�E�N���X���̐ݒ�***
	ZeroMemory(&wcex, sizeof(wcex));
	//�쐬����E�B���h�E�ƕR�Â�
	wcex.hInstance = hInstance;
	//�E�B���h�E�N���X�������ʂ��閼�O
	wcex.lpszClassName = "Class Name";
	//�E�B���h�E�v���V�[�W���̎w��
	wcex.lpfnWndProc = WndProc;
	//�E�B���h�E�̃X�^�C���w��
	wcex.style = CS_CLASSDC;
	//�\���̂̃T�C�Y��ݒ�
	wcex.cbSize = sizeof(WNDCLASSEX);
	//�^�X�N�o�[�ɕ\������A�C�R�����w��
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//16*16�T�C�Y�̃A�C�R��
	wcex.hIconSm = wcex.hIcon;
	//�J�[�\���ݒ�
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//�w�i�̎w��
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//�E�B���h�E�N���X���̓o�^
	if (RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			"�E�B���h�E�N���X�̏��o�^�Ɏ��s",
			"error",
			MB_OK | MB_ICONERROR);
		return 0;
	}

	//***�E�B���h�E�̍쐬***
	hWnd = CreateWindowEx(
		//�E�B���h�E�̃X�^�C����ǉ��w��
		WS_EX_OVERLAPPEDWINDOW,
		//�E�B���h�E�쐬�ׂ̈̃E�B���h�E�N���X���w��
		wcex.lpszClassName,
		//�L���v�V���������ɕ\�����閼�O
		"test",
		//��{�̃E�B���h�E�X�^�C��
		WS_CAPTION | WS_SYSMENU,
		//�E�B���h�E�̕\���ʒuX
		CW_USEDEFAULT,
		//�E�B���h�E�̕\���ʒuY
		CW_USEDEFAULT,
		//�E�B���h�E�̉���
		SCREEN_WIDTH,
		//�E�B���h�E�̏c��
		SCREEN_HEIGHT,
		//�e�E�B���h�E�̎w��
		HWND_DESKTOP,
		//���j���[�̎w��
		NULL,
		//�E�B���h�E��R�Â���A�v���P�[�V����
		hInstance,
		NULL
	);

	//***�E�B���h�E�̕\��***
	ShowWindow(
		hWnd,		//�\������E�B���h�E
		nCmdShow	//�\�����@
	);
	//�E�B���h�E�̒��g�����t���b�V��
	UpdateWindow(hWnd);

	//������
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

	//���Ԍv���̐��x���w��
	timeBeginPeriod(1);		//1m�b�Ԋu

	//FPS����̏�����
	int fpsCount = 0;	
	//�v���J�n����
	DWORD countStartTime = timeGetTime();
	//�O��̎��s����
	DWORD preExecTime = countStartTime;

	//---�E�B���h�E�̊Ǘ�---
	while (1) {

		//OS�Ŕ����������b�Z�[�W���L���[�Ɏ󂯎��
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
			//�L���[�ɗ��܂������b�Z�[�W�����o��
			if (!GetMessage(&message, NULL, 0, 0)) {
				break;
			}
			else {
				//�󂯎�������b�Z�[�W���E�B���h�E�v���V�[�W���ɑ��M
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else {
			//FPS�̐���
			DWORD nowTime = timeGetTime();		//���݂̎���
			//1�b�o�߂���������
			if (nowTime - countStartTime >= 1000)
			{
				char fpsText[20];
				sprintf(fpsText, "FPS:%d", fpsCount);
				SetWindowText(hWnd, fpsText);
				//���̂P�b�Ԃ̌v������
				countStartTime = nowTime;
				fpsCount = 0;
			}

		}
	}
	
	//===�I�����̏���===
	timeEndPeriod(1);		//���Ԍv���̐��x��߂�
	//Uninit();
	//�E�B���h�E�N���X���̓o�^����
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(
	HWND   hWnd,
	UINT   message,
	WPARAM wParam,
	LPARAM lParam
)
{
	// �󂯎�������b�Z�[�W���Ƃɏ���
	switch (message)
	{
		// �E�B���h�E�����
	case WM_DESTROY:
		// WM_Quit���b�Z�[�W
		// �v���O���������S�I�������閽��
		PostQuitMessage(0);
		break;

		//[�~]�������ꂽ
	case WM_CLOSE:
		//#ifndef _DEBUG
		if (IDNO == MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO))
		{
			// �E�B���h�E�v���V�[�W����
			// �r����return���Ăяo����
			// �ʏ�̓�����s��Ȃ��Ȃ�
			return 0;
		}
		//#endif
		break;
	}

	// ���̃��b�Z�[�W��
	// ��{�̏������s�킹��
	return DefWindowProc(
		hWnd, message,
		wParam, lParam
	);
}