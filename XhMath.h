#pragma once
	  static double PI = 3.141592653589793;
class XhMath
{
public:
	XhMath();
	~XhMath();
	/*����x��ƽ����*/
	static double sqrt(double);
	/*��e��x����*/
	static double exp(double);
	static double pow(double, double);
private:
	static double pow_i(double, int);
	static double pow_f(double, double);
};

