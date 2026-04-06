

#include "Matrix.h"
 #include <sstream>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
//for std::cout
using namespace std;
#define __EPSILON 0.0000000001 
//Need this to compare doubles because representation.
//Quick function that returns if two doubles are very similar to each other.

/*
We will represent the data inside our Matrix class by using a two-dimensional array.
 Because a matrix may be any size, you will need to use dynamic memory for this task. 
*/

//from matrix main
bool double_compare(double a, double b);

Matrix::Matrix( unsigned theRows,  unsigned theCols, double theFill)
{
  rows = theRows; 
  cols = theCols; 
  fill = theFill;
  if (rows == 0 || cols == 0)
  {
    rows = 0;
    cols = 0;
    matrix = nullptr;
  }
  else
  {
    matrix = new double*[rows];
        for (unsigned int i = 0; i < rows; i++) 
        {
            matrix[i] = new double[cols];
            for (unsigned int c = 0; c < cols; c++)
            {
              matrix[i][c] = fill;
            }
        }
  }
}

Matrix::Matrix( const Matrix& other)
{
  //copy constructo r
if (other.rows == 0 || other.cols == 0) 
{
  rows = 0; 
  cols = 0;
  fill = 0;
  matrix = nullptr;
  return;
 }
  rows = other.rows;
  cols = other.cols;
  matrix = new double*[rows];
  for (unsigned int i = 0; i < rows; i ++)
  {
    matrix[i] = new double[cols];
    for (unsigned int c = 0; c < cols; c++)
    {
      matrix[i][c] = other.matrix[i][c];
    }
  }
  fill = other.fill;
}
Matrix::Matrix()
{
  rows = 0;
  cols = 0;
  matrix = nullptr;
  fill = 0.0;
}

 unsigned int Matrix::num_rows()  const
{
  return rows;
}

 unsigned int Matrix:: num_cols() const
{
  return cols;
}

bool Matrix::operator==(const Matrix& other) const
 {
    if (rows != other.rows || cols != other.cols)
    {
        return false;
    }
    for (unsigned int r = 0; r < rows; r++)
    {
        for (unsigned int c = 0; c < cols; c++)
        {
            if (!double_compare(matrix[r][c], other.matrix[r][c]))
            {
                return false;
            }
        }
    }
    return true;
}


bool Matrix::operator!=(const Matrix& other) const
{
  if (other == *this)
  {
    return false;
  }
  return true;
}


