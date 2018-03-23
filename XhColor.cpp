#include "XhColor.h"


XhColor::XhColor()
{
}


XhColor::~XhColor()
{
}

int XhColor::alpha(int color)
{
	return color >> 24;
}

int XhColor::red(int color)
{
	return (color >> 16) & 0xff;
}

int XhColor::green(int color)
{
	return (color >> 8) & 0xff;
}

int XhColor::blue(int color)
{
	return color & 0xff;
}

int XhColor::rgb(int red, int green, int blue)
{
	return (0xff << 24) | (red << 16) | (green << 8) | blue;
}

int XhColor::argb(int alpha, int red, int green, int blue)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}
