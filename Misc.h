#pragma once
#define ASSERT_RANGE(theoretic,delta,practical) ASSERT(((theoretic)-(delta))<=(practical)&&(practical)<=((theoretic)+(delta)))
void Rainbow(unsigned char &red,unsigned char &green,unsigned char &blue,double hue,bool loop);
void ColorFromValue(unsigned char &red,unsigned char &green,unsigned char &blue,double value);//0~1
double TemperatureKeVFromK(double k);