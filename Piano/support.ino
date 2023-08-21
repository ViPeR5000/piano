#include "typedef.h"
/*------------------------------------------------------------------------------------------*/



void (*const PlayNote[])(bool /* on or off */, UINT8 /* octave */) = {
  C, Cs, D, Ds, E, F_note, Fs, G, Gs, A, As, B
};

/* Copy dots from dotMatriz to display array 
 * Matriz will be updated by UpdateDisplay function
 *  */
static void UpdateDisplayArray(bool on, UINT8 display, const UINT8 *dotMatriz) {

  UINT8 dotMatrizReverted[8];
  bool shift = false;

  /* adjust some notes because the misalignment between displays and keys */
  if (display == 18 || display == 19 || display == 22 || display == 23 || display == 24 || display == 27 || display == 28 || display == 29 || display == 32 || display == 33 || display == 34 || display == 37) {
    shift = true;
  }

  ReverseDots(dotMatriz, dotMatrizReverted, shift);

  for (UINT8 i = 0; i < 8; i++) {
    if (on) {
      Displays[display][i] |= dotMatrizReverted[i];
    } else {
      Displays[display][i] &= (~dotMatrizReverted[i]);
    }
  }
}

/*The dots in  C_dots... arrays are human readable
 The dots are reverted on the display, so this functions reverses these order
 bit 0 -> bit 7
 bit 7 -> bit 0*/
static void ReverseDots(const UINT8 *dotMatriz, UINT8 *dotMatrizReverted, bool shift) {
  UINT8 x;
  UINT8 m;
  UINT8 n;
  for (UINT8 j = 0; j < 8; j++) {
    m = 0b00000001;
    n = 0b10000000;
    x = 0;
    for (UINT8 i = 0; i < 8; i++) {
      if ((pgm_read_word_near(dotMatriz + j) & m) != 0) {
        x |= n;
      }
      m <<= 1;
      n >>= 1;
    }
    if (shift) {
      dotMatrizReverted[j] = x >> 1;
    } else {
      dotMatrizReverted[j] = x;
    }
  }
}

void U1_Handler(void) {

  while (Serial.available() > 0) {

    receivedData = Serial.read();

    switch (state_ui8) {

      case WAIT_START:
        {
          wait_data_ui16 = 1000U;

          MessageType = receivedData;

          switch (MessageType) {

            default:
              {

                state_ui8 = WAIT_START;

                Serial.write(0);

                break;
              }

            case 0xFF:  //Play Note
              {
                state_ui8 = WAIT_LEN;

                break;
              }

            case 0xFE:  //Clear All Displays
              {
                Clear_All_Rows_All_Displays(0);

                state_ui8 = WAIT_START;

                Serial.write(0);

                break;
              }

            case 0xFD:  //Set Brightness
              {
                state_ui8 = WAIT_LEN;

                break;
              }

            case 0xFC:  //Init Matriz
              {
                InitMatriz(0);

                state_ui8 = WAIT_START;

                Serial.write(0);

                break;
              }

            case 0xFB:  //send excel row number
              {
                state_ui8 = WAIT_LEN;

                break;
              }
          }

          break;  //WAIT_START
        }

      case WAIT_LEN:
        {

          wait_data_ui16 = 1000U;

          MessageLen = receivedData;

          index_ui8 = 0;

          state_ui8 = WAIT_MSG;

          break;  //WAIT_LEN
        }


      case WAIT_MSG:
        {

          wait_data_ui16 = 1000;

          RxData[index_ui8] = receivedData;

          index_ui8++;

          if (index_ui8 >= MessageLen) {

            state_ui8 = WAIT_START;

            switch (MessageType) {

              default:
                {
                  state_ui8 = WAIT_START;

                  Serial.write(0);

                  break;
                }

              case 0xFF:
                {
                  /* RxData[0] = note 0~11
                     * RxData[1] = octave 1~7
                     * RxData[3H][4L] = time (ex: time = 25 -> timeout = 250ms)
                     * index = note + ((octave-1)*12)
                     * note =  0, octave = 1 -> index = 0
                     * note = 11, octave = 7 -> index = 83
                     */

                  if ((RxData[0] <= 11)                       /*Check [0] Note  */
                      && (RxData[1] >= 1) && (RxData[1] <= 7) /*Check [1] octave*/
                  ) {
                    /* Register timeout RxData[0] +((RxData[1] - 1)*12) piano key between 0 and 83                 */
                    time[RxData[0] + ((RxData[1] - 1) * 12)] = (((UINT16)RxData[2]) << 8) + ((UINT16)RxData[3]);

                    /*turn on note. Timer will turn it off besed on time[] array*/
                    PlayNote[RxData[0]](true, RxData[1]); /* calls C, Db...*/
                  }

                  Serial.write(0);

                  break;
                }


              case 0xFD:  //Set Brightness
                {

                  Matriz_Send_Command_All_Displays(0x0A, RxData[0]);  //MATRIZ_INTENSITY_00

                  Serial.write(0);

                  break;
                }

              case 0xFB:  //Play Number
                {

                  /* RxData[0] = number Left (0~9)
                     * RxData[1] = number middle (0~9)
                     * RxData[2] = number right (0~9)
                     * RxData[3] = display
                     * RxData[4] = display
                     * RxData[5] = display
                     */
                  if (RxData[0] == 0xFF || RxData[1] == 0xFF || RxData[2] == 0xFF) {

                    Clear_All_Rows_DisplayArray(RxData[3]);

                    Update_Display(RxData[3]);

                    Clear_All_Rows_DisplayArray(RxData[4]);

                    Update_Display(RxData[4]);

                    Clear_All_Rows_DisplayArray(RxData[5]);

                    Update_Display(RxData[5]);

                  } else {
                    PlayNumber(true, RxData[3], RxData[0]);

                    PlayNumber(true, RxData[4], RxData[1]);

                    PlayNumber(true, RxData[5], RxData[2]);
                  }
                  Serial.write(0);

                  break;
                }
            }
          }
          break;  //WAIT_MSG
        }

      default:
        {
          state_ui8 = WAIT_START;

          Serial.write(0);

          break;
        }

    }  //switch MessageType

  }  //Serial.Available>0

  /* check timeout incomplete message */
  if ((state_ui8 != WAIT_START) && (wait_data_ui16 == 0)) {
    Serial.write(0);
    state_ui8 = WAIT_START;
  }
}
/*U1_Handler*/

