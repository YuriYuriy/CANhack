//----------------------------------------------------------------------------------------------------
//by YuriYuriy
//----------------------------------------------------------------------------------------------------
#include "buttonClickFun.h"

#define startIDmode 1
#define finishIDmode 2
#define dataCANmode 3
#define timeClick 300

bool downFlag = 0;
bool upFlag = 0;
bool leftFlag = 0;
bool rightFlag = 0;
bool okFlag = 0;
bool outFlag = 0;
bool readORWriteFlag = 0;
bool startBomberCANflagKey = 0;
bool iniCANflagKey = 0;
uint8_t iNum = 0;
uint8_t OKmode = 0;
uint64_t numberKey = 0;
uint16_t prescalerCAN = 0;
uint16_t startIDkey = 0x0;
uint16_t finishIDkey = 0xffff;
uint16_t bomberTIMEkey = 10;
uint64_t dataCANkey = 0xffffffffffffffff;
uint32_t timeDown = 0;
uint32_t timeUp = 0;
uint32_t timeLeft = 0;
uint32_t timeRight = 0;
uint32_t timeOk = 0;
uint32_t timeOut = 0;


/*---------------Button_DOWN_UP---------------*/
uint8_t buttonClickUpDown(uint8_t startPoints, uint8_t numPoints, uint8_t stepPoints, uint8_t cursorXF, uint8_t cursorYF)
{
	/*---------------Button_DOWN---------------*/
	if ((HAL_GPIO_ReadPin(GPIOB, DOWN_Pin) == 0) && (downFlag == 0) && ((HAL_GetTick() - timeDown) >= timeClick) )
	{
		ST7735_WriteString(cursorXF, cursorYF, " ", Font_7x10, ST7735_WHITE, ST7735_BLACK);
		cursorYF = cursorYF + stepPoints;
		if (cursorYF > (startPoints + (stepPoints * (numPoints - 1))))
		{
			cursorYF = startPoints;
		};
		downFlag = 1;
		timeDown = HAL_GetTick();
	}

	if ((HAL_GPIO_ReadPin(GPIOB, DOWN_Pin) == 1) && (downFlag == 1))
	{
		downFlag = 0;
	}
	/*------------------------------*/
	/*---------------Button_UP---------------*/
	if ((HAL_GPIO_ReadPin(GPIOB, UP_Pin) == 0) && (upFlag == 0) && ((HAL_GetTick() - timeUp) >= timeClick) )
	{

		ST7735_WriteString(cursorXF, cursorYF, " ", Font_7x10, ST7735_WHITE, ST7735_BLACK);
		cursorYF = cursorYF - stepPoints;
		if (cursorYF < startPoints)
		{
			cursorYF = (startPoints + (stepPoints * (numPoints - 1)));
		};
		upFlag = 1;
		timeUp = HAL_GetTick();
	}

	if ((HAL_GPIO_ReadPin(GPIOB, UP_Pin) == 1) && (upFlag == 1))
	{
		upFlag = 0;
	}
	/*------------------------------*/
	return cursorYF;
}

/*---------------Button_LEFT_RIGHT---------------*/
uint8_t buttonClickLeftRight(uint8_t modeIfLEFTRIGHT)
{
	/*---------------Button_LEFT---------------*/
	if ((HAL_GPIO_ReadPin(GPIOB, LEFT_Pin) == 0) && (leftFlag == 0) && ((HAL_GetTick() - timeLeft) >= timeClick) )
	{
		switch (modeIfLEFTRIGHT)
		{
		case modeNumHEXone:
			modeIfLEFTRIGHT = modeNumHEXtwo;
			break;
		case modeNumHEXtwo:
			modeIfLEFTRIGHT = modeNumHEXone;
			break;
		}
		leftFlag = 1;
		timeLeft = HAL_GetTick();
	}
	if ((HAL_GPIO_ReadPin(GPIOB, LEFT_Pin) == 1) && (leftFlag == 1))
	{
		leftFlag = 0;
	}
	/*------------------------------*/
	/*---------------Button_RIGHT---------------*/
	if ((HAL_GPIO_ReadPin(GPIOB, RIGHT_Pin) == 0) && (rightFlag == 0) && ((HAL_GetTick() - timeRight) >= timeClick) )
	{
		switch (modeIfLEFTRIGHT)
		{
		case modeNumHEXone:
			modeIfLEFTRIGHT = modeNumHEXtwo;
			break;
		case modeNumHEXtwo:
			modeIfLEFTRIGHT = modeNumHEXone;
			break;
		}
		rightFlag = 1;
		timeRight = HAL_GetTick();
	}
	if ((HAL_GPIO_ReadPin(GPIOB, RIGHT_Pin) == 1) && (rightFlag == 1))
	{
		rightFlag = 0;
	}

	return modeIfLEFTRIGHT;
	/*------------------------------*/
}

