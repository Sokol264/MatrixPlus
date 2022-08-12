#include "s21_matrix_oop.h"

ExceptionError::ExceptionError() {}
ExceptionError::~ExceptionError() {}

void S21Matrix::init_matrix() {
    _matrix = new double*[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new double[_cols];
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = 0.0;
        }
    }
}

bool S21Matrix::comp_doubles(double a, double b) {
    bool result = true;
    double error = fabs(a - b);
    if (error > E) result = false;
    return result;
}

void S21Matrix::clean_matrix() {
    if (_matrix != nullptr) {
        for (int i = 0; i < _rows; i++) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
}

void S21Matrix::copy_matrix(const S21Matrix& other) {
    init_matrix();
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

S21Matrix S21Matrix::s21_get_minor_matrix(const S21Matrix& mat, int index, int jndex) {
    S21Matrix result(mat._rows - 1, mat._cols - 1);
    for (int i = 0, mi = 0; i < mat._rows; i++) {
        for (int j = 0, mj = 0; j < mat._cols; j++) {
            if (i != index && j != jndex) result._matrix[mi][mj++] = mat._matrix[i][j];
        }
        if (index != i) mi++;
    }
    return result;
}

int S21Matrix::get_rows() { return _rows; }

int S21Matrix::get_cols() { return _cols; }

void S21Matrix::set_rows(int rows) { _rows = rows; }

void S21Matrix::set_cols(int cols) { _cols = cols; }
