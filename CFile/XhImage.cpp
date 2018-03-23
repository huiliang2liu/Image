#include "XhImage.h"
#include "XhColor.h"
#include "XhMatrix.h"
#include "XhMath.h"

XhImage::XhImage()
{
}


XhImage::~XhImage()
{
}
int XhImage::min(int mina, int minb)
{
	return mina>minb ? minb : mina;
}

int XhImage::max(int maxa, int maxb)
{
	return maxa>maxb ? maxa : maxb;
}
void XhImage::gaussBlur(int* data, int width, int height,
	int radius, float sigma)
{
	float pa = (float)(1 / (XhMath::sqrt(2 * PI) * sigma));
	float pb = -1.0f / (2 * sigma * sigma);
	int length = radius * 2 + 1;
	// generate the Gauss Matrix
	float gaussMatrix[length];
	float gaussSum = 0.0f;
	for (int i = 0, x = -radius; x <= radius; ++x, ++i) {
		float g = (float)(pa * XhMath::exp(pb * x * x));
		gaussMatrix[i] = g;
		gaussSum += g;
	}

	for (int i = 0; i < length; ++i) {
		gaussMatrix[i] /= gaussSum;
	}

	// x direction
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			float r = 0, g = 0, b = 0;
			gaussSum = 0;
			for (int j = -radius; j <= radius; ++j) {
				int k = x + j;
				if (k >= 0 && k < width) {
					int index = y * width + k;
					int color = data[index];
					int cr = (color & 0x00ff0000) >> 16;
					int cg = (color & 0x0000ff00) >> 8;
					int cb = (color & 0x000000ff);

					r += cr * gaussMatrix[j + radius];
					g += cg * gaussMatrix[j + radius];
					b += cb * gaussMatrix[j + radius];

					gaussSum += gaussMatrix[j + radius];
				}
			}

			int index = y * width + x;
			int cr = (int)(r / gaussSum);
			int cg = (int)(g / gaussSum);
			int cb = (int)(b / gaussSum);

			data[index] = cr << 16 | cg << 8 | cb | 0xff000000;
		}
	}

	// y direction
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			float r = 0, g = 0, b = 0;
			gaussSum = 0;
			for (int j = -radius; j <= radius; ++j) {
				int k = y + j;
				if (k >= 0 && k < height) {
					int index = k * width + x;
					int color = data[index];
					int cr = (color & 0x00ff0000) >> 16;
					int cg = (color & 0x0000ff00) >> 8;
					int cb = (color & 0x000000ff);

					r += cr * gaussMatrix[j + radius];
					g += cg * gaussMatrix[j + radius];
					b += cb * gaussMatrix[j + radius];

					gaussSum += gaussMatrix[j + radius];
				}
			}

			int index = y * width + x;
			int cr = (int)(r / gaussSum);
			int cg = (int)(g / gaussSum);
			int cb = (int)(b / gaussSum);
			data[index] = cr << 16 | cg << 8 | cb | 0xff000000;
		}
	}

}
void XhImage::colorDodge(int * baseColor, int * mixColor, int length)
{ 
	for (int i = 0; i < length; ++i) {
		int bColor = baseColor[i];
		int br = (bColor & 0x00ff0000) >> 16;
		int bg = (bColor & 0x0000ff00) >> 8;
		int bb = (bColor & 0x000000ff);

		int mColor = mixColor[i];
		int mr = (mColor & 0x00ff0000) >> 16;
		int mg = (mColor & 0x0000ff00) >> 8;
		int mb = (mColor & 0x000000ff);

		int nr = colorDodgeFormular(br, mr);
		int ng = colorDodgeFormular(bg, mg);
		int nb = colorDodgeFormular(bb, mb);

		baseColor[i] = nr << 16 | ng << 8 | nb | 0xff000000;
	}
}
int XhImage::colorDodgeFormular(int base, int mix)
{
	int result = base + (base * mix) / (255 - mix);
	result = result > 255 ? 255 : result;
	return result;
}
jintArray XhImage::rotate270(JNIEnv * env, jintArray arr, jint heigth)
{
	int length = env->GetArrayLength(arr);
	int matrix[length];
	env->GetIntArrayRegion(arr, 0, length, matrix);
	env->SetIntArrayRegion(arr, 0, length, XhMatrix::rotate270(matrix, length / heigth, heigth));
	return arr;
}

