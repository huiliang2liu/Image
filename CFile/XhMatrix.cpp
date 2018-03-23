#include "XhMatrix.h"

XhMatrix::XhMatrix()
{
}


XhMatrix::~XhMatrix()
{
}
int*  XhMatrix::rotate270(int * matrix, int width, int heigth)
{
	int matrix_[width*heigth];
	for (int y = 0; y < heigth; y++) {
		for (int x = 0; x < width; x++) {
			matrix_[(width - 1 - x) * heigth + y] = matrix[width * y + x];
		}
	}
	return matrix_;
}

int*  XhMatrix::rotate90(int *matrix, int width, int heigth)
{
	int matrix_[width*heigth];
	for (int y = 0; y < heigth; y++) {
		for (int x = 0; x < width; x++) {
			matrix_[heigth * x + (heigth - 1 - y)]
				= matrix[width * y + x];
		}
	}
	return matrix_;
}

int*  XhMatrix::rotate180(int *matrix, int width, int heigth)
{
	int matrix_[width*heigth];
	int width_2 = (width >> 1) + 1;
	for (int x = 0; x < width_2; x++) {
		for (int y = 0; y < heigth; y++) {
			int x_ = (width - 1) - x;
			matrix_[width * y + x] = matrix[width * y + x_];
			matrix_[width * y + x_] = matrix[width * y + x];
		}
	}
	return matrix_;
}

int*  XhMatrix::interception(int *matrix, int width, int heigth, int start_x, int end_x, int start_y, int end_y)
{
	int heigth_ = end_y - start_y;
	int width_ = end_x - start_x;
	int len_ = heigth_ * width_;
	int matrix_[len_];
	for (int y = start_y; y < end_y; y++) {
		for (int x = start_x; x < end_x; x++) {
			matrix_[(y - start_y) * (width_)+(x - start_x)] = matrix[y * width
				+ x];
		}
	}
	return matrix_;
}

int*  XhMatrix::symmetry_y(int *matrix, int width, int heigth)
{
	int matrix_[width*heigth];
	int width_2 = (width >> 1) + 1;
	for (int x = 0; x < width_2; x++) {
		for (int y = 0; y < heigth; y++) {
			int x_ = (width - 1) - x;
			matrix_[width * y + x] = matrix[width * y + x_];
			matrix_[width * y + x_] = matrix[width * y + x];
		}
	}
	return matrix_;
}
int* XhMatrix::symmetry_x(int *matrix, int width, int heigth)
{
	int matrix_[width*heigth];
	int width_2 = (heigth >> 1) + 1;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < width_2; y++) {
			int x_ = (width - 1) - x;
			matrix_[width * y + x] = matrix[width * y + x_];
			matrix_[width * y + x_] = matrix[width * y + x];
		}
	}
	return matrix_;
}
