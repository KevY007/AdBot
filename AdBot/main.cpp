#include "main.h"

DWORD				g_SAMP = NULL;
HANDLE				g_DllHandle;

bool				samp037 = false;


string				admsg = "N/A";
string				adcmd = "N/A";
bool				advertising = false;

std::vector<string> callkeywords;
bool				callbot = false;
string				callcmd = "/call";
string				numberformat = "[PH: ~]";

std::string get_str_between_two_str(const std::string& s,
	const std::string& start_delim,
	const std::string& stop_delim)
{
	unsigned first_delim_pos = s.find(start_delim);
	unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
	unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);

	return s.substr(end_pos_of_first_delim,
		last_delim_pos - end_pos_of_first_delim);
}

void SendAd()
{
	char buf[256];
	sprintf(buf, "%s %s", adcmd.c_str(), admsg.c_str());
	say(buf);
	return;
}

void cmd_adbot(char* params)
{
	if (strlen(params) <= 2 || params == nullptr) {
		addMessageToChatWindow(WHITE, "/adbot [enable/admsg/cmd]");
		return;
	}

	std::stringstream s(params);

	std::string first, second;
	s >> first >> second;

	if (first.find("enable") != string::npos)
	{
		if (admsg.compare("N/A") == 0 || adcmd.compare("N/A") == 0)
			return addMessageToChatWindow(WHITE, "The advertise message XOR command are not set.");

		advertising = !advertising;
		addMessageToChatWindow(WHITE, "{1F8415} Toggled adbot: %s.", advertising ? "{00FF33}Enabled" : "{FF0000}Disabled");
		if(advertising) SendAd();
	}
	else if (first.find("admsg") != string::npos)
	{
		if (second.empty())
			return addMessageToChatWindow(WHITE, "/adbot [admsg] [text to find & send]");

		admsg = second;

		while (s >> second)
			admsg.append(" " + second);
		
		addMessageToChatWindow(WHITE, "{1F8415} Advertising: {FFFFFF}\"%s\"", admsg.c_str());
	}
	else if (first.find("cmd") != string::npos)
	{
		if (second.empty())
			return addMessageToChatWindow(WHITE, "/adbot [cmd] [cmd e.g. /ad]");

		adcmd = second;
		addMessageToChatWindow(WHITE, "{1F8415} Advertise command set to: \"{FFFFFF}%s\"", adcmd.c_str());
	}
	else
	{
		cmd_adbot("");
	}
	return;
}


