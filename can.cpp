
//         Author:  lbk
//        Contact:  804872510@qq.com
//    Last update:  2020.11.13

#include <iostream>
#include <canlib.h>
#include "can.h"

using namespace std;
namespace lbk
{
	
	void pciecan::CheckForError(char cmd[50], canStatus stat)
	{
		//if stat not ok, print error
		if (stat != canOK)
		{
			char buf[255];
			buf[0] = '\0';
			canGetErrorText(stat, buf, sizeof(buf));

			printf("[%s] %s: failed, stat=%d\n", cmd, buf, (int)stat);
			printf("ABORT (Press any key)");

			getchar();
			abort();
		}
	}


	bool pciecan::caninit()
	{
		

		canInitializeLibrary();  //must be first
		hn = canOpenChannel(channel, canOPEN_EXCLUSIVE); //open can channel
		//cout << hn << "\n";
		
		stat = canGetNumberOfChannels(&number_channel);
		//std::cout << stat << "\n";
		if (number_channel > 0)
			cout << "found" << " " << number_channel << " " << "channnels\n";
		else
			cout << "not found channels\n";
		for (int i = 0; i < number_channel; i++)
		{
			canGetChannelData(i, canCHANNELDATA_DEVDESCR_ASCII, device_name, sizeof(device_name));
			CheckForError((char*)"canGetNumberOfChannels", stat);
			//canGetChannelData(i, canCHANNELDATA_CHAN_NO_ON_CARD, &device_channel, sizeof(device_channel));
			cout << "channel_data:" << i << " " << device_name << "\n";

		}

		if (hn)
		{
			cout << "open can device failed!";
			return 1;
		}

		if (canSetBusParams(hn, canBITRATE_250K, 0, 0, 0, 0, 0))
		{
			cout << "setting params failed!";
			return 1;
		}

		if (canSetBusOutputControl(hn, canDRIVER_NORMAL))
		{
			cout << "Setting CAN bus control failed!";
			return 1;
		}

		if (canBusOn(hn))
		{
			cout << "buson failed!";
			return 1;
		} 

		cout << "can channel "<<(int)channel<< "  initialized!!!\n";
		can_on = 1;
		return 0;
	}


	bool pciecan::CanRcv(int64* _rcv_id, uint8* _rcv_buf, uint32* _rcv_len)  //receive can data
	{
		uint32 flags = 0;
		uint64 timestamp = 0;  

		// Note that canRead func returns 0 if OK, and negative values otherwise.
		return !canRead(hn, _rcv_id, _rcv_buf, _rcv_len, &flags, &timestamp);
	}


	bool pciecan::CanSend(int64 _send_id, uint8* _send_buf, uint32 _send_len)
	{
		// Note that canWrite func returns 0 if OK, and negative values otherwise.
		return !canWrite(hn, _send_id, _send_buf, _send_len, 0);
	}

	bool pciecan::Canoff()
	{
		if (canBusOff(hn))
		{
			cout << "can off failed!";
				return 1;
		}
		return 0;
	}

	bool pciecan::CanClose()
	{
		// Note that canClose func returns 0 if OK, and negative values otherwise.
		if (can_on)
			if (canClose(hn))
			{
				cout << "CAN device close failed!";
				return 1;
			}
		//cout << "can closed!";
		can_on = 0;
		return 0;
	}







}