// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <cmath>
#define FLOAT 4
#define ROWS_COLS_ERROR "Error: number of rows or columns is Invalid."
#define UN_MUCH_MATRIX "Error: matrix are not at the same size."
#define OUT_OF_RANGE "Error: Index out of rang."
#define FILE_ERROR "Error: File length is invalid"
#define ALLOC_ERROR "Error: Allocation failed!"

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * This class represents a matrix that contains floats.
 */
class Matrix
{
 public:
  /**
   * Constructor - inits matrix with r rows and c cols, inits all elements
   * with zero.
   * @param r - number of rows
   * @param c - number of columns
   */
  Matrix(int r, int c);
  /**
   * Default Ctor - Inits matrix of 1x1, with 0.
   */
  Matrix();
  /**
   *  copy ctor
   * @param other - other matrix to copy from
   */
  Matrix(const Matrix& other);
  /**
   * Destructor - delete the matrix array.
   */
  ~Matrix();
  // getters
  int get_rows() const;
  int get_cols() const;
  /**
   * Transforms a matrix into its transpose matrix.
   * @return reference to this.
   */
  Matrix& transpose();
  /**
   * Transforms a matrix into a column vector.
   * @return reference to this.
   */
  Matrix& vectorize();
  /**
  * Prints matrix elements - Prints space after each element, and new line
  * after each row.
  */
  void plain_print() const;
  /**
   * Returns a matrix which is the dot product of this matrix and another
   * matrix.
   * @return new Matrix object
   */
  Matrix dot(const Matrix& m) const;
  /**
   * Returns the norm of the given matrix
   * @return norm from type of float.
   */
  float norm() const;
  /**
   * add the given matrix to this matrix.
   * @param m - the matrix to add
   * @return new matrix - the sum of both matrix.
   */
  Matrix operator+(const Matrix& m) const;
  /**
   * assignment operator.
   * @param m the matrix to assign to this matrix.
   * @return reference to the matrix.
   */
  Matrix& operator=(const Matrix& m);
  /**
   * duplicate to matrix with the matrix m.
   * @param m the matrix to duplicate with the current matrix.
   * @return new matrix - the result.
   */
  Matrix operator*(const Matrix& m) const;
  /**
   * Scalar multiplication on the right
   * @param c - the scalar
   * @return new matrix
   */
  Matrix operator*(float c) const;
  /**
   * Scalar multiplication on the left
   * @param c - the scalar
   * @param Matrix - the matrix to duplicate
   * @return new matrix
   */
  friend Matrix operator*(float c,const Matrix& m);
  /**
   * add the m matrix to this matrix, and change it
   * @param m - the other matrix.
   * @return this matrix.
   */
  Matrix& operator+=(const Matrix& m);
  /**
   * this method will return the i,j element in the matrix.
   * this is the non - const version.
   * @param i - the row index
   * @param j - the col index
   * @return the item in the i'th row, j'th col.
   */
  float& operator()(int i, int j);
  // the const version of the function above.
  float operator()(int i, int j) const;
  /**
 * this method will return the i'th element in the matrix.
 * this is the non - const version.
 * @param i - the index of the element we return
 * @return the item in the index i in the matrix.
 */
  float& operator[](int i);
  // the const version of the function above.
  float operator[](int i) const;

  /**
   * method that prints the image that the matrix represent.
   * @param s - the output stream
   * @param m - the matrix
   * @return reference to the stream
   */
  friend std::ostream &operator<<(std::ostream &s, const Matrix &m);
  /**
   * Fills matrix elements from binary file
   * @param file_stream - the file
   * @param m - the matrix to read in
   */
  friend std::istream& read_binary_file(std::istream& file_stream, Matrix& m);

 private:
  int _rows, _cols;
  float* _matrix;

};

#endif //MATRIX_H