void Clear_All_Rows_DisplayArray(UINT8 display) {

  //Clear display array
  for (row = 0; row < 8; row++) {
    Displays[display][row] = 0;
  }
}

void PlayNumber(bool on, UINT8 display, UINT8 number) {

  Clear_All_Rows_DisplayArray(display);

  switch (number) {
    case 0:
      UpdateDisplayArray(on, display, _0_dots);
      break;
    case 1:
      UpdateDisplayArray(on, display, _1_dots);
      break;
    case 2:
      UpdateDisplayArray(on, display, _2_dots);
      break;
    case 3:
      UpdateDisplayArray(on, display, _3_dots);
      break;
    case 4:
      UpdateDisplayArray(on, display, _4_dots);
      break;
    case 5:
      UpdateDisplayArray(on, display, _5_dots);
      break;
    case 6:
      UpdateDisplayArray(on, display, _6_dots);
      break;
    case 7:
      UpdateDisplayArray(on, display, _7_dots);
      break;
    case 8:
      UpdateDisplayArray(on, display, _8_dots);
      break;
    case 9:
      UpdateDisplayArray(on, display, _9_dots);
      break;
  }

  Update_Display(display);
}


static void C(bool on, UINT8 octave) {

  display = 5 * (octave - 1);

  UpdateDisplayArray(on, display, C_Note_dots);

  Update_Display(display);
}


static void Cs(bool on, UINT8 octave) {

  display = 5 * (octave - 1) + 1;

  UpdateDisplayArray(on, display, Cs_Bars_dots);

  Update_Display(display);
}

void D(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 1;

  UpdateDisplayArray(on, display, D_Note_dots);

  Update_Display(display);
}

static void Ds(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 1;

  UpdateDisplayArray(on, display, Ds_Bars_dots);

  Update_Display(display);
}

static void E(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 2;

  UpdateDisplayArray(on, display, E_Note_dots);

  Update_Display(display);
}

static void F_note(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 2;

  UpdateDisplayArray(on, display, F_Note_dots);

  Update_Display(display);
}

static void Fs(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 3;

  UpdateDisplayArray(on, display, Fs_Bars_dots);

  Update_Display(display);
}

static void G(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 3;

  UpdateDisplayArray(on, display, G_Note_dots);

  Update_Display(display);
}

static void Gs(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 3;

  UpdateDisplayArray(on, display, Gs_Bars_dots);

  Update_Display(display);
}

static void A(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 4;

  UpdateDisplayArray(on, display, A_Note_dots);

  Update_Display(display);
}

static void As(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 4;

  UpdateDisplayArray(on, display, As_Bars_dots);

  Update_Display(display);
}

static void B(bool on, UINT8 octave) {

  display = (5 * (octave - 1)) + 5;

  UpdateDisplayArray(on, display, B_Note_dots);

  Update_Display(display);
}


/* Update display with content of Display[] array */
static void Update_Display(UINT8 display) {

  for (row = 0; row <= 7; row++) {
    Matriz_Send_Command_Sync(8 - row, display, Displays[display][row]);
  }
}

/*
 * row 1~8
 * display 0~N_Display -1
 * example 8 displays 
 * display to be updated 5
 * ? ? ? ? ? ? ? Initial shift registers on each display
 * shift 2 nops (8-5-1)
 * 0 0 ? ? ? ? ?
 * shift e
 * e 0 0 ? ? ? ? ?
 * shift 5 nops (display = 5)
 * 0 1 2 3 4 5 6 7
 * 0 0 0 0 0 e 0 0
 * Load
 */
static void Matriz_Send_Command_Sync(UINT8 row, UINT8 display, UINT8 value) {

  UINT16 e;

  if ((display < N_DISPLAYS) && (row >= 1) && (row <= 8)) {

    digitalWrite(SS, LOW);

    e = N_DISPLAYS - display - 1;

    // shift NOPs to the first displays
    while (e > 0) {
      Mastereceive = SPI.transfer(MATRIZ_NO_OP);
      Mastereceive = SPI.transfer(MATRIZ_NO_OP);
      e--;
    }

    //Prepare display
    //send row Value to first display shifting right the previous NOPs
    //Command must go first. value must go last
    //See page 5 ogf MAX7219
    Mastereceive = SPI.transfer(row);
    Mastereceive = SPI.transfer(value);


    //shift e to the display position sending NOP2 to the display on the left
    while (display > 0) {
      Mastereceive = SPI.transfer(MATRIZ_NO_OP);
      Mastereceive = SPI.transfer(MATRIZ_NO_OP);
      display--;
    }

    digitalWrite(SS, HIGH);
  }
}
