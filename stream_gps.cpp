// Copyright (c) 2023 Barnabas Nomo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "stream_gps.h"

Stream_GPS::Stream_GPS()
{
  dataReady = false;
  initialized = false;
}

void Stream_GPS::init(Stream *s)
{
  dataReady = false;
  serial = s;
  initialized = true;
}

void Stream_GPS::updateFrame()
{
  if (!initialized)
  {
    Serial.println("Error: must call Stream_GPS::init()");
    return;
  }
  dataReady = false;
  if (serial->available() > 0)
  {
    // size_t len = serial->readBytes(rawBytes, 20);

    nextByte = serial->read();
    // Serial.println(len);
    if (gps.encode(nextByte))
    {
      dataReady = true;
      // Serial.println("Data ready");
    }
  }
}

bool Stream_GPS::hasNewData()
{
  return dataReady;
}

gps_location_info Stream_GPS::getLocation()
{
  gps_location_info location;
  if (gps.location.isValid())
    location = {gps.location.lng(),
                gps.location.lat()};
  else
    location = getDefaultLocation();

  return location;
}

void Stream_GPS::setDefaultLocation(float lon, float lat)
{
  gps_location_info location = {lon,
                                lat};
  defaultLocation = location;
}
gps_location_info Stream_GPS::getDefaultLocation()
{
  return defaultLocation;
}