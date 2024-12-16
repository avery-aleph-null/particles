#include "Matrices.h"
#include <iostream> 
#include <iomanip>

namespace Matrices
{
   
   Matrix::Matrix(int _rows, int _cols)
   {
     /* rows = _rows;
      cols = _cols;
      a.resize(_rows);
      for (int i = 0; i < a.size(); i++)
      { 
         a[i] = vector<double>(_cols);
         for(int j = 0; j < a[i].size(); j++) { a[i][j] = 0; }
      }
      */
      a = vector<vector<double>>(_rows, vector<double>(_cols, 0));
      rows = _rows;
      cols = _cols;
   }
   ///Add each corresponding element.
   ///usage:  c = a + b;
   Matrix operator+(const Matrix& a, const Matrix& b)
   {
      if(a.getRows() != b.getRows() || a.getCols() != b.getCols()) {throw runtime_error("Error: dimensions must agree");}
      Matrix c(a.getRows(), a.getCols());
      for(int i = 0; i < a.getRows(); i++) 
      { 
         for(int j = 0; j< a.getCols(); j++) {c(i,j) = a(i,j) + b(i,j);}
      }
      return c;
   }   
   
   ///Matrix multiply.  See description.
   ///usage:  c = a * b;
   Matrix operator*(const Matrix& a, const Matrix& b)
   {
      if(a.getCols() != b.getRows()) {throw runtime_error("Error: dimensions must agree");}
      Matrix c(a.getRows(), b.getCols());
      for(int i = 0; i < a.getRows(); i++)
      {
         for(int k = 0; k < b.getCols(); k++)
            {
               c(i,k) = 0;
               for(int j = 0; j < a.getCols(); j++)
               {
                  c(i,k) += a(i,j) * b(j,k);
               }
            }
      }
      return c;
   }
   ///Matrix comparison.  See description.
   ///usage:  a == b
   bool operator==(const Matrix& a, const Matrix& b)
   {
      if(a.getRows() != b.getRows() || a.getCols() != b.getCols()) {return false;}
      for(int i = 0; i < a.getRows(); i++)
      {
         for(int j = 0; j < a.getCols(); j++)
         {
            if(abs(a(i,j) - b(i,j)) >= 0.001) {return false;}
         }
      }
      return true;
   }
   ///Matrix comparison.  See description.
      
   ///usage:  a != b
   bool operator!=(const Matrix& a, const Matrix& b)
   {
      return !(a == b);
   }
   ///Output matrix.
   ///Separate columns by ' ' and rows by '\n'
   ostream& operator<<(ostream& os, const Matrix& a)
   {
      for(int i = 0; i < a.getRows(); i++)
      {
         for(int j = 0; j < a.getCols(); j++)
         {
            os << setw(10) << a(i,j) << ' ';
         }
         os << '\n'; // Add newline after each row
      }
      return os;
   }
}
