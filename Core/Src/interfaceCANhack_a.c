//----------------------------------------------------------------------------------------------------
//by YuriYuriy
//----------------------------------------------------------------------------------------------------
#include  "interfaceCANhack_a.h"

bool cursorFlag = 0;
bool showBomberDataFlag = 0;
bool startCANtest = 0;
uint8_t startPointsCur = 0;
uint8_t numPointsCur = 0;
uint8_t stepPointsCur = 0;
uint8_t startY = 0;
uint8_t startX = 0;
uint16_t startIDnum = 0;
uint16_t finishIDnum = 0;
uint16_t bomberTIMEnum = 0;
uint64_t cursorTime = 0;
uint64_t dataCANnum = 0;

void interfaceInit(uint8_t modeIf, uint8_t CANp)
{
	switch (modeIf)
	{
	case menu:
		startPointsCur = 20;
		numPointsCur = 3;
		stepPointsCur = 15;
		startY = 20;
		menuDATA();
		break;
	case modeSpeedCAN:
		startPointsCur = 20;
		numPointsCur = 7;
		stepPointsCur = 15;
		startY = 20;
		speedCANdata();
		break;
	case modeReadCAN:
		startPointsCur = 0;
		numPointsCur = 1;
		stepPointsCur = 0;
		startY = 0;
		readDATA();
		break;
	case modeSetting:
		startPointsCur = 0;
		numPointsCur = 1;
		stepPointsCur = 0;
		startY = 0;
		settingDATA();
		break;
	case modeBomber:
		startPointsCur = 20;
		numPointsCur = 5;
		stepPointsCur = 15;
		startY = 20;
		startX = 0;
		bomberDATA();
		bomberDATAnumber();
		showBomberDataFlag = 0;
		break;
	case modeWritting:
		startPointsCur = 20;
		numPointsCur = 3;
		stepPointsCur = 15;
		startY = 20;
		startX = 0;
		writtingDATA();
		break;
	case modeNumHEXone:
		startPointsCur = 20;
		numPointsCur = 8;
		stepPointsCur = 11;
		startY = 20;
		startX = 138;
		numberHEXone();
		showBomberDataFlag = 1;
		break;
	case modeNumHEXtwo:
		startPointsCur = 20;
		numPointsCur = 8;
		stepPointsCur = 11;
		startY = 20;
		startX = 138;
		numberHEXtwo();
		showBomberDataFlag = 1;
		break;
	case modeNumTime:
		startPointsCur = 20;
		numPointsCur = 4;
		stepPointsCur = 11;
		startY = 20;
		startX = 124;
		numberTime();
		showBomberDataFlag = 1;
		break;
	case modeStartCAN:
		testStartCAN();
		break;
	}
}
void menuDATA(void)
{
	ST7735_FillScreenFast(ST7735_BLACK);
	ST7735_WriteString(66, 0, "Menu", Font_7x10, titleColour, ST7735_BLACK);
	ST7735_WriteString(10, 20, "readCAN", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 35, "writeCAN", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 50, "Setting", Font_7x10, textColour, ST7735_BLACK);
}
void speedCANdata(void)
{
	ST7735_FillScreenFast(ST7735_BLACK);
	ST7735_WriteString(52, 0, "speedCAN", Font_7x10, titleColour, ST7735_BLACK);
	ST7735_WriteString(10, 20, "20 kb/s", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 35, "50 kb/s", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 50, "100 kb/s", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 65, "125 kb/s", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 80, "250 kb/s", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 95, "500 kb/s", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 110, "1000 kb/s", Font_7x10, textColour, ST7735_BLACK);
}
void cursor(uint8_t curX, uint8_t curY)
{
		if (cursorFlag == 0)
		{
			ST7735_WriteString(curX, curY, ">", Font_7x10, cursorColour, ST7735_BLACK);
		}
		else
		{
			ST7735_WriteString(curX, curY, " ", Font_7x10, cursorColour, ST7735_BLACK);
		}
		if ((HAL_GetTick() - cursorTime) >= 400)
		{
			cursorFlag = !cursorFlag;
			cursorTime = HAL_GetTick();
		}
}
void readDATA(void)
{
	ST7735_FillScreenFast(ST7735_BLACK);
	ST7735_WriteString(55, 0, "readCAN", Font_7x10, titleColour, ST7735_BLACK);
}
void settingDATA(void)
{
	ST7735_FillScreenFast(ST7735_BLACK);
	ST7735_WriteString(55, 0, "Setting", Font_7x10, titleColour, ST7735_BLACK);
	ST7735_WriteString(10, 20, "by Yuriy Golovin 2024", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 35, "Russia Tyumen", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 50, "program v: alpha 0.1", Font_7x10, textColour, ST7735_BLACK);
}
void writtingDATA(void)
{
	ST7735_FillScreenFast(ST7735_BLACK);
	ST7735_WriteString(63, 0, "writting", Font_7x10, titleColour, ST7735_BLACK);
	ST7735_WriteString(10, 20, "startCAN:", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 35, "ID:", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 50, "data:", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 65, "ff ff ff ff", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 80, "ff ff ff ff", Font_7x10, textColour, ST7735_BLACK);
}
void bomberDATA(void)
{
	ST7735_FillScreenFast(ST7735_BLACK);
	ST7735_WriteString(49, 0, "bomberCAN", Font_7x10, titleColour, ST7735_BLACK);
	ST7735_WriteString(10, 20, "startCAN", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 35, "ID start:", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 50, "ID finish:", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 65, "time (ms):", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(10, 80, "data:", Font_7x10, textColour, ST7735_BLACK);
	/*------------------------------*/
}
void bomberDATAnumber(void)
{
	char dataText[64] =
	{ 0, };
	/*---------------IDSTART---------------*/

	snprintf(dataText, 23, "%x", startIDnum);
	ST7735_WriteString(80, 35, dataText, Font_7x10, textColour, ST7735_BLACK);
	/*------------------------------*/
	/*---------------IDFINISH---------------*/

	snprintf(dataText, 23, "%x", finishIDnum);
	ST7735_WriteString(87, 50, dataText, Font_7x10, textColour, ST7735_BLACK);
	/*------------------------------*/
	/*---------------TIME---------------*/

	snprintf(dataText, 23, "%d", bomberTIMEnum);
	ST7735_WriteString(87, 65, dataText, Font_7x10, textColour, ST7735_BLACK);
	/*------------------------------*/
	/*---------------DATA---------------*/
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t data = dataCANnum;
		uint8_t HighLine = 18;
		snprintf(dataText, 23, "%x", data);
		if (i < 4)
		{
			ST7735_WriteString(10 + HighLine * i, 95, dataText, Font_7x10, textColour, ST7735_BLACK);
		}
		else
		{
			ST7735_WriteString(10 + HighLine * (i - 4), 110, dataText, Font_7x10, textColour, ST7735_BLACK);
		}
		dataCANnum = dataCANnum >> 8;
	}
	/*------------------------------*/
}
void testStartCAN(void)
{
	/*	char dataText[64] =
	 { 0, };
	 snprintf(dataText, 23, " %d", pCAN);
	 ST7735_WriteString(10, 0, dataText, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	 */
	if (startIDnum > finishIDnum)
	{
		ST7735_FillScreenFast(ST7735_BLACK);
		ST7735_WriteString(0, 0, "Error:", Font_7x10, ST7735_RED, ST7735_BLACK);
		ST7735_WriteString(39, 0, "IDstart>IDfinish", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	}
	/*	else
	 {
	 snprintf(dataText, 23, " %x", startIDnum);
	 ST7735_WriteString(10, 15, dataText, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	 snprintf(dataText, 23, " %x", finishIDnum);
	 ST7735_WriteString(10, 30, dataText, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	 }
	 snprintf(dataText, 23, " %d", bomberTIMEnum);
	 ST7735_WriteString(10, 45, dataText, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	 */
}
void numberHEXone(void)
{
	char dataText[64] =
	{ 0, };
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t HeightLine = 11;
		HeightLine = HeightLine * i;
		snprintf(dataText, 23, " %x", i);
		ST7735_WriteString(138, 20 + HeightLine, dataText, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	}
}
void numberHEXtwo(void)
{
	char dataText[64] =
	{ 0, };
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t HeightLine = 11;
		HeightLine = HeightLine * i;
		snprintf(dataText, 23, " %x", i + 8);
		ST7735_WriteString(138, 20 + HeightLine, dataText, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	}
}
void numberTime(void)
{
	ST7735_WriteString(124, 20, " 10", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(124, 31, " 100", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(124, 42, " 500", Font_7x10, textColour, ST7735_BLACK);
	ST7735_WriteString(124, 53, " 2000", Font_7x10, textColour, ST7735_BLACK);
}
/*-----------------------------*/
uint8_t startPointsCurSet(void)
{
	return startPointsCur;
}
uint8_t numPointsCurSet(void)
{
	return numPointsCur;
}
uint8_t stepPointsCurSet(void)
{
	return stepPointsCur;
}
uint8_t cursorYSet(void)
{
	return startY;
}
uint8_t cursorXSet(void)
{
	return startX;
}
bool showBomberDataFlagSet(void)
{
	return showBomberDataFlag;
}
bool testCANset(bool flagCANstart)
{
	if (startIDnum > finishIDnum)
	{
		flagCANstart = 0;

	}
	return flagCANstart;
}
/*-----------------------------*/
void startIDnumSet(uint16_t IDstart)
{
	startIDnum = IDstart;
}
void finishIDnumSet(uint16_t IDfinish)
{
	finishIDnum = IDfinish;
}
void bomberTIMEnumSet(uint16_t bomberTIME)
{
	bomberTIMEnum = bomberTIME;
}
void dataCANnumSet(uint64_t numCANdata)
{
	dataCANnum = numCANdata;
}


