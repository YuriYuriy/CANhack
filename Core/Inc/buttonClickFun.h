//----------------------------------------------------------------------------------------------------
//by YuriYuriy
//----------------------------------------------------------------------------------------------------
#ifndef INC_BUTTONCLICKFUN_H_
#define INC_BUTTONCLICKFUN_H_

#include "main.h"

uint8_t buttonClickUpDown(uint8_t startPoints, uint8_t numPoints, uint8_t stepPoints, uint8_t cursorXF, uint8_t cursorYF);
uint8_t buttonClickOK(uint8_t cursorYOK, uint8_t modeIfOK);
uint8_t buttonClickOut(uint8_t modeIfOUT);
uint8_t buttonClickLeftRight(uint8_t modeIfLEFTRIGHT);
void numberKeyHEXone(uint8_t cursorYkeySet);
void numberKeyHEXtwo(uint8_t cursorYkeySet);
/*-----------------------------*/
uint16_t prescalerCANset(void);
uint16_t startIDkeySet(void);
uint16_t finishIDkeySet(void);
uint16_t bomberTIMEkeySet(void);
uint64_t dataCANkeySet(void);
bool startBomberCANflagSet();
bool iniCANflagKeySet();
/*-----------------------------*/
bool iniCANflagSet(bool flagCAN);
#endif /* INC_BUTTONCLICKFUN_H_ */


