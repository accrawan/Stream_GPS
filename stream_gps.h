#ifndef _Stream_GPS_H_
#define _Stream_GPS_H_

#include <Arduino.h>
#include <TinyGPS++.h>

// TinyGPSPlus gps;

typedef struct gps_location_info
{
  float longitude;
  float latitude;
} gps_location_info;

class Stream_GPS
{
public:
  Stream_GPS();
  void init(Stream *serial);
  void updateFrame();
  bool hasNewData();
  void setDefaultLocation(float lon, float lat);
  gps_location_info getDefaultLocation();
  gps_location_info getLocation();

private:
  bool dataReady;
  bool initialized;
  unsigned char lastByte, nextByte;
  char rawBytes[100];
  int bufIndex;
  Stream *serial;
  TinyGPSPlus gps;
  gps_location_info defaultLocation{0, 0};
};

#endif