jintArray XhImage::rotate90(JNIEnv * env, jintArray arr, jint heigth)
{
	int len = env->GetArrayLength(arr);
	int matrix[len];
	env->GetIntArrayRegion(arr, 0, len, matrix);
	env->SetIntArrayRegion(arr, 0, len, XhMatrix::rotate90(matrix, len / heigth, heigth));
	return arr;
}

jintArray XhImage::rotate180(JNIEnv * env, jintArray arr, jint heigth)
{
	int len = env->GetArrayLength(arr);
	int matrix[len];
	env->GetIntArrayRegion(arr, 0, len, matrix);
	env->SetIntArrayRegion(arr, 0, len, XhMatrix::rotate180(matrix, len / heigth, heigth));
	return arr;
}

jintArray XhImage::interception(JNIEnv * env, jintArray arr, jint start_x, jint start_y, jint end_x, jint end_y, jint heigth)
{
	int len = env->GetArrayLength(arr);
	int matrix[len];
	env->GetIntArrayRegion(arr, 0, len, matrix);
	int mWidth = end_x - start_x;
	int mHeigth = end_y - start_y;
	int mLen = mWidth * mHeigth;
	jintArray mArr = env->NewIntArray(mLen);
	env->SetIntArrayRegion(mArr, 0, mLen, XhMatrix::interception(matrix, len / heigth, heigth, start_x, end_x, start_y, end_y));
	return mArr;
}

jintArray XhImage::symmetry_y(JNIEnv * env, jintArray arr, jint heigth)
{
	int len = env->GetArrayLength(arr);
	int matrix[len];
	env->GetIntArrayRegion(arr, 0, len, matrix);
	env->SetIntArrayRegion(arr, 0, len, XhMatrix::symmetry_y(matrix, len / heigth, heigth));
	return arr;
}

jintArray XhImage::symmetry_x(JNIEnv * env, jintArray arr, jint heigth)
{
	int len = env->GetArrayLength(arr);
	int matrix[len];
	env->GetIntArrayRegion(arr, 0, len, matrix);
	env->SetIntArrayRegion(arr, 0, len, XhMatrix::symmetry_x(matrix, len / heigth, heigth));
	return arr;
}

jintArray XhImage::nostalgia(JNIEnv * env, jintArray arr, jint heigth)
{
	/*
	* 怀旧处理算法即设置新的RGB R=0.393r+0.769g+0.189b G=0.349r+0.686g+0.168b
	* B=0.272r+0.534g+0.131b
	*/
	int len = env->GetArrayLength(arr);
	int width = len/heigth;
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int newR = 0;
	int newG = 0;
	int newB = 0;
	int pixels[width * heigth];
	env->GetIntArrayRegion(arr, 0, len, pixels);
	for (int i = 0; i < heigth; i++) {
		for (int k = 0; k < width; k++) {
			pixColor = pixels[width * i + k];
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			newR = (int)(0.393 * pixR + 0.769 * pixG + 0.189 * pixB);
			newG = (int)(0.349 * pixR + 0.686 * pixG + 0.168 * pixB);
			newB = (int)(0.272 * pixR + 0.534 * pixG + 0.131 * pixB);
			int newColor = XhColor::argb(255, newR > 255 ? 255 : newR,
				newG > 255 ? 255 : newG, newB > 255 ? 255 : newB);
			pixels[width * i + k] = newColor;
		}
	}
	env->SetIntArrayRegion(arr,0,len,pixels);
	return arr;
}

