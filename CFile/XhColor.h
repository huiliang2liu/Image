#pragma once
class XhColor
{
public:
	XhColor();
	~XhColor();
	/*��ȡ��ɫ�е�͸����*/
	static int alpha(int color);
	/*��ȡ��ɫ�еĺ�ɫֵ*/
	static int red(int color);

	/*��ȡ��ɫ�е���ɫֵ*/
	static int green(int color);

	/*��ȡ��ɫ�е���ɫֵ*/
	static int blue(int color);

	/*����������ԭɫת��Ϊ��ɫ*/
	static int rgb(int red, int green, int blue);

	/*����������ԭɫת��Ϊ��ɫ������͸����*/
	static int argb(int alpha, int red, int green, int blue);
};

