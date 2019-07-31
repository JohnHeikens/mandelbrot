#pragma once
#include <windows.h>
#include <iostream>
#include <cmath>
#include "include.h"
//defines

//vars

//structs

//functions
constexpr int max_iteration = 1000;
//https://en.wikipedia.org/wiki/Mandelbrot_set
extern color palette[max_iteration];
inline color GetColor(const fp& x0, const fp& y0)
{
	
	fp x = 0.0;
	fp y = 0.0;
	fp iteration = 0;
	//const int max_iteration = 1 << 16;
	const fp d1 = (1 << 16);
	fp xx = 0,//x * x, 
		yy = 0;//y * y;
		// Here N=2^8 is chosen as a reasonable bailout radius.
		while (xx + yy <= d1 && iteration < max_iteration) {
			const fp xtemp = xx - yy + x0;
			y = 2 * x * y + y0;
				x = xtemp;
				xx = x * x;
				yy = y * y;
				iteration++;
		}
	// Used to avoid floating point issues with points inside the set.
	if (iteration < max_iteration) {
		// sqrt of inner term removed using log simplification rules.
		const fp l2 = log(2);
		const fp log_zn = log(xx +yy) / 2;
		const fp nu = log(log_zn / l2) / l2;
		// Rearranging the potential function.
		// Dividing log_zn by log(2) instead of log(N = 1<<8)
		// because we want the entire palette to range from the
		// center to radius 2, NOT our bailout radius.
		iteration = iteration + 1 - nu;
	}
	else 
	{
		//iteration--;
	}
	const color color1 = palette[(int)floor(iteration)];
	const color color2 = palette[(int)floor(iteration) + 1];
		// iteration % 1 = fractional part of iteration.
	return color::lerp(color1, color2, iteration - floor(iteration));
	//return color((int)(iteration * 255 / max_iteration), (int)iteration % 256, (int)((iteration- floor(iteration)) * 255));
}

void ProcessInput();
bool DoEvents();
void ClearColor(color BackGroundColor);
void FillPixel(int x, int y, color color);
void FillPixelUnsafe(int x, int y, color color);
void FillTriangle3D(fp x1, fp y1, fp d1, fp x2, fp y2, fp d2, fp x3, fp y3, fp d3, fp minx, fp maxx, color FillWith);
void FillRectangle(int x, int y, int w, int h, color FillWith);
void FillCircle(fp x, fp y, fp w, fp h, color FillWith);