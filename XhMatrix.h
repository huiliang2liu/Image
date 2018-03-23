#pragma once
class XhMatrix
{
public:
	XhMatrix();
	~XhMatrix();
	/*��ת270�ȣ���һ��������Ҫ��ת�ľ���,�ڶ��������Ǿ�����ȣ������������Ǿ���ĸ߶�*/
	static int*  rotate270(int*, int, int);
	/*��ת90�ȣ���һ��������Ҫ��ת�ľ���,�ڶ��������Ǿ�����ȣ������������Ǿ���ĸ߶�*/
	static int*  rotate90(int*, int, int);
	/*��ת180�ȣ���һ��������Ҫ��ת�ľ���,�ڶ��������Ǿ�����ȣ������������Ǿ���ĸ߶�*/
	static int*  rotate180(int *, int, int);
	/*��ȡ����һ��������Ҫ��ת�ľ���,�ڶ��������Ǿ�����ȣ������������Ǿ���ĸ߶ȣ����ĸ������ǽ�ȡ���ȿ�ʼλ�ã�����������ǽ�ȡ�߶ȿ�ʼλ�ã������������ǽ�ȡ���Ƚ���λ�ã����߸������ǽ�ȡ�߶Ƚ���λ��*/
	static int*  interception(int *, int, int, int, int, int, int);
	/*����y��Գ�,�ڶ��������Ǿ�����ȣ������������Ǿ���ĸ߶�*/
	static int*  symmetry_y(int*, int, int);
	/*����x��Գ�,�ڶ��������Ǿ�����ȣ������������Ǿ���ĸ߶�*/
	static int*  symmetry_x(int*, int, int);
};
