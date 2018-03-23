#pragma once
class XhColor
{
public:
	XhColor();
	~XhColor();
	/*获取颜色中的透明度*/
	static int alpha(int color);
	/*获取颜色中的红色值*/
	static int red(int color);

	/*获取颜色中的绿色值*/
	static int green(int color);

	/*获取颜色中的蓝色值*/
	static int blue(int color);

	/*将红绿蓝三原色转化为颜色*/
	static int rgb(int red, int green, int blue);

	/*将红绿蓝三原色转化为颜色并且有透明度*/
	static int argb(int alpha, int red, int green, int blue);
};

