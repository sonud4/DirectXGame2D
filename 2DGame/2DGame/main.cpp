#include<Windows.h>
#include<stdio.h>

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
	MSG		   messsage;

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
}