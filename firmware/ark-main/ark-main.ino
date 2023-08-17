/*
  SPDX-FileCopyrightText: 2023 Turm Design Works LLC. <info@turmdesignworks.com>
  SPDX-License-Identifier: MIT

  Seeed SAMD21 board "version 1.8.3" required.
*/

#include "MIDIUSB.h"
#include "SoftwareSerial.h"

SoftwareSerial Third(5, -1);

const int Pin_UP = 0;
const int Pin_DOWN = 1;

const int Pin_MODE = 2;
const int Pin_MLED = 3;

byte pushUP = 1;
byte pushDOWN = 1;
byte pushUPp = 1;
byte pushDOWNp = 1;

byte pushMode = 0;
byte pushModep = 1;

byte mRx[3];

byte SysRx[2];
byte SysEND;

byte SerRx[2];
byte SerTx[2];

byte SubRx[2];

byte MidiCH = 0;

byte CC1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CC2[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CC3[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CC4[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CC5[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CC6[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CC7[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CC8[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC2[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC3[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC4[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC5[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC6[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC7[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte CCC8[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

byte CCx1[8] = {64, 64, 64, 64, 64, 64, 64, 64};
byte CCx2[8] = {64, 64, 64, 64, 64, 64, 64, 64};

byte CID[8] = {1, 2, 3, 4, 5, 6, 7, 8};
byte CIDx[8] = {11, 12, 13, 14, 15, 16, 17, 18};

byte D1 = 64;
byte D2 = 64;
byte D3 = 64;
byte D4 = 64;
byte D5 = 64;
byte D6 = 64;
byte D7 = 64;
byte D8 = 64;

byte Rand1;
byte Rand2;
byte Rand3;
byte Rand4;
byte Rand5;
byte Rand6;
byte Rand7;
byte Rand8;

unsigned long CMS1 = 0;
unsigned long CMS2 = 0;
unsigned long CMS3 = 0;
unsigned long CMS4 = 0;
unsigned long CMS5 = 0;
unsigned long CMS6 = 0;
unsigned long CMS7 = 0;
unsigned long CMS8 = 0;
unsigned long interval = 111;

unsigned long DMS = 0;
unsigned long DMSp = 0;
unsigned long DMSp2 = 0;

byte ICC[8] = {1, 1, 1, 1, 1, 1, 1, 1};
byte DCC[8] = {1, 1, 1, 1, 1, 1, 1, 1};

byte LayerVal = 1;
byte LayerValp = 1;

byte DriveMODE1 = 1;
byte DriveMODE2 = 2;



void setup() {

  pinMode( Pin_UP, INPUT_PULLUP );
  pinMode( Pin_DOWN, INPUT_PULLUP );
  pinMode( Pin_MODE, INPUT_PULLUP );
  pinMode( Pin_MLED, OUTPUT );

  SerialUSB.begin(115200);       //USB Serial.
  Serial1.begin(115200);         //UART Rx.
  Third.begin(9600);         //Software Serial Rx

  while(!Serial1){
    ;
  }

  while(!Third){
    ;
  }

}



void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void SysExStart(byte dids, byte cids) {
  midiEventPacket_t event = {0x04, 0xF0, dids, cids};
  MidiUSB.sendMIDI(event);
}

void SysExEND(byte zero1, byte zero2) {
  midiEventPacket_t event = {0x05, 0xF7, zero1, zero2};
  MidiUSB.sendMIDI(event);
}



void loop() {

//Button Action

  pushUP = digitalRead(Pin_UP);
  delay(1);
  pushDOWN = digitalRead(Pin_DOWN);
  delay(1);
  pushMode = digitalRead(Pin_MODE);
  delay(1);

  if(pushUP != pushUPp){
    if(pushUP == 1){ 
      if(MidiCH < 15) { 
        MidiCH = MidiCH + 1; 
        pushUPp = pushUP;
        Serial1.write(88);
        Serial1.write(MidiCH);
        Serial1.write(64);
        Serial1.write(64);
        delay(1);
      } else if(MidiCH == 15) { 
        MidiCH = 0; 
        pushUPp = pushUP;
        Serial1.write(88);
        Serial1.write(MidiCH);
        Serial1.write(64);
        Serial1.write(64);
        delay(1);
      }
    } else { pushUPp = pushUP; }
  }

  if(pushDOWN != pushDOWNp){
    if(pushDOWN == 1){ 
      if(MidiCH > 0) { 
        MidiCH = MidiCH - 1; 
        pushDOWNp = pushDOWN;
        Serial1.write(88);
        Serial1.write(MidiCH);
        Serial1.write(64);
        Serial1.write(64);
        delay(1);
      } else if(MidiCH == 0) { 
        MidiCH = 15; 
        pushDOWNp = pushDOWN;
        Serial1.write(88);
        Serial1.write(MidiCH);
        Serial1.write(64);
        Serial1.write(64);
        delay(1);
      }
    } else { pushDOWNp = pushDOWN; }
  }

  if(pushMode != pushModep){
    if(pushMode == 1){ 
      if(LayerVal == 1) { 
        LayerVal = 2; 
        delay(1);
        pushModep = pushMode; 
      } else if(LayerVal == 2) { 
        LayerVal = 1; 
        delay(1);
        pushModep = pushMode; 
      }
    } else { pushModep = pushMode; }
  }

  if(LayerVal == 1){
       digitalWrite(Pin_MLED, LOW);
    } 
    else if(LayerVal == 2){
       digitalWrite(Pin_MLED, HIGH);
  }
       

  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {

      if (rx.header == 11){
        mRx[0] = rx.byte1;
        mRx[1] = rx.byte2;
        mRx[2] = rx.byte3;
        delay[1];

        if (DriveMODE1 == 1){

          if (mRx[0] == 176){
                   if (mRx[1] == CID[0]){ CC1[0] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[0] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[0] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[0] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[0] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[0] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[0] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[0] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 177){
                   if (mRx[1] == CID[0]){ CC1[1] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[1] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[1] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[1] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[1] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[1] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[1] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[1] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 178){
                   if (mRx[1] == CID[0]){ CC1[2] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[2] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[2] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[2] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[2] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[2] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[2] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[2] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 179){
                   if (mRx[1] == CID[0]){ CC1[3] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[3] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[3] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[3] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[3] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[3] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[3] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[3] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 180){
                   if (mRx[1] == CID[0]){ CC1[4] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[4] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[4] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[4] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[4] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[4] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[4] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[4] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 181){
                   if (mRx[1] == CID[0]){ CC1[5] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[5] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[5] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[5] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[5] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[5] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[5] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[5] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 182){
                   if (mRx[1] == CID[0]){ CC1[6] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[6] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[6] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[6] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[6] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[6] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[6] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[6] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 183){
                   if (mRx[1] == CID[0]){ CC1[7] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[7] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[7] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[7] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[7] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[7] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[7] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[7] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 184){
                   if (mRx[1] == CID[0]){ CC1[8] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[8] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[8] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[8] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[8] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[8] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[8] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[8] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 185){
                   if (mRx[1] == CID[0]){ CC1[9] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[9] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[9] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[9] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[9] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[9] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[9] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[9] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 186){
                   if (mRx[1] == CID[0]){ CC1[10] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[10] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[10] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[10] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[10] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[10] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[10] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[10] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 187){
                   if (mRx[1] == CID[0]){ CC1[11] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[11] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[11] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[11] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[11] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[11] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[11] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[11] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 188){
                   if (mRx[1] == CID[0]){ CC1[12] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[12] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[12] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[12] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[12] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[12] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[12] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[12] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 189){
                   if (mRx[1] == CID[0]){ CC1[13] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[13] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[13] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[13] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[13] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[13] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[13] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[13] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 190){
                   if (mRx[1] == CID[0]){ CC1[14] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[14] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[14] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[14] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[14] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[14] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[14] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[14] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 191){
                   if (mRx[1] == CID[0]){ CC1[15] = mRx[2]; 
            } else if (mRx[1] == CID[1]){ CC2[15] = mRx[2];
            } else if (mRx[1] == CID[2]){ CC3[15] = mRx[2];
            } else if (mRx[1] == CID[3]){ CC4[15] = mRx[2]; 
            } else if (mRx[1] == CID[4]){ CC5[15] = mRx[2]; 
            } else if (mRx[1] == CID[5]){ CC6[15] = mRx[2]; 
            } else if (mRx[1] == CID[6]){ CC7[15] = mRx[2]; 
            } else if (mRx[1] == CID[7]){ CC8[15] = mRx[2]; 
            } else {}
          }

        }

        if (DriveMODE2 == 1){

          if (mRx[0] == 176){
                   if (mRx[1] == CIDx[0]){ CCC1[0] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[0] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[0] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[0] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[0] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[0] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[0] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[0] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 177){
                   if (mRx[1] == CIDx[0]){ CCC1[1] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[1] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[1] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[1] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[1] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[1] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[1] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[1] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 178){
                   if (mRx[1] == CIDx[0]){ CCC1[2] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[2] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[2] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[2] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[2] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[2] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[2] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[2] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 179){
                   if (mRx[1] == CIDx[0]){ CCC1[3] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[3] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[3] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[3] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[3] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[3] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[3] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[3] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 180){
                   if (mRx[1] == CIDx[0]){ CCC1[4] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[4] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[4] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[4] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[4] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[4] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[4] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[4] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 181){
                   if (mRx[1] == CIDx[0]){ CCC1[5] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[5] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[5] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[5] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[5] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[5] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[5] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[5] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 182){
                   if (mRx[1] == CIDx[0]){ CCC1[6] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[6] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[6] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[6] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[6] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[6] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[6] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[6] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 183){
                   if (mRx[1] == CIDx[0]){ CCC1[7] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[7] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[7] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[7] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[7] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[7] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[7] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[7] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 184){
                   if (mRx[1] == CIDx[0]){ CCC1[8] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[8] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[8] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[8] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[8] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[8] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[8] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[8] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 185){
                   if (mRx[1] == CIDx[0]){ CCC1[9] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[9] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[9] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[9] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[9] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[9] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[9] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[9] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 186){
                   if (mRx[1] == CIDx[0]){ CCC1[10] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[10] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[10] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[10] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[10] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[10] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[10] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[10] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 187){
                   if (mRx[1] == CIDx[0]){ CCC1[11] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[11] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[11] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[11] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[11] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[11] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[11] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[11] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 188){
                   if (mRx[1] == CIDx[0]){ CCC1[12] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[12] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[12] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[12] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[12] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[12] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[12] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[12] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 189){
                   if (mRx[1] == CIDx[0]){ CCC1[13] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[13] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[13] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[13] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[13] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[13] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[13] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[13] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 190){
                   if (mRx[1] == CIDx[0]){ CCC1[14] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[14] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[14] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[14] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[14] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[14] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[14] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[14] = mRx[2]; 
            } else {}
          }
  
          if (mRx[0] == 191){
                   if (mRx[1] == CIDx[0]){ CCC1[15] = mRx[2]; 
            } else if (mRx[1] == CIDx[1]){ CCC2[15] = mRx[2];
            } else if (mRx[1] == CIDx[2]){ CCC3[15] = mRx[2];
            } else if (mRx[1] == CIDx[3]){ CCC4[15] = mRx[2]; 
            } else if (mRx[1] == CIDx[4]){ CCC5[15] = mRx[2]; 
            } else if (mRx[1] == CIDx[5]){ CCC6[15] = mRx[2]; 
            } else if (mRx[1] == CIDx[6]){ CCC7[15] = mRx[2]; 
            } else if (mRx[1] == CIDx[7]){ CCC8[15] = mRx[2]; 
            } else {}
          }

        }

      } else if (rx.header == 4){
        if (rx.byte1 = 240){
          SysRx[0] = rx.byte2;
          SysRx[1] = rx.byte3;
          //SerialUSB.println("rx4");
          //SerialUSB.println(rx.header);
          //SerialUSB.println(rx.byte1);
          //SerialUSB.println(rx.byte2);
          //SerialUSB.println(rx.byte3);

          if (SysRx[0] == 1){ 
            CID[0] = rx.byte3;
            Serial1.write(1);
            Serial1.write(CID[0]);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 2){ 
            CID[1] = rx.byte3;
            Serial1.write(2);
            Serial1.write(CID[1]);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 3){ 
            CID[2] = rx.byte3;
            Serial1.write(3);
            Serial1.write(CID[2]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 4){ 
            CID[3] = rx.byte3;
            Serial1.write(4);
            Serial1.write(CID[3]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 5){ 
            CID[4] = rx.byte3;
            Serial1.write(5);
            Serial1.write(CID[4]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 6){ 
            CID[5] = rx.byte3;
            Serial1.write(6);
            Serial1.write(CID[5]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 7){ 
            CID[6] = rx.byte3;
            Serial1.write(7);
            Serial1.write(CID[6]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 8){ 
            CID[7] = rx.byte3;
            Serial1.write(8);
            Serial1.write(CID[7]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 11){ 
            CIDx[0] = rx.byte3;
            Serial1.write(11);
            Serial1.write(CIDx[0]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 12){ 
            CIDx[1] = rx.byte3;
            Serial1.write(12);
            Serial1.write(CIDx[1]);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 13){ 
            CIDx[2] = rx.byte3;
            Serial1.write(13);
            Serial1.write(CIDx[2]);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 14){ 
            CIDx[3] = rx.byte3;
            Serial1.write(14);
            Serial1.write(CIDx[3]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 15){ 
            CIDx[4] = rx.byte3;
            Serial1.write(15);
            Serial1.write(CIDx[4]);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 16){ 
            CIDx[5] = rx.byte3;
            Serial1.write(16);
            Serial1.write(CIDx[5]);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 17){ 
            CIDx[6] = rx.byte3;
            Serial1.write(17);
            Serial1.write(CIDx[6]);
            Serial1.write(64);
            Serial1.write(64); 
          }
          else if (SysRx[0] == 18){ 
            CIDx[7] = rx.byte3;
            Serial1.write(18);
            Serial1.write(CIDx[7]);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 88){ 
            MidiCH = rx.byte3;
            Serial1.write(88);
            Serial1.write(MidiCH);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 89){
            LayerVal = rx.byte3;
          }
          else if (SysRx[0] == 101){ 
            DriveMODE1 = rx.byte3;
            Serial1.write(101);
            Serial1.write(DriveMODE1);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 102){ 
            DriveMODE2 = rx.byte3;
            Serial1.write(102);
            Serial1.write(DriveMODE2);
            Serial1.write(64);
            Serial1.write(64);
          }
          else if (SysRx[0] == 127){
            for(byte i = 0; i < 16; i++){
              CC1[i] = 0;
              CC2[i] = 0;
              CC3[i] = 0;
              CC4[i] = 0;
              CC5[i] = 0;
              CC6[i] = 0;
              CC7[i] = 0;
              CC8[i] = 0;
              CCC1[i] = 0;
              CCC2[i] = 0;
              CCC3[i] = 0;
              CCC4[i] = 0;
              CCC5[i] = 0;
              CCC6[i] = 0;
              CCC7[i] = 0;
              CCC8[i] = 0;
              MidiCH = 0;              
            }
            Serial1.write(127);
            Serial1.write(127);
            SysExStart(99, 0);
            SysExEND(0, 0);
            MidiUSB.flush();
          }
          else if (SysRx[0] == 0){
            SysExStart(1, CID[0]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(2, CID[1]);
            SysExEND(0, 0); 
            delay(250);
            SysExStart(3, CID[2]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(4, CID[3]);
            SysExEND(0, 0);
            delay(250); 
            SysExStart(5, CID[4]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(6, CID[5]);
            SysExEND(0, 0);
            delay(250); 
            SysExStart(7, CID[6]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(8, CID[7]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(11, CIDx[0]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(12, CIDx[1]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(13, CIDx[2]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(14, CIDx[3]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(15, CIDx[4]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(16, CIDx[5]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(17, CIDx[6]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(18, CIDx[7]);
            SysExEND(0, 0);
            delay(250);
            SysExStart(101, DriveMODE1);
            SysExEND(0, 0);
            delay(250);
            SysExStart(102, DriveMODE2);
            SysExEND(0, 0);
            delay(250);
            MidiUSB.flush();
          }
        
        }

      } else if (rx.header == 5){
        //SerialUSB.println("rx5");
        //SerialUSB.println(rx.header);
        //SerialUSB.println(rx.byte1);
        //SerialUSB.println(rx.byte2);
        //SerialUSB.println(rx.byte3);
        MidiUSB.flush();
        
      }
    }
  } while (rx.header != 0);

  if(Third.available()){
    for(byte i = 0; i < 2; i++){
      SubRx[i] = Third.read();
      //SerialUSB.print(i);
      //SerialUSB.print(":");
      //SerialUSB.println(SubRx[i]);
      delay(1);
    }
  } else {}

  switch(SubRx[0]){
      case 1:   CID[0] = SubRx[1];
                //SerialUSB.println(CID[0]);      
                break;
      case 2:   CID[1] = SubRx[1];
                //SerialUSB.println(CID[1]);
                break;
      case 3:   CID[2] = SubRx[1];
                //SerialUSB.println(CID[2]);
                break;
      case 4:   CID[3] = SubRx[1];
                //SerialUSB.println(CID[3]);
                break;
      case 5:   CID[4] = SubRx[1];
                //SerialUSB.println(CID[4]);
                break;
      case 6:   CID[5] = SubRx[1];
                //SerialUSB.println(CID[5]);
                break;
      case 7:   CID[6] = SubRx[1];
                //SerialUSB.println(CID[6]);
                break;
      case 8:   CID[7] = SubRx[1];
                //SerialUSB.println(CID[7]);
                break;
     case 11:   CIDx[0] = SubRx[1];
                //SerialUSB.println(CIDx[0]);
                break;
     case 12:   CIDx[1] = SubRx[1];
                //SerialUSB.println(CIDx[1]);
                break;
     case 13:   CIDx[2] = SubRx[1];
                //SerialUSB.println(CIDx[2]);
                break;
     case 14:   CIDx[3] = SubRx[1];
                //SerialUSB.println(CIDx[3]);
                break;
     case 15:   CIDx[4] = SubRx[1];
                //SerialUSB.println(CIDx[4]);
                break;
     case 16:   CIDx[5] = SubRx[1];
                //SerialUSB.println(CIDx[5]);
                break;
     case 17:   CIDx[6] = SubRx[1];
                //SerialUSB.println(CIDx[6]);
                break;
     case 18:   CIDx[7] = SubRx[1];
                //SerialUSB.println(CIDx[7]);
                break;
    case 101:   DriveMODE1 = SubRx[1];
                //SerialUSB.println(DriveMODE1);
                break;
    case 102:   DriveMODE2 = SubRx[1];
                //SerialUSB.println(DriveMODE2);
                break;
     default:   break;
  }

  if(Serial1.available() > 0){
    for(byte i = 0; i < 2; i++){
      SerRx[i] = Serial1.read();
      delay(1);
    }
  } else {}

  switch(SerRx[0]){
      case 1:   D1 = SerRx[1];
                break;
      case 2:   D2 = SerRx[1];
                break;
      case 3:   D3 = SerRx[1];
                break;
      case 4:   D4 = SerRx[1];
                break;
      case 5:   D5 = SerRx[1];
                break;
      case 6:   D6 = SerRx[1];
                break;
      case 7:   D7 = SerRx[1];
                break;
      case 8:   D8 = SerRx[1];
                break;
     default:   break;
  }


  if (LayerVal == 1){

    if (DriveMODE1 == 1){

      switch(D1){
        
        case 65:
          if (CC1[MidiCH] < 127){
            if(CMS1 + interval < millis()){
              CMS1 = millis();
              ICC[0] = 1;
              CC1[MidiCH] = constrain(CC1[MidiCH] + ICC[0], 0, 127);
              controlChange(MidiCH, CID[0], CC1[MidiCH]);
              //SerialUSB.println(CC1[MidiCH]);
              MidiUSB.flush();
            } else if(CMS1 + interval > millis()){
              ICC[0] = ICC[0] + 1;
              CC1[MidiCH] = constrain(CC1[MidiCH] + ICC[0], 0, 127);
              controlChange(MidiCH, CID[0], CC1[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC1[MidiCH] > 0){
            if(CMS1 + interval < millis()){
              CMS1 = millis();
              DCC[0] = 1;
              CC1[MidiCH] = constrain(CC1[MidiCH] - DCC[0], 0, 127);
              controlChange(MidiCH, CID[0], CC1[MidiCH]);
              MidiUSB.flush();
            } else if(CMS1 + interval > millis()){
              DCC[0] = DCC[0] + 1;
              CC1[MidiCH] = constrain(CC1[MidiCH] - DCC[0], 0, 127);
              controlChange(MidiCH, CID[0], CC1[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          if (CC2[MidiCH] < 127){
            if(CMS2 + interval < millis()){
              CMS2 = millis();
              ICC[1] = 1;
              CC2[MidiCH] = constrain(CC2[MidiCH] + ICC[1], 0, 127);
              controlChange(MidiCH, CID[1], CC2[MidiCH]);
              MidiUSB.flush();
            } else if(CMS2 + interval > millis()){
              ICC[1] = ICC[1] + 1;
              CC2[MidiCH] = constrain(CC2[MidiCH] + ICC[1], 0, 127);
              controlChange(MidiCH, CID[1], CC2[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC2[MidiCH] > 0){
            if(CMS2 + interval < millis()){
              CMS2 = millis();
              DCC[1] = 1;
              CC2[MidiCH] = constrain(CC2[MidiCH] - DCC[1], 0, 127);
              controlChange(MidiCH, CID[1], CC2[MidiCH]);
              MidiUSB.flush();
            } else if(CMS2 + interval > millis()){
              DCC[1] = DCC[1] + 1;
              CC2[MidiCH] = constrain(CC2[MidiCH] - DCC[1], 0, 127);
              controlChange(MidiCH, CID[1], CC2[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          if (CC3[MidiCH] < 127){
            if(CMS3 + interval < millis()){
              CMS3 = millis();
              ICC[2] = 1;
              CC3[MidiCH] = constrain(CC3[MidiCH] + ICC[2], 0, 127);
              controlChange(MidiCH, CID[2], CC3[MidiCH]);
              MidiUSB.flush();
            } else if(CMS3 + interval > millis()){
              ICC[2] = ICC[2] + 1;
              CC3[MidiCH] = constrain(CC3[MidiCH] + ICC[2], 0, 127);
              controlChange(MidiCH, CID[2], CC3[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC3[MidiCH] > 0){
            if(CMS3 + interval < millis()){
              CMS3 = millis();
              DCC[2] = 1;
              CC3[MidiCH] = constrain(CC3[MidiCH] - DCC[2], 0, 127);
              controlChange(MidiCH, CID[2], CC3[MidiCH]);
              MidiUSB.flush();
            } else if(CMS3 + interval > millis()){
              DCC[2] = DCC[2] + 1;
              CC3[MidiCH] = constrain(CC3[MidiCH] - DCC[2], 0, 127);
              controlChange(MidiCH, CID[2], CC3[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
          
      switch(D4){
        
        case 65:
          if (CC4[MidiCH] < 127){
            if(CMS4 + interval < millis()){
              CMS4 = millis();
              ICC[3] = 1;
              CC4[MidiCH] = constrain(CC4[MidiCH] + ICC[3], 0, 127);
              controlChange(MidiCH, CID[3], CC4[MidiCH]);
              MidiUSB.flush();
            } else if(CMS4 + interval > millis()){
              ICC[3] = ICC[3] + 1;
              CC4[MidiCH] = constrain(CC4[MidiCH] + ICC[3], 0, 127);
              controlChange(MidiCH, CID[3], CC4[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC4[MidiCH] > 0){
            if(CMS4 + interval < millis()){
              CMS4 = millis();
              DCC[3] = 1;
              CC4[MidiCH] = constrain(CC4[MidiCH] - DCC[3], 0, 127);
              controlChange(MidiCH, CID[3], CC4[MidiCH]);
              MidiUSB.flush();
            } else if(CMS4 + interval > millis()){
              DCC[3] = DCC[3] + 1;
              CC4[MidiCH] = constrain(CC4[MidiCH] - DCC[3], 0, 127);
              controlChange(MidiCH, CID[3], CC4[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          if (CC5[MidiCH] < 127){
            if(CMS5 + interval < millis()){
              CMS5 = millis();
              ICC[4] = 1;
              CC5[MidiCH] = constrain(CC5[MidiCH] + ICC[4], 0, 127);
              controlChange(MidiCH, CID[4], CC5[MidiCH]);
              MidiUSB.flush();
            } else if(CMS5 + interval > millis()){
              ICC[4] = ICC[4] + 1;
              CC5[MidiCH] = constrain(CC5[MidiCH] + ICC[4], 0, 127);
              controlChange(MidiCH, CID[4], CC5[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC5[MidiCH] > 0){
            if(CMS5 + interval < millis()){
              CMS5 = millis();
              DCC[4] = 1;
              CC5[MidiCH] = constrain(CC5[MidiCH] - DCC[4], 0, 127);
              controlChange(MidiCH, CID[4], CC5[MidiCH]);
              MidiUSB.flush();
            } else if(CMS5 + interval > millis()){
              DCC[4] = DCC[4] + 1;
              CC5[MidiCH] = constrain(CC5[MidiCH] - DCC[4], 0, 127);
              controlChange(MidiCH, CID[4], CC5[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          if (CC6[MidiCH] < 127){
            if(CMS6 + interval < millis()){
              CMS6 = millis();
              ICC[5] = 1;
              CC6[MidiCH] = constrain(CC6[MidiCH] + ICC[5], 0, 127);
              controlChange(MidiCH, CID[5], CC6[MidiCH]);
              MidiUSB.flush();
            } else if(CMS6 + interval > millis()){
              ICC[5] = ICC[5] + 1;
              CC6[MidiCH] = constrain(CC6[MidiCH] + ICC[5], 0, 127);
              controlChange(MidiCH, CID[5], CC6[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC6[MidiCH] > 0){
            if(CMS6 + interval < millis()){
              CMS6 = millis();
              DCC[5] = 1;
              CC6[MidiCH] = constrain(CC6[MidiCH] - DCC[5], 0, 127);
              controlChange(MidiCH, CID[5], CC6[MidiCH]);
              MidiUSB.flush();
            } else if(CMS6 + interval > millis()){
              DCC[5] = DCC[5] + 1;
              CC6[MidiCH] = constrain(CC6[MidiCH] - DCC[5], 0, 127);
              controlChange(MidiCH, CID[5], CC6[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          if (CC7[MidiCH] < 127){
            if(CMS7 + interval < millis()){
              CMS7 = millis();
              ICC[6] = 1;
              CC7[MidiCH] = constrain(CC7[MidiCH] + ICC[6], 0, 127);
              controlChange(MidiCH, CID[6], CC7[MidiCH]);
              MidiUSB.flush();
            } else if(CMS7 + interval > millis()){
              ICC[6] = ICC[6] + 1;
              CC7[MidiCH] = constrain(CC7[MidiCH] + ICC[6], 0, 127);
              controlChange(MidiCH, CID[6], CC7[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC7[MidiCH] > 0){
            if(CMS7 + interval < millis()){
              CMS7 = millis();
              DCC[6] = 1;
              CC7[MidiCH] = constrain(CC7[MidiCH] - DCC[6], 0, 127);
              controlChange(MidiCH, CID[6], CC7[MidiCH]);
              MidiUSB.flush();
            } else if(CMS7 + interval > millis()){
              DCC[6] = DCC[6] + 1;
              CC7[MidiCH] = constrain(CC7[MidiCH] - DCC[6], 0, 127);
              controlChange(MidiCH, CID[6], CC7[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
          
      switch(D8){
        
        case 65:
          if (CC8[MidiCH] < 127){
            if(CMS8 + interval < millis()){
              CMS8 = millis();
              ICC[7] = 1;
              CC8[MidiCH] = constrain(CC8[MidiCH] + ICC[7], 0, 127);
              controlChange(MidiCH, CID[7], CC8[MidiCH]);
              MidiUSB.flush();
            } else if(CMS8 + interval > millis()){
              ICC[7] = ICC[7] + 1;
              CC8[MidiCH] = constrain(CC8[MidiCH] + ICC[7], 0, 127);
              controlChange(MidiCH, CID[7], CC8[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CC8[MidiCH] > 0){
            if(CMS8 + interval < millis()){
              CMS8 = millis();
              DCC[7] = 1;
              CC8[MidiCH] = constrain(CC8[MidiCH] - DCC[7], 0, 127);
              controlChange(MidiCH, CID[7], CC8[MidiCH]);
              MidiUSB.flush();
            } else if(CMS8 + interval > millis()){
              DCC[7] = DCC[7] + 1;
              CC8[MidiCH] = constrain(CC8[MidiCH] - DCC[7], 0, 127);
              controlChange(MidiCH, CID[7], CC8[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }

    } else if (DriveMODE1 == 2){

        switch(D1){
        
        case 65:
          if(CMS1 + interval < millis()){
            CMS1 = millis();
            CCx1[0] = 65;
            controlChange(MidiCH, CID[0], CCx1[0]);
            MidiUSB.flush();
          } else if(CMS1 + interval > millis()){
            CCx1[0] = CCx1[0] + 1;
            controlChange(MidiCH, CID[0], CCx1[0]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS1 + interval < millis()){
            CMS1 = millis();
            CCx1[0] = 63;
            controlChange(MidiCH, CID[0], CCx1[0]);
            MidiUSB.flush();
          } else if(CMS1 + interval > millis()){
            CCx1[0] = CCx1[0] - 1;
            controlChange(MidiCH, CID[0], CCx1[0]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          if(CMS2 + interval < millis()){
            CMS2 = millis();
            CCx1[1] = 65;
            controlChange(MidiCH, CID[1], CCx1[1]);
            MidiUSB.flush();
          } else if(CMS2 + interval > millis()){
            CCx1[1] = CCx1[1] + 1;
            controlChange(MidiCH, CID[1], CCx1[1]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS2 + interval < millis()){
            CMS2 = millis();
            CCx1[1] = 63;
            controlChange(MidiCH, CID[1], CCx1[1]);
            MidiUSB.flush();
          } else if(CMS2 + interval > millis()){
            CCx1[1] = CCx1[1] - 1;
            controlChange(MidiCH, CID[1], CCx1[1]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          if(CMS3 + interval < millis()){
            CMS3 = millis();
            CCx1[2] = 65;
            controlChange(MidiCH, CID[2], CCx1[2]);
            MidiUSB.flush();
          } else if(CMS3 + interval > millis()){
            CCx1[2] = CCx1[2] + 1;
            controlChange(MidiCH, CID[2], CCx1[2]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS3 + interval < millis()){
            CMS3 = millis();
            CCx1[2] = 63;
            controlChange(MidiCH, CID[2], CCx1[2]);
            MidiUSB.flush();
          } else if(CMS3 + interval > millis()){
            CCx1[2] = CCx1[2] - 1;
            controlChange(MidiCH, CID[2], CCx1[2]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D4){
        
        case 65:
          if(CMS4 + interval < millis()){
            CMS4 = millis();
            CCx1[3] = 65;
            controlChange(MidiCH, CID[3], CCx1[3]);
            MidiUSB.flush();
          } else if(CMS4 + interval > millis()){
            CCx1[3] = CCx1[3] + 1;
            controlChange(MidiCH, CID[3], CCx1[3]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS4 + interval < millis()){
            CMS4 = millis();
            CCx1[3] = 63;
            controlChange(MidiCH, CID[3], CCx1[3]);
            MidiUSB.flush();
          } else if(CMS4 + interval > millis()){
            CCx1[3] = CCx1[3] - 1;
            controlChange(MidiCH, CID[3], CCx1[3]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          if(CMS5 + interval < millis()){
            CMS5 = millis();
            CCx1[4] = 65;
            controlChange(MidiCH, CID[4], CCx1[4]);
            MidiUSB.flush();
          } else if(CMS5 + interval > millis()){
            CCx1[4] = CCx1[4] + 1;
            controlChange(MidiCH, CID[4], CCx1[4]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS5 + interval < millis()){
            CMS5 = millis();
            CCx1[4] = 63;
            controlChange(MidiCH, CID[4], CCx1[4]);
            MidiUSB.flush();
          } else if(CMS5 + interval > millis()){
            CCx1[4] = CCx1[4] - 1;
            controlChange(MidiCH, CID[4], CCx1[4]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          if(CMS6 + interval < millis()){
            CMS6 = millis();
            CCx1[5] = 65;
            controlChange(MidiCH, CID[5], CCx1[5]);
            MidiUSB.flush();
          } else if(CMS6 + interval > millis()){
            CCx1[5] = CCx1[5] + 1;
            controlChange(MidiCH, CID[5], CCx1[5]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS6 + interval < millis()){
            CMS6 = millis();
            CCx1[5] = 63;
            controlChange(MidiCH, CID[5], CCx1[5]);
            MidiUSB.flush();
          } else if(CMS6 + interval > millis()){
            CCx1[5] = CCx1[5] - 1;
            controlChange(MidiCH, CID[5], CCx1[5]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          if(CMS7 + interval < millis()){
            CMS7 = millis();
            CCx1[6] = 65;
            controlChange(MidiCH, CID[6], CCx1[6]);
            MidiUSB.flush();
          } else if(CMS7 + interval > millis()){
            CCx1[6] = CCx1[6] + 1;
            controlChange(MidiCH, CID[6], CCx1[6]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS7 + interval < millis()){
            CMS7 = millis();
            CCx1[6] = 63;
            controlChange(MidiCH, CID[6], CCx1[6]);
            MidiUSB.flush();
          } else if(CMS7 + interval > millis()){
            CCx1[6] = CCx1[6] - 1;
            controlChange(MidiCH, CID[6], CCx1[6]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D8){
        
        case 65:
          if(CMS8 + interval < millis()){
            CMS8 = millis();
            CCx1[7] = 65;
            controlChange(MidiCH, CID[7], CCx1[7]);
            MidiUSB.flush();
          } else if(CMS8 + interval > millis()){
            CCx1[7] = CCx1[7] + 1;
            controlChange(MidiCH, CID[7], CCx1[7]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS8 + interval < millis()){
            CMS8 = millis();
            CCx1[7] = 63;
            controlChange(MidiCH, CID[7], CCx1[7]);
            MidiUSB.flush();
          } else if(CMS8 + interval > millis()){
            CCx1[7] = CCx1[7] - 1;
            controlChange(MidiCH, CID[7], CCx1[7]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
    
    } else if (DriveMODE1 == 3){

        switch(D1){
        
        case 65:
          Rand1 = random(64, 128);
          controlChange(MidiCH, CID[0], Rand1);
          MidiUSB.flush();          
          break;
        case 63:
          Rand1 = random(0, 65);
          controlChange(MidiCH, CID[0], Rand1);
          MidiUSB.flush();          
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          Rand2 = random(64, 128);
          controlChange(MidiCH, CID[1], Rand2);
          MidiUSB.flush();
          break;
        case 63:
          Rand2 = random(0, 65);
          controlChange(MidiCH, CID[1], Rand2);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          Rand3 = random(64, 128);
          controlChange(MidiCH, CID[2], Rand3);
          MidiUSB.flush();
          break;
        case 63:
          Rand3 = random(0, 65);
          controlChange(MidiCH, CID[2], Rand3);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D4){
        
        case 65:
          Rand4 = random(64, 128);
          controlChange(MidiCH, CID[3], Rand4);
          MidiUSB.flush();
          break;
        case 63:
          Rand4 = random(0, 65);
          controlChange(MidiCH, CID[3], Rand4);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          Rand5 = random(64, 128);
          controlChange(MidiCH, CID[4], Rand5);
          MidiUSB.flush();
          break;
        case 63:
          Rand5 = random(0, 65);
          controlChange(MidiCH, CID[4], Rand5);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          Rand6 = random(64, 128);
          controlChange(MidiCH, CID[5], Rand6);
          MidiUSB.flush();
          break;
        case 63:
          Rand6 = random(0, 65);
          controlChange(MidiCH, CID[5], Rand6);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          Rand7 = random(64, 128);
          controlChange(MidiCH, CID[6], Rand7);
          MidiUSB.flush();
          break;
        case 63:
          Rand7 = random(0, 65);
          controlChange(MidiCH, CID[6], Rand7);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D8){
        
        case 65:
          Rand8 = random(64, 128);
          controlChange(MidiCH, CID[7], Rand8);
          MidiUSB.flush();
          break;
        case 63:
          Rand8 = random(0, 65);
          controlChange(MidiCH, CID[7], Rand8);
          MidiUSB.flush();
          break;
        default:
          break;
      }
    
    } else if (DriveMODE1 == 4){

        switch(D1){
        
        case 65:
          controlChange(MidiCH, CID[0], 127);
          MidiUSB.flush();          
          break;
        case 63:
          controlChange(MidiCH, CID[0], 0);
          MidiUSB.flush();          
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          controlChange(MidiCH, CID[1], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CID[1], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          controlChange(MidiCH, CID[2], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CID[2], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D4){
        
        case 65:
          controlChange(MidiCH, CID[3], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CID[3], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          controlChange(MidiCH, CID[4], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CID[4], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          controlChange(MidiCH, CID[5], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CID[5], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          controlChange(MidiCH, CID[6], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CID[6], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D8){
        
        case 65:
          controlChange(MidiCH, CID[7], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CID[7], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
    
    }

  } else if (LayerVal == 2) {

    if (DriveMODE2 == 1){

      switch(D1){
        
        case 65:
          if (CC1[MidiCH] < 127){
            if(CMS1 + interval < millis()){
              CMS1 = millis();
              ICC[0] = 1;
              CC1[MidiCH] = constrain(CCC1[MidiCH] + ICC[0], 0, 127);
              controlChange(MidiCH, CIDx[0], CCC1[MidiCH]);
              MidiUSB.flush();
            } else if(CMS1 + interval > millis()){
              ICC[0] = ICC[0] + 1;
              CCC1[MidiCH] = constrain(CCC1[MidiCH] + ICC[0], 0, 127);
              controlChange(MidiCH, CIDx[0], CCC1[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC1[MidiCH] > 0){
            if(CMS1 + interval < millis()){
              CMS1 = millis();
              DCC[0] = 1;
              CCC1[MidiCH] = constrain(CCC1[MidiCH] - DCC[0], 0, 127);
              controlChange(MidiCH, CIDx[0], CCC1[MidiCH]);
              MidiUSB.flush();
            } else if(CMS1 + interval > millis()){
              DCC[0] = DCC[0] + 1;
              CCC1[MidiCH] = constrain(CCC1[MidiCH] - DCC[0], 0, 127);
              controlChange(MidiCH, CIDx[0], CCC1[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          if (CCC2[MidiCH] < 127){
            if(CMS2 + interval < millis()){
              CMS2 = millis();
              ICC[1] = 1;
              CCC2[MidiCH] = constrain(CCC2[MidiCH] + ICC[1], 0, 127);
              controlChange(MidiCH, CIDx[1], CCC2[MidiCH]);
              MidiUSB.flush();
            } else if(CMS2 + interval > millis()){
              ICC[1] = ICC[1] + 1;
              CCC2[MidiCH] = constrain(CCC2[MidiCH] + ICC[1], 0, 127);
              controlChange(MidiCH, CIDx[1], CCC2[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC2[MidiCH] > 0){
            if(CMS2 + interval < millis()){
              CMS2 = millis();
              DCC[1] = 1;
              CCC2[MidiCH] = constrain(CCC2[MidiCH] - DCC[1], 0, 127);
              controlChange(MidiCH, CIDx[1], CCC2[MidiCH]);
              MidiUSB.flush();
            } else if(CMS2 + interval > millis()){
              DCC[1] = DCC[1] + 1;
              CCC2[MidiCH] = constrain(CCC2[MidiCH] - DCC[1], 0, 127);
              controlChange(MidiCH, CIDx[1], CCC2[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          if (CCC3[MidiCH] < 127){
            if(CMS3 + interval < millis()){
              CMS3 = millis();
              ICC[2] = 1;
              CCC3[MidiCH] = constrain(CCC3[MidiCH] + ICC[2], 0, 127);
              controlChange(MidiCH, CIDx[2], CCC3[MidiCH]);
              MidiUSB.flush();
            } else if(CMS3 + interval > millis()){
              ICC[2] = ICC[2] + 1;
              CCC3[MidiCH] = constrain(CCC3[MidiCH] + ICC[2], 0, 127);
              controlChange(MidiCH, CIDx[2], CCC3[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC3[MidiCH] > 0){
            if(CMS3 + interval < millis()){
              CMS3 = millis();
              DCC[2] = 1;
              CCC3[MidiCH] = constrain(CCC3[MidiCH] - DCC[2], 0, 127);
              controlChange(MidiCH, CIDx[2], CCC3[MidiCH]);
              MidiUSB.flush();
            } else if(CMS3 + interval > millis()){
              DCC[2] = DCC[2] + 1;
              CCC3[MidiCH] = constrain(CCC3[MidiCH] - DCC[2], 0, 127);
              controlChange(MidiCH, CIDx[2], CCC3[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
          
      switch(D4){
        
        case 65:
          if (CCC4[MidiCH] < 127){
            if(CMS4 + interval < millis()){
              CMS4 = millis();
              ICC[3] = 1;
              CCC4[MidiCH] = constrain(CCC4[MidiCH] + ICC[3], 0, 127);
              controlChange(MidiCH, CIDx[3], CCC4[MidiCH]);
              MidiUSB.flush();
            } else if(CMS4 + interval > millis()){
              ICC[3] = ICC[3] + 1;
              CCC4[MidiCH] = constrain(CCC4[MidiCH] + ICC[3], 0, 127);
              controlChange(MidiCH, CIDx[3], CCC4[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC4[MidiCH] > 0){
            if(CMS4 + interval < millis()){
              CMS4 = millis();
              DCC[3] = 1;
              CCC4[MidiCH] = constrain(CCC4[MidiCH] - DCC[3], 0, 127);
              controlChange(MidiCH, CIDx[3], CCC4[MidiCH]);
              MidiUSB.flush();
            } else if(CMS4 + interval > millis()){
              DCC[3] = DCC[3] + 1;
              CCC4[MidiCH] = constrain(CCC4[MidiCH] - DCC[3], 0, 127);
              controlChange(MidiCH, CIDx[3], CCC4[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          if (CCC5[MidiCH] < 127){
            if(CMS5 + interval < millis()){
              CMS5 = millis();
              ICC[4] = 1;
              CCC5[MidiCH] = constrain(CCC5[MidiCH] + ICC[4], 0, 127);
              controlChange(MidiCH, CIDx[4], CCC5[MidiCH]);
              MidiUSB.flush();
            } else if(CMS5 + interval > millis()){
              ICC[4] = ICC[4] + 1;
              CCC5[MidiCH] = constrain(CCC5[MidiCH] + ICC[4], 0, 127);
              controlChange(MidiCH, CIDx[4], CCC5[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC5[MidiCH] > 0){
            if(CMS5 + interval < millis()){
              CMS5 = millis();
              DCC[4] = 1;
              CCC5[MidiCH] = constrain(CCC5[MidiCH] - DCC[4], 0, 127);
              controlChange(MidiCH, CIDx[4], CCC5[MidiCH]);
              MidiUSB.flush();
            } else if(CMS5 + interval > millis()){
              DCC[4] = DCC[4] + 1;
              CCC5[MidiCH] = constrain(CCC5[MidiCH] - DCC[4], 0, 127);
              controlChange(MidiCH, CIDx[4], CCC5[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          if (CCC6[MidiCH] < 127){
            if(CMS6 + interval < millis()){
              CMS6 = millis();
              ICC[5] = 1;
              CCC6[MidiCH] = constrain(CCC6[MidiCH] + ICC[5], 0, 127);
              controlChange(MidiCH, CIDx[5], CCC6[MidiCH]);
              MidiUSB.flush();
            } else if(CMS6 + interval > millis()){
              ICC[5] = ICC[5] + 1;
              CCC6[MidiCH] = constrain(CCC6[MidiCH] + ICC[5], 0, 127);
              controlChange(MidiCH, CIDx[5], CCC6[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC6[MidiCH] > 0){
            if(CMS6 + interval < millis()){
              CMS6 = millis();
              DCC[5] = 1;
              CCC6[MidiCH] = constrain(CCC6[MidiCH] - DCC[5], 0, 127);
              controlChange(MidiCH, CIDx[5], CCC6[MidiCH]);
              MidiUSB.flush();
            } else if(CMS6 + interval > millis()){
              DCC[5] = DCC[5] + 1;
              CCC6[MidiCH] = constrain(CCC6[MidiCH] - DCC[5], 0, 127);
              controlChange(MidiCH, CIDx[5], CCC6[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          if (CCC7[MidiCH] < 127){
            if(CMS7 + interval < millis()){
              CMS7 = millis();
              ICC[6] = 1;
              CCC7[MidiCH] = constrain(CCC7[MidiCH] + ICC[6], 0, 127);
              controlChange(MidiCH, CIDx[6], CCC7[MidiCH]);
              MidiUSB.flush();
            } else if(CMS7 + interval > millis()){
              ICC[6] = ICC[6] + 1;
              CCC7[MidiCH] = constrain(CCC7[MidiCH] + ICC[6], 0, 127);
              controlChange(MidiCH, CIDx[6], CCC7[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC7[MidiCH] > 0){
            if(CMS7 + interval < millis()){
              CMS7 = millis();
              DCC[6] = 1;
              CCC7[MidiCH] = constrain(CCC7[MidiCH] - DCC[6], 0, 127);
              controlChange(MidiCH, CIDx[6], CCC7[MidiCH]);
              MidiUSB.flush();
            } else if(CMS7 + interval > millis()){
              DCC[6] = DCC[6] + 1;
              CCC7[MidiCH] = constrain(CCC7[MidiCH] - DCC[6], 0, 127);
              controlChange(MidiCH, CIDx[6], CCC7[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }
          
      switch(D8){
        
        case 65:
          if (CCC8[MidiCH] < 127){
            if(CMS8 + interval < millis()){
              CMS8 = millis();
              ICC[7] = 1;
              CCC8[MidiCH] = constrain(CCC8[MidiCH] + ICC[7], 0, 127);
              controlChange(MidiCH, CIDx[7], CCC8[MidiCH]);
              MidiUSB.flush();
            } else if(CMS8 + interval > millis()){
              ICC[7] = ICC[7] + 1;
              CCC8[MidiCH] = constrain(CCC8[MidiCH] + ICC[7], 0, 127);
              controlChange(MidiCH, CIDx[7], CCC8[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        case 63:
          if (CCC8[MidiCH] > 0){
            if(CMS8 + interval < millis()){
              CMS8 = millis();
              DCC[7] = 1;
              CCC8[MidiCH] = constrain(CCC8[MidiCH] - DCC[7], 0, 127);
              controlChange(MidiCH, CIDx[7], CCC8[MidiCH]);
              MidiUSB.flush();
            } else if(CMS8 + interval > millis()){
              DCC[7] = DCC[7] + 1;
              CCC8[MidiCH] = constrain(CCC8[MidiCH] - DCC[7], 0, 127);
              controlChange(MidiCH, CIDx[7], CCC8[MidiCH]);
              MidiUSB.flush();
            }
          } else {}
          break;
        default:
          break;
      }

    } else if (DriveMODE2 == 2){

      switch(D1){
        
        case 65:
          if(CMS1 + interval < millis()){
            CMS1 = millis();
            CCx2[0] = 65;
            controlChange(MidiCH, CIDx[0], CCx2[0]);
            MidiUSB.flush();
          } else if(CMS1 + interval > millis()){
            CCx2[0] = CCx2[0] + 1;
            controlChange(MidiCH, CIDx[0], CCx2[0]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS1 + interval < millis()){
            CMS1 = millis();
            CCx2[0] = 63;
            controlChange(MidiCH, CIDx[0], CCx2[0]);
            MidiUSB.flush();
          } else if(CMS1 + interval > millis()){
            CCx2[0] = CCx2[0] - 1;
            controlChange(MidiCH, CIDx[0], CCx2[0]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          if(CMS2 + interval < millis()){
            CMS2 = millis();
            CCx2[1] = 65;
            controlChange(MidiCH, CIDx[1], CCx2[1]);
            MidiUSB.flush();
          } else if(CMS2 + interval > millis()){
            CCx2[1] = CCx2[1] + 1;
            controlChange(MidiCH, CIDx[1], CCx2[1]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS2 + interval < millis()){
            CMS2 = millis();
            CCx2[1] = 63;
            controlChange(MidiCH, CIDx[1], CCx2[1]);
            MidiUSB.flush();
          } else if(CMS2 + interval > millis()){
            CCx2[1] = CCx2[1] - 1;
            controlChange(MidiCH, CIDx[1], CCx2[1]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          if(CMS3 + interval < millis()){
            CMS3 = millis();
            CCx2[2] = 65;
            controlChange(MidiCH, CIDx[2], CCx2[2]);
            MidiUSB.flush();
          } else if(CMS3 + interval > millis()){
            CCx2[2] = CCx2[2] + 1;
            controlChange(MidiCH, CIDx[2], CCx2[2]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS3 + interval < millis()){
            CMS3 = millis();
            CCx2[2] = 63;
            controlChange(MidiCH, CIDx[2], CCx2[2]);
            MidiUSB.flush();
          } else if(CMS3 + interval > millis()){
            CCx2[2] = CCx2[2] - 1;
            controlChange(MidiCH, CIDx[2], CCx2[2]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D4){
        
        case 65:
          if(CMS4 + interval < millis()){
            CMS4 = millis();
            CCx2[3] = 65;
            controlChange(MidiCH, CIDx[3], CCx2[3]);
            MidiUSB.flush();
          } else if(CMS4 + interval > millis()){
            CCx2[3] = CCx2[3] + 1;
            controlChange(MidiCH, CIDx[3], CCx2[3]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS4 + interval < millis()){
            CMS4 = millis();
            CCx2[3] = 63;
            controlChange(MidiCH, CIDx[3], CCx2[3]);
            MidiUSB.flush();
          } else if(CMS4 + interval > millis()){
            CCx2[3] = CCx2[3] - 1;
            controlChange(MidiCH, CIDx[3], CCx2[3]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          if(CMS5 + interval < millis()){
            CMS5 = millis();
            CCx2[4] = 65;
            controlChange(MidiCH, CIDx[4], CCx2[4]);
            MidiUSB.flush();
          } else if(CMS5 + interval > millis()){
            CCx2[4] = CCx2[4] + 1;
            controlChange(MidiCH, CIDx[4], CCx2[4]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS5 + interval < millis()){
            CMS5 = millis();
            CCx2[4] = 63;
            controlChange(MidiCH, CIDx[4], CCx2[4]);
            MidiUSB.flush();
          } else if(CMS5 + interval > millis()){
            CCx2[4] = CCx2[4] - 1;
            controlChange(MidiCH, CIDx[4], CCx2[4]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          if(CMS6 + interval < millis()){
            CMS6 = millis();
            CCx2[5] = 65;
            controlChange(MidiCH, CIDx[5], CCx2[5]);
            MidiUSB.flush();
          } else if(CMS6 + interval > millis()){
            CCx2[5] = CCx2[5] + 1;
            controlChange(MidiCH, CIDx[5], CCx2[5]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS6 + interval < millis()){
            CMS6 = millis();
            CCx2[5] = 63;
            controlChange(MidiCH, CIDx[5], CCx2[5]);
            MidiUSB.flush();
          } else if(CMS6 + interval > millis()){
            CCx2[5] = CCx2[5] - 1;
            controlChange(MidiCH, CIDx[5], CCx2[5]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          if(CMS7 + interval < millis()){
            CMS7 = millis();
            CCx2[6] = 65;
            controlChange(MidiCH, CIDx[6], CCx2[6]);
            MidiUSB.flush();
          } else if(CMS7 + interval > millis()){
            CCx2[6] = CCx2[6] + 1;
            controlChange(MidiCH, CIDx[6], CCx2[6]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS7 + interval < millis()){
            CMS7 = millis();
            CCx2[6] = 63;
            controlChange(MidiCH, CIDx[6], CCx2[6]);
            MidiUSB.flush();
          } else if(CMS7 + interval > millis()){
            CCx2[6] = CCx2[6] - 1;
            controlChange(MidiCH, CIDx[6], CCx2[6]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
  
      switch(D8){
        
        case 65:
          if(CMS8 + interval < millis()){
            CMS8 = millis();
            CCx2[7] = 65;
            controlChange(MidiCH, CIDx[7], CCx2[7]);
            MidiUSB.flush();
          } else if(CMS8 + interval > millis()){
            CCx2[7] = CCx2[7] + 1;
            controlChange(MidiCH, CIDx[7], CCx2[7]);
            MidiUSB.flush();
          }
          break;
        case 63:
          if(CMS8 + interval < millis()){
            CMS8 = millis();
            CCx2[7] = 63;
            controlChange(MidiCH, CIDx[7], CCx2[7]);
            MidiUSB.flush();
          } else if(CMS8 + interval > millis()){
            CCx2[7] = CCx2[7] - 1;
            controlChange(MidiCH, CIDx[7], CCx2[7]);
            MidiUSB.flush();
          }
          break;
        default:
          break;
      }
      
    } else if (DriveMODE2 == 3){

        switch(D1){
        
        case 65:
          Rand1 = random(64, 128);
          controlChange(MidiCH, CIDx[0], Rand1);
          MidiUSB.flush();          
          break;
        case 63:
          Rand1 = random(0, 65);
          controlChange(MidiCH, CIDx[0], Rand1);
          MidiUSB.flush();          
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          Rand2 = random(64, 128);
          controlChange(MidiCH, CIDx[1], Rand2);
          MidiUSB.flush();
          break;
        case 63:
          Rand2 = random(0, 65);
          controlChange(MidiCH, CIDx[1], Rand2);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          Rand3 = random(64, 128);
          controlChange(MidiCH, CIDx[2], Rand3);
          MidiUSB.flush();
          break;
        case 63:
          Rand3 = random(0, 65);
          controlChange(MidiCH, CIDx[2], Rand3);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D4){
        
        case 65:
          Rand4 = random(64, 128);
          controlChange(MidiCH, CIDx[3], Rand4);
          MidiUSB.flush();
          break;
        case 63:
          Rand4 = random(0, 65);
          controlChange(MidiCH, CIDx[3], Rand4);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          Rand5 = random(64, 128);
          controlChange(MidiCH, CIDx[4], Rand5);
          MidiUSB.flush();
          break;
        case 63:
          Rand5 = random(0, 65);
          controlChange(MidiCH, CIDx[4], Rand5);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          Rand6 = random(64, 128);
          controlChange(MidiCH, CIDx[5], Rand6);
          MidiUSB.flush();
          break;
        case 63:
          Rand6 = random(0, 65);
          controlChange(MidiCH, CIDx[5], Rand6);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          Rand7 = random(64, 128);
          controlChange(MidiCH, CIDx[6], Rand7);
          MidiUSB.flush();
          break;
        case 63:
          Rand7 = random(0, 65);
          controlChange(MidiCH, CIDx[6], Rand7);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D8){
        
        case 65:
          Rand8 = random(64, 128);
          controlChange(MidiCH, CIDx[7], Rand8);
          MidiUSB.flush();
          break;
        case 63:
          Rand8 = random(0, 65);
          controlChange(MidiCH, CIDx[7], Rand8);
          MidiUSB.flush();
          break;
        default:
          break;
      }
    
    } else if (DriveMODE1 == 4){

        switch(D1){
        
        case 65:
          controlChange(MidiCH, CIDx[0], 127);
          MidiUSB.flush();          
          break;
        case 63:
          controlChange(MidiCH, CIDx[0], 0);
          MidiUSB.flush();          
          break;
        default:
          break;
      }
  
      switch(D2){
        
        case 65:
          controlChange(MidiCH, CIDx[1], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CIDx[1], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D3){
        
        case 65:
          controlChange(MidiCH, CIDx[2], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CIDx[2], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D4){
        
        case 65:
          controlChange(MidiCH, CIDx[3], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CIDx[3], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D5){
        
        case 65:
          controlChange(MidiCH, CIDx[4], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CIDx[4], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D6){
        
        case 65:
          controlChange(MidiCH, CIDx[5], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CIDx[5], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D7){
        
        case 65:
          controlChange(MidiCH, CIDx[6], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CIDx[6], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
  
      switch(D8){
        
        case 65:
          controlChange(MidiCH, CIDx[7], 127);
          MidiUSB.flush();
          break;
        case 63:
          controlChange(MidiCH, CIDx[7], 0);
          MidiUSB.flush();
          break;
        default:
          break;
      }
    
    }
    
  }
}
