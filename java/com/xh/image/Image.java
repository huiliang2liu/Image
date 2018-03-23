package com.xh.image;

import android.graphics.Bitmap;

/**
 * @author xh E-mail:825378291@qq.com
 * @version 创建时间：2017-2-28 上午9:24:22
 * 
 */
public class Image {
	static {
		System.loadLibrary("SharedObject5");
	}

	public native static int test(String[] tag);

	/**
	 * 旋转270度 author:xh email:825378291@qq.com time:2017-2-27 上午10:27:28
	 * 
	 * @param matrix
	 * @return
	 */
	public native static int[] rotate270(int[] matrix, int heigth);

	/**
	 * 旋转270度
	 * 
	 * @param bitmap
	 * @return
	 */
	public static Bitmap rotate270(Bitmap bitmap) {
		if (bitmap == null)
			return null;
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		int[] pixels = bitmap2pixels(bitmap);
		return pixels2bitmap(rotate270(pixels, heigth), width, heigth);
	}

	/**
	 * 旋转90度 author:xh email:825378291@qq.com time:2017-2-27 上午11:03:13
	 */
	public native static int[] rotate90(int matrix[], int heigth);

	/**
	 * 旋转90度
	 * 
	 * @param bitmap
	 * @return
	 */
	public static Bitmap rotate90(Bitmap bitmap) {
		if (bitmap == null)
			return null;
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		int[] pixels = bitmap2pixels(bitmap);
		return pixels2bitmap(rotate90(pixels, heigth), width, heigth);
	}

	/**
	 * 矩阵照镜子 author:xh email:825378291@qq.com time:2017-2-27 上午11:13:20
	 * 
	 * @param matrix
	 * @return
	 */
//	public native static int[] look_mirror(int[] matrix, int heigth);

	/**
	 * 照镜子
	 * 
	 * @param bitmap
	 * @return
	 */
//	public static Bitmap look_mirror(Bitmap bitmap) {
//		if (bitmap == null)
//			return null;
//		int heigth = bitmap.getHeight();
//		int width = bitmap.getWidth();
//		int[] pixels = bitmap2pixels(bitmap);
//		return pixels2bitmap(look_mirror(pixels, heigth), heigth, width);
//	}

	/**
	 * 旋转180度 author:xh email:825378291@qq.com time:2017-2-27 上午10:06:16
	 * 
	 * @param matrix
	 * @return
	 */
	public native static int[] rotate180(int[] matrix, int heigth);

	/**
	 * 旋转180度
	 * 
	 * @param bitmap
	 * @return
	 */
	public static Bitmap rotate180(Bitmap bitmap) {
		if (bitmap == null)
			return null;
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		int[] pixels = bitmap2pixels(bitmap);
		return pixels2bitmap(rotate180(pixels, heigth), heigth, width);
	}

	/**
	 * 截取数据 author:xh email:825378291@qq.com time:2017-2-27 下午09:16:30
	 * 
	 * @param matrix
	 * @param start_x
	 * @param start_y
	 * @param end_x
	 * @param end_y
	 * @return
	 */
	public native static int[] interception(int[] matrix, int start_x,
			int start_y, int end_x, int end_y, int heigth);

	/**
	 * 截取图片
	 * 
	 * @param bitmap
	 * @param start_x
	 * @param start_y
	 * @param end_x
	 * @param end_y
	 * @return
	 */
	public static Bitmap interception(Bitmap bitmap, int start_x, int start_y,
			int end_x, int end_y) {
		if (bitmap == null)
			return null;
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		start_x = start_x < 0 ? 0 : start_x;
		start_y = start_y < 0 ? 0 : start_y;
		end_y = end_y > heigth ? heigth : end_y;
		end_x = end_x > width ? width : end_x;
		int[] pixels = bitmap2pixels(bitmap);
		return pixels2bitmap(
				interception(pixels, start_x, start_y, end_x, end_y, heigth),
				end_y - start_y, end_x - start_x);
	}

	/**
	 * 1维数组2维遍历 author:xh email:825378291@qq.com time:2017-2-27 下午02:17:46
	 * 
	 * @param matrix
	 * @param heigth
	 */
	public static void traverse(int[] matrix, int heigth) {
		if (matrix == null || matrix.length == 0)
			System.out.println("an empty array");
		int wigth = matrix.length / heigth;
		for (int x = 0; x < heigth; x++) {
			for (int y = 0; y < wigth; y++) {
				System.out.print(matrix[wigth * x + y] + "\t");
			}
			System.out.println();
		}

	}

