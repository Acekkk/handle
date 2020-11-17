
//         Author:  lbk
//        Contact:  804872510@qq.com
//    Last update:  2020.11.13

#pragma once


#include <iostream>
#include <canlib.h>
#include <string>
#include"my_typedef.h"

#ifndef _CAN_H_
#define _CAN_H_



namespace lbk
{
	class pciecan
	{
	public:

		canHandle hn;                        //canhandle
		canStatus stat;                      //error stat
		bool can_on;                         //canbus stat
		char channel = 0;                    
		int number_channel = 0;
		char device_name[100] = { 0 };

	public:
		
		bool caninit();
		void CheckForError(char cmd[50], canStatus stat);
		bool CanRcv(int64* _rcv_id, uint8* _rcv_buf, uint32* _rcv_len);
		bool CanSend(int64 _send_id, uint8* _send_buf, uint32 _send_len);
		bool Canoff();
		bool CanClose();







	};
}

#endif