/*---------------Button_OK---------------*/
uint8_t buttonClickOK(uint8_t cursorYOK, uint8_t modeIfOK)
{
	if ((HAL_GPIO_ReadPin(GPIOB, OK_Pin) == 0) && (okFlag == 0) && ((HAL_GetTick() - timeOk) >= timeClick) )
	{
		switch (modeIfOK)
		{
		case menu:
			/*---------------MENU---------------*/
			switch (cursorYOK)
			{
			case modeReadSpeedCANPoint:
				modeIfOK = modeSpeedCAN;
				readORWriteFlag = 1;
				break;
			case modeWriteSpeedCANPoint:
				modeIfOK = modeSpeedCAN;
				readORWriteFlag = 0;
				break;
			case modeSettingPoint:
				modeIfOK = modeSetting;
				break;
			}
			break;
			/*------------------------------*/
			/*---------------SpeedCAN---------------*/
		case modeSpeedCAN:
			switch (cursorYOK)
			{
			case setPrescalerCAN200Point:
				prescalerCAN = setPrescalerCAN200;
				break;
			case setPrescalerCAN80Point:
				prescalerCAN = setPrescalerCAN80;
				break;
			case setPrescalerCAN40Point:
				prescalerCAN = setPrescalerCAN40;
				break;
			case setPrescalerCAN32Point:
				prescalerCAN = setPrescalerCAN32;
				break;
			case setPrescalerCAN16Point:
				prescalerCAN = setPrescalerCAN16;
				break;
			case setPrescalerCAN8Point:
				prescalerCAN = setPrescalerCAN8;
				break;
			case setPrescalerCAN4Point:
				prescalerCAN = setPrescalerCAN4;
				break;
			}

			if (readORWriteFlag == 1)
			{
				modeIfOK = modeReadCAN;
			}
			else
			{
				modeIfOK = modeBomber;
			}
			break;
			/*------------------------------*/
			/*---------------BOMBER---------------*/
		case modeBomber:
			switch (cursorYOK)
			{
			case modeStartCANPoint:
				modeIfOK = modeStartCAN;
				startBomberCANflagKey = 1;
				break;
			case modeStartIdPoint:
				modeIfOK = modeNumHEXone;
				OKmode = startIDmode;
				break;
			case modeFinishIdPoint:
				modeIfOK = modeNumHEXone;
				OKmode = finishIDmode;
				break;
			case modeTimePoint:
				modeIfOK = modeNumTime;
				break;
			case modeDataPoint:
				modeIfOK = modeNumHEXone;
				OKmode = dataCANmode;
				break;
			}
			numberKey = 0;
			break;
			/*------------------------------*/
			/*---------------NUMBER---------------*/
		case modeNumHEXone:
			ST7735_WriteString(80, 35, "    ", Font_7x10, textColour, ST7735_BLACK);
			ST7735_WriteString(87, 50, "    ", Font_7x10, textColour, ST7735_BLACK);
			ST7735_WriteString(10, 95, "            ", Font_7x10, textColour, ST7735_BLACK);
			ST7735_WriteString(10, 110, "            ", Font_7x10, textColour, ST7735_BLACK);
			numberKeyHEXone(cursorYOK);
			break;
		case modeNumHEXtwo:
			ST7735_WriteString(80, 35, "    ", Font_7x10, textColour, ST7735_BLACK);
			ST7735_WriteString(87, 50, "    ", Font_7x10, textColour, ST7735_BLACK);
			ST7735_WriteString(10, 95, "            ", Font_7x10, textColour, ST7735_BLACK);
			ST7735_WriteString(10, 110, "            ", Font_7x10, textColour, ST7735_BLACK);
			numberKeyHEXtwo(cursorYOK);
			break;
		case modeNumTime:
			ST7735_WriteString(87, 65, "    ", Font_7x10, textColour, ST7735_BLACK);
			switch (cursorYOK)
			{
			case 20:
				bomberTIMEkey = 10;
				break;
			case 31:
				bomberTIMEkey = 100;
				break;
			case 42:
				bomberTIMEkey = 500;
				break;
			case 53:
				bomberTIMEkey = 2000;
				break;
			}
			break;
			/*------------------------------*/
			case modeStartCAN:
				modeIfOK = modeStartCANstop;
				ST7735_WriteString(10, 15, "CANstop", Font_7x10, textColour, ST7735_BLACK);
				startBomberCANflagKey = 0;
				iniCANflagKey = 0;
				break;
		}
		okFlag = 1;
		timeOk = HAL_GetTick();
	}

	if ((HAL_GPIO_ReadPin(GPIOB, OK_Pin) == 1) && (okFlag == 1))
	{
		okFlag = 0;
	}
	return modeIfOK;
}

