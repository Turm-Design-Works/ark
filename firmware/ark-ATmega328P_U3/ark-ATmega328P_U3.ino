/*
  SPDX-FileCopyrightText: 2023 Turm Design Works LLC. <info@turmdesignworks.com>
  SPDX-License-Identifier: MIT
*/

#include <EEPROM.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(-1, 3); // RX, TX

const int Pin_Reset = 2;

const int Pin_ONE = A1;
const int Pin_TEN = A2;
const int Pin_SER = A3;
const int Pin_RCLK = A4;
const int Pin_SCLK = A5;

byte LD = 10;

byte iTEN = 10;
byte iONE = 1;

byte SerRx[2];

byte D1 = 1;
byte D2 = 2;
byte D3 = 3;
byte D4 = 4;
byte D5 = 5;
byte D6 = 6;
byte D7 = 7;
byte D8 = 8;
byte D11 = 11;
byte D12 = 12;
byte D13 = 13;
byte D14 = 14;
byte D15 = 15;
byte D16 = 16;
byte D17 = 17;
byte D18 = 18;
byte M1 = 1;
byte M2 = 2;

byte D1p = 255;
byte D2p = 255;
byte D3p = 255;
byte D4p = 255;
byte D5p = 255;
byte D6p = 255;
byte D7p = 255;
byte D8p = 255;
byte D11p = 255;
byte D12p = 255;
byte D13p = 255;
byte D14p = 255;
byte D15p = 255;
byte D16p = 255;
byte D17p = 255;
byte D18p = 255;
byte M1p = 255;
byte M2p = 255;

byte Power = 0;

byte patterns[] =
 {
    B00011000, //0       0
    B11011101, //1       1
    B00101001, //2       2
    B10001001, //3       3
    B11001100, //4       4
    B10001010, //5       5
    B00001010, //6       6
    B11011000, //7       7
    B00001000, //8       8
    B10001000, //9       9
    B11111111, //Null    10
 };

byte MidiCH = 0;



void setup() {
  digitalWrite(Pin_Reset, HIGH);

  pinMode( Pin_ONE, OUTPUT );
  pinMode( Pin_TEN, OUTPUT );
  pinMode( Pin_SER, OUTPUT );
  pinMode( Pin_RCLK, OUTPUT );
  pinMode( Pin_SCLK, OUTPUT );

  pinMode( Pin_Reset, OUTPUT);
  
  Serial.begin(115200);
  
  while(!Serial){
    ;
  }

  mySerial.begin(9600);

  D1 = EEPROM.read(0);
  D2 = EEPROM.read(1);
  D3 = EEPROM.read(2);
  D4 = EEPROM.read(3);
  D5 = EEPROM.read(4);
  D6 = EEPROM.read(5);
  D7 = EEPROM.read(6);
  D8 = EEPROM.read(7);
  D11 = EEPROM.read(8);
  D12 = EEPROM.read(9);
  D13 = EEPROM.read(10);
  D14 = EEPROM.read(11);
  D15 = EEPROM.read(12);
  D16 = EEPROM.read(13);
  D17 = EEPROM.read(14);
  D18 = EEPROM.read(15);
  M1 = EEPROM.read(16);
  M2 = EEPROM.read(17);

  delay(500);

  if(D1 = 255){ D1 = 1; } else {}
  if(D2 = 255){ D2 = 2; } else {}
  if(D3 = 255){ D3 = 3; } else {}
  if(D4 = 255){ D4 = 4; } else {}
  if(D5 = 255){ D5 = 5; } else {}
  if(D6 = 255){ D6 = 6; } else {}
  if(D7 = 255){ D7 = 7; } else {}
  if(D8 = 255){ D8 = 8; } else {}
  if(D11 = 255){ D11 = 11; } else {}
  if(D12 = 255){ D12 = 12; } else {}
  if(D13 = 255){ D13 = 13; } else {}
  if(D14 = 255){ D14 = 14; } else {}
  if(D15 = 255){ D15 = 15; } else {}
  if(D16 = 255){ D16 = 16; } else {}
  if(D17 = 255){ D17 = 17; } else {}
  if(D18 = 255){ D18 = 18; } else {}
  if(M1 = 255){ M1 = 1; } else {}
  if(M2 = 255){ M2 = 2; } else {}    

  delay(1500);

}



