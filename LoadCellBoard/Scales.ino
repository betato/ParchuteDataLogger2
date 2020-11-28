#include "HX711.h"

// HX711 Loadcell Amplifiers
#define VERTICAL_DOUT 7
#define AXIAL_DOUT 8
#define HORIZONTAL_DOUT 9
#define LOADCELL_SCK 10

#define VERTICAL_SCALE 41615.3
#define AXIAL_SCALE 41615.3
#define HORIZONTAL_SCALE 41615.3

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
  
  setScalePower(false);
}

float getVertical() {
  return verticalScale.get_units(1);
}

float getAxial() {
  return axialScale.get_units(1);
}

float getHorizontal() {
  return horizontalScale.get_units(1);
}

bool scalesReady() {
  return verticalScale.is_ready() && axialScale.is_ready() && horizontalScale.is_ready();
}

void setScalePower(bool on) {
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
