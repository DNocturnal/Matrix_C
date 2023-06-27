#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <stdio.h>

#include <cmath>
#include <exception>
#include <iostream>

#define EPS 1e-7

class S21Matrix {
 public:
  S21Matrix();                        // Default constructor
  S21Matrix(int rows, int cols);      // Contructor with parameter's
  S21Matrix(const S21Matrix &other);  // Copy constructor
  S21Matrix(S21Matrix &&other);       // Move constructor
  ~S21Matrix();                       // Destructor

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  void MinorMatrix(S21Matrix &other, int rows, int cols);

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);  // assignment
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix &operator=(S21Matrix &&other);

  double &operator()(int row, int column);
  bool operator==(const S21Matrix &other);  // comparisons

  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  void print();

 private:
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated
  void AllocationMatrix();
  void DestroyMatrix();
  void CopyMatrix(const S21Matrix &other);

  bool IncorrectMatrix(const S21Matrix &other);
};

S21Matrix operator*(const double num, const S21Matrix &other);
#endif  // SRC_S21_MATRIX_OOP_H_