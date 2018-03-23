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
	* ���ɴ����㷨�������µ�RGB R=0.393r+0.769g+0.189b G=0.349r+0.686g+0.168b
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
	* �㷨ԭ��(ǰһ�����ص�RGB-��ǰ���ص�RGB+127)��Ϊ��ǰ���ص�RGBֵ ��ABC�м���B�㸡��Ч��(RGBֵ��0~255)
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
			// ��ȡǰһ��������ɫ
			pixColor = pixels[width * i + k];
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			// ��ȡ��ǰ����
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
	* �㷨ԭ�� ���㷨��������Χ�˸�����������Ÿ���RGBֵ�ֱ���Ӻ�ƽ��,��ǰ���ص��RGBֵ �����㷨���ø�˹ģ�� ��˹����
	* int[] gauss = new int[] { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
	* ���Ÿ����RGBֵ�ֱ����˹�����еĶ�Ӧ����˵ĺ�,�ٳ���һ����Ӧ��ֵ��Ϊ��ǰ���ص��RGB
	*/
	int gauss[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 }; // ��˹����
	//int delta = 16; // ����ֵ ֵԽСͼƬ��Խ��,Խ����Խ��
	int len = env->GetArrayLength(arr);
	int width = len/height;
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	int newR, newG, newB;
	int pos = 0; // λ��
	int pixels[width * height];
	env->GetIntArrayRegion(arr,0,len,pixels);
	// ѭ����ֵ
	for (int i = 1; i < height - 1; i++) {
		for (int k = 1; k < width - 1; k++) {
			pos = 0;
			newR = 0;
			newG = 0;
			newB = 0;
			for (int m = -1; m <= 1; m++) // ����
			{
				for (int n = -1; n <= 1; n++) // ���ȱ�
				{
					pixColor = pixels[(i + m) * width + k + n];
					pixR = XhColor::red(pixColor);
					pixG = XhColor::green(pixColor);
					pixB = XhColor::blue(pixColor);
					// 3*3�������
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
	// Χ��Բ�ι���
	int radius = min(ligth_x, ligth_y);
	float strength = 150; // ����ǿ��100-150
	int pixels[len];
	env->GetIntArrayRegion(arr, 0, len, pixels);
	for (int i = 1; i < height - 1; i++) {
		for (int k = 1; k < width - 1; k++) {
			// ��ȡǰһ��������ɫ
			pixColor = pixels[width * i + k];
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			newR = pixR;
			newG = pixG;
			newB = pixB;
			// ���㵱ǰ�㵽�������ĵľ���,ƽ������ϵ������֮��ľ���
			int distance = (int)(XhMath::pow((ligth_y - i), 2) + XhMath::pow(
				(ligth_x - k), 2));
			if (distance < radius * radius) {
				// ���վ����С������ǿ�Ĺ���ֵ
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
	* �񻯻���˼���Ǽ�ǿͼ���о���ı�Ե������,ʹͼ�������� ��ͼ��ƽ����ʹͼ���б߽���������ģ��
	*
	* ������˹����ͼ���� ��ȡ��Χ9����ľ������ģ��9���ľ��� ���
	*/
	// ������˹����ģ�� { 0, -1, 0, -1, -5, -1, 0, -1, 0 } { -1, -1, -1, -1, 9, -1,
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
	float alpha = 0.3F; // ͼƬ͸����
	int pixels[width * heigth];
	env->GetIntArrayRegion(arr,0,len,pixels);
	// ͼ����
	for (int i = 1; i < heigth - 1; i++) {
		for (int k = 1; k < width - 1; k++) {
			idx = 0;
			newR = 0;
			newG = 0;
			newB = 0;
			for (int n = -1; n <= 1; n++) // ȡ��ͼ��3*3��������
			{
				for (int m = -1; m <= 1; m++) // n�������� m�б任
				{
					pixColor = pixels[(i + n) * width + k + m]; // ��ǰ��(i,k)
					pixR = XhColor::red(pixColor);
					pixG = XhColor::green(pixColor);
					pixB = XhColor::blue(pixColor);
					// ͼ���������Ӧ�������
					newR = newR + (int)(pixR * laplacian[idx] * alpha);
					newG = newG + (int)(pixG * laplacian[idx] * alpha);
					newB = newB + (int)(pixB * laplacian[idx] * alpha);
					idx++;
				}
			}
			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			// ��ֵ
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
			// ��ȡǰһ��������ɫ
			pixColor = pixels[width * i + k];
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			// ��ɫ
			newColor = pixR - pixG - pixB;
			newColor = newColor * 3 / 2;
			if (newColor < 0) {
				newColor = -newColor;
			}
			if (newColor > 255) {
				newColor = 255;
			}
			newR = newColor;
			// ��ɫ
			newColor = pixG - pixB - pixR;
			newColor = newColor * 3 / 2;
			if (newColor < 0) {
				newColor = -newColor;
			}
			if (newColor > 255) {
				newColor = 255;
			}
			newG = newColor;
			// ��ɫ
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
	// ������Bitmap
	int len = env->GetArrayLength(arr);
	int width = len/ height;
	int pixels[len]; // �洢�任ͼ��
	int linpix[len]; // �洢�Ҷ�ͼ��
	env->GetIntArrayRegion(arr,0,len,pixels);
	int pixColor = 0;
	int pixR = 0;
	int pixG = 0;
	int pixB = 0;
	// �Ҷ�ͼ��
	for (int i = 1; i < height - 1; i++)
		// ������˹����ģ�� { 0, -1, 0, -1, -5,
		for (int j = 1; j < width - 1; j++) {
			// -1, 0, -1, 0
			{
				// ��ȡǰһ��������ɫ
				pixColor = pixels[width * i + j];
				pixR = XhColor::red(pixColor);
				pixG = XhColor::green(pixColor);
				pixB = XhColor::blue(pixColor);
				// �Ҷ�ͼ��
				int gray = (int)(0.3 * pixR + 0.59 * pixG + 0.11 * pixB);
				linpix[width * i + j] = XhColor::argb(255, gray, gray, gray);
				// ͼ����
				gray = 255 - gray;
				pixels[width * i + j] = XhColor::argb(255, gray, gray, gray);
			}
		}
	gaussBlur(pixels, width, height, 10, 10 / 3); // ��˹ģ��
																   // ���ð뾶10
	colorDodge(linpix, pixels,len); // ����ͼ�� ��ɫ����
	env->SetIntArrayRegion(arr, 0, len, linpix);
	return arr;
}

jintArray XhImage::addFrameToImageTwo(JNIEnv * env, jintArray frameBitmap, jint h, jintArray bmp, jint heigth)
{// bmpԭͼ ������λͼ
	int bmpLen = env->GetArrayLength(bmp);
	int width = bmpLen/heigth;
	// �Ա߿��������
	int frameBitmapLen = env->GetArrayLength(frameBitmap);
	int bmpPixel[bmpLen];
	env->GetIntArrayRegion(bmp,0,bmpLen,bmpPixel);
	int frameBmpPixel[frameBitmapLen];
	env->GetIntArrayRegion(frameBitmap, 0, frameBitmapLen, frameBmpPixel);
	int w = frameBitmapLen/h;
	float scaleX = width * 1.0f/ w; // ���ű� ���ͼƬ�ߴ糬���߿�ߴ� ���Զ�ƥ��
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
			// ��ȡԭͼƬ��RGBAֵ
			pixR = XhColor::red(pixColor);
			pixG = XhColor::green(pixColor);
			pixB = XhColor::blue(pixColor);
			pixA = XhColor::alpha(pixColor);
			// ��ȡ�߿�ͼƬ��RGBAֵ
			layR = XhColor::red(layColor);
			layG = XhColor::green(layColor);
			layB = XhColor::blue(layColor);
			layA = XhColor::alpha(layColor);
			// ��ɫ�봿��ɫ����ĵ�
			if (layR < 20 && layG < 20 && layB < 20) {
				alpha = 1.0F;
			}
			else {
				alpha = 0.3F;
			}
			alphaR = alpha;
			alphaG = alpha;
			alphaB = alpha;
			// ������ɫ����
			newR = (int)(pixR * alphaR + layR * (1 - alphaR));
			newG = (int)(pixG * alphaG + layG * (1 - alphaG));
			newB = (int)(pixB * alphaB + layB * (1 - alphaB));
			layA = (int)(pixA * alpha + layA * (1 - alpha));
			// ֵ��0~255֮��
			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			newA = min(255, max(0, layA));
			// ����
			newColor = XhColor::argb(newA, newR, newG, newB);
			bmpPixel[i*heigth + k] = newColor;
		}
	}
	env->SetIntArrayRegion(bmp,0,bmpLen,bmpPixel);
	return bmp;
}









