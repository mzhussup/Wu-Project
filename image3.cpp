#include <stdio.h>
#include <iostream>
#include "image3.hpp"
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
	{
		for(int i = 0; i < rows; i++)
		{
			delete[] pixels[i];
		}
		delete[] pixels;
	}
}

int Image::resize( unsigned int width,  unsigned int height, uint8_t fillcolour )
{
	pixels = new uint8_t*[height];
	if(pixels == NULL)
		return 1;
	for(int i = 0; i < height; i++)
	{
		pixels[i] = new uint8_t[width];
	}
	rows = height;
	cols = width;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			pixels[i][j] = fillcolour;
		}
	}
	return 0;
}

int Image::set_pixel( unsigned int x, unsigned int y, uint8_t colour )
{
	if(pixels == NULL)
		return 1;
	if((x >= cols) || (y >= rows))
		return 1;
	pixels[y][x] = colour;
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
	*colourp = pixels[y][x];
	return 0;
}

int Image::save( const char* filename )
{
	if(filename == NULL)
		return 1;
	FILE* f = fopen(filename, "w");
	if(f == NULL)
		return 1;
	if((cols < 0) || (rows < 0))
		return 1;
	int len[2];
	len[0] = cols;
	len[1] = rows;
	if( fwrite(len, sizeof(int), 2, f) != 2)
	{
		return 2;
	}
	/*if( fwrite(pixels, sizeof(uint8_t), rows*cols, f) != rows*cols)
	{
		return 3;
	}*/
	for(int i =0; i < rows; i++)
	{
		if( fwrite(pixels[i], sizeof(uint8_t), cols, f) != cols)
			return 3;	
	}
	fclose(f);
	return 0;
}

int Image::load( const char* filename )
{
	if(filename == NULL)
		return 1;
	FILE* f = fopen(filename, "r");
	if(f == NULL)
		return 1;
	int len[2];
	if( fread(len, sizeof(int), 2, f) != 2)
		return 2;
	cols = len[0];
	rows = len[1];
	if((cols == 0) && (rows == 0))
	{
		pixels == NULL;
		fclose(f);
		return 0;
	}
	//pixels = new uint8_t[cols * rows];
	pixels = new uint8_t*[rows];
	if(pixels == NULL)
		return 1;
	for(int i = 0; i < rows; i++)
	{
		pixels[i] = new uint8_t[cols];
	}
	//if( fread(pixels, sizeof(uint8_t), cols * rows , f) != cols * rows)
		//return 2;
	/*for(int i = 0; i < rows ; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			fscanf(f, "%c", &pixels[i][j]);
		}
	}*/
	for(int i = 0; i < rows; i++)
	{
		//pixels[i] = new uint8_t[width];
		if( fread(pixels[i], sizeof(uint8_t), cols , f) != cols )
			return 2;
	}
	fclose(f);
	return 0;
}
