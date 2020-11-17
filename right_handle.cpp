
//

#include <iostream>
#include<thread>
#include<string>
//#include<DInput.h>
#include"righthandle.h"

//#pragma comment(lib,"dinput8.lib")
//#pragma comment(lib,"dxguid.lib")



int righthandle(void)
{
	//JOYINFO joyinfo;//定义joystick信息结构体
	
	joyinfoex.dwSize = sizeof(JOYINFOEX);
	joyinfoex.dwFlags = JOY_RETURNALL;

	//thread test(Threadsend);

	while (1)
	{
		//读取手柄信息
		UINT joyNums;
		joyNums = joyGetNumDevs();
				printf("当前设备数量:%d \n",joyNums);
		if (joyNums >= 1)
		{
			MMRESULT joyreturn = joyGetPosEx(JOYSTICKID1, &joyinfoex);
			if (joyreturn == JOYERR_NOERROR)
			{
				printf("x坐标 0x%09d ", joyinfoex.dwXpos);
				printf("y坐标 0x%09d ", joyinfoex.dwYpos);
				printf("z坐标 0x%09X ", joyinfoex.dwZpos);
				//printf("r坐标 0x%09X ", joyinfoex.dwRpos);
				//printf("U坐标 0x%09X ", joyinfoex.dwUpos);
				//printf("V坐标 0x%09X ", joyinfoex.dwVpos);
				printf("pov坐标 0x%09X ", joyinfoex.dwPOV);
				printf("按键 0x%09X ", joyinfoex.dwButtons);
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
					printf("未知错误\n");
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



/*  direct x方式，有点麻烦

//创建DirectInput设备
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
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单


