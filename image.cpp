#include <stdio.h>
#include <iostream>
#include "image.hpp"
using namespace std;

Image::Image()
{
	cols = 0;
	rows = 0;
	pixels = NULL;
}

Image::~Image()
{
	if(pixels != NULL)
		delete[] pixels;
}

int Image::resize( unsigned int width,  unsigned int height, uint8_t fillcolour )
{
	pixels = new uint8_t[height*width];
	if(pixels == NULL)
		return 1;
	rows = height;
	cols = width;
	for(int i = 0; i < height * width; i++)
	{
		pixels[i] = fillcolour;
	}
	return 0;
}
int Image::set_pixel( unsigned int x, unsigned int y, uint8_t colour )
{
	if(pixels == NULL)
		return 1;
	if((x >= cols) || (y >= rows))
		return 1;
	pixels[y*cols + x] = colour;
	return 0;
}
int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colourp )
{
	if(pixels == NULL)
		return 1;
	if(colourp == NULL)
		return 1;
	if((x >= cols) || (y >= rows))
		return 1;
	*colourp = pixels[y*cols + x];
	return 0;
}
