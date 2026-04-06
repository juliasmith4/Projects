#ifndef MATRIX_H
#define MATRIX_H 
 
 #include <sstream>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>


class Matrix 
{
private: 
//rows, cols, matrix, fill are private variables
         unsigned rows;
         unsigned cols; 
        double **matrix;
        double fill;
           

 public:
    Matrix( unsigned int theRows, unsigned int theCols, double theFill);

Matrix(const Matrix& other);
Matrix();
unsigned int num_rows() const;
unsigned int num_cols()const ;

bool operator== (const Matrix& other) const ;

bool operator!= (const Matrix& other) const ;

~Matrix();
friend std::ostream& operator<< (std::ostream& out,  const Matrix& m);  







 
void clear();
bool get( unsigned int theRow,  unsigned int theCol, double &theVal);
bool set( unsigned int theRow,  unsigned int theCol, double theVal);
void multiply_by_coefficient(double co);
bool swap_row( unsigned int row1,  unsigned int row2);
void transpose();
bool add( const Matrix& other);
bool subtract( const Matrix& other);

double* get_row( unsigned int row) ;
double* get_col( unsigned int col) ;




Matrix& operator=(const Matrix& other);

Matrix* quarter();


    

    




}  ; 

#endif

