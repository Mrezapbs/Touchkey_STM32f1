
#include "Touchkeys.h"
#include "API.h"
#include "Buzzer.h"
#include "LCD_ILI_9341_Driver.h"
#include "main.h"
#include "stm32f1xx_it.h"
#include "Com.h"

void Touchkeys_User_Menu_Handler(void)
{
	switch (FunctionalStatus.Touchkeys.TouchedKey)
	{
		case UP_KEY_TOUCHED:
			if(ScreenStatus.Struct.Data.PowerStatus == SYSTEM_ON)
			{
				if((ScreenStatus.Struct.Data.OperationModeStatus == COOL_OPERATION)||(ScreenStatus.Struct.Data.OperationModeStatus == HEAT_OPERATION))
				{
					UserDefinedStatus.Struct.Data.SetTemperature++;
					if(UserDefinedStatus.Struct.Data.SetTemperature > 45)
						UserDefinedStatus.Struct.Data.SetTemperature = 45;
				}
			}
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case DOWN_KEY_TOUCHED:
			if(ScreenStatus.Struct.Data.PowerStatus == SYSTEM_ON)
			{
				if((ScreenStatus.Struct.Data.OperationModeStatus == COOL_OPERATION)||(ScreenStatus.Struct.Data.OperationModeStatus == HEAT_OPERATION))
				{
					UserDefinedStatus.Struct.Data.SetTemperature--;
					if(UserDefinedStatus.Struct.Data.SetTemperature < 10)
						UserDefinedStatus.Struct.Data.SetTemperature = 10;
				}
			}
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case MODE_KEY_TOUCHED:
			if(ScreenStatus.Struct.Data.PowerStatus == SYSTEM_ON)
			{
				UserDefinedStatus.Struct.Data.OperationModeStatus++;
				if(ScreenStatus.Struct.Setting.OperationType == FANCOIL)
				{
					if(UserDefinedStatus.Struct.Data.OperationModeStatus > FAN_OPERATION)
						UserDefinedStatus.Struct.Data.OperationModeStatus = COOL_OPERATION;
				}
				else if(ScreenStatus.Struct.Setting.OperationType == SPLIT)
				{
					if(UserDefinedStatus.Struct.Data.OperationModeStatus > AUTO_OPERATION)
						UserDefinedStatus.Struct.Data.OperationModeStatus = COOL_OPERATION;
				}
				switch(UserDefinedStatus.Struct.Data.OperationModeStatus)
				{
					case COOL_OPERATION:
						UserDefinedStatus.Struct.Data.SetTemperature = 22;
						ScreenStatus.Struct.Data.SetTemperature 	 = IRRELEVANT_VALUE;
						break;

					case HEAT_OPERATION:
						UserDefinedStatus.Struct.Data.SetTemperature = 26;
						ScreenStatus.Struct.Data.SetTemperature 	 = IRRELEVANT_VALUE;
						break;

					case FAN_OPERATION:
						ScreenStatus.Struct.Data.SetTemperature		 = IRRELEVANT_VALUE;
						break;

					case DRY_OPERATION:
						UserDefinedStatus.Struct.Data.FanVelocityOperation = LOW_SPEED;
						break;

					case AUTO_OPERATION:
						UserDefinedStatus.Struct.Data.SetTemperature = 24;
						ScreenStatus.Struct.Data.SetTemperature 	 = IRRELEVANT_VALUE;
						break;
				}
			}
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case FAN_KEY_TOUCHED:
			if(ScreenStatus.Struct.Data.PowerStatus == SYSTEM_ON)
			{
				if(ScreenStatus.Struct.Data.OperationModeStatus != DRY_OPERATION)
				{
					UserDefinedStatus.Struct.Data.FanVelocityOperation++;
					if(UserDefinedStatus.Struct.Data.FanVelocityOperation > AUTO_SPEED)
						UserDefinedStatus.Struct.Data.FanVelocityOperation = LOW_SPEED;
				}
			}
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case POWER_KEY_TOUCHED:
			UserDefinedStatus.Struct.Data.PowerStatus     = !UserDefinedStatus.Struct.Data.PowerStatus;
			TimerI.Flags.TenMinuteFlag = SET;
			if(UserDefinedStatus.Struct.Data.PowerStatus == SYSTEM_ON)
			{
				ScreenStatus.Struct.Data.OperationModeStatus  = IRRELEVANT_VALUE;
				ScreenStatus.Struct.Data.FanVelocityOperation = IRRELEVANT_VALUE;
				ScreenStatus.Struct.Data.SetTemperature		  = IRRELEVANT_VALUE;
				ScreenStatus.Struct.Setting.SwingMode		  = IRRELEVANT_VALUE;
			}
			FunctionalStatus.Display.Initializer		  = EXECUTE_ONCE;
			FunctionalStatus.Touchkeys.TouchKeyCounter 	  = ZERO_SECOND;
			break;

		case SWING_KEY_TOUCHED:
			if(ScreenStatus.Struct.Data.PowerStatus == SYSTEM_ON)
				UserDefinedStatus.Struct.Setting.SwingMode = !UserDefinedStatus.Struct.Setting.SwingMode;
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case TIMER_KEY_TOUCHED:
			if(ScreenStatus.Struct.Data.PowerStatus == SYSTEM_ON)
			{
				if(UserDefinedStatus.Struct.Setting.OffTimerMinute < 30)
					UserDefinedStatus.Struct.Setting.OffTimerMinute = 30;
				else if(UserDefinedStatus.Struct.Setting.OffTimerMinute >= 30)
				{
					UserDefinedStatus.Struct.Setting.OffTimerHour++;
					UserDefinedStatus.Struct.Setting.OffTimerMinute = 0;
				}
				if((UserDefinedStatus.Struct.Setting.OffTimerHour >= 8)&&(UserDefinedStatus.Struct.Setting.OffTimerMinute >= 30))
				{
					UserDefinedStatus.Struct.Setting.OffTimerMinute = 0;
					UserDefinedStatus.Struct.Setting.OffTimerHour	= 0;
				}
			}
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case LIGHT_KEY_TOUCHED:
			HAL_GPIO_TogglePin(LCD_BL_GPIO_Port, LCD_BL_Pin);
			HAL_GPIO_TogglePin(LCD_BL_DIM_GPIO_Port, LCD_BL_DIM_Pin);
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		default:
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;
	}
}
void Touchkeys_Settings_Menu_Handler(void)
{
	switch (FunctionalStatus.Touchkeys.TouchedKey)
	{
		case UP_KEY_TOUCHED:
			UserDefinedStatus.Struct.Setting.BGcolorSelect++;
			if(UserDefinedStatus.Struct.Setting.BGcolorSelect  > 20)
				UserDefinedStatus.Struct.Setting.BGcolorSelect = 1;
			FunctionalStatus.Touchkeys.IdleKeysCounter = 0;
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case DOWN_KEY_TOUCHED:
			UserDefinedStatus.Struct.Setting.BGcolorSelect--;
			if(UserDefinedStatus.Struct.Setting.BGcolorSelect  < 1)
				UserDefinedStatus.Struct.Setting.BGcolorSelect = 20;
			FunctionalStatus.Touchkeys.IdleKeysCounter = 0;
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case MODE_KEY_TOUCHED:
			UserDefinedStatus.Struct.Setting.OperationType	= !UserDefinedStatus.Struct.Setting.OperationType;
			FunctionalStatus.Touchkeys.IdleKeysCounter = 0;
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case FAN_KEY_TOUCHED:
			FunctionalStatus.Touchkeys.IdleKeysCounter = 0;
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case LIGHT_KEY_TOUCHED:
			FunctionalStatus.Touchkeys.IdleKeysCounter = 0;
			HAL_GPIO_TogglePin(LCD_BL_GPIO_Port, LCD_BL_Pin);
			HAL_GPIO_TogglePin(LCD_BL_DIM_GPIO_Port, LCD_BL_DIM_Pin);
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		default:
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;
	}

}
void Touchkeys_Communication_Menu_Handler(void)
{
	switch (FunctionalStatus.Touchkeys.TouchedKey)
	{
		case UP_KEY_TOUCHED:
			UserDefinedStatus.Struct.Setting.NumberOfSlaves++;
			if(UserDefinedStatus.Struct.Setting.NumberOfSlaves > 16)
				UserDefinedStatus.Struct.Setting.NumberOfSlaves = 16;
			FunctionalStatus.Touchkeys.IdleKeysCounter = ZERO_SECOND;
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case DOWN_KEY_TOUCHED:
			UserDefinedStatus.Struct.Setting.NumberOfSlaves--;
			if(UserDefinedStatus.Struct.Setting.NumberOfSlaves < 1)
				UserDefinedStatus.Struct.Setting.NumberOfSlaves = 1;
			FunctionalStatus.Touchkeys.IdleKeysCounter = ZERO_SECOND;
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		case LIGHT_KEY_TOUCHED:
			FunctionalStatus.Touchkeys.IdleKeysCounter = ZERO_SECOND;
			HAL_GPIO_TogglePin(LCD_BL_GPIO_Port, LCD_BL_Pin);
			HAL_GPIO_TogglePin(LCD_BL_DIM_GPIO_Port, LCD_BL_DIM_Pin);
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;

		default:
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
			break;
	}

}
void Held_Down_Keys_Handler(void)
{
	if(FunctionalStatus.Touchkeys.TouchKeysStatus != NO_KEY_TOUCHED)
	{
		if(FunctionalStatus.Touchkeys.TouchKeyCounter > SEVEN_SECONDS)
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
		switch(FunctionalStatus.Touchkeys.TouchKeysStatus)
		{
			case UP_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = UP_KEY_TOUCHED;
				break;

			case DOWN_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = DOWN_KEY_TOUCHED;
				break;

			case MODE_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = MODE_KEY_TOUCHED;
				break;

			case FAN_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = FAN_KEY_TOUCHED;
				break;

			case POWER_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = POWER_KEY_TOUCHED;
				FunctionalStatus.Touchkeys.IdleKeysCounter = ZERO_SECOND;
				break;

			case TIMER_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = TIMER_KEY_TOUCHED;
				break;

			case SWING_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = SWING_KEY_TOUCHED;
				break;

			case LIGHT_KEY_TOUCHED:
				FunctionalStatus.Touchkeys.TouchedKey = LIGHT_KEY_TOUCHED;
				break;
		}
		if(FunctionalStatus.Display.ScreenMenu == USER_MENU)
		{
			if(FunctionalStatus.Touchkeys.TouchKeyCounter >= ONE_HALF_SECOND)/*ThreeSeconds bud*/
			{
				FunctionalStatus.Touchkeys.IdleKeysCounter = ZERO_SECOND;
				if(ScreenStatus.Struct.Data.PowerStatus == SYSTEM_ON)
				{
					switch(FunctionalStatus.Touchkeys.TouchKeysStatus)
					{
						case MODE_FAN_KEYS_TOUCHED:
							FunctionalStatus.Display.ScreenMenu 		= COMMUNICATION_MENU;
							ScreenStatus.Struct.Setting.NumberOfSlaves	= IRRELEVANT_VALUE;
							FunctionalStatus.Display.Execution 			= 1;
							LCD_Partial_Fill(ERROR_Y_POS, ERROR_X_POS, 30, 60, FunctionalStatus.Display.BackgroundColor);
							FunctionalStatus.Touchkeys.TouchedKey 		= NO_KEY_TOUCHED;
							FunctionalStatus.Touchkeys.TouchKeyCounter  = ZERO_SECOND;
							break;

						case SWING_TIMER_KEYS_TOUCHED:
							FunctionalStatus.Display.Initializer 	   	 = EXECUTE_ONCE;
							FunctionalStatus.Display.ScreenMenu  		 = SETTINGS_MENU;
							FunctionalStatus.Touchkeys.TouchedKey        = NO_KEY_TOUCHED;
							FunctionalStatus.Touchkeys.TouchKeyCounter   = ZERO_SECOND;
							break;

						default:
							FunctionalStatus.Touchkeys.TouchedKey        = NO_KEY_TOUCHED;
							FunctionalStatus.Touchkeys.TouchKeyCounter   = ZERO_SECOND;
							break;
					}
				}
			}
		}
	}
}
void Touchkeys_Menu_Handler(void)
{
	switch (FunctionalStatus.Display.ScreenMenu)
	{
		case USER_MENU:
			Touchkeys_User_Menu_Handler();
			break;
		case SETTINGS_MENU:
			Touchkeys_Settings_Menu_Handler();
			break;
		case COMMUNICATION_MENU:
			Touchkeys_Communication_Menu_Handler();
			break;
	}
}
void Touched_Keys_Handler(void)
{
	if(FunctionalStatus.Touchkeys.TouchKeysStatus == NO_KEY_TOUCHED)
	{
//		if(FunctionalStatus.Touchkeys.TouchKeyCounter >= THREE_SECONDS)
//			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;
		if(FunctionalStatus.Touchkeys.TouchKeyCounter >= ONE_HALF_SECOND)
			FunctionalStatus.Touchkeys.TouchKeyCounter = ZERO_SECOND;

		if(FunctionalStatus.Touchkeys.TouchKeyCounter > ZERO_SECOND && FunctionalStatus.Touchkeys.TouchKeyCounter < ONE_HALF_SECOND) //????
		{
			FunctionalStatus.Touchkeys.IdleKeysCounter = 0;
			//Buzzer_Beep(KEY_SOUND);
			Buzzer_Beep(BEEP);
			Touchkeys_Menu_Handler();
		}
	}
}
void Keys_Handler(void)
{
	FunctionalStatus.Touchkeys.TouchKeysStatus = (((GPIOB->IDR)&(0xFF00))>>8); //read PortB and return 8 MSBs
	Touched_Keys_Handler();
	Held_Down_Keys_Handler();
//	} else
//		Touchkeys_System_Power_Off_Handler();

}
