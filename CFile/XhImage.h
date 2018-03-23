#pragma once
#include<jni.h>
class XhImage
{
public:
	XhImage();
	~XhImage();
	/*��ת270��*/
	static jintArray rotate270(JNIEnv * env, jintArray arr, jint heigth);
	/*��ת90�ȣ���һ��������Ҫ��ת�����ؼ�,�ڶ���������ͼƬ��ȣ�������������ͼƬ�ĸ߶�*/
	static jintArray rotate90(JNIEnv * env, jintArray arr, jint heigth);
	/*��ת180�ȣ���һ��������Ҫ��ת�����ؼ�,�ڶ���������ͼƬ��ȣ�������������ͼƬ�ĸ߶�*/
	static jintArray rotate180(JNIEnv * env, jintArray arr, jint heigth);
	/*��ȡ����һ��������Ҫ��ת�����ؼ�,�ڶ��������Ǿ����ȣ������������Ǿ���ĸ߶ȣ����ĸ������ǽ�ȡ��ȿ�ʼλ�ã�����������ǽ�ȡ�߶ȿ�ʼλ�ã������������ǽ�ȡ��Ƚ���λ�ã����߸������ǽ�ȡ�߶Ƚ���λ��*/
	static jintArray interception(JNIEnv * env, jintArray arr, jint start_x, jint start_y,
		jint end_x, jint end_y, jint heigth);
	/*����y��Գƣ���һ��������Ҫ��ת�����ؼ�,�ڶ��������Ǿ����ȣ������������Ǿ���ĸ߶�*/
	static jintArray symmetry_y(JNIEnv * env, jintArray arr, jint heigth);
	/*����x��Գƣ���һ��������Ҫ��ת�����ؼ�,�ڶ��������Ǿ����ȣ������������Ǿ���ĸ߶�*/
	static jintArray symmetry_x(JNIEnv * env, jintArray arr, jint heigth);
	/*���ɴ���*/
	static jintArray nostalgia(JNIEnv*,jintArray,jint);
	/*������*/
	static jintArray relief(JNIEnv*, jintArray, jint);
	/*ģ������*/
	static jintArray fuzzy(JNIEnv*, jintArray, jint,jint);
	/*����Ч��*/
	static jintArray sunshine(JNIEnv*, jintArray, jint, jint, jint);
	/*�񻯴���*/
	static jintArray sharpen(JNIEnv*, jintArray, jint);
	/*��������*/
	static jintArray ice(JNIEnv*, jintArray, jint);
	/*���账��*/
	static jintArray sketch(JNIEnv*, jintArray, jint);
	static jintArray addFrameToImageTwo(JNIEnv*, jintArray, jint, jintArray, jint);
private :
	/*���������е���Сֵ*/
	static int min(int, int);
	/*���������е����ֵ*/
	static int max(int, int);
	/*��˹ģ��*/
	static void gaussBlur(int*, int  , int  ,
		int  , float  );
	/*��ɫ����*/
	static void colorDodge(int*, int*,int);
	/**/
	static int colorDodgeFormular(int,int);
};

