#include "Matrix.h"
#include <iostream>

mtx::Matrix::Matrix(int colsInMatrix, int rowsInMatrix)
{
	totalSize = colsInMatrix * rowsInMatrix;
	columes = colsInMatrix;
	rows = rowsInMatrix;
}

mtx::Matrix::Matrix()
{

}

void mtx::Matrix::set(float *matrix)
{
	matrixValues = matrix;
}

void mtx::Matrix::printMatrixValues()
{
	int rows = totalSize / columes;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columes; c++) {
			std::cout << matrixValues[r*columes + c] << " ";
		}
		std::cout << "\n";
	}
}


mtx::Matrix mtx::operator*(Matrix const & a, Matrix const & b)
{
	
	if (a.columes != b.rows) { std::cout << "Error: cannot multiply th vectors\n"; return Matrix(1,1); }
	int cols = b.columes;
	int rows = a.rows;
	float * vals = new float[cols*rows];
	memset(vals, 0, sizeof(vals)*cols*rows);
	for (int c = 0; c < cols; c++) {
		for (int r = 0; r < rows; r++) {
			for(int i=0; i < a.columes; i++)
				vals[c*cols + r] += a.matrixValues[r*a.columes + i] * b.matrixValues[c + cols*i];
		}
	}
	Matrix matricProduct(cols, cols*rows);
	matricProduct.set(vals);
	return matricProduct;
}