jintArray XhImage::relief(JNIEnv * env, jintArray arr, jint heigth)
{
	/*
	* 算法原理：(前一个像素点RGB-当前像素点RGB+127)作为当前像素点RGB值 在ABC中计算B点浮雕效果(RGB值在0~255)
	* B.r = C.r - B.r + 127 B.g = C.g - B.g + 127 B.b = C.b - B.b + 127
	*/
	int len = env->GetArrayLength(arr);
	int width = len/heigth;
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int newR = 0;
	int newG = 0;
	int newB = 0;
	int pixels[width*heigth];
	env->GetIntArrayRegion(arr,0,len,pixels);
	for (int i = 1; i < heigth - 1; i++) {
		for (int k = 1; k < width - 1; k++) {
			// 获取前一个像素颜色
			pixColor = pixels[width * i + k];
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			// 获取当前像素
			pixColor = pixels[(width * i + k) + 1];
			newR = XhColor::red(pixColor) - pixR + 127;
			newG = XhColor::green(pixColor) - pixG + 127;
			newB = XhColor::blue(pixColor) - pixB + 127;
			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			pixels[width * i + k] = XhColor::argb(255, newR, newG, newB);
		}
	}
	env->SetIntArrayRegion(arr,0,len,pixels);
	return arr;
}