//destructor 
Matrix::~Matrix()
{
    if (matrix != nullptr)
    {
        for (unsigned int i = 0; i < rows; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    rows = 0;
    cols = 0;
    matrix = nullptr;
}


//printing 
std::ostream& operator<< (std::ostream& out,  const Matrix& m)
{
  string output = "";
  output += to_string(m.rows) + "x" + to_string(m.cols) + "matrix:\n[ ";
  for (unsigned int r = 0; r < m.rows; r++)
  {
    for (unsigned int c = 0; c < m.cols; c++)
    {
      output += to_string(m.matrix[r][c]);
      output += " " ;
    }
    if (r != m.rows -1)
    {
    output += "\n";

    }
    else
    {
      output += "]";
    }
  }
  out<<output;
  return out;
}

/*
 We may want to change a previously filled matrix to an empty one,
  so you must write a clear() method as well. 
  This method should reset the number of rows and columns to 0, 
  and deallocate any memory currently held by the Matrix.

*/
void Matrix::clear() 
{
    if (matrix != nullptr)
     {
        for ( unsigned int r = 0; r < rows; r++) 
        {
            delete[] matrix[r];
        }
        delete[] matrix;
    }
    //clearing 
    rows = 0;
    cols = 0;
    matrix = nullptr;
}
/*
Naturally we want to be able to access data stored in the Matrix class.
To do so we will implement a “safe” accessor called get(), 
which takes in a row, a column, and a double. If the row and column 
are within the bounds of the matrix, then the value at arow,col should
 be stored in the double, and the function should return true.
  Otherwise the function should return false.


*/
bool Matrix::get( unsigned int theRow,  unsigned int theCol, double &theVal)
{
  if (theRow < rows && theCol < cols)
  {
    theVal = matrix[theRow][theCol];
    return true;
  }
  return false;
}
/*
A complementary, but similar task to accessing data is to be able to set a value at 
a particular position in the matrix. This is done through a safe modifier called set(). 
This function also takes in a row, column, and a double value. set() returns
 false if the position is out of bounds, and true if the position is valid.
  If the position is valid, the function should also set arow,col to the 
  value of the double that was passed in.


*/
bool Matrix::set( unsigned int theRow,  unsigned int theCol, double theVal)
{
  if (theRow < rows && theCol < cols)
  {
    matrix[theRow][theCol] = theVal;
    return true;
  }

  return false;
}

/*
To start with, we introduce some basic matrix operations. 
The first is the method multiply by coefficient(), 
which takes a double called a coefficient. The method should
 multiply every element in the matrix by the coefficient. For example:*/

void Matrix::multiply_by_coefficient(double co)
{
  for (unsigned int i  = 0; i < rows; i++)
  {
    for (unsigned int c = 0; c < cols; c++)
    {
      matrix[i][c] = co * matrix[i][c];
    }
  }
}


/*
Another common operation is to swap two rows of a matrix. 
This will be accomplished by the method swap row(), 
which takes two arguments of type unsigned int: a 
source row number and a target row number. If both
 rows are inside the bounds of the matrix, then the 
 function should switch the values in the two rows and
  return true. Otherwise the function should return false. 

*/


bool Matrix::swap_row( unsigned int row1,  unsigned int row2)
{
  if (row1 < rows && row2 < rows)
  {
    double* temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp; 
    return true;
  }
  return false;
}


/*
It is common to need to “flip” a matrix, a process called transposition. 
You will need to write the transpose() method, which has a return type
 of void. Formally, transposition of m×n matrix A into n×m matrix AT is defined as:

*/

void Matrix::transpose()
{

  //rows become columns and vice versa
  double** newMatrix = new double*[cols];
  for (unsigned int i = 0; i < cols; i++ )
  {
    newMatrix[i] = new double[rows];
  }
  for (unsigned int c = 0; c<cols; c++)
  {
    for (unsigned int r = 0; r < rows; r++)
    {
      newMatrix[c][r] = matrix[r][c];
    }
  }

  // delete old matrix
  for ( unsigned int i = 0; i < rows; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
  matrix = newMatrix; 
  int temp = rows; 
  rows = cols;
  cols = temp; 
}




/*

 Matrix object will always be the “left-hand” matrix, A. 
 You will be required to implement both add() and subtract(). 
 Both functions take in just one argument, a second Matrix which we will refer to as B, 
 and modify A if the dimensions of A and B match. If the dimensions match, 
 the functions should return true, otherwise they should return false. 
 Addition of two matrices, C = A + B, and subtraction of two matrices, D = A − B 

*/
bool Matrix::add( const Matrix& other)
{
  if (other.rows != rows)
  {
    return false;
  }
  if (other.cols != cols)
  {
    return false;
  }
  for ( unsigned int r = 0; r < rows; r++)
  {
    for ( unsigned int c = 0; c < cols; c++)
    {
      matrix[r][c] += other.matrix[r][c];
    }
  }
  return true;


  

}

bool Matrix::subtract(const Matrix& other)
{
    if (other.rows != rows)
  {
    return false;
  }
  if (other.cols != cols)
  {
    return false;
  }
  for (unsigned int r = 0; r < rows; r++)
  {
    for (unsigned int c = 0; c < cols; c++)
    {
      matrix[r][c] -= other.matrix[r][c];
    }
  }
  return true;

}

/*
To fix this, you will implement two more accessors, get_row() and get_col(). 
Both functions take one unsigned int and return a double*. For get_row() 
the argument is the number of row to retrieve, while for get_col() the 
argument is the number of the column to retrieve. If the requested row/column 
is outside of the matrix bounds, the method should return a pointer set to NULL.
*/

double* Matrix::get_row(unsigned int row)
{
    if (row >= rows)
        return nullptr;

    double* theReturn = new double[cols];
    for (unsigned int i = 0; i < cols; i++)
        theReturn[i] = matrix[row][i];

    return theReturn;
}


double* Matrix::get_col( unsigned int col) 
{
    if (col >= cols)
    {
      return nullptr; // out of bounds
    } 

    // allocate  new array for the column

    double* theReturn = new double[rows];

    for (unsigned int r = 0; r < rows; r++)
    {
        theReturn[r] = matrix[r][col]; 
        
        // copy each element
    }
    return theReturn;
}

/*
The final method we expect you to implement, quarter(), is not a traditional 
 matrix operation. The method takes no arguments and returns a Matrix* containing 
 four new Matrix elements in order: an Upper Left (UL) quadrant, an Upper Right 
 (UR) quadrant, a Lower Left (LL) quadrant, and finally a Lower Right (LR) quadrant.
  All four quadrants should be the same size. Remember that when a function ends all
   local variables go out of scope and are destroyed, so you will need to be
    particularly careful about how you construct and return the quadrants.

*/




Matrix& Matrix::operator=( const Matrix& other)
{
    if (this == &other)
    {
        return *this;
    }

    // free  memory
    if (matrix != nullptr)
     {
        for (unsigned int i = 0; i < rows; i++)
            {
              delete[] matrix[i];
            }
        delete[] matrix;
    }

    rows = other.rows;
    cols = other.cols;
    fill = other.fill;

    if (rows == 0 || cols == 0) 
    {
        matrix = nullptr;
        return *this;
    }

    // allcate new memory
    matrix = new double*[rows];
    for (unsigned int i = 0; i < rows; i++) 
    {
        matrix[i] = new double[cols];
        for (unsigned int c = 0; c < cols; c++)
            {
              matrix[i][c] = other.matrix[i][c];
            }
    }
    return *this;
}

Matrix* Matrix::quarter()
{
  //if not enough rows or cols 

    if (rows < 2 || cols < 2)
        return nullptr;

    //half of the size of rows 

    unsigned int newRows = rows / 2;
    unsigned int newCols = cols / 2;
    
    //in case of odd 

    unsigned int quadRows = rows - newRows;
    unsigned int quadCols = cols - newCols;

    Matrix* quadrants = new Matrix[4];

    quadrants[0] = Matrix(quadRows, quadCols, 0.0); // UL
    quadrants[1] = Matrix(quadRows, quadCols, 0.0); // UR
    quadrants[2] = Matrix(quadRows, quadCols, 0.0); // LL
    quadrants[3] = Matrix(quadRows, quadCols, 0.0); // LR

    for (unsigned int i = 0; i < quadRows; i++)
    {
        for (unsigned int c = 0; c < quadCols; c++)
        {
          //each quadrant 
          //upper left
            quadrants[0].matrix[i][c] = matrix[i][c];
          //upper right 
            quadrants[1].matrix[i][c] = matrix[i][c + newCols];
          //lower left
            quadrants[2].matrix[i][c] = matrix[i + newRows][c];
          //lower right 
            quadrants[3].matrix[i][c] = matrix[i + newRows][c + newCols];
        }
    }
    return quadrants;
}
