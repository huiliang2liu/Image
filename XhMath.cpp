#include "XhMath.h"


XhMath::XhMath()
{
}


XhMath::~XhMath()
{
}

double XhMath::sqrt(double m)
{
	float i = 0;
	float x1, x2;
	while ((i*i) <= m)
		i += 0.1;
	x1 = i;
	for (int j = 0; j<10; j++)
	{
		x2 = m;
		x2 /= x1;
		x2 += x1;
		x2 /= 2;
		x1 = x2;
	}
	return x2;
}

double XhMath::exp(double x)
{
	int i, k, m, t;
	int xm = (int)x;
	double sum;
	double e;
	double ef;
	double z;
	double sub = x - xm;
	m = 1;      //阶乘算法分母
	e = 1.0;  //e的xm
	ef = 1.0;
	t = 10;      //算法精度
	z = 1;  //分子初始化
	sum = 1;
	//  printf("x=%f\n",x);
	//  printf("sub=%f\n",sub);
	if (xm<0) {     //判断xm是否大于0？
		xm = (-xm);
		for (k = 0; k<xm; k++) { ef *= 2.718281; }
		e /= ef;
	}
	else { for (k = 0; k<xm; k++) { e *= 2.718281; } }
	//  printf("e=%f\n",e);
	//  printf("xm=%d\n",xm);
	for (i = 1; i<t; i++) {
		m *= i;
		z *= sub;
		sum += z / m;
	}
	return sum * e;
}

double XhMath::pow(double num, double m)
{
	if (num == 0 && m != 0) return 0;//若num为0，则返回0
	else if (num == 0 && m == 0) return 1;// 若num和m都为0，则返回1
	else if (num<0 && m - int(m) != 0) return 0;//若num为负，且m不为整数数，则出错，返回0 
	if (num>2)//把底数大于2的情况转为(1/num)^-m计算
	{
		num = 1 / num;
		m = -m;
	}
	if (m<0) return 1 / pow(num, -m);//把指数小于0的情况转为1/num^-m计算
	if (m - int(m) == 0) return pow_i(num, m);/*当指数为浮点数是，分成整数和小数分别求
											  幂，这是因为但底数较小式，用pow_f直接求幂
											  误差大，所以分为指数的整数部分用pow_i,小
											  数部分用pow_f求.*/
	else return pow_f(num, m - int(m))*pow_i(num, int(m));
	return pow_f(num, m);
}

double XhMath::pow_i(double num, int n)
{
	double powint = 1;
	int i;
	for (i = 1; i <= n; i++) powint *= num;
	return powint;
}

double XhMath::pow_f(double num, double m)
{
	int i, j;
	double powf = 0, x, tmpm = 1;
	x = num - 1;
	for (i = 1; tmpm>1e-12 || tmpm<-1e-12; i++)//当tmpm不在次范围时，停止循环,范围可改 
	{
		for (j = 1, tmpm = 1; j <= i; j++)
			tmpm *= (m - j + 1)*x / j;
		powf += tmpm;
	}
	return powf + 1;
}
