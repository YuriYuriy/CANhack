//----------------------------------------------------------------------------------------------------
// Program for device CANhack
// Copyright (C) 2024 YuriYuri (Yuriy Golovin)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
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

