//         Author:  lbk
//        Contact:  804872510@qq.com
//    Last update:  2020.11.13

#ifndef _RIGHTHANDLE_H_
#define _RIGHTHANDLE_H_

#include<Windows.h>

//���joystick����api��֧�ֿ�
#include<MMSystem.h>
#pragma comment(lib, "Winmm.lib")

//void Threadsend(void);

using namespace std;
JOYINFOEX joyinfoex;

int righthandle(void)
{
	//JOYINFO joyinfo;//����joystick��Ϣ�ṹ��

	joyinfoex.dwSize = sizeof(JOYINFOEX);
	joyinfoex.dwFlags = JOY_RETURNALL;

	//thread test(Threadsend);

	while (1)
	{
		//��ȡ�ֱ���Ϣ
		UINT joyNums;
		joyNums = joyGetNumDevs();
		printf("��ǰ�豸����:%d \n", joyNums);
		if (joyNums >= 1)
		{
			MMRESULT joyreturn = joyGetPosEx(JOYSTICKID1, &joyinfoex);
			if (joyreturn == JOYERR_NOERROR)
			{
				printf("x���� 0x%09d ", joyinfoex.dwXpos);
				printf("y���� 0x%09d ", joyinfoex.dwYpos);
				printf("z���� 0x%09X ", joyinfoex.dwZpos);
				//printf("r���� 0x%09X ", joyinfoex.dwRpos);
				//printf("U���� 0x%09X ", joyinfoex.dwUpos);
				//printf("V���� 0x%09X ", joyinfoex.dwVpos);
				printf("pov���� 0x%09X ", joyinfoex.dwPOV);
				printf("���� 0x%09X ", joyinfoex.dwButtons);
				printf("\n");
			}
			else
			{
				switch (joyreturn)
				{
				case JOYERR_PARMS:
					printf("bad parameters\n");
					break;
				case JOYERR_NOCANDO:
					printf("request not completed\n");
					break;
				case JOYERR_UNPLUGGED:
					printf("joystick is unplugged\n");
					break;
				default:
					printf("δ֪����\n");
					break;
				}
			}
		}

		//if (kbhit()) break;
		Sleep(500);
	}



	//test.join();
	return 0;
}


/*
void Threadsend(void)
{
	while (1)
	{
		if (joyinfoex.dwXpos < 12000)
			cout << "left" << "\n";
		if(joyinfoex.dwXpos >50000)
			cout << "right" << "\n";


		Sleep(500);

	}


}

*/

//int main()
//{


	 // std::cout << "Hello World!\n";
//}



/*  direct x��ʽ���е��鷳

//����DirectInput�豸
LPDIRECTINPUT8 g_pDirectInput = NULL;
HINSTANCE hInstance = 0;
if (FAILED(DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (void**)&g_pDirectInput, NULL)))
{
	return E_FAIL;
}

LPVOID pvR = 0;
LPDIENUMDEVICESCALLBACK lpCall = 0;
HRESULT EnumDevices
(
	DWORD dwDevType,
	LPDIENUMDEVICESCALLBACK lpCallBack,
	LPVOID pvRef,
	DWORD dwFlags
);
EnumDevices(DI8DEVCLASS_ALL, lpCall, pvR, DIEDFL_ALLDEVICES);
std::cout << "pvR " << pvR << "\n";

HRESULT CreateDevice(
	REFGUID rguid,
	LPDIRECTINPUTDEVICE * lplpDirectInputDevice,
	LPUNKNOWN pUnkOuter
);
CreateDevice((REFGUID)pvR, (LPDIRECTINPUTDEVICE*)g_pDirectInput, 0);

std::cout << g_pDirectInput << "\n";

*/









#endif