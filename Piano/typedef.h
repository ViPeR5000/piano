#ifndef TYPEDEF_H
#define TYPEDEF_H

#define MATRIZ_NO_OP 0x00u

#define WAIT_START 0
#define WAIT_LEN 1
#define WAIT_MSG 2

#define N_DISPLAYS 36
#define N_PIANO_KEYS 84
#define ________ 0b00000000
#define _______O 0b00000001
#define _____O_O 0b00000101
#define _____O__ 0b00000100
#define _____OOO 0b00000111
#define ____O___ 0b00001000
#define ____OOO_ 0b00001110
#define ___O____ 0b00010000
#define _OOO____ 0b01110000
#define OO______ 0b11000000
#define OOO_____ 0b11100000
#define ____OO__ 0b00001100
#define ____O_O_ 0b00001010
#define ______OO 0b00000011
#define ______O_ 0b00000010
#define __O_____ 0b00100000
#define _O______ 0b01000000
#define O_______ 0b10000000
#define O_O_____ 0b10100000
#define __O_O___ 0b00101000
#define __OOO___ 0b00111000
#define _O_O____ 0b01010000
#define _OO_____ 0b01100000
#define _OOOOOO_ 0b01111110
#define _O____O_ 0b01000010
#define ___OO___ 0b00011000
#define __OOOO__ 0b00111100
#define __O__O__ 0b00100100
#define OOOOOOOO 0b11111111
#define ___OOO__ 0b00011100
#define __OO____ 0b00110000
#define ___O_O__ 0b00010100
#define _____OO_ 0b00000110



typedef unsigned int UINT16;
typedef signed int SINT16;
typedef unsigned char UINT8;

typedef signed long SINT32;
typedef unsigned long UINT32;
typedef signed long long SINT64;
typedef unsigned long long UINT64;

UINT8 receivedData = 0;  // for incoming serial data
UINT8 MessageLen;
UINT8  Mastereceive;
UINT8 display;
UINT8 row;

volatile UINT16 Timeout_Turn_Off_Note;
extern void (*const PlayNote[])(bool /* on or off */, UINT8 /* octave */);

/* The pattern for each display when only note   are shown */
const UINT8 C_Note_dots[] PROGMEM = {
  _____OO_,
  ____O___,
  ____O___,
  ____O___,
  ____O___,
  ____O___,
  ____O___,
  _____OO_,

};

const UINT8 D_Note_dots[] PROGMEM = {
  __OO____,
  __O_O___,
  __O_O___,
  __O_O___,
  __O_O___,
  __O_O___,
  __O_O___,
  __OO____,

};



const UINT8 E_Note_dots[] PROGMEM = {
  _OOO____,
  _O______,
  _O______,
  _OOO____,
  _O______,
  _O______,
  _O______,
  _OOO____,

};
const UINT8 F_Note_dots[] PROGMEM = {
  _____OOO,
  _____O__,
  _____O__,
  _____OOO,
  _____O__,
  _____O__,
  _____O__,
  _____O__,

};

const UINT8 G_Note_dots[] PROGMEM = {
  ___OOO__,
  ___O____,
  ___O____,
  ___O____,
  ___OOO__,
  ___O_O__,
  ___O_O__,
  ___OOO__,

};


const UINT8 A_Note_dots[] PROGMEM = {
  _OOO____,
  _O_O____,
  _O_O____,
  _OOO____,
  _O_O____,
  _O_O____,
  _O_O____,
  _O_O____,

};


const UINT8 B_Note_dots[] PROGMEM = {
  OO______,
  O_O_____,
  O_O_____,
  OO______,
  O_O_____,
  O_O_____,
  O_O_____,
  OO______,

};

/* The pattern for each display when only sharp notes  are shown */
const UINT8 Cs_Bars_dots[] PROGMEM = {
  ________,
  ________,
  ________,
  ________,
  O_______,
  O_______,
  O_______,
  O_______,
};

