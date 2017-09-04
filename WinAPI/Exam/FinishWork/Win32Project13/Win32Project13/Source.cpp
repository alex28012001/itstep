#include<Windows.h>
#include<vector>
#include<string>
#include<ctime>
#include<CommCtrl.h>
#pragma comment (lib, "comctl32")
#include"resource.h"
#define GameOver 876
#define ProgressTimer 228
#define Get(id)  GetDlgItem(hWnd, id)  //������ GetDlgItem


void sort(std::vector<int> &A, int size) 
{
	for (int i = 0; i < size; i++)
	{
		int temp = A[i];
		int min = A[i], imin = i;
		for (int j = i + 1; j < size; j++)
		{
			if (A[j] < min)
			{
				min = A[j];
				imin = j;
			}
		}
		A[i] = min;
		A[imin] = temp;
	}
}
BOOL CALLBACK DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadLibrary(L"Riched20.dll");
	HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(WindowMain), NULL, DlgProc);
	ShowWindow(hWnd, true);
	
	MSG iMsg;
	while (GetMessage(&iMsg, NULL, NULL, 0))
	{
		TranslateMessage(&iMsg);
		DispatchMessage(&iMsg);
		if (iMsg.message == WM_SYSKEYDOWN || iMsg.message == WM_CHAR)
		{
			SendMessage(hWnd, iMsg.message, iMsg.wParam, iMsg.lParam);
		}
	}
	return iMsg.wParam;

}



BOOL CALLBACK DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int timer; //�����
	static int count; //������� ��� �������
	static int index_now; //����� ����� , ������� �������� ������������(�� �����)
	static std::vector<int> numb; // ������ ��������� �����
	static HWND list, edit, spin, prog;
	static std::vector<HWND> buttons;// ����������� ������
	int pos; //������� ��� ������ �� ���������
	std::wstring str; //��� ��������
	HMENU hMenu;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_MENU));
		SetMenu(hWnd, hMenu);
		prog = Get(Progress);
		list = Get(List);
		edit = Get(Edit);
		spin = Get(Spin);
		SendMessage(spin, UDM_SETBUDDY, WPARAM(edit), 0);
		SendMessage(spin, UDM_SETRANGE32, 0, 1000);

		for (int i = 0, id = 1032; i < 16; ++i, ++id) // id ������ ���� , ������� 1032
		{
			buttons.push_back(Get(id));
			EnableWindow(buttons[i], false);
		}
		return true;

	case WM_COMMAND:

		if (LOWORD(wParam) == ID_EXIT)
			SendMessage(hWnd, WM_CLOSE, 0, 0);

		else if (LOWORD(wParam) == ID_NEW)
			SendMessage(hWnd, WM_COMMAND, WPARAM(ButtonStart), 0);

		else if (LOWORD(wParam) == ID_ABOUT)
			MessageBox(hWnd, L"����� ���� � ���, ����� �� ��������� ����� ������ �������� �� ���� ������� � ������� ����������� �����.\n\n\t\tZhenyaProduction, Inc.", L"� ���������", NULL);

		if (LOWORD(wParam) == ButtonStart) //������� �� ������ "������ ����"
		{
			numb.clear();
			numb.shrink_to_fit();
			index_now = 0;
			count = 0;
			SendMessage(list, LB_RESETCONTENT, 0, 0);

			wchar_t buf[5];
			GetWindowText(edit, buf, 5);
			std::wstring temp = buf;
			if (temp == L"")
			{
				MessageBox(hWnd, L"������� ������ ����� (�� ������ 1000)", L"����������", NULL);
				return true;
			}
			timer = stoi(temp);

			if (timer < 0 || timer > 1000 )
			{
				MessageBox(hWnd, L"������� ������ ����� (�� ������ 1000)", L"����������", NULL);
				return true;
			}

			srand((unsigned)time(0));
			for (int i = 0; i < 16; ++i)//�������� �����
			{
				numb.push_back(rand() % 100);
			}


			for (int i = 0; i < buttons.size(); ++i)//��������� ������
			{
				std::wstring  str = std::to_wstring(numb[i]);
				SetWindowText(buttons[i], str.c_str());
				EnableWindow(buttons[i], true);
			}

			sort(numb, numb.size());
			

			SendMessage(prog, PBM_SETRANGE, 0, MAKELPARAM(0, timer * 4));
			SendMessage(prog, PBM_SETPOS, 0, 0);
			SetTimer(hWnd, ProgressTimer, 250, NULL);
			SetTimer(hWnd, GameOver, timer * 1000 + 1, NULL);
		}


		else if (HIWORD(wParam) == EN_CHANGE) // ��������� � ���� ��� �������(��� ��������)
		{
			wchar_t buf1[5];
			GetWindowText(edit, buf1, 5);
			std::wstring temp = buf1;
			if (temp != L"")
			{
				int value = stoi(temp);
				SendMessage(spin, UDM_SETPOS32, 0, value);
			}
		}
	

		for (int i = 0, id = 1032; i < 16; ++i, ++id) //����������� �� ���� �������
		{
			if (LOWORD(wParam) == id) // ����� �� ������ � �������
			{
				wchar_t buf1[5];
				GetWindowText(Get(id), buf1, 5);
				std::wstring temp = buf1;
				int value = stoi(temp);
				if (value == numb[index_now])
				{
					SendMessage(list, LB_ADDSTRING, 0, LPARAM(temp.c_str()));
					EnableWindow(Get(id), false);
					++index_now;
					++count;
					if (count == 16)
					{
						KillTimer(hWnd, ProgressTimer);
						KillTimer(hWnd, GameOver);
						MessageBox(hWnd, L"���������� , �� �������!!!", L"����������", MB_OK);
					}
				}
				else
				{
					KillTimer(hWnd, ProgressTimer);
					KillTimer(hWnd, GameOver);
					for (int i = 0; i < 16; ++i) 
					{
						EnableWindow(buttons[i], false);
					}
					MessageBox(hWnd, L"���� ���������!!!", L"����������", MB_OK);
				}
			}
		}


		return true;

		
	case  WM_VSCROLL: //�������
		pos = SendMessage(spin, UDM_GETPOS32, 0, 0); 
		str = std::to_wstring(pos);
		SetWindowText(edit, str.c_str());
		return true;

	case WM_TIMER:
		if (wParam == ProgressTimer)
		{
			SendMessage(prog, PBM_DELTAPOS, 1, 0);
		}

		else if (wParam == GameOver)
		{
			KillTimer(hWnd, ProgressTimer);
			KillTimer(hWnd, GameOver);
			for (int i = 0; i < 16; ++i)
			{
				EnableWindow(buttons[i], false);
			}
			MessageBox(hWnd, L"���� ���������", L"����� ����", NULL);
		}

		return true;

	
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return true;


	}
	return false;
}