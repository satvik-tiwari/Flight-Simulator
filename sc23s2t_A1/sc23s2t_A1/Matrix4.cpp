//////////////////////////////////////////////////////////////////////
//
//  University of Leeds
//  COMP 5812M Foundations of Modelling & Rendering
//  User Interface for Coursework
//
//  September, 2020
//
//  ------------------------
//  Matrix4.h
//  ------------------------
//  
//  A minimal class for a homogeneous 4x4 matrix
//  
//  Note: the emphasis here is on clarity, not efficiency
//  A number of the routines could be implemented more
//  efficiently but aren't
//  
///////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include "Matrix4.h"
#include <math.h>

// constructor - default to the zero matrix
Matrix4::Matrix4()
    { // default constructor
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            coordinates[row][col] = 0.0;
    } // default constructor

// equality operator
bool Matrix4::operator ==(const Matrix4 &other) const
    { // operator ==()
    // loop through, testing for mismatches
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            if (coordinates[row][col] != other.coordinates[row][col])
                return false;
    // if no mismatches, matrices are the same
    return true;
    } // operator ==()


// indexing - retrieves the beginning of a line
// array indexing will then retrieve an element
float * Matrix4::operator [](const int rowIndex)
    { // operator *()
    // return the corresponding row
    return coordinates[rowIndex];
    } // operator *()

// similar routine for const pointers
const float * Matrix4::operator [](const int rowIndex) const
    { // operator *()
    // return the corresponding row
    return coordinates[rowIndex];
    } // operator *()

// scalar operations
// multiplication operator (no division operator)
Matrix4 Matrix4::operator *(float factor) const
    { // operator *()
    // start with a zero matrix
    Matrix4 returnMatrix;
    // multiply by the factor
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            returnMatrix.coordinates[row][col] = coordinates[row][col] * factor;
    // and return it
    return returnMatrix;
    } // operator *()

// vector operations on homogeneous coordinates
// multiplication is the only operator we use
Homogeneous4 Matrix4::operator *(const Homogeneous4 &vector) const
    { // operator *()
    // get a zero-initialised vector
    Homogeneous4 productVector;
    
    // now loop, adding products
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            productVector[row] += coordinates[row][col] * vector[col];
    
    // return the result
    return productVector;
    } // operator *()

// and on Cartesian coordinates
Cartesian3 Matrix4::operator *(const Cartesian3 &vector) const
    { // cartesian multiplication
    // convert to Homogeneous coords and multiply
    Homogeneous4 productVector = (*this) * Homogeneous4(vector);

    // then divide back through
    return productVector.Point();
    } // cartesian multiplication

// matrix operations
// addition operator
Matrix4 Matrix4::operator +(const Matrix4 &other) const
    { // operator +()
    // start with a zero matrix
    Matrix4 sumMatrix;
    
    // now loop, adding products
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            sumMatrix.coordinates[row][col] = coordinates[row][col] + other.coordinates[row][col];

    // return the result
    return sumMatrix;
    } // operator +()

// subtraction operator
Matrix4 Matrix4::operator -(const Matrix4 &other) const
    { // operator -()
    // start with a zero matrix
    Matrix4 differenceMatrix;
    
    // now loop, adding products
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            differenceMatrix.coordinates[row][col] = coordinates[row][col] + other.coordinates[row][col];

    // return the result
    return differenceMatrix;
    } // operator -()

// multiplication operator
Matrix4 Matrix4::operator *(const Matrix4 &other) const
    { // operator *()
    // start with a zero matrix
    Matrix4 productMatrix;
    
    // now loop, adding products
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            for (int entry = 0; entry < 4; entry++)
                productMatrix.coordinates[row][col] += coordinates[row][entry] * other.coordinates[entry][col];

    // return the result
    return productMatrix;
    } // operator *()

// matrix transpose
Matrix4 Matrix4::transpose() const
    { // transpose()
    // start with a zero matrix
    Matrix4 transposeMatrix;
    
    // now loop, adding products
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            transposeMatrix.coordinates[row][col] = coordinates[col][row];

    // return the result
    return transposeMatrix;
    } // transpose()

// returns a column-major array of 16 values
// for use with OpenGL
columnMajorMatrix Matrix4::columnMajor() const
    { // columnMajor()
    // start off with an unitialised array
    columnMajorMatrix returnArray;
    // loop to fill in
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            returnArray.coordinates[4 * col + row] = coordinates[row][col];
    // now return the array
    return returnArray;
    } // columnMajor()

