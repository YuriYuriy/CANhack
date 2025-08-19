//----------------------------------------------------------------------------------------------------
// (C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#ifndef INC_INTERFACECANHACK_A_H_
#define INC_INTERFACECANHACK_A_H_

#include "main.h"

void interfaceInit(uint8_t modeIf, uint8_t CANsp);
void menuDATA(void);
void speedCANdata(void);
void readDATA(void);
void settingDATA(void);
void writtingDATA(void);
void bomberDATA(void);
void numberHEXone(void);
void numberHEXtwo(void);
void bomberDATAnumber(void);
void numberTime(void);
void cursor(uint8_t curX, uint8_t curY);
/*-----------------------------*/
uint8_t startPointsCurSet(void);
uint8_t numPointsCurSet(void);
uint8_t stepPointsCurSet(void);
uint8_t cursorYSet(void);
uint8_t cursorXSet(void);
bool showBomberDataFlagSet(void);
void testStartCAN(void);
bool testCANset(bool flagCANstart);
/*-----------------------------*/
void startIDnumSet(uint16_t IDstart);
void finishIDnumSet(uint16_t IDfinish);
void bomberTIMEnumSet(uint16_t bomberTIME);
void dataCANnumSet(uint64_t numCANdata);

#endif /* INC_INTERFACECANHACK_A_H_ */




