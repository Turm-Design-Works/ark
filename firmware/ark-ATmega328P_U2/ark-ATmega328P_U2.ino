/*
  SPDX-FileCopyrightText: 2023 Turm Design Works LLC. <info@turmdesignworks.com>
  SPDX-License-Identifier: MIT
*/

int const Enc1A = 12;
int const Enc1B = 11;
int const Enc2A = A1;
int const Enc2B = A0;
int const Enc3A = A3;
int const Enc3B = A2;
int const Enc4A = A5;
int const Enc4B = A4;
int const Enc5A = 10;
int const Enc5B = 9;
int const Enc6A = 8;
int const Enc6B = 7;
int const Enc7A = 6;
int const Enc7B = 5;
int const Enc8A = 3;
int const Enc8B = 2;

byte valEnc1;
byte valEnc2;
byte valEnc3;
byte valEnc4;
byte valEnc5;
byte valEnc6;
byte valEnc7;
byte valEnc8;

byte id1 = 1;
byte id2 = 2;
byte id3 = 3;
byte id4 = 4;
byte id5 = 5;
byte id6 = 6;
byte id7 = 7;
byte id8 = 8;

byte RT = 65;
byte LT = 63;
byte NT = 64;

byte VAL[8] = {64, 64, 64, 64, 64, 64, 64, 64};

void setup() {
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  pinMode(Enc1A,INPUT_PULLUP);
  pinMode(Enc1B,INPUT_PULLUP);
  pinMode(Enc2A,INPUT_PULLUP);
  pinMode(Enc2B,INPUT_PULLUP);
  pinMode(Enc3A,INPUT_PULLUP);
  pinMode(Enc3B,INPUT_PULLUP);
  pinMode(Enc4A,INPUT_PULLUP);
  pinMode(Enc4B,INPUT_PULLUP);
  pinMode(Enc5A,INPUT_PULLUP);
  pinMode(Enc5B,INPUT_PULLUP);
  pinMode(Enc6A,INPUT_PULLUP);
  pinMode(Enc6B,INPUT_PULLUP);
  pinMode(Enc7A,INPUT_PULLUP);
  pinMode(Enc7B,INPUT_PULLUP);
  pinMode(Enc8A,INPUT_PULLUP);
  pinMode(Enc8B,INPUT_PULLUP);

}

void loop() {
  
  valEnc1 = valEnc1 + (digitalRead(Enc1A) << 1) + digitalRead(Enc1B);
  valEnc2 = valEnc2 + (digitalRead(Enc2A) << 1) + digitalRead(Enc2B);
  valEnc3 = valEnc3 + (digitalRead(Enc3A) << 1) + digitalRead(Enc3B);
  valEnc4 = valEnc4 + (digitalRead(Enc4A) << 1) + digitalRead(Enc4B);
  valEnc5 = valEnc5 + (digitalRead(Enc5A) << 1) + digitalRead(Enc5B);
  valEnc6 = valEnc6 + (digitalRead(Enc6A) << 1) + digitalRead(Enc6B);
  valEnc7 = valEnc7 + (digitalRead(Enc7A) << 1) + digitalRead(Enc7B);
  valEnc8 = valEnc8 + (digitalRead(Enc8A) << 1) + digitalRead(Enc8B);

  switch(valEnc1){
    case B00000001:  Serial.write(id1);
                     Serial.write(RT);
                     Serial.write(id1);
                     Serial.write(NT);
                     VAL[0] = RT;
                     break;
    case B00000010:  Serial.write(id1);
                     Serial.write(LT);
                     Serial.write(id1);
                     Serial.write(NT);
                     VAL[0] = LT;
                     break;
    default:         break;
  }
  valEnc1 = (valEnc1<<2) & B00001100;
  
  switch(valEnc2){
    case B00000001:  Serial.write(id2);
                     Serial.write(RT);
                     Serial.write(id2);
                     Serial.write(NT);
                     VAL[1] = RT;
                     break;
    case B00000010:  Serial.write(id2);
                     Serial.write(LT);
                     Serial.write(id2);
                     Serial.write(NT);
                     VAL[1] = LT;
                     break;
    default:         break;
  }
  valEnc2 = (valEnc2<<2) & B00001100;
  
  switch(valEnc3){
    case B00000001:  Serial.write(id3);
                     Serial.write(RT);
                     Serial.write(id3);
                     Serial.write(NT);
                     VAL[2] = RT;
                     break;
    case B00000010:  Serial.write(id3);
                     Serial.write(LT);
                     Serial.write(id3);
                     Serial.write(NT);
                     VAL[2] = LT;
                     break;
    default:         break;
  }
  valEnc3 = (valEnc3<<2) & B00001100;
 
  switch(valEnc4){
    case B00000001:  Serial.write(id4);
                     Serial.write(RT);
                     Serial.write(id4);
                     Serial.write(NT);
                     VAL[3] = RT;
                     break;
    case B00000010:  Serial.write(id4);
                     Serial.write(LT);
                     Serial.write(id4);
                     Serial.write(NT);
                     VAL[3] = LT;
                     break;
    default:         break;
  }
  valEnc4 = (valEnc4<<2) & B00001100;
 
  switch(valEnc5){
    case B00000001:  Serial.write(id5);
                     Serial.write(RT);
                     Serial.write(id5);
                     Serial.write(NT);
                     VAL[4] = RT;
                     break;
    case B00000010:  Serial.write(id5);
                     Serial.write(LT);
                     Serial.write(id5);
                     Serial.write(NT);
                     VAL[4] = LT;
                     break;
    default:         break;
  }
  valEnc5 = (valEnc5<<2) & B00001100;

  switch(valEnc6){
    case B00000001:  Serial.write(id6);
                     Serial.write(RT);
                     Serial.write(id6);
                     Serial.write(NT);
                     VAL[5] = RT;
                     break;
    case B00000010:  Serial.write(id6);
                     Serial.write(LT);
                     Serial.write(id6);
                     Serial.write(NT);
                     VAL[5] = LT;
                     break;
    default:         break;
  }
  valEnc6 = (valEnc6<<2) & B00001100;
    
  switch(valEnc7){
    case B00000001:  Serial.write(id7);
                     Serial.write(RT);
                     Serial.write(id7);
                     Serial.write(NT);
                     VAL[6] = RT;
                     break;
    case B00000010:  Serial.write(id7);
                     Serial.write(LT);
                     Serial.write(id7);
                     Serial.write(NT);
                     VAL[6] = LT;
                     break;
    default:         break;
  }
  valEnc7 = (valEnc7<<2) & B00001100;

  switch(valEnc8){
    case B00000001:  Serial.write(id8);
                     Serial.write(RT);
                     Serial.write(id8);
                     Serial.write(NT);
                     VAL[7] = RT;
                     break;
    case B00000010:  Serial.write(id8);
                     Serial.write(LT);
                     Serial.write(id8);
                     Serial.write(NT);
                     VAL[7] = LT;
                     break;
    default:         break;
  }
  valEnc8 = (valEnc8<<2) & B00001100;

}
