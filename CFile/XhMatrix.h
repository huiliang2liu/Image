#pragma once
class XhMatrix
{
public:
	XhMatrix();
	~XhMatrix();
	/*旋转270度，第一个参数是要旋转的矩阵,第二个参数是矩阵宽度，第三个参数是矩阵的高度*/
	static int*  rotate270(int*, int, int);
	/*旋转90度，第一个参数是要旋转的矩阵,第二个参数是矩阵宽度，第三个参数是矩阵的高度*/
	static int*  rotate90(int*, int, int);
	/*旋转180度，第一个参数是要旋转的矩阵,第二个参数是矩阵宽度，第三个参数是矩阵的高度*/
	static int*  rotate180(int *, int, int);
	/*截取，第一个参数是要旋转的矩阵,第二个参数是矩阵宽度，第三个参数是矩阵的高度，第四个参数是截取宽度开始位置，第五个参数是截取高度开始位置，第六个参数是截取宽度结束位置，第七个参数是截取高度结束位置*/
	static int*  interception(int *, int, int, int, int, int, int);
	/*关于y轴对称,第二个参数是矩阵宽度，第三个参数是矩阵的高度*/
	static int*  symmetry_y(int*, int, int);
	/*关于x轴对称,第二个参数是矩阵宽度，第三个参数是矩阵的高度*/
	static int*  symmetry_x(int*, int, int);
};

