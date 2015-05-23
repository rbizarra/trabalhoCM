#ifndef _AUXILIAR
#define _AUXILIAR

#include <stdio.h>
#include "ofxUI.h"
#include <math.h>

class Auxiliar
{
private:
	unsigned char * pixels;
	int width; 
	int num_pixels; 
public:
	Auxiliar();	
	void setPixels(unsigned char * p);
	void setWidth(int width);
	void setNrPixels(int nr_pixels);
	float calcColor(float green, float red, float blue);
	double calculateContrast(int i); 
};

#endif