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
	m = 1;      //�׳��㷨��ĸ
	e = 1.0;  //e��xm
	ef = 1.0;
	t = 10;      //�㷨����
	z = 1;  //���ӳ�ʼ��
	sum = 1;
	//  printf("x=%f\n",x);
	//  printf("sub=%f\n",sub);
	if (xm<0) {     //�ж�xm�Ƿ����0��
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
	if (num == 0 && m != 0) return 0;//��numΪ0���򷵻�0
	else if (num == 0 && m == 0) return 1;// ��num��m��Ϊ0���򷵻�1
	else if (num<0 && m - int(m) != 0) return 0;//��numΪ������m��Ϊ�����������������0 
	if (num>2)//�ѵ�������2�����תΪ(1/num)^-m����
	{
		num = 1 / num;
		m = -m;
	}
	if (m<0) return 1 / pow(num, -m);//��ָ��С��0�����תΪ1/num^-m����
	if (m - int(m) == 0) return pow_i(num, m);/*��ָ��Ϊ�������ǣ��ֳ�������С���ֱ���
											  �ݣ�������Ϊ��������Сʽ����pow_fֱ������
											  �������Է�Ϊָ��������������pow_i,С
											  ��������pow_f��.*/
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
	for (i = 1; tmpm>1e-12 || tmpm<-1e-12; i++)//��tmpm���ڴη�Χʱ��ֹͣѭ��,��Χ�ɸ� 
	{
		for (j = 1, tmpm = 1; j <= i; j++)
			tmpm *= (m - j + 1)*x / j;
		powf += tmpm;
	}
	return powf + 1;
}
