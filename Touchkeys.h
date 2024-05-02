

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


#endif
