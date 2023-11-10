// Copyright (c) 2023 Barnabas Nomo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <Arduino.h>
#include "wiring_private.h"
#include "stream_gps.h"

Stream_GPS atgm = Stream_GPS();
Uart Serial2(&sercom1, 10, 11, SERCOM_RX_PAD_2, UART_TX_PAD_0);

void SERCOM1_Handler() {
  Serial2.IrqHandler();
}
void setup() {
  Serial.begin(115200);
  Serial.println("==================================");
  delay(5000);

  Serial2.begin(9600);
  pinPeripheral(10, PIO_SERCOM);
  pinPeripheral(11, PIO_SERCOM);
  atgm.init(&Serial2);
}
void loop() {
  atgm.updateFrame();
  if (atgm.hasNewData()) {
    Serial.println("Data Ready");
    gps_location_info location = atgm.getLocation();
    Serial.print("longitude:\t");
    Serial.print(location.longitude);
    Serial.print("\tlatitude:\t");
    Serial.println(location.latitude);
  }
  delay(1000);
  // Serial.println();
}