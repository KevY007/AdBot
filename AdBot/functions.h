#pragma once

#include "main.h"

#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

#ifndef byte
typedef unsigned char byte;
#endif

// maps unsigned 8 bits/channel to D3DCOLOR // Copied from d3d9types with love.
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

#define D3DCOLOR_XYUV(y,u,v)   D3DCOLOR_ARGB(0xff,y,u,v)
#define D3DCOLOR_AYUV(a,y,u,v) D3DCOLOR_ARGB(a,y,u,v)

// maps floating point channels (0.f to 1.f range) to D3DCOLOR
#define D3DCOLOR_COLORVALUE(r,g,b,a) \
    D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))

#define WHITE D3DCOLOR_XRGB(255, 255, 255)

#pragma pack(push, 1)


enum Limits
{
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 2100,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
	SAMP_MAX_MAPICONS = 100,
};

enum Gamestate
{
	GAMESTATE_WAIT_CONNECT = 9,
	GAMESTATE_CONNECTING = 13,
	GAMESTATE_AWAIT_JOIN = 15,
	GAMESTATE_CONNECTED = 14,
	GAMESTATE_RESTARTING = 18
};

struct stSAMP_037
{
	void* pUnk0;
	struct stServerInfo_037* pServerInfo;
	uint8_t					byteSpace[24];
	char					szIP[257];
	char					szHostname[259];
	bool					bNametagStatus; // changes by /nametagstatus
	uint32_t				ulPort;
	uint32_t				ulMapIcons[100];
	int						iLanMode;
	int						iGameState;
	uint32_t				ulConnectTick;
	struct stServerPresets_037* pSettings;
	void* pRakClientInterface;
	struct stSAMPPools_037* pPools;
};

struct stChatEntry_037
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct stFontRenderer_037
{
	void* m_pChatFont;
	void* m_pLittleFont;
	void* m_pChatShadowFont;
	void* m_pLittleShadowFont;
	void* m_pCarNumberFont;
	void* m_pTempSprite;
	void* m_pD3DDevice;
	char* m_pszTextBuffer;
};

struct stChatInfo_037
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	struct stChatEntry_037	chatEntry[100];
	stFontRenderer_037* m_pFontRenderer;
	void* m_pChatTextSprite;
	void* m_pSprite;
	void* m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	void* pID3DXRenderToSurface;
	void* m_pTexture;
	void* pSurface;
	void* pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
	int					m_iTimeStampTextOffset;
};

struct stInputBox_037
{
	void* pUnknown;
	uint8_t	bIsChatboxOpen;
	uint8_t	bIsMouseInChatbox;
	uint8_t	bMouseClick_related;
	uint8_t	unk;
	DWORD	dwPosChatInput[2];
	uint8_t	unk2[263];
	int		iCursorPosition;
	uint8_t	unk3;
	int		iMarkedText_startPos; // Highlighted text between this and iCursorPosition
	uint8_t	unk4[20];
	int		iMouseLeftButton;
};

typedef void(__cdecl* CMDPROC) (PCHAR);
struct stInputInfo_037
{
	void* pD3DDevice;
	void* pDXUTDialog;
	stInputBox_037* pDXUTEditBox;
	CMDPROC				pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC				pszDefaultCMD;
};

struct stTextdraw_037
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct stTextdrawPool_037
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw_037* textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw_037* playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};

struct stServerInfo_037 {
	uint32_t 			uiIP;
	uint16_t 			usPort;

	// ...

};

struct stServerPresets_037
{
	uint8_t byteCJWalk;
	int m_iDeathDropMoney;
	float	fWorldBoundaries[4];
	bool m_bAllowWeapons;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint32_t ulVehicleFriendlyFire;
	bool m_byteHoldTime;
	bool m_bInstagib;
	bool m_bZoneNames;
	bool m_byteFriendlyFire;
	int		iClassesAvailable;
	float	fNameTagsDistance;
	bool m_bManualVehicleEngineAndLight;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t byteNoNametagsBehindWalls;
	int iPlayerMarkersMode;
	float	fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
	bool m_bLimitGlobalChatRadius;
};

