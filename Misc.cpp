#include "stdafx.h"
#include "Misc.h"

void ColorFromValue(unsigned char &red,unsigned char &green,unsigned char &blue,double value)
{
	double hue;
	hue=(-1.0/6)+5*(1-value)/6;
	if(hue<0)
		hue+=1;
	Rainbow(red,green,blue,hue,true);
}
double TemperatureKeVFromK(double k)
{
	//http://www.baike.com/wiki/%E7%94%B5%E5%AD%90%E4%BC%8F
	//https://en.wikipedia.org/wiki/Electronvolt
	return k/11604.505;
}