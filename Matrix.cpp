#include "Matrix.h"

#define ZERO_DOT_ONE 0.1

/**
 * Constructor - inits matrix with r rows and c cols, inits all elements
 * with zero.
 * @param r - number of rows
 * @param c - number of columns
 */
Matrix::Matrix (int r, int c)
{
  if (r <= 0 || c <= 0)
    {
      std::cerr << ROWS_COLS_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  _rows = r;
  _cols = c;
  _matrix = new(std::nothrow) float[_rows * _cols];
  if (_matrix == nullptr)
    {
      std::cerr << ALLOC_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  for (int i = 0; i < _cols * _rows; i++)
    {
      _matrix[i] = 0;
    }
}


/**
 * Default Ctor - Inits matrix of 1x1, with 0.
 */
Matrix::Matrix () : Matrix (1, 1)
{}

/**
 *  copy ctor
 * @param other - other matrix to copy from
 */
Matrix::Matrix (const Matrix &other)
{
  _rows = other._rows;
  _cols = other._cols;
  _matrix = new(std::nothrow) float[_rows * _cols];
  if (_matrix == nullptr)
    {
      std::cerr << ALLOC_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  for (int i = 0; i < _rows * _cols; i++)
    {
      _matrix[i] = other._matrix[i]; // copy values from the other matrix
    }
}

/**
 * Destructor - delete the matrix array.
 */
Matrix::~Matrix ()
{
  delete[] _matrix;
}

// getters
int Matrix::get_rows () const
{
  return _rows;
}

int Matrix::get_cols () const
{
  return _cols;
}

/**
  * Transforms a matrix into its transpose matrix.
  * @return reference to this.
  */
Matrix &Matrix::transpose ()
{
  // initialize new array for the transpose matrix.
  auto *new_matrix = new(std::nothrow) float[_cols * _rows];
  if (new_matrix == nullptr)
    {
      std::cerr << ALLOC_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  for (int i = 0; i < _cols; i++)
    {
      for (int j = 0; j < _rows; j++)
        {
          // inits the row of original matrix into column of transposed matrix.
          new_matrix[i * _rows + j] = _matrix[j * _cols + i];
        }
    }
  int c = _cols;
  // change the rows to cols, and the cols to rows.
  _cols = _rows;
  _rows = c;
  // delete the oldest matrix.
  delete[] _matrix;
  _matrix = new_matrix;
  return *this;
}

/**
 * Transforms a matrix into a column vector.
 * @return reference to this.
 */
Matrix &Matrix::vectorize ()
{
  int r = _rows;
  int c = _cols;
  _cols = 1;
  _rows = r * c;
  return *this;
}

/**
* Prints matrix elements - Prints space after each element, and new line
* after each row.
*/
void Matrix::plain_print () const
{
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < _cols; j++)
        {
          std::cout << _matrix[i * _cols + j] << " ";
        }
      // add new line after each row.
      std::cout << std::endl;
    }
}

/**
 * Returns a matrix which is the dot product of this matrix and another
 * matrix.
 * @return new Matrix object
 */
Matrix Matrix::dot (const Matrix &m) const
{
  if (_rows != m._rows || _cols != m._cols) // validity check
    {
      std::cerr << UN_MUCH_MATRIX << std::endl;
      exit(EXIT_FAILURE);
    }
  // create new matrix.
  Matrix dot_matrix = Matrix (_rows, _cols);
  for (int i = 0; i < _cols * _rows; i++)
    {
      // multiple each element in this with the relevant element in m.
      dot_matrix._matrix[i] = _matrix[i] * m._matrix[i];
    }
  return dot_matrix;
}

/**
 * Returns the norm of the given matrix
 * @return norm from type of float.
 */
float Matrix::norm () const
{
  float norm = 0;
  for (int i = 0; i < _rows * _cols; i++)
    {
      // multiple each element with itself, and add to the norm.
      norm += _matrix[i] * _matrix[i];
    }
  return sqrtf (norm);
}

/**
 * add the given matrix to this matrix.
 * @param m - the matrix to add
 * @return new matrix - the sum of both matrix.
 */
Matrix Matrix::operator+ (const Matrix &m) const
{
  // create new matrix with the content of this.
  Matrix temp = *this;
  // add m to the new matrix by += operator
  temp += m;
  return temp;
}

/**
 * assignment operator.
 * @param m the matrix to assign to this matrix.
 * @return reference to the matrix.
 */
Matrix &Matrix::operator= (const Matrix &m)
{
  // if m is this, we only return this.
  if (this == &m)
    {
      return *this;
    }
  _rows = m._rows;
  _cols = m._cols;
  // delete the current matrix, and create new in the correct size.
  delete[] _matrix;
  _matrix = new(std::nothrow) float[_rows * _cols];
  if (_matrix == nullptr)
    {
      std::cerr << ALLOC_ERROR << std::endl;
      exit(EXIT_FAILURE);
    }
  // fill the new matrix with m's matrix values.
  for (int i = 0; i < _cols * _rows; i++)
    {
      _matrix[i] = m._matrix[i];
    }
  return *this;
}

/**
 * duplicate to matrix with the matrix m.
 * @param m the matrix to duplicate with the current matrix.
 * @return new matrix - the result.
 */
Matrix Matrix::operator* (const Matrix &m) const
{
  if (_cols != m._rows) // validity check
    {
      std::cerr << UN_MUCH_MATRIX << std::endl;
      exit(EXIT_FAILURE);
    }
  // create new matrix for the result
  Matrix new_matrix = Matrix (_rows, m._cols);
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < m._cols; j++)
        {
          // the sum for each row*col
          float sum = 0;
          for (int l = 0; l < _cols; l++)
            {
              sum += _matrix[i * _cols + l] * m._matrix[l * m._cols + j];
            }
          new_matrix._matrix[i * new_matrix._cols + j] = sum;
        }
    }
  return new_matrix;
}

/**
 * Scalar multiplication on the right
 * @param c - the scalar
 * @return new matrix
 */
Matrix Matrix::operator* (float c) const
{
  // create new matrix
  Matrix new_matrix = Matrix (_rows, _cols);
  // fill the new matrix with the duplicate of every element with the scalar c.
  for (int i = 0; i < _cols * _rows; i++)
    {
      new_matrix._matrix[i] = _matrix[i] * c;
    }
  return new_matrix;
}

/**
 * Scalar multiplication on the left
 * @param c - the scalar
 * @param Matrix - the matrix to duplicate
 * @return new matrix
 */
Matrix operator* (float c, const Matrix &m)
{
  // using operator * of matrix.
  return m * c;
}

/**
 * add the m matrix to this matrix, and change it
 * @param m - the other matrix.
 * @return this matrix.
 */
Matrix &Matrix::operator+= (const Matrix &m)
{
  if (_rows != m._rows || _cols != m._cols) // validity check
    {
      std::cerr << UN_MUCH_MATRIX << std::endl;
      exit(EXIT_FAILURE);
    }
  for (int i = 0; i < _cols * _rows; i++)
    {
      _matrix[i] += m._matrix[i];
    }
  return *this;
}

/**
 * this method will return the i,j element in the matrix.
 * this is the non - const version.
 * @param i - the row index
 * @param j - the col index
 * @return the item in the i'th row, j'th col.
 */
float &Matrix::operator() (int i, int j)
{
  if (i < 0 || i >= _rows || j < 0 || j >= _cols)
    {
      std::cerr << OUT_OF_RANGE << std::endl;
      exit(EXIT_FAILURE);
    }
  return _matrix[i * _cols + j];
}

// the const version of the function above.
float Matrix::operator() (int i, int j) const
{
  if (i < 0 || i >= _rows || j < 0 || j >= _cols)
    {
      std::cerr << OUT_OF_RANGE << std::endl;
      exit(EXIT_FAILURE);
    }
  return _matrix[i * _cols + j];
}

/**
* this method will return the i'th element in the matrix.
* this is the non - const version.
* @param i - the index of the element we return
* @return the item in the index i in the matrix.
*/
float &Matrix::operator[] (int i)
{
  if (i<0 || i >= _cols*_rows)
    {
      std::cerr << OUT_OF_RANGE << std::endl;
      exit(EXIT_FAILURE);
    }
  return _matrix[i];
}

// the const version of the function above.
float Matrix::operator[] (int i) const
{
  if (i<0 || i >= _cols*_rows)
    {
      std::cerr << OUT_OF_RANGE << std::endl;
      exit(EXIT_FAILURE);
    }
  return _matrix[i];
}

/**
 * method that prints the image that the matrix represent.
 * @param s - the output stream
 * @param m - the matrix
 * @return reference to the stream
 */
std::ostream &operator<< (std::ostream &s, const Matrix &m)
{
  for (int i = 0; i < m._rows; i++)
    {
      for (int j = 0; j < m._cols; j++)
        {
          if (m (i, j) >= ZERO_DOT_ONE) // prints double space in full cell
            {
              s << "  ";
            }
          else  // prints double * in empty cell
            {
              s << "**";
            }
        }
      s << std::endl;
    }
  return s;
}

/**
  * Fills matrix elements from binary file. if not all expected bytes was read,
  * or the file does not contain enough bytes to read, exit with code 1.
  * @param file_stream - the file
  * @param m - the matrix to read in
  */
std::istream& read_binary_file(std::istream& my_file, Matrix& m)
{
  if (!my_file.good())
    {
      std::cerr << FILE_ERROR << std::endl;
      exit (EXIT_FAILURE);
    }
  int size = m._rows * m._cols * FLOAT; // number of values we need to read
  my_file.seekg(0, my_file.end); // go to end of file
  if(my_file.tellg() < size) // tell how many bytes since beginning of file
    {
      std::cerr << FILE_ERROR << std::endl;
      exit (EXIT_FAILURE);
    }
  my_file.seekg(0, std::ios_base::beg); // go to beginning of file
  my_file.read((char*) m._matrix, size);
  if (!my_file)
    {
      std::cerr << FILE_ERROR << std::endl;
      exit (EXIT_FAILURE);
    }
  return my_file;
}