void cmd_callbot(char* params)
{
	if (strlen(params) <= 2 || params == nullptr) {
		addMessageToChatWindow(WHITE, "/callbot [enable/addword/removeword/callcmd/numberformat/words/reset/help]");
		return;
	}

	std::stringstream s(params);

	std::string first, second;
	s >> first >> second;

	if (first.find("enable") != string::npos)
	{
		if (callkeywords.size() == 0)
			return addMessageToChatWindow(WHITE, "The keywords are not set, refer to /callbot help.");

		callbot = !callbot;
		addMessageToChatWindow(WHITE, "{1F8415} Toggled callbot: %s.", callbot ? "{00FF33}Enabled" : "{FF0000}Disabled");
	}
	else if (first.find("addword") != string::npos)
	{
		if (second.empty())
			return addMessageToChatWindow(WHITE, "/callbot addword <keyword>");

		callkeywords.push_back(second);

		addMessageToChatWindow(WHITE, "Added the keyword: %s", second.c_str());
	}
	else if (first.find("removeword") != string::npos)
	{
		if (second.empty())
			return addMessageToChatWindow(WHITE, "/callbot removeword <keyword>");

		auto itr = std::find(callkeywords.begin(), callkeywords.end(), second);
		if (itr != callkeywords.end())
		{
			callkeywords.erase(itr);

			addMessageToChatWindow(WHITE, "Removed the keyword [%s]", second.c_str());
		}
		else addMessageToChatWindow(WHITE, "Could not find the keyword: %s", second.c_str());
	}
	else if (first.find("callcmd") != string::npos)
	{
		if (second.empty())
			return addMessageToChatWindow(WHITE, "/callbot callcmd <cmd>");


		callcmd = second;

		addMessageToChatWindow(WHITE, "Call command is now %s.", callcmd.c_str());
	}
	else if (first.find("numberformat") != string::npos)
	{
		if (second.empty()) {
			addMessageToChatWindow(WHITE, "/callbot numberformat <number format with '~' as number>");
			addMessageToChatWindow(WHITE, "e.g. /callbot numberformat [PH: ~]");
			return;
		}

		if (second.find("~") == string::npos) return addMessageToChatWindow(WHITE, "The number format is incorrect! No tidle was found!");
		
		numberformat = second;

		addMessageToChatWindow(WHITE, "Number format changed to {1F8415}%s.", numberformat.c_str());
	}
	else if (first.find("words") != string::npos)
	{
		addMessageToChatWindow(WHITE, "Keywords Specified:");

		for each (auto var in callkeywords) {
			addMessageToChatWindow(WHITE, "{1F8415}%s", var.c_str());
		}
	}
	else if (first.find("reset") != string::npos)
	{
		callkeywords.clear();
		callbot = false;
		addMessageToChatWindow(WHITE, "{1F8415}Callbot Keywords & Settings Reset.");
	}
	else if (first.find("help") != string::npos)
	{
		addMessageToChatWindow(WHITE, "{1F8415}Callbot Documentation - Commands:");
		addMessageToChatWindow(WHITE, "enable - Enables the callbot, it will start finding for ads matching the specific words set.");
		addMessageToChatWindow(WHITE, "addword - Adds a word to the keyword list, when all keywords are found in an ad, only then it will trigger.");
		addMessageToChatWindow(WHITE, "removeword - To remove a word from the list, use words to see the list or reset to clear.");
		addMessageToChatWindow(WHITE, "words - To output the entire list of keywords that have to be matched in the ad.");
		addMessageToChatWindow(WHITE, "reset - Resets the keyword list and turns the callbot off.");
		addMessageToChatWindow(WHITE, "callcmd - Sets the call command, by default it's /call. You can change to /c or whatever.");
		addMessageToChatWindow(WHITE, "numberformat - The format which has the number in to set, e.g. [PH: ~] where tidle will be place of number.");

		addMessageToChatWindow(WHITE, "");
		addMessageToChatWindow(WHITE, "{1F8415}Callbot Documentation - Overview/Basic:");
		addMessageToChatWindow(WHITE, "To use this, start by deciding on a list of word and adding them, like if you wanna buy a jester or call any ad");
		addMessageToChatWindow(WHITE, "with the word 'selling' and 'jester' in it, then /callbot addword selling, /callbot addword jester.");
		addMessageToChatWindow(WHITE, "Now this have added the keywords selling and jester in it, now once you /callbot enable it, it will look at");
		addMessageToChatWindow(WHITE, "ANY ad that has ALL of the keywords you specified in it and call the guy automatically (/call number).");
		addMessageToChatWindow(WHITE, "WARNING: IT REQUIRES ALL KEYWORDS TO BE MATCHED.");
	}
	else
	{
		cmd_callbot("");
	}
	return;
}