	/**
	 * bitmap转化位int数组
	 * 
	 * @param bitmap
	 * @param heigth
	 * @param width
	 * @return
	 */
	public static int[] bitmap2pixels(Bitmap bitmap) {
		if (bitmap == null)
			return null;
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		int[] pixels = new int[heigth * width];
		bitmap.getPixels(pixels, 0, width, 0, 0, width, heigth);
		return pixels;
	}

	/**
	 * int数组转化位bitmap
	 * 
	 * @param pixels
	 * @param heigth
	 * @param width
	 * @return
	 */
	public static Bitmap pixels2bitmap(int[] pixels, int heigth, int width) {
		if (pixels == null)
			return null;
		if (pixels.length < heigth * width)
			return null;
		Bitmap output = Bitmap.createBitmap(width, heigth,
				Bitmap.Config.ARGB_8888);
		output.setPixels(pixels, 0, width, 0, 0, width, heigth);
		return output;
	}

	/**
	 * 矩阵照镜子 author:xh email:825378291@qq.com time:2017-2-27 上午11:13:20
	 * 
	 * @param matrix
	 * @return
	 */
//	public native static int[] look_mirrorX(int[] matrix, int heigth);
//
//	public static Bitmap look_mirrorX(Bitmap bitmap) {
//		int[] pixels = bitmap2pixels(bitmap);
//		int heigth = bitmap.getHeight();
//		int width = bitmap.getWidth();
//		return pixels2bitmap(look_mirrorX(pixels, heigth), heigth, width);
//	}

	/**
	 * 怀旧处理
	 * 
	 * @param bmp
	 * @return
	 */
	public native static int[] nostalgia(int[] matrix, int heigth);

	public static Bitmap nostalgia(Bitmap bitmap) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		return pixels2bitmap(nostalgia(pixels, heigth), heigth, width);
	}

	/**
	 * 浮雕处理
	 * 
	 * @param bmp
	 * @return
	 */
	public native static int[] relief(int[] matrix, int heigth);

	public static Bitmap relief(Bitmap bitmap) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		return pixels2bitmap(relief(pixels, heigth), heigth, width);
	}

	/**
	 * 模糊处理
	 * 
	 * @param bmp
	 * @return
	 */
	public native static int[] fuzzy(int[] matrix, int heigth);

	public static Bitmap fuzzy(Bitmap bitmap) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		return pixels2bitmap(fuzzy(pixels, heigth), heigth, width);
	}

	/**
	 * 光照效果
	 * 
	 * @param bmp
	 * @return
	 */
	public native static int[] sunshine(int[] matrix, int heigth, int c_x,
			int c_y);

	public static Bitmap sunshine(Bitmap bitmap) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		return pixels2bitmap(sunshine(pixels, heigth, width >> 1, heigth >> 1),
				heigth, width);
	}

	/**
	 * 锐化处理
	 * 
	 * @param bmp
	 * @return
	 */
	public native static int[] sharpen(int[] matrix, int heigth);

	public static Bitmap sharpen(Bitmap bitmap) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		return pixels2bitmap(sharpen(pixels, heigth), heigth, width);
	}

	/**
	 * 冰冻处理
	 * 
	 * @param bmp
	 * @return
	 */
	public native static int[] ice(int[] matrix, int heigth);

	public static Bitmap ice(Bitmap bitmap) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		return pixels2bitmap(ice(pixels, heigth), heigth, width);
	}

	/**
	 * 素描处理
	 * 
	 * @param bmp
	 * @return
	 */
	public native static int[] sketch(int[] matrix, int heigth);

	public static Bitmap sketch(Bitmap bitmap) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		return pixels2bitmap(sketch(pixels, heigth), heigth, width);
	}

	/**
	 * 图片合成
	 * 
	 * @param frameBitmap
	 * @param bmp
	 * @return
	 */
	public native static int[] addFrameToImageTwo(int[] matrix, int heigth,
			int[] matrix1, int heigth1);

	public static Bitmap addFrameToImageTwo(Bitmap bitmap, Bitmap bitmap1) {
		int[] pixels = bitmap2pixels(bitmap);
		int heigth = bitmap.getHeight();
		int width = bitmap.getWidth();
		int[] pixels1 = bitmap2pixels(bitmap1);
		int heigth1 = bitmap1.getHeight();
		int width1 = bitmap1.getWidth();
		return pixels2bitmap(
				addFrameToImageTwo(pixels, heigth, pixels1, heigth1), heigth,
				width);
	}
}