const UINT8 Ds_Bars_dots[] PROGMEM = {
  ________,
  ________,
  ________,
  ________,
  _______O,
  _______O,
  _______O,
  _______O,
};

const UINT8 Fs_Bars_dots[] PROGMEM = {
  ________,
  ________,
  ________,
  ________,
  _O______,
  _O______,
  _O______,
  _O______,
};



const UINT8 Gs_Bars_dots[] PROGMEM = {
  ________,
  ________,
  ________,
  ________,
  _______O,
  _______O,
  _______O,
  _______O,
};


const UINT8 As_Bars_dots[] PROGMEM = {
  ________,
  ________,
  ________,
  ________,
  ______O_,
  ______O_,
  ______O_,
  ______O_,
};

/* Numbers */
const UINT8 _0_dots[] PROGMEM = {
  ________,
  __OOOO__,
  __O__O__,
  __O__O__,
  __O__O__,
  __O__O__,
  __OOOO__,
  ________,
};
const UINT8 _1_dots[] PROGMEM = {
  ________,
  ____O___,
  ___OO___,
  __O_O___,
  ____O___,
  ____O___,
  ____O___,
  ________,
}

;
const UINT8 _2_dots[] PROGMEM = {
  ________,
  __OOOO__,
  _____O__,
  __OOOO__,
  __O_____,
  __O_____,
  __OOOO__,
  ________,
}

;
const UINT8 _3_dots[] PROGMEM = {
  ________,
  __OOOO__,
  _____O__,
  __OOOO__,
  _____O__,
  _____O__,
  __OOOO__,
  ________,
};

const UINT8 _4_dots[] PROGMEM = {
  ________,
  __O__O__,
  __O__O__,
  __OOOO__,
  _____O__,
  _____O__,
  _____O__,
  ________,
};

const UINT8 _5_dots[] PROGMEM = {
  ________,
  __OOOO__,
  __O_____,
  __OOOO__,
  _____O__,
  _____O__,
  __OOOO__,
  ________,
};

const UINT8 _6_dots[] PROGMEM = {
  ________,
  __OOOO__,
  __O_____,
  __OOOO__,
  __O__O__,
  __O__O__,
  __OOOO__,
  ________,

};
const UINT8 _7_dots[] PROGMEM = {
  ________,
  __OOOO__,
  _____O__,
  _____O__,
  _____O__,
  _____O__,
  _____O__,
  ________,

};
const UINT8 _8_dots[] PROGMEM = {
  ________,
  __OOOO__,
  __O__O__,
  __OOOO__,
  __O__O__,
  __O__O__,
  __OOOO__,
  ________,

};
const UINT8 _9_dots[] PROGMEM = {
  ________,
  __OOOO__,
  __O__O__,
  __OOOO__,
  _____O__,
  _____O__,
  _____O__,
  ________,
};

const UINT8 _off_dots[] PROGMEM = {
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
};


UINT8 index_ui8 = 0;

UINT8 notes[2 * N_DISPLAYS];

UINT16 time[N_PIANO_KEYS];

UINT8 RxData[100];

UINT16 wait_data_ui16;

byte MessageType;

UINT8 state_ui8 = WAIT_START;
/* Array to keep how the dots on each displays will be shown*/
UINT8 Displays[N_DISPLAYS][8] = {
  { /* D0 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D1 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D2 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D3 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D4 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D5 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D6*/
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D7 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D8 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D9 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D10 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D11 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D12 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D13 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D14*/
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D15 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D16 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D17 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D18 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D19 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D20 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D21 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D22*/
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D23 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D24 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D25 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D26 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D27 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D28 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D29 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D30*/
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D31 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D32 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D33 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D34 */
    0, 0, 0, 0, 0, 0, 0, 0 },
  { /* D35 */
    0, 0, 0, 0, 0, 0, 0, 0 }
};
#endif