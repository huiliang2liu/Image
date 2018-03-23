#pragma once
	  static double PI = 3.141592653589793;
class XhMath
{
public:
	XhMath();
	~XhMath();
	/*计算x的平方根*/
	static double sqrt(double);
	/*求e的x次幂*/
	static double exp(double);
	static double pow(double, double);
private:
	static double pow_i(double, int);
	static double pow_f(double, double);
};