/*---------------Button_OUT---------------*/
uint8_t buttonClickOut(uint8_t modeIfOUT)
{
	if ((HAL_GPIO_ReadPin(GPIOB, OUT_Pin) == 0) && (outFlag == 0) && ((HAL_GetTick() - timeOut) >= timeClick) )
	{
		if (modeIfOUT != menu)
		{
			switch (modeIfOUT)
			{
			case modeSpeedCAN:
				modeIfOUT = menu;
				break;
			case modeReadCAN:
				modeIfOUT = modeSpeedCAN;
				break;
			case modeBomber:
				modeIfOUT = modeSpeedCAN;
				break;
			case modeSetting:
				modeIfOUT = menu;
				break;
			case modeWritting:
				modeIfOUT = modeBomber;
				break;
			case modeNumHEXone:
				modeIfOUT = modeBomber;
				break;
			case modeNumHEXtwo:
				modeIfOUT = modeBomber;
				break;
			case modeStartCANstop:
				modeIfOUT = modeBomber;
				startBomberCANflagKey = 0;
				iniCANflagKey = 0;
				break;
			case modeNumTime:
				modeIfOUT = modeBomber;
				break;
			}
		}
		outFlag = 1;
		timeOut = HAL_GetTick();
	}
	if ((HAL_GPIO_ReadPin(GPIOB, OUT_Pin) == 1) && (outFlag == 1))
	{
		outFlag = 0;
	}
	return modeIfOUT;
}

/*---------------Button_Num---------------*/
void numberKeyHEXone(uint8_t cursorYkeySet)
{
	switch (cursorYkeySet)
	{
	case 20:
		numberKey = numberKey + 0;
		break;
	case 31:
		numberKey = numberKey + 1;
		break;
	case 42:
		numberKey = numberKey + 2;
		break;
	case 53:
		numberKey = numberKey + 3;
		break;
	case 64:
		numberKey = numberKey + 4;
		break;
	case 75:
		numberKey = numberKey + 5;
		break;
	case 86:
		numberKey = numberKey + 6;
		break;
	case 97:
		numberKey = numberKey + 7;
		break;
	}
	switch (OKmode)
	{
	case startIDmode:
		startIDkey = numberKey;
		break;
	case finishIDmode:
		finishIDkey = numberKey;
		break;
	case dataCANmode:
		dataCANkey = numberKey;
		break;
	}
	numberKey = numberKey << 4;
}
void numberKeyHEXtwo(uint8_t cursorYkeySet)
{
	switch (cursorYkeySet)
	{
	case 20:
		numberKey = numberKey + 8;
		break;
	case 31:
		numberKey = numberKey + 9;
		break;
	case 42:
		numberKey = numberKey + 0xa;
		break;
	case 53:
		numberKey = numberKey + 0xb;
		break;
	case 64:
		numberKey = numberKey + 0xc;
		break;
	case 75:
		numberKey = numberKey + 0xd;
		break;
	case 86:
		numberKey = numberKey + 0xe;
		break;
	case 97:
		numberKey = numberKey + 0xf;
		break;
	}
	switch (OKmode)
	{
	case startIDmode:
		startIDkey = numberKey;
		break;
	case finishIDmode:
		finishIDkey = numberKey;
		break;
	case dataCANmode:
		dataCANkey = numberKey;
		break;
	}
	numberKey = numberKey << 4;
}


uint16_t prescalerCANset(void)
{
	return prescalerCAN;
}
uint16_t startIDkeySet(void)
{
	return startIDkey;
}
uint16_t finishIDkeySet(void)
{
	return finishIDkey;
}
uint16_t bomberTIMEkeySet(void)
{
	return bomberTIMEkey;
}
uint64_t dataCANkeySet(void)
{
	return dataCANkey;
}
bool startBomberCANflagSet()
{
	return startBomberCANflagKey;
}
bool iniCANflagKeySet()
{

	return iniCANflagKey;
}
bool iniCANflagSet(bool flagCAN)
{
	iniCANflagKey = flagCAN;
}