struct stSAMPKeys_037
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stOnFootData_037
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys_037	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	short		sCurrentAnimationID;
	short		sAnimFlags;
};

struct stInCarData_037
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys_037	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
	};
};

struct stVehiclePool_037
{
	int						iVehicleCount;
	void* pUnk0;
	uint8_t					byteSpace1[0x112C];
	struct stSAMPVehicle* pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	struct vehicle_info* pGTA_Vehicle[SAMP_MAX_VEHICLES];
	uint8_t					byteSpace2[SAMP_MAX_VEHICLES * 6];
	uint32_t				ulShit[SAMP_MAX_VEHICLES];
	int						iIsListed2[SAMP_MAX_VEHICLES];
	uint32_t				byteSpace3[SAMP_MAX_VEHICLES * 2];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated;
};

struct stSAMPPools_037
{
	struct stActorPool_037* pActor;
	struct stObjectPool_037* pObject;
	struct stGangzonePool_037* pGangzone;
	struct stTextLabelPool_037* pText3D;
	struct stTextdrawPool_037* pTextdraw;
	void* pPlayerLabels;
	struct stPlayerPool_037* pPlayer;
	struct stVehiclePool_037* pVehicle;
	struct stPickupPool_037* pPickup;
};

struct stLocalPlayer037
{
	struct stSAMPPed		*pSAMP_Actor;
	uint16_t				sCurrentAnimID;
	uint16_t				sAnimFlags;
	uint32_t				ulUnk0;
	int						iIsActive;
	int						iIsWasted;
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	struct stOnFootData*		onFootData;
	struct stPassengerData*	passengerData;
	struct stTrailerData*	trailerData;
	struct stInCarData*		inCarData;
	struct stAimData*		aimData;
	uint8_t					byteTeamID;
	int						iSpawnSkin;
	uint8_t					byteUnk1;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID2;
	uint16_t				usUnk2;
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint16_t				sAimingAtPid;
	uint16_t				usUnk3;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	uint16_t				sTargetObjectID;
	uint16_t				sTargetVehicleID;
	uint16_t				sTargetPlayerID;
	struct stHeadSync*		headSyncData;
	uint32_t				ulHeadSyncTick;
	BYTE					byteSpace3[260];
	struct stSurfData*		surfData;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	uint32_t				ulUnk4;
	uint8_t					byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t					byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int						iSpectateID;
	int						iInitiatedSpectating;
	struct stDamageData*		vehicleDamageData;
};

struct stPlayerPool_037
{
	uint32_t				ulMaxPlayerID;
	uint16_t				sLocalPlayerID;
	void* pVTBL_txtHandler;
	std::string				strLocalPlayerName;
	struct stLocalPlayer_037* pLocalPlayer;
	int						iLocalPlayerPing;
	int						iLocalPlayerScore;
	struct stRemotePlayer_037* pRemotePlayer[SAMP_MAX_PLAYERS];
	int						iIsListed[SAMP_MAX_PLAYERS];
	DWORD						dwPlayerIP[SAMP_MAX_PLAYERS]; // always 0
};

struct stSAMPPools
{
	void* pMenu;
	struct stActorPool* pActor;
	struct stPlayerPool* pPlayer;
	struct stVehiclePool* pVehicle;
	struct stPickupPool* pPickup;
	struct stObjectPool* pObject;
	struct stGangzonePool* pGangzone;
	struct stTextLabelPool* pText3D;
	struct stTextdrawPool* pTextdraw;
};

struct stVehiclePool
{
	int						iVehicleCount;
	void* pUnk0;
	uint8_t					byteSpace1[0x112C];
	struct stSAMPVehicle* pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	struct vehicle_info* pGTA_Vehicle[SAMP_MAX_VEHICLES];
	uint8_t					byteSpace2[SAMP_MAX_VEHICLES * 6];
	uint32_t				ulShit[SAMP_MAX_VEHICLES];
	int						iIsListed2[SAMP_MAX_VEHICLES];
	uint32_t				byteSpace3[SAMP_MAX_VEHICLES * 2];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated;
};

