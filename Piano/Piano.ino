#include <SPI.h>
#include <arduino-timer.h>
#include "typedef.h"





auto timer = timer_create_default();





void loop() {

  timer.tick();  // tick the timer

  U1_Handler();

  Notes_Timeout(); /* turn off displays by timeout*/
}

bool aTimer_1ms(void *) {
  if (wait_data_ui16 > (UINT16)0) {

    wait_data_ui16--;
  }

  if (Timeout_Turn_Off_Note > (UINT16)0) {
    --Timeout_Turn_Off_Note;
  }

  return true;  // repeat? true
}


/* clear notes every 10ms*/
void Notes_Timeout(void) {
  UINT8 note;
  UINT8 octave;

  if (Timeout_Turn_Off_Note == (UINT16)0) {

    Timeout_Turn_Off_Note = (UINT16)10;

    for (UINT8 index = 0; index < N_PIANO_KEYS; index++) {

      if (time[index] != 0xFFFF) {

        if (time[index] > (UINT16)0) {

          time[index]--;

          if (time[index] == (UINT16)0) {

            octave = (index / 12) + 1;

            note = index - ((octave - 1) * 12);

            PlayNote[note](false, octave); /* calls C, CS...*/

          }
        }
      }
    }
  }
}


void setup() {

  Serial.begin(115200);

  digitalWrite(SS, HIGH);

  SPI.begin();

  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

  InitMatriz(0);

  /* 1 ms*/
  timer.every(1, aTimer_1ms);
}


void InitMatriz(byte initialValue) {
  Matriz_Send_Command_All_Displays(0x0C, 0x01);  //MATRIZ_NORMAL_OPERATION
  Matriz_Send_Command_All_Displays(0x09, 0x00);  //MATRIZ_NO_DECODE
  Matriz_Send_Command_All_Displays(0x0A, 0x00);  //MATRIZ_INTENSITY_00
  Matriz_Send_Command_All_Displays(0x0B, 0x07);  //MATRIZ_SCAN_ALL
  Clear_All_Rows_All_Displays(initialValue);
}


//Update  the array that is used to write on the display with No-Op command (See datasheet table 2)  

void Clear_All_Rows_All_Displays(UINT8 Value) {
  //Clear display array
  for (display = 0; display < N_DISPLAYS; display++) {
    for (row = 0; row < 8; row++) {
      Displays[display][row] = 0;
    }
  }

  //Clear matriz. row is the command
  for (row = 0x01; row <= 0x08; row += 0x01) {
    Matriz_Send_Command_All_Displays(row, Value);
  }
}


void Matriz_Send_Command_All_Displays(UINT8 Command, UINT8 Value) {

  digitalWrite(SS, LOW);

  for (display = 0; display < N_DISPLAYS; display++) {

    Mastereceive = SPI.transfer(Command);

    Mastereceive = SPI.transfer(Value);
  }
  digitalWrite(SS, HIGH);

  delay(5);
}