void loop() {

  if(Power != 1){
  mySerial.write(1);
  mySerial.write(D1);
  mySerial.write(2);
  mySerial.write(D2);
  mySerial.write(3);
  mySerial.write(D3);
  mySerial.write(4);
  mySerial.write(D4);
  mySerial.write(5);
  mySerial.write(D5);
  mySerial.write(6);
  mySerial.write(D6);
  mySerial.write(7);
  mySerial.write(D7);
  mySerial.write(8);
  mySerial.write(D8);
  mySerial.write(11);
  mySerial.write(D11);
  mySerial.write(12);
  mySerial.write(D12);
  mySerial.write(13);
  mySerial.write(D13);
  mySerial.write(14);
  mySerial.write(D14);
  mySerial.write(15);
  mySerial.write(D15);
  mySerial.write(16);
  mySerial.write(D16);
  mySerial.write(17);
  mySerial.write(D17);
  mySerial.write(18);
  mySerial.write(D18);
  mySerial.write(101);
  mySerial.write(M1);
  mySerial.write(102);
  mySerial.write(M2);
  mySerial.write(64);
  mySerial.write(64);
  Power = 1;
  }

  if(Serial.available()){
    for(byte i = 0; i < 2; i++){
      SerRx[i] = Serial.read();
      delay(1);
    }
  } else {}
  
  switch(SerRx[0]){
      case 1:   D1 = SerRx[1];
                EEPROM.update(0,D1);
                break;
      case 2:   D2 = SerRx[1];
                EEPROM.update(1,D2);
                break;
      case 3:   D3 = SerRx[1];
                EEPROM.update(2,D3);
                break;
      case 4:   D4 = SerRx[1];
                EEPROM.update(3,D4);
                break;
      case 5:   D5 = SerRx[1];
                EEPROM.update(4,D5);
                break;
      case 6:   D6 = SerRx[1];
                EEPROM.update(5,D6);
                break;
      case 7:   D7 = SerRx[1];
                EEPROM.update(6,D7);
                break;
      case 8:   D8 = SerRx[1];
                EEPROM.update(7,D8);
                break;
     case 11:   D11 = SerRx[1];
                EEPROM.update(8,D11);
                break;
     case 12:   D12 = SerRx[1];
                EEPROM.update(9,D12);
                break;
     case 13:   D13 = SerRx[1];
                EEPROM.update(10,D13);
                break;
     case 14:   D14 = SerRx[1];
                EEPROM.update(11,D14);
                break;
     case 15:   D15 = SerRx[1];
                EEPROM.update(12,D15);
                break;
     case 16:   D16 = SerRx[1];
                EEPROM.update(13,D16);
                break;
     case 17:   D17 = SerRx[1];
                EEPROM.update(14,D17);
                break;
     case 18:   D18 = SerRx[1];
                EEPROM.update(15,D18);
                break;
     case 88:   MidiCH = SerRx[1];
                break;
    case 101:   M1 = SerRx[1];
                EEPROM.update(16,M1);
                break;
    case 102:   M2 = SerRx[1];
                EEPROM.update(17,M2);
                break;
    case 127:   digitalWrite(Pin_Reset, LOW);
                break;
     default:   break;
  }

  switch(MidiCH){
     case 0:   iTEN = 10; iONE = 1; LD = 10; break;
     case 1:   iTEN = 10; iONE = 2; LD = 10; break;
     case 2:   iTEN = 10; iONE = 3; LD = 10; break;
     case 3:   iTEN = 10; iONE = 4; LD = 10; break;
     case 4:   iTEN = 10; iONE = 5; LD = 10; break;
     case 5:   iTEN = 10; iONE = 6; LD = 10; break;
     case 6:   iTEN = 10; iONE = 7; LD = 10; break;
     case 7:   iTEN = 10; iONE = 8; LD = 10; break;
     case 8:   iTEN = 10; iONE = 9; LD = 10; break;
     case 9:   iTEN = 1;  iONE = 0; LD = 12; break;
     case 10:  iTEN = 1;  iONE = 1; LD = 5;  break;
     case 11:  iTEN = 1;  iONE = 2; LD = 10; break;
     case 12:  iTEN = 1;  iONE = 3; LD = 10; break;
     case 13:  iTEN = 1;  iONE = 4; LD = 10; break;
     case 14:  iTEN = 1;  iONE = 5; LD = 10; break;
     case 15:  iTEN = 1;  iONE = 6; LD = 10; break;
     default:   break;
  }
  
  digitalWrite( Pin_ONE, LOW );
  digitalWrite( Pin_RCLK, LOW );
  shiftOut( Pin_SER, Pin_SCLK, LSBFIRST, patterns[iTEN] );
  digitalWrite( Pin_RCLK, HIGH );
  digitalWrite( Pin_TEN, HIGH );
  delay(5);

  digitalWrite( Pin_TEN, LOW );
  digitalWrite( Pin_RCLK, LOW );
  shiftOut( Pin_SER, Pin_SCLK, LSBFIRST, patterns[iONE] );
  digitalWrite( Pin_RCLK, HIGH );
  digitalWrite( Pin_ONE, HIGH );
  delay(LD);

}