struct stSAMP
{
	uint8_t                  	_pad0[20];
	void* pUnk0;
	struct stServerInfo* pServerInfo;
	uint8_t				_pad1[16];
	void* pRakClientInterface;
	char				szIP[256 + 1];
	char				szHostname[256 + 1];
	uint8_t                 	_pad2;
	bool                    	m_bUpdateCameraTarget;
	bool				m_bNoNameTagStatus;
	uint32_t			ulPort;
	BOOL				m_bLanMode;
	uint32_t			ulMapIcons[SAMP_MAX_MAPICONS];
	Gamestate			iGameState;
	uint32_t			ulConnectTick;
	struct stServerPresets* pSettings;
	uint8_t                 	_pad3[5];
	struct stSAMPPools* pPools;
};

struct stChatEntry
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct stFontRenderer
{
	void* m_pChatFont;
	void* m_pLittleFont;
	void* m_pChatShadowFont;
	void* m_pLittleShadowFont;
	void* m_pCarNumberFont;
	void* m_pTempSprite;
	void* m_pD3DDevice;
	char* m_pszTextBuffer;
};

struct stChatInfo
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	struct stChatEntry	chatEntry[100];
	stFontRenderer* m_pFontRenderer;
	void* m_pChatTextSprite;
	void* m_pSprite;
	void* m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	void* pID3DXRenderToSurface;
	void* m_pTexture;
	void* pSurface;
	void* pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
};

struct stInputBox
{
	void* pUnknown;
	uint8_t	bIsChatboxOpen;
	uint8_t	bIsMouseInChatbox;
	uint8_t	bMouseClick_related;
	uint8_t	unk;
	DWORD	dwPosChatInput[2];
	uint8_t	unk2[263];
	int		iCursorPosition;
	uint8_t	unk3;
	int		iMarkedText_startPos; // Highlighted text between this and iCursorPosition
	uint8_t	unk4[20];
	int		iMouseLeftButton;
};

typedef void(__cdecl* CMDPROC) (PCHAR);
struct stInputInfo
{
	void* pD3DDevice;
	void* pDXUTDialog;
	stInputBox* pDXUTEditBox;
	CMDPROC				pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC				pszDefaultCMD;
};

struct stTextdraw
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct stTextdrawPool
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw* textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw* playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};

struct stServerInfo {
	uint32_t 			uiIP;
	uint16_t 			usPort;

	// ...

};

struct stServerPresets
{
	uint8_t byteCJWalk;
	int m_iDeathDropMoney;
	float	fWorldBoundaries[4];
	bool m_bAllowWeapons;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint32_t ulVehicleFriendlyFire;
	bool m_byteHoldTime;
	bool m_bInstagib;
	bool m_bZoneNames;
	bool m_byteFriendlyFire;
	int		iClassesAvailable;
	float	fNameTagsDistance;
	bool m_bManualVehicleEngineAndLight;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t byteNoNametagsBehindWalls;
	int iPlayerMarkersMode;
	float	fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
	bool m_bLimitGlobalChatRadius;
};


enum ChatMessageType
{
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 2,
	CHAT_TYPE_INFO = 4,
	CHAT_TYPE_DEBUG = 8
};

struct stSAMPKeys
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stOnFootData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	short		sCurrentAnimationID;
	short		sAnimFlags;
};

struct stInCarData
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
		float       fBikeSideAngle;
	};
};