jintArray XhImage::fuzzy(JNIEnv * env, jintArray arr, jint height,jint delta)
{
	/*
	* 算法原理： 简单算法将像素周围八个点包括自身共九个点RGB值分别相加后平均,当前像素点的RGB值 复杂算法采用高斯模糊 高斯矩阵
	* int[] gauss = new int[] { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
	* 将九个点的RGB值分别与高斯矩阵中的对应项相乘的和,再除以一个相应的值作为当前像素点的RGB
	*/
	int gauss[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 }; // 高斯矩阵
	//int delta = 16; // 除以值 值越小图片会越亮,越大则越暗
	int len = env->GetArrayLength(arr);
	int width = len/height;
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int newR, newG, newB;
	int pos = 0; // 位置
	int pixels[width * height];
	env->GetIntArrayRegion(arr,0,len,pixels);
	// 循环赋值
	for (int i = 1; i < height - 1; i++) {
		for (int k = 1; k < width - 1; k++) {
			pos = 0;
			newR = 0;
			newG = 0;
			newB = 0;
			for (int m = -1; m <= 1; m++) // 宽不变
			{
				for (int n = -1; n <= 1; n++) // 高先变
				{
					pixColor = pixels[(i + m) * width + k + n];
					pixR = XhColor::red(pixColor);
					pixG = XhColor::green(pixColor);
					pixB = XhColor::blue(pixColor);
					// 3*3像素相加
					newR = newR + (int)(pixR * gauss[pos]);
					newG = newG + (int)(pixG * gauss[pos]);
					newB = newB + (int)(pixB * gauss[pos]);
					pos++;
				}
			}
			newR /= delta;
			newG /= delta;
			newB /= delta;
			newR = min(255,max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			pixels[i * width + k] = XhColor::argb(255, newR, newG, newB);
		}
	}
	env->SetIntArrayRegion(arr,0,len,pixels);
	return arr;
}

jintArray XhImage::sunshine(JNIEnv * env, jintArray arr, jint height, jint ligth_x, jint ligth_y)
{ 
	int len = env->GetArrayLength(arr);
	int width = len/ height;
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int newR = 0;
	int newG = 0;
	int newB = 0;
	// 围绕圆形光照
	int radius = min(ligth_x, ligth_y);
	float strength = 150; // 光照强度100-150
	int pixels[len];
	env->GetIntArrayRegion(arr, 0, len, pixels);
	for (int i = 1; i < height - 1; i++) {
		for (int k = 1; k < width - 1; k++) {
			// 获取前一个像素颜色
			pixColor = pixels[width * i + k];
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			newR = pixR;
			newG = pixG;
			newB = pixB;
			// 计算当前点到光照中心的距离,平面坐标系中两点之间的距离
			int distance = (int)(XhMath::pow((ligth_y - i), 2) + XhMath::pow(
				(ligth_x - k), 2));
			if (distance < radius * radius) {
				// 按照距离大小计算增强的光照值
				int result = (int)(strength * (1.0 - XhMath::sqrt(distance)
					/ radius));
				newR = pixR + result;
				newG = newG + result;
				newB = pixB + result;
			}
			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			pixels[width * i + k] = XhColor::argb(255, newR, newG, newB);
		}
	}
	env->SetIntArrayRegion(arr,0,len,pixels);
	return arr;
}

jintArray XhImage::sharpen(JNIEnv * env, jintArray arr, jint heigth)
{
	/*
	* 锐化基本思想是加强图像中景物的边缘和轮廓,使图像变得清晰 而图像平滑是使图像中边界和轮廓变得模糊
	*
	* 拉普拉斯算子图像锐化 获取周围9个点的矩阵乘以模板9个的矩阵 卷积
	*/
	// 拉普拉斯算子模板 { 0, -1, 0, -1, -5, -1, 0, -1, 0 } { -1, -1, -1, -1, 9, -1,
	// -1, -1, -1 }
	int laplacian[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };
	int len = env->GetArrayLength(arr);
	int width = len/heigth;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int pixColor = 0;
	int newR = 0;
	int newG = 0;
	int newB = 0;
	int idx = 0;
	float alpha = 0.3F; // 图片透明度
	int pixels[width * heigth];
	env->GetIntArrayRegion(arr,0,len,pixels);
	// 图像处理
	for (int i = 1; i < heigth - 1; i++) {
		for (int k = 1; k < width - 1; k++) {
			idx = 0;
			newR = 0;
			newG = 0;
			newB = 0;
			for (int n = -1; n <= 1; n++) // 取出图像3*3领域像素
			{
				for (int m = -1; m <= 1; m++) // n行数不变 m列变换
				{
					pixColor = pixels[(i + n) * width + k + m]; // 当前点(i,k)
					pixR = XhColor::red(pixColor);
					pixG = XhColor::green(pixColor);
					pixB = XhColor::blue(pixColor);
					// 图像像素与对应摸板相乘
					newR = newR + (int)(pixR * laplacian[idx] * alpha);
					newG = newG + (int)(pixG * laplacian[idx] * alpha);
					newB = newB + (int)(pixB * laplacian[idx] * alpha);
					idx++;
				}
			}
			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			// 赋值
			pixels[i * width + k] = XhColor::argb(255, newR, newG, newB);
		}
	}
	env->SetIntArrayRegion(arr,0,len,pixels);
	return arr;
}

jintArray XhImage::ice(JNIEnv * env, jintArray arr, jint heigth)
{
	int len = env->GetArrayLength(arr);
	int width = len/heigth;
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int newColor = 0;
	int newR = 0;
	int newG = 0;
	int newB = 0;
	int pixels[width * heigth];
	env->GetIntArrayRegion(arr, 0, len, pixels);
	for (int i = 0; i < heigth; i++) {
		for (int k = 0; k < width; k++) {
			// 获取前一个像素颜色
			pixColor = pixels[width * i + k];
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			// 红色
			newColor = pixR - pixG - pixB;
			newColor = newColor * 3 / 2;
			if (newColor < 0) {
				newColor = -newColor;
			}
			if (newColor > 255) {
				newColor = 255;
			}
			newR = newColor;
			// 绿色
			newColor = pixG - pixB - pixR;
			newColor = newColor * 3 / 2;
			if (newColor < 0) {
				newColor = -newColor;
			}
			if (newColor > 255) {
				newColor = 255;
			}
			newG = newColor;
			// 蓝色
			newColor = pixB - pixG - pixR;
			newColor = newColor * 3 / 2;
			if (newColor < 0) {
				newColor = -newColor;
			}
			if (newColor > 255) {
				newColor = 255;
			}
			newB = newColor;
			pixels[width * i + k] = XhColor::argb(255, newR, newG, newB);
		}
	}
	env->SetIntArrayRegion(arr,0,len,pixels);
	return arr;
}

jintArray XhImage::sketch(JNIEnv *env, jintArray arr, jint height)
{
	// 创建新Bitmap
	int len = env->GetArrayLength(arr);
	int width = len/ height;
	int pixels[len]; // 存储变换图像
	int linpix[len]; // 存储灰度图像
	env->GetIntArrayRegion(arr,0,len,pixels);
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	// 灰度图像
	for (int i = 1; i < height - 1; i++)
		// 拉普拉斯算子模板 { 0, -1, 0, -1, -5,
		for (int j = 1; j < width - 1; j++) {
			// -1, 0, -1, 0
			{
				// 获取前一个像素颜色
				pixColor = pixels[width * i + j];
				pixR = XhColor::red(pixColor);
				pixG = XhColor::green(pixColor);
				pixB = XhColor::blue(pixColor);
				// 灰度图像
				int gray = (int)(0.3 * pixR + 0.59 * pixG + 0.11 * pixB);
				linpix[width * i + j] = XhColor::argb(255, gray, gray, gray);
				// 图像反向
				gray = 255 - gray;
				pixels[width * i + j] = XhColor::argb(255, gray, gray, gray);
			}
		}
	gaussBlur(pixels, width, height, 10, 10 / 3); // 高斯模糊
																   // 采用半径10
	colorDodge(linpix, pixels,len); // 素描图像 颜色减淡
	env->SetIntArrayRegion(arr, 0, len, linpix);
	return arr;
}

jintArray XhImage::addFrameToImageTwo(JNIEnv * env, jintArray frameBitmap, jint h, jintArray bmp, jint heigth)
{// bmp原图 创建新位图
	int bmpLen = env->GetArrayLength(bmp);
	int width = bmpLen/heigth;
	// 对边框进行缩放
	int frameBitmapLen = env->GetArrayLength(frameBitmap);
	int bmpPixel[bmpLen];
	env->GetIntArrayRegion(bmp,0,bmpLen,bmpPixel);
	int frameBmpPixel[frameBitmapLen];
	env->GetIntArrayRegion(frameBitmap, 0, frameBitmapLen, frameBmpPixel);
	int w = frameBitmapLen/h;
	float scaleX = width * 1.0f/ w; // 缩放比 如果图片尺寸超过边框尺寸 会自动匹配
	float scaleY = heigth * 1.0f / h;

	int pixColor = 0;
	int layColor = 0;
	int newColor = 0;

	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int pixA = 0;

	int newR = 0;
	int newG = 0;
	int newB = 0;
	int newA = 0;

	int layR = 0;
	int layG = 0;
	int layB = 0;
	int layA = 0;

	float alpha = 0.8F;
	float alphaR = 0.0F;
	float alphaG = 0.0F;
	float alphaB = 0.0F;

	for (int i = 0; i < width; i++) {
		for (int k = 0; k < heigth; k++) {
			pixColor = bmpPixel[i*heigth + k];
			layColor = frameBmpPixel[i*heigth + k];
			// 获取原图片的RGBA值
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			pixA = XhColor::alpha(pixColor);
			// 获取边框图片的RGBA值
			layR = XhColor::red(layColor);
			layG = XhColor::green(layColor);
			layB = XhColor::blue(layColor);
			layA = XhColor::alpha(layColor);
			// 颜色与纯黑色相近的点
			if (layR < 20 && layG < 20 && layB < 20) {
				alpha = 1.0F;
			}
			else {
				alpha = 0.3F;
			}
			alphaR = alpha;
			alphaG = alpha;
			alphaB = alpha;
			// 两种颜色叠加
			newR = (int)(pixR * alphaR + layR * (1 - alphaR));
			newG = (int)(pixG * alphaG + layG * (1 - alphaG));
			newB = (int)(pixB * alphaB + layB * (1 - alphaB));
			layA = (int)(pixA * alpha + layA * (1 - alpha));
			// 值在0~255之间
			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			newA = min(255, max(0, layA));
			// 绘制
			newColor = XhColor::argb(newA, newR, newG, newB);
			bmpPixel[i*heigth + k] = newColor;
		}
	}
	env->SetIntArrayRegion(bmp,0,bmpLen,bmpPixel);
	return bmp;
}









