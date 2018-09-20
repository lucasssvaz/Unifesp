#include "Fader.h"

Fader::Fader()
{
}

Fader::init(float initial)
{
  _startTime = millis() -1;
  _startValue = initial -1;

  _stopTime = _startTime;
  _stopValue = initial;
}

void Fader::fadeTo(float value, unsigned long duration)
{
  _startTime = millis();
  _startValue = getFade();

  _stopTime = _startTime + duration;
  _stopValue = value;
}

float Fader::getFade()
{
  unsigned long currentTime = millis();
  float currentValue = lerp(_startTime, _startValue, _stopTime, _stopValue, currentTime);
  currentValue = constrain(currentValue, _startValue, _stopValue);
  return currentValue;
}

// Linear interpolation
float Fader::lerp (float m1, float M1, float m2, float M2, float v1)
{
  float d  = M1 - m1;
  float c  = (M2 - m2) / d;
  float o = ( -(M2 * m1) + (m2 * m1) + m2 * d) / d;
  return v1 * c + o;
}
