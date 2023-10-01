/***************************************************************************
* File Name: PwFusion_I2C_Buttons.ino
* Processor/Platform: ATtiny841-MMHR (tested)
* Development Environment: Arduino 2.1.1
*
* Designed for use with with Playing With Fusion IFB-40003 I2C Buttons
* Copyright � 2023 Playing With Fusion, Inc.
* SOFTWARE LICENSE AGREEMENT: This code is released under the MIT License.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
* **************************************************************************
* REVISION HISTORY:
* Author		    Date		    Comments
* N. Johnson    2023Oct1   Original version
*
* Playing With Fusion, Inc. invests time and resources developing open-source
* code. Please support Playing With Fusion and continued open-source
* development by buying products from Playing With Fusion!
*
* **************************************************************************
* ADDITIONAL NOTES:
* This file contains functions to flash an AtTiny841-MMHR included in
* the Playing with Fusion i2c buttons interface board (IFB-40003).
* Funcionality is as described below:
*   - Read values from the buttons
*   - Pack values into a register struct
*   - Send values over the i2c bus when requested
***************************************************************************/

#include <WireS.h>

uint8_t primaryAddress = 0x05;
uint8_t secondaryAddress = 0x06;

#define ADR_SEL 9

int buttonVoltage;

int analogPin = A0;

struct memoryMap {
  uint8_t btn;
  // uint8_t vry;
  // uint8_t sw;
};

volatile memoryMap registerMap = {
  .btn = 0x00,
  // .vry = 0x01,
  // .sw = 0x02,
};

// Create a pointer so the register number refers to data in the registerMap.
uint8_t *registerPointer = (uint8_t *)&registerMap;

volatile byte registerPosition;


void setup() {

  pinMode(ADR_SEL, INPUT);

  startI2C();

  

  //pinMode(analogPin, INPUT);
  //pinMode(addressSelector, INPUT);


}

void startI2C() {
  if (digitalRead(ADR_SEL) == LOW) {
    Wire.begin(primaryAddress);
  } else {
    Wire.begin(secondaryAddress);
  }

  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  //registerMap.btn = analogRead(analogPin);
  // registerMap.btn = (analogRead(analogPin) * 5  +512) / 1024;
  buttonVoltage = map(analogRead(analogPin), 0, 1024, 0, 255);

  if (buttonVoltage > 210) registerMap.btn = 0;
  else if (buttonVoltage > 200) registerMap.btn = 1;
  else if (buttonVoltage > 180) registerMap.btn = 2;
  else if (buttonVoltage > 150) registerMap.btn = 3;
  else if (buttonVoltage > 100) registerMap.btn = 4;
  else registerMap.btn = 5;

}

void requestEvent() {
  Wire.write(registerMap.btn);
  // for (int i = 0; i < 2; i++) {
  //    Wire.write(arr[i]);
  // }
}

void receiveEvent(byte howMany) {
  if (howMany < 1) return;

  // Set the register offset position to what the master requests.
  registerPosition = Wire.read();
  howMany--;
  if (!howMany) return;
}
