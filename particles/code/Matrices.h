#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace Matrices {
class Matrix {
public:

  Matrix(int _rows, int _cols);

  const double &operator()(int i, int j) const { return a.at(i).at(j); }

  double &operator()(int i, int j) {
    // return a[i][j];
    return a.at(i).at(j);
  }

  int getRows() const { return rows; }
  int getCols() const { return cols; }

private:
  vector<vector<double>> a;
  int rows;
  int cols;
};

Matrix operator+(const Matrix &a, const Matrix &b);
Matrix operator*(const Matrix &a, const Matrix &b);
bool operator==(const Matrix &a, const Matrix &b);
bool operator!=(const Matrix &a, const Matrix &b);
ostream &operator<<(ostream &os, const Matrix &a);


class RotationMatrix : public Matrix
{
public:
  RotationMatrix(double theta) : Matrix(2, 2)
  {
    (*this)(0, 0) = cos(theta);
    (*this)(0, 1) = -sin(theta);
    (*this)(1, 0) = sin(theta);
    (*this)(1, 1) = cos(theta);
  }
};

// Derived class for 2D scaling matrix
class ScalingMatrix : public Matrix
{
public:
  ScalingMatrix(double scale) : Matrix(2, 2)
  {
    (*this)(0, 0) = scale;
    (*this)(0, 1) = 0;
    (*this)(1, 0) = 0;
    (*this)(1, 1) = scale;
  }
};

// Derived class for 2D translation matrix
class TranslationMatrix : public Matrix
{
public:
  TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
  {
    for (int i = 0; i < nCols; ++i)
    {
      (*this)(0, i) = xShift;
      (*this)(1, i) = yShift;
    }
  }
};

} // namespace Matrices

#endif // MATRIX_H_INCLUDED