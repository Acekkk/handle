#pragma once
//         Author:  lbk
//        Contact:  804872510@qq.com
//    Last update:  2020.11.13

#include<iostream>
#include<string>
#include <canlib.h>
#include"can.h"



#ifndef _FUNCTION_H_
#define _FUNCTION_H_

namespace lbk
{
	class function
	{
	public:
		 



	public:
		void decode0x180(const uint8 *buf);
		void decode0x280(const uint8* buf);
		void decode0x380(const uint8* buf);
		
		//bool UDP();
	};


	


}



#endif