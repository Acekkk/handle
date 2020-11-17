
//         Author:  lbk
//        Contact:  804872510@qq.com
//    Last update:  2020.11.13

// Left_handle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <canlib.h>
#include<thread>
#include<string>
#include "can.h"
#include<tchar.h>
//#include <WinSock2.h>
#include <Windows.h>
#include "function.h"
#include"righthandle.h"
#include<stdio.h>
//#include <WinSock2.h>

#pragma  warning(disable: 4996)
#pragma comment(lib,"ws2_32.lib")

using namespace std;
using namespace lbk;

//void Threadleft(void);



pciecan pcie_can;
function func;

int main()
{
    
    pcie_can.caninit();
    //func.TCP();
    //thread test_l(Threadleft); //左手柄

    thread test_r(righthandle); //右手柄

    Sleep(500);

    WSAData wsd;           //初始化信息
    SOCKET soSend;         //发送SOCKET
    int nRet = 0;
    //int i = 0;
    int dwSendSize = 0;
    SOCKADDR_IN siLocal;    //远程发送机地址和本机接收机地址

    //启动Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {/*进行WinSocket的初始化,
        windows 初始化socket网络库，申请2，2的版本，windows socket编程必须先初始化。*/
        cout << "WSAStartup Error = " << WSAGetLastError() << endl;
        return 0;
    }

    //创建socket

    //AF_INET 协议族:决定了要用ipv4地址（32位的）与端口号（16位的）的组合
    //SOCK_DGRAM --  UDP类型，不保证数据接收的顺序，非可靠连接；
    soSend = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (soSend == SOCKET_ERROR) {
        cout << "socket Error = " << WSAGetLastError() << endl;
        return 1;
    }

    //设置端口号
    int nPort = 8888;
    siLocal.sin_family = AF_INET;
    siLocal.sin_port = htons(nPort);
    siLocal.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1)//for (int i = 0; i < 30; i++) 
    {
        //开始发送数据
        //发送数据到指定的IP地址和端口
        nRet = sendto(soSend, "rov_up_on", strlen("rov_up_on"), 0,
            (SOCKADDR*)&siLocal, sizeof(SOCKADDR));
        Sleep(500);
        nRet = sendto(soSend, "rov_up_off", strlen("rov_up_on"), 0,
            (SOCKADDR*)&siLocal, sizeof(SOCKADDR));
        nRet = sendto(soSend, "rov_foward_on", strlen("rov_up_on"), 0,
            (SOCKADDR*)&siLocal, sizeof(SOCKADDR));
        Sleep(500);
        nRet = sendto(soSend, "rov_foward_off", strlen("rov_up_on"), 0,
            (SOCKADDR*)&siLocal, sizeof(SOCKADDR));
        Sleep(500);

        if (nRet == SOCKET_ERROR) 
        {
            cout << "sendto Error " << WSAGetLastError() << endl;
            break;
        }
    }
    //关闭socket连接
    closesocket(soSend);
    //清理
    WSACleanup();
    
    //test_l.join();
    //pcie_can.CanClose();
    
    

    test_r.join();

    return 0;


	
    //std::cout << "Hello World!\n";
}


void Threadleft(void)
{
    int64 can_id = 0;
    uint32 can_len = 0;
    uint8 can_buf[8] = {0};
    uint8 testdata[8] = { 0x11,0x22,0x33 };
          
         
    while (1)
    {
        pcie_can.CanRcv(&can_id, can_buf, &can_len);
       
        cout <<"can receive id:"<<can_id<<"  "<<"data: "<<(int)can_buf[0]<<" "<<(int)can_buf[1]<<" "
            << (int)can_buf[2] <<" "<< (int)can_buf[3] <<" "<< (int)can_buf[4]<<" "<< (int)can_buf[5]
            <<" "<< (int)can_buf[6]<<" "<< (int)can_buf[7] <<"\n";
        //pcie_can.CanSend(0x66, testdata, 8);
        //cout << "can send data" <<"\n";
        Sleep(2000);
        
    }
}





// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