// routine that returns a row vector as a Homogeneous4
Homogeneous4 Matrix4::row(int rowNum)
	{ // row()
	// temporary variable
	Homogeneous4 returnValue;
	// loop to copy
	for (int column = 0; column < 4; column++)
		returnValue[column] = (*this)[rowNum][column];
	// and return it
	return returnValue;	
	} // row()

// and similar for a column
Homogeneous4 Matrix4::column(int colNum)
	{ // column()
	// temporary variable
	Homogeneous4 returnValue;
	// loop to copy
	for (int row = 0; row < 4; row++)
		returnValue[row] = (*this)[row][colNum];
	// and return it
	return returnValue;	
	} // column()

// static member functions that create specific matrices
// the zero matrix
Matrix4 Matrix4::Zero()
    { // Zero()
    // create a temporary matrix - constructor will automatically zero it
    Matrix4 returnMatrix;
	// so we just return it
	return returnMatrix;
    } // Zero()

// the identity matrix
Matrix4 Matrix4::Identity()
    { // Identity()
    // create a temporary matrix - constructor will automatically zero it
    Matrix4 returnMatrix;
    // fill in the diagonal with 1's
    for (int row = 0; row < 4; row++)
            returnMatrix.coordinates[row][row] = 1.0;

	// return it
	return returnMatrix;
	} // Identity()

Matrix4 Matrix4::Translate(const Cartesian3 &vector)
    { // Translation()
    // create a temporary matrix  and set to identity
    Matrix4 returnMatrix = Identity();

    // put the translation in the w column
    for (int entry = 0; entry < 3; entry++)
        returnMatrix.coordinates[entry][3] = vector[entry];

    // return it
    return returnMatrix;
    } // Translation()

 Matrix4 Matrix4::RotateX(float degrees)
 	{ // RotateX()
	// convert angle from degrees to radians
 	float theta = DEG2RAD(degrees);

    // create a temporary matrix  and set to identity
    Matrix4 returnMatrix = Identity();

	// now set the four coefficients affected
	returnMatrix.coordinates[1][1] = cos(theta);
	returnMatrix.coordinates[1][2] = sin(theta);
	returnMatrix.coordinates[2][1] = -sin(theta);
	returnMatrix.coordinates[2][2] = cos(theta);

	// return it
	return returnMatrix;
 	} // RotateX()
 	
 Matrix4 Matrix4::RotateY(float degrees)
 	{ // RotateY()
	// convert angle from degrees to radians
 	float theta = DEG2RAD(degrees);

    // create a temporary matrix  and set to identity
    Matrix4 returnMatrix = Identity();

	// now set the four coefficients affected
	returnMatrix.coordinates[0][0] = cos(theta);
	returnMatrix.coordinates[0][2] = -sin(theta);
	returnMatrix.coordinates[2][0] = sin(theta);
	returnMatrix.coordinates[2][2] = cos(theta);

	// return it
	return returnMatrix;
 	} // RotateY()

 Matrix4 Matrix4::RotateZ(float degrees)
 	{ // RotateZ()
	// convert angle from degrees to radians
 	float theta = DEG2RAD(degrees);

    // create a temporary matrix  and set to identity
    Matrix4 returnMatrix = Identity();

	// now set the four coefficients affected
	returnMatrix.coordinates[0][0] = cos(theta);
	returnMatrix.coordinates[0][1] = sin(theta);
	returnMatrix.coordinates[1][0] = -sin(theta);
	returnMatrix.coordinates[1][1] = cos(theta);

	// return it
	return returnMatrix;
 	} // RotateZ()
 
// scalar operations
// additional scalar multiplication operator
Matrix4 operator *(float factor, const Matrix4 &matrix)
    { // operator *()
    // since this is commutative, call the other version
    return matrix * factor;
    } // operator *()

// stream input
std::istream & operator >> (std::istream &inStream, Matrix4 &matrix)
    { // operator >>()
    // just loop, reading them in
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            inStream >> matrix.coordinates[row][col];   
    // and return the stream
    return inStream;
    } // operator >>()

// stream output
std::ostream & operator << (std::ostream &outStream, const Matrix4 &matrix)
    { // operator <<()
    // just loop, reading them in
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            outStream << std::setw(12) << std::setprecision(5) << std::fixed << matrix.coordinates[row][col] << ((col == 3) ? "\n" : " "); 
    // and return the stream
    return outStream;
    } // operator <<()