struct stLocalPlayer
{
	struct stSAMPPed* pSAMP_Actor;
	struct stTrailerData*		trailerData;
	struct stOnFootData*		onFootData;
	struct stPassengerData*		passengerData;
	struct stInCarData*		inCarData;
	struct stAimData*		aimData;
	int				iIsActive;
	int				iIsWasted;
	uint16_t			sCurrentVehicleID;
	uint16_t			sLastVehicleID;
	uint16_t			sCurrentAnimID;
	uint16_t			sAnimFlags;
	uint32_t			ulUnk0;
	void*       	cameraTarget;
	uint32_t			ulCameraTargetTick;
	struct stHeadSync*		headSyncData;
	uint32_t			ulHeadSyncTick;
	int				iIsSpectating;
	uint8_t				byteTeamID2;
	uint16_t			usUnk2;
	uint32_t			ulSendTick;
	uint32_t			ulSpectateTick;
	uint32_t			ulAimTick;
	uint32_t			ulStatsUpdateTick;
	int				iSpawnClassLoaded;
	uint32_t			ulSpawnSelectionTick;
	uint32_t			ulSpawnSelectionStart;
	void*      		spawnInfo;
	int				iIsActorAlive;
	uint32_t			ulWeapUpdateTick;
	uint16_t			sAimingAtPlayerID;
	uint16_t			sAimingAtActorID;
	uint8_t				byteCurrentWeapon;
	uint8_t				byteWeaponInventory[13];
	int				iWeaponAmmo[13];
	int				iPassengerDriveBy;
	uint8_t				byteCurrentInterior;
	int				iIsInRCVehicle;
	char                    	szPlayerName[256];
	struct stSurfData*		surfData;
	int				iClassSelectionOnDeath;
	int				iSpawnClassID;
	int				iRequestToSpawn;
	int				iIsInSpawnScreen;
	uint32_t			ulDisplayZoneTick;
	uint8_t				byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t				byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int				iSpectateID;
	int				iInitiatedSpectating;
	struct stDamageData*		vehicleDamageData;
};

struct stPlayerPool
{
	uint16_t				sLocalPlayerID;
	void* pVTBL_txtHandler;
	std::string				strLocalPlayerName;
	struct stLocalPlayer* pLocalPlayer;
	uint32_t				ulMaxPlayerID;
	struct stRemotePlayer* pRemotePlayer[SAMP_MAX_PLAYERS];
	int					iIsListed[SAMP_MAX_PLAYERS];
	BOOL					bSavedCheckCollision[SAMP_MAX_PLAYERS];
	int					iLocalPlayerPing;
	int					iLocalPlayerScore;
};


// FUNCTIONS

struct stSAMP* stGetSampInfo(void);
struct stSAMP_037* stGetSampInfo037(void);
extern struct stSAMP* g_stSAMP;
extern struct stChatInfo* g_Chat;
extern struct stInputInfo* g_Input;

extern struct stSAMP_037* g_stSAMP037;
extern struct stChatInfo_037* g_Chat037;
extern struct stInputInfo_037* g_Input037;


static signed char hex_to_dec(signed char ch);
uint8_t* hex_to_bin(const char* str);
void SetupSAMPHook(const char* szName, DWORD dwFuncOffset, void* Func, int iType, int iSize, const char* szCompareBytes);
int memcpy_safe(void* _dest, const void* _src, uint32_t len, int check = NULL, const void* checkdata = NULL);
int memcmp_safe(const void* _s1, const void* _s2, uint32_t len);
bool isBadPtr_writeAny(void* pointer, ULONG size);
bool isBadPtr_readAny(void* pointer, ULONG size);
bool isBadPtr_handlerAny(void* pointer, ULONG size, DWORD dwFlags);
struct stChatInfo* stGetSampChatInfo(void);
struct stInputInfo* stGetInputInfo(void);
struct stChatInfo_037* stGetSampChatInfo037(void);
struct stInputInfo_037* stGetInputInfo037(void);
void addToChatWindow(char* text, D3DCOLOR textColor);
void addMessageToChatWindow(D3DCOLOR col, const char* text, ...);
uint8_t hook_handle_rpc_packet2();
uint8_t hook_handle_rpc_packet();
void __stdcall CNetGame__destructor();
void say(char* msg);
void addClientCommand(char* name, CMDPROC function);