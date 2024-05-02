

#ifndef TOUCHKEYS_H_
#define TOUCHKEYS_H_
typedef enum
{
	NO_KEY_TOUCHED				=	0xFF,
	TIMER_KEY_TOUCHED			=	0xEF,
	POWER_KEY_TOUCHED			=	0xDF,
	LIGHT_KEY_TOUCHED			=	0xBF,
	SWING_KEY_TOUCHED			=	0x7F,
	DOWN_KEY_TOUCHED			=	0xFE,
	UP_KEY_TOUCHED				=	0xFD,
	FAN_KEY_TOUCHED				=	0xFB,
	MODE_KEY_TOUCHED			=	0xF7,

	MODE_FAN_KEYS_TOUCHED		=   0xF3,
	SWING_TIMER_KEYS_TOUCHED	= 	0x6F,

}KeysConstType;

void Keys_Handler(void);

typedef union
{
	struct
	{
		struct
		{
			uint8_t OperationType;
			uint8_t SwingMode;
			uint8_t NumberOfSlaves;
			uint8_t BGcolorSelect;
			uint8_t OffTimerMinute;
			uint8_t OffTimerHour;
//			uint8_t TouckeySound;
		}Setting;
		struct
		{
			uint8_t PowerStatus;
			uint8_t OperationModeStatus;
			uint8_t FanVelocityOperation;
			uint8_t SetTemperature;

			int16_t RoomTemp;
			uint8_t OutdoorAirTemp;
			uint8_t IndoorCoilTemp;
			uint8_t DefrostStatus;
			uint8_t ModuleLockStatus;
			uint8_t TimerCounter;
		}Data;
	}Struct;
	uint16_t ErrorBuff[16];
	uint8_t Buff[11];

}OperatingStatusType;

typedef struct
{
	struct
	{
		uint8_t TouchKeysStatus;
		uint8_t TouchedKey;
		uint8_t	TouchKeyCounter;
		uint8_t IdleKeysCounter;
		uint8_t Initializer;
	}Touchkeys;
	struct
	{
		uint16_t ScreenMenu;
		uint8_t  WaitScreenFlag;
		uint8_t  ErrorByte;
		uint8_t  ErrorByteAddress;
		uint8_t  ErrorFound;
		uint8_t  Initializer;
		uint8_t	 Execution;
		uint16_t BackgroundColor;
	}Display;
	struct
	{
		uint16_t ADCRead[10];
		uint16_t ADCReadSum;
		uint16_t ADCReadAvg;
	}Analog;
	struct
	{
		uint8_t Status;
		uint8_t Second;
	}OffTimer;
	uint8_t StartUpDelay;
	uint8_t EEPROMStatus;
	uint8_t EEPROMBuff[10];
}FunctionalStatusType;


extern OperatingStatusType   UserDefinedStatus;
extern OperatingStatusType   ScreenStatus;
extern FunctionalStatusType  FunctionalStatus;

#endif
