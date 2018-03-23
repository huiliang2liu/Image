#include "com_xh_image_Image.h"
#include "XhImage.h"

JNIEXPORT jint JNICALL Java_com_xh_image_Image_test
(JNIEnv * env, jclass jc, jobjectArray arr) {
	return env->GetArrayLength(arr);
}

/*
* Class:     com_xh_image_Image
* Method:    rotate270
* Signature: ([II)[I
*/
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_rotate270
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::rotate270(env,arr,heigth);
}

/*
* Class:     com_xh_image_Image
* Method:    rotate90
* Signature: ([II)[I
*/
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_rotate90
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::rotate90(env,arr,heigth);
}

/*
* Class:     com_xh_image_Image
* Method:    look_mirror
* Signature: ([II)[I
*/
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_look_mirrorX
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::symmetry_y(env,arr,heigth);
}



/*
* Class:     com_xh_image_Image
* Method:    rotate180
* Signature: ([II)[I
*/
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_rotate180
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::rotate180(env,arr,heigth);
}

/*
* Class:     com_xh_image_Image
* Method:    interception
* Signature: ([IIIIII)[I
*/
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_interception
(JNIEnv * env, jclass jc, jintArray arr, jint start_x, jint start_y, jint end_x, jint end_y, jint heigth) {
	return XhImage::interception(env,arr,start_x,start_y,end_x,end_y,heigth);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_nostalgia
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::nostalgia(env, arr, heigth);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_relief
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::relief(env, arr, heigth);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_fuzzy
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::fuzzy(env, arr, heigth, 16);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_sunshine
(JNIEnv * env, jclass jc, jintArray arr, jint heigth, jint c_x, jint c_y) {
	return XhImage::sunshine(env, arr, heigth, c_x, c_y);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_sharpen
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::sharpen(env, arr, heigth);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_ice
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::ice(env, arr, heigth);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_sketch
(JNIEnv * env, jclass jc, jintArray arr, jint heigth) {
	return XhImage::sketch(env,arr,heigth);
}
JNIEXPORT jintArray JNICALL Java_com_xh_image_Image_addFrameToImageTwo
(JNIEnv * env, jclass jc, jintArray arr1, jint heigth1, jintArray arr2, jint heigth2) {
	

}
