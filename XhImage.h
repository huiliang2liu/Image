#pragma once
#include<jni.h>
class XhImage
{
public:
	XhImage();
	~XhImage();
	/*旋转270度*/
	static jintArray rotate270(JNIEnv * env, jintArray arr, jint heigth);
	/*旋转90度，第一个参数是要旋转的像素集,第二个参数是图片宽度，第三个参数是图片的高度*/
	static jintArray rotate90(JNIEnv * env, jintArray arr, jint heigth);
	/*旋转180度，第一个参数是要旋转的像素集,第二个参数是图片宽度，第三个参数是图片的高度*/
	static jintArray rotate180(JNIEnv * env, jintArray arr, jint heigth);
	/*截取，第一个参数是要旋转的像素集,第二个参数是矩阵宽度，第三个参数是矩阵的高度，第四个参数是截取宽度开始位置，第五个参数是截取高度开始位置，第六个参数是截取宽度结束位置，第七个参数是截取高度结束位置*/
	static jintArray interception(JNIEnv * env, jintArray arr, jint start_x, jint start_y,
		jint end_x, jint end_y, jint heigth);
	/*关于y轴对称，第一个参数是要旋转的像素集,第二个参数是矩阵宽度，第三个参数是矩阵的高度*/
	static jintArray symmetry_y(JNIEnv * env, jintArray arr, jint heigth);
	/*关于x轴对称，第一个参数是要旋转的像素集,第二个参数是矩阵宽度，第三个参数是矩阵的高度*/
	static jintArray symmetry_x(JNIEnv * env, jintArray arr, jint heigth);
	/*怀旧处理*/
	static jintArray nostalgia(JNIEnv*,jintArray,jint);
	/*浮雕处理*/
	static jintArray relief(JNIEnv*, jintArray, jint);
	/*模糊处理*/
	static jintArray fuzzy(JNIEnv*, jintArray, jint,jint);
	/*光照效果*/
	static jintArray sunshine(JNIEnv*, jintArray, jint, jint, jint);
	/*锐化处理*/
	static jintArray sharpen(JNIEnv*, jintArray, jint);
	/*冰冻处理*/
	static jintArray ice(JNIEnv*, jintArray, jint);
	/*素描处理*/
	static jintArray sketch(JNIEnv*, jintArray, jint);
	static jintArray addFrameToImageTwo(JNIEnv*, jintArray, jint, jintArray, jint);
private :
	/*两个数字中的最小值*/
	static int min(int, int);
	/*两个数字中的最大值*/
	static int max(int, int);
	/*高斯模糊*/
	static void gaussBlur(int*, int  , int  ,
		int  , float  );
	/*颜色减淡*/
	static void colorDodge(int*, int*,int);
	/**/
	static int colorDodgeFormular(int,int);
};

