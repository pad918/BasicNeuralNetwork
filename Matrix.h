#pragma once
#include <array>

namespace mtx {

	class Matrix {
	private:
		int columes;
		int rows;
		int totalSize;
		float *matrixValues;
		float **mVals;
	public:
		Matrix(int colsInMatrix, int rowsInMatrix);
		Matrix();
		void set(float *matrix);
		void printMatrixValues();
		friend Matrix operator * (Matrix const &a, Matrix const &b);
	};

}