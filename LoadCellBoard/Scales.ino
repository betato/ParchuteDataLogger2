#include "HX711.h"

// HX711 Loadcell Amplifiers
#define VERTICAL_DOUT 7
#define AXIAL_DOUT 8
#define HORIZONTAL_DOUT 9
#define LOADCELL_SCK 10

#define VERTICAL_SCALE -6087.36 // Scaling factor from calibration [1/N]
#define AXIAL_SCALE
#define HORIZONTAL_SCALE -6087.36

HX711 verticalScale;
HX711 axialScale;
HX711 horizontalScale;

void initScales() {
  verticalScale.begin(VERTICAL_DOUT, LOADCELL_SCK);
  verticalScale.set_scale(VERTICAL_SCALE);
  verticalScale.tare();
  
  axialScale.begin(AXIAL_DOUT, LOADCELL_SCK);
  axialScale.set_scale(AXIAL_SCALE);
  axialScale.tare();
  
  horizontalScale.begin(HORIZONTAL_DOUT, LOADCELL_SCK);
  horizontalScale.set_scale(HORIZONTAL_SCALE);
  horizontalScale.tare();
  
  setScalePower(true);
}

float getVertical() {
  float vf = verticalScale.get_units(1);
  Serial.print(vf);
  Serial.print(",");
  return vf;
}

float getAxial() {
  float vf = axialScale.get_units(1);
  Serial.print(vf);
  Serial.print(",");
  return vf;
}

float getHorizontal() {
  float vf = horizontalScale.get_units(1);
  Serial.println(vf);
  return vf;
}

bool scalesReady() {
  return verticalScale.is_ready() && axialScale.is_ready() && horizontalScale.is_ready();
}

void setScalePower(bool on) {
  digitalWrite(LED_BUILTIN, on);
  if (on) {
    verticalScale.power_up();
    axialScale.power_up();
    horizontalScale.power_up();
  } else {
    verticalScale.power_down();
    axialScale.power_down();
    horizontalScale.power_down();
  }
}