void ThrMainFS() 
{
	while (g_SAMP == NULL || (g_Chat == NULL && g_Chat037 == NULL))
	{
		g_SAMP = (DWORD)GetModuleHandleA("samp.dll");

		g_Chat = stGetSampChatInfo();
        g_Chat037 = stGetSampChatInfo037();
		Sleep(1000);
	}
	
	bool initSampRak = false;
	while (true)
	{
		if (!initSampRak)
		{
			if (memcmp_safe((uint8_t*)g_SAMP + 0xBABE, hex_to_bin(SAMP037_CMP), 10))
			{
				samp037 = true;
			}
			else samp037 = false;

			if (samp037)
			{
				g_stSAMP037 = stGetSampInfo037();

				if (isBadPtr_writeAny(g_stSAMP037, sizeof(stSAMP_037)))
				{
					continue;
				}

				if (isBadPtr_writeAny(g_stSAMP037->pPools, sizeof(stSAMPPools_037)))
				{
					continue;
				}

				g_Chat037 = stGetSampChatInfo037();
				if (isBadPtr_writeAny(g_Chat037, sizeof(stChatInfo_037)))
				{
					continue;
				}

				g_Input037 = stGetInputInfo037();
				if (isBadPtr_writeAny(g_Input037, sizeof(stInputInfo_037)))
				{
					continue;
				}

				if (g_stSAMP037->pRakClientInterface == NULL)
				{
					continue;
				}

				g_RakClient = new RakClient(g_stSAMP037->pRakClientInterface);
				g_stSAMP037->pRakClientInterface = new HookedRakClientInterface();

				SetupSAMPHook("HandleRPCPacket", SAMP037_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet, DETOUR_TYPE_JMP, 6, "FF5701");
				SetupSAMPHook("HandleRPCPacket2", SAMP037_HOOKENTER_HANDLE_RPC2, hook_handle_rpc_packet2, DETOUR_TYPE_JMP, 8, "FF5701");
				SetupSAMPHook("CNETGAMEDESTR1", SAMP037_HOOKENTER_CNETGAME_DESTR, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
				SetupSAMPHook("CNETGAMEDESTR2", SAMP037_HOOKENTER_CNETGAME_DESTR2, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
			}
			else
			{
				g_stSAMP = stGetSampInfo();

				if (isBadPtr_writeAny(g_stSAMP, sizeof(stSAMP)))
				{
					continue;
				}

				if (isBadPtr_writeAny(g_stSAMP->pPools, sizeof(stSAMPPools)))
				{
					continue;
				}

				g_Chat = stGetSampChatInfo();
				if (isBadPtr_writeAny(g_Chat, sizeof(stChatInfo)))
				{
					continue;
				}

				g_Input = stGetInputInfo();
				if (isBadPtr_writeAny(g_Input, sizeof(stInputInfo)))
				{
					continue;
				}

				if (g_stSAMP->pRakClientInterface == NULL)
				{
					continue;
				}

				g_RakClient = new RakClient(g_stSAMP->pRakClientInterface);
				g_stSAMP->pRakClientInterface = new HookedRakClientInterface();

				SetupSAMPHook("HandleRPCPacket", SAMP_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet, DETOUR_TYPE_JMP, 6, "FF5701");
				SetupSAMPHook("HandleRPCPacket2", SAMP_HOOKENTER_HANDLE_RPC2, hook_handle_rpc_packet2, DETOUR_TYPE_JMP, 8, "FF5701");
				SetupSAMPHook("CNETGAMEDESTR1", SAMP_HOOKENTER_CNETGAME_DESTR, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
				SetupSAMPHook("CNETGAMEDESTR2", SAMP_HOOKENTER_CNETGAME_DESTR2, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
			}

			initSampRak = true;
			addClientCommand("adbot", cmd_adbot);
			addClientCommand("callbot", cmd_callbot);
			addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "{999999}Advertise Bot Loaded. /adbot /callbot");
		}
		if (initSampRak)
		{
			// Code if you wanna execute any. Put it in here so it doesn't execute before samp has loaded.
		}
		Sleep(100); // Adjust according to your needs
	}
}

bool OnSendRPC(int uniqueID, BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (uniqueID == RPCEnumeration::RPC_RequestSpawn) // Example
	{

	}
	return true;
}

bool OnSendPacket(BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	uint8_t packetId;
	parameters->ResetReadPointer();
	parameters->Read(packetId);
	
	if (packetId == PacketEnumeration::ID_BULLET_SYNC) // Example
	{

	}
	return true;
}

void HandleRPCPacketFunc(unsigned char id, RPCParameters* rpcParams, void(*callback) (RPCParameters*))
{
	if (rpcParams != nullptr && rpcParams->numberOfBitsOfData >= 8)
	{
		BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
		if (id == RPC_ClientMessage)
		{
			UINT32 color;
			UINT32 stringlen;
			char string[255];

			bsData.ResetReadPointer();
			bsData.Read(color);
			bsData.Read(stringlen);
			bsData.Read(string, stringlen);

			string[stringlen] = '\0';

			if (strlen(string) >= 2)
			{
				if (advertising)
				{
					std::string find = admsg.substr(0, 24);
					char* findPos = strstr(string, find.c_str());
					if (findPos != NULL)
					{
						SendAd();
					}
				}
				if (callbot && callkeywords.size() > 0)
				{
					std::string cstr = string;
					bool found = true;
					for each (auto key in callkeywords)
					{
						auto found = cstr.find(key);
						if (found != std::string::npos)
							continue;
						else
							found = false;
					}

					if (found)
					{
						std::size_t tidlepos = numberformat.find("~");

						if (tidlepos == string::npos) {
							addMessageToChatWindow(WHITE, "Tidle not found in numberformat! [CALLBOT]");
						}
						else
						{
							std::string phstart = numberformat.substr(0, tidlepos);

							std::string phend = numberformat.substr(tidlepos + 1);

							std::string number = get_str_between_two_str(cstr, phstart, phend);
							if (number.length() > 2)
							{
								addMessageToChatWindow(D3DCOLOR_XRGB(52, 165, 14), "[CALLBOT] Matched last ad with keywords, calling number: %s..", 
									number.c_str());

								char buf[256];
								sprintf(buf, "%s %s", callcmd.c_str(), number.c_str());
								say(buf);
							}
						}
					}
				}
			}
		}
	}
	callback(rpcParams);
}

bool OnReceivePacket(Packet* p)
{
	if (p->data == nullptr || p->length == 0)
		return true;
	
	if (p->data[0] == PacketEnumeration::ID_VEHICLE_SYNC) // Example.
	{
		
	}
	return true;
}


BOOL WINAPI DllMain(
	HINSTANCE hinstDLL, 
	DWORD fdwReason,    
	LPVOID lpReserved) 
{

	g_DllHandle = hinstDLL;

	DisableThreadLibraryCalls((HMODULE)hinstDLL);

	if (fdwReason != DLL_PROCESS_ATTACH)
		return FALSE;

	if (GetModuleHandle("samp.dll"))
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThrMainFS, NULL, 0, NULL);
	}

	return TRUE;  
}