#include "s21_matrix_oop.h"

// constructors
S21Matrix::S21Matrix() : _rows(1), _cols(1) { init_matrix(); }
S21Matrix::S21Matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        _rows = 1;
        _cols = 1;
    } else {
        _rows = rows;
        _cols = cols;
    }
    init_matrix();
}
S21Matrix::S21Matrix(const S21Matrix& other) : _rows(other._rows), _cols(other._cols) { copy_matrix(other); }
S21Matrix::S21Matrix(S21Matrix&& other) : _rows(other._rows), _cols(other._cols), _matrix(other._matrix) {
    other._rows = 0;
    other._cols = 0;
    other._matrix = 0;
}
S21Matrix::~S21Matrix() { clean_matrix(); }

// main functions
bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool result = true;
    if (other._cols != _cols || other._rows != _rows) {
        result = false;
    } else {
        for (int i = 0; i < _rows && result; i++) {
            for (int j = 0; j < _cols && result; j++) {
                if (!comp_doubles(_matrix[i][j], other._matrix[i][j])) {
                    result = false;
                }
            }
        }
    }
    return result;
}
void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw ExceptionError();
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
}
void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw ExceptionError();
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }
}
void S21Matrix::mul_number(const double num) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] *= num;
        }
    }
}
void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (_cols != other._rows) {
        throw ExceptionError();
    }
    S21Matrix temp(*this);
    clean_matrix();
    _rows = temp._rows, _cols = other._cols;
    init_matrix();
    for (int i = 0; i < temp._rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            for (int k = 0; k < temp._cols; k++) {
                _matrix[i][j] += temp._matrix[i][k] * other._matrix[k][j];
            }
        }
    }
}
S21Matrix S21Matrix::transpose() {
    S21Matrix result(_cols, _rows);
    for (int i = 0; i < _cols; i++) {
        for (int j = 0; j < _rows; j++) {
            result._matrix[i][j] = _matrix[j][i];
        }
    }
    return result;
}
S21Matrix S21Matrix::calc_complements() {
    S21Matrix result(_rows, _cols);
    if (_rows != _cols) {
        throw ExceptionError();
    }
    if (_rows == 1) {
        result._matrix[0][0] = 1;
    } else {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                S21Matrix temp = s21_get_minor_matrix(*this, i, j);
                result._matrix[i][j] = temp.determinant() * pow(-1, (i + 1) + (j + 1));
            }
        }
    }
    return result;
}
double S21Matrix::determinant() {
    double result = 0.0;
    if (_rows != _cols) {
        throw ExceptionError();
    }
    if (_rows == 1) {
        result = _matrix[0][0];
    } else if (_rows == 2) {
        result = _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
    } else {
        double det = 0.0;
        for (int i = 0; i < _cols; i++) {
            S21Matrix temp = s21_get_minor_matrix(*this, 0, i);
            double k = pow(-1, i + 2);
            det += k * _matrix[0][i] * temp.determinant();
        }
        result = det;
    }
    return result;
}
S21Matrix S21Matrix::inverse_matrix() {
    S21Matrix result(_rows, _cols);
    if (_rows != _cols) {
        throw ExceptionError();
    }
    double det = determinant();
    if (!comp_doubles(0.0, det)) {
        if (_rows == 1) {
            result._matrix[0][0] = 1 / det;
        } else {
            S21Matrix trans = transpose();
            S21Matrix temp = trans.calc_complements();
            temp.mul_number(1 / det);
            result = temp;
        }
    } else {
        throw ExceptionError();
    }
    return result;
}

// operators
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    clean_matrix();
    _rows = other._rows;
    _cols = other._cols;
    copy_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    sum_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    mul_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const double number) {
    mul_number(number);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    sub_matrix(other);
    return *this;
}
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix result(*this);
    result.sum_matrix(other);
    return result;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.sub_matrix(other);
    return result;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.mul_matrix(other);
    return result;
}
S21Matrix S21Matrix::operator*(const double number) {
    S21Matrix result(*this);
    result.mul_number(number);
    return result;
}
bool S21Matrix::operator==(const S21Matrix& other) { return eq_matrix(other); }
double& S21Matrix::operator()(int row, int col) {
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
        throw ExceptionError();
    }
    return _matrix[row][col];
}
S21Matrix operator*(const double num, const S21Matrix& m) {
    S21Matrix result(m);
    result.mul_number(num);
    return result;
}
