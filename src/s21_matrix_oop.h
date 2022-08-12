#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <math.h>
#include <stdio.h>

#include <iostream>

#define E 1e-6

class ExceptionError {
 public:
    ExceptionError();
    ~ExceptionError();
};

class S21Matrix {
 private:
    int _rows, _cols;
    double** _matrix;

    void init_matrix();
    bool comp_doubles(double, double);
    S21Matrix s21_get_minor_matrix(const S21Matrix&, int, int);
    void copy_matrix(const S21Matrix&);

 public:
    // double** _matrix;

    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    int get_rows();
    int get_cols();
    void set_rows(int rows);
    void set_cols(int cols);
    void clean_matrix();

    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();

    S21Matrix operator+(const S21Matrix& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix operator*(const double number);
    S21Matrix& operator*=(const double number);
    S21Matrix& operator=(const S21Matrix& other);
    bool operator==(const S21Matrix& other);
    double& operator()(int row, int col);
};

S21Matrix operator*(const double num, const S21Matrix& m);

#endif  // SRC_S21_MATRIX_OOP_H_
