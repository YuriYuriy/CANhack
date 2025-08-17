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
//---------------------------------------------------------------------------------------------------

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

