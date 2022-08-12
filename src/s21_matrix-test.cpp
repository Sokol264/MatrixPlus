#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(DefaultConstructorTest, SingleTest) {
    S21Matrix t1;
    ASSERT_NEAR(0.0, t1(0, 0), E);
}

TEST(ConstructorWithIntegerParameters, CorrectInput) {
    S21Matrix t1(2, 2);
    ASSERT_NEAR(0.0, t1(0, 0), E);
    ASSERT_NEAR(0.0, t1(0, 1), E);
    ASSERT_NEAR(0.0, t1(1, 0), E);
    ASSERT_NEAR(0.0, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(ConstructorWithIntegerParameters, IncorrectInput) {
    S21Matrix t1(2, -1);
    ASSERT_NEAR(0.0, t1(0, 0), E);
    ASSERT_EQ(1, t1.get_rows());
    ASSERT_EQ(1, t1.get_cols());
}

TEST(CopyConstructor, SingleTest) {
    S21Matrix t1(2, 2);
    t1(1, 1) = 1.2;
    S21Matrix t2(t1);
    ASSERT_NEAR(0.0, t2(0, 0), E);
    ASSERT_NEAR(0.0, t2(0, 1), E);
    ASSERT_NEAR(0.0, t2(1, 0), E);
    ASSERT_NEAR(1.2, t2(1, 1), E);
    ASSERT_EQ(2, t2.get_rows());
    ASSERT_EQ(2, t2.get_cols());
}

TEST(MoveConstructor, SingleTest) {
    S21Matrix t1(2, 2);
    t1(1, 1) = 1.2;
    S21Matrix t2(std::move(t1));
    ASSERT_NEAR(0.0, t2(0, 0), E);
    ASSERT_NEAR(0.0, t2(0, 1), E);
    ASSERT_NEAR(0.0, t2(1, 0), E);
    ASSERT_NEAR(1.2, t2(1, 1), E);
    ASSERT_EQ(2, t2.get_rows());
    ASSERT_EQ(2, t2.get_cols());
    ASSERT_EQ(0, t1.get_rows());
    ASSERT_EQ(0, t1.get_cols());
}

TEST(EqualMatrix, CorrectInput) {
    S21Matrix t1(2, 3);
    S21Matrix t2(2, 3);
    t1(1, 1) = 1.2;
    t2(1, 1) = 1.2;
    ASSERT_EQ(1, t1.eq_matrix(t2));
}

TEST(EqualMatrix, IncorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 3);
    t1(1, 1) = 1.2;
    t2(1, 1) = 1.2;
    ASSERT_EQ(0, t1.eq_matrix(t2));
}

TEST(EqualMatrix, DifferentValues) {
    S21Matrix t1(2, 3);
    S21Matrix t2(2, 3);
    t1(1, 1) = 1.4;
    t2(1, 1) = 1.2;
    ASSERT_EQ(0, t1.eq_matrix(t2));
}

TEST(SumMatrix, CorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 1.2;
    t2(1, 0) = 2.5;
    t1.sum_matrix(t2);
    ASSERT_NEAR(1.2, t1(0, 0), E);
    ASSERT_NEAR(0.0, t1(0, 1), E);
    ASSERT_NEAR(2.5, t1(1, 0), E);
    ASSERT_NEAR(0.0, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(SubMatrix, CorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 1.2;
    t2(1, 0) = 2.5;
    t1.sub_matrix(t2);
    ASSERT_NEAR(1.2, t1(0, 0), E);
    ASSERT_NEAR(0.0, t1(0, 1), E);
    ASSERT_NEAR(-2.5, t1(1, 0), E);
    ASSERT_NEAR(0.0, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(MulMatrixByNumber, SingleTest) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;
    t1.mul_number(2);
    ASSERT_NEAR(4, t1(0, 0), E);
    ASSERT_NEAR(2, t1(0, 1), E);
    ASSERT_NEAR(8.4, t1(1, 0), E);
    ASSERT_NEAR(-6.4, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(MulMatrix, SqrMatrix) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;

    t2(0, 0) = 4;
    t2(0, 1) = 2;
    t2(1, 0) = -1;
    t2(1, 1) = -3;

    t1.mul_matrix(t2);
    ASSERT_NEAR(7, t1(0, 0), E);
    ASSERT_NEAR(1, t1(0, 1), E);
    ASSERT_NEAR(20, t1(1, 0), E);
    ASSERT_NEAR(18, t1(1, 1), E);

    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(MulMatrix, TwoRowsFirstOneColsSecond) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 1);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;

    t2(0, 0) = 3;
    t2(1, 0) = 2;

    t1.mul_matrix(t2);
    ASSERT_NEAR(8, t1(0, 0), E);
    ASSERT_NEAR(6.2, t1(1, 0), E);

    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(1, t1.get_cols());
}

TEST(MulMatrix, OneRowsFirstOneColsSecond) {
    S21Matrix t1(1, 2);
    S21Matrix t2(2, 1);
    t1(0, 0) = 2;
    t1(0, 1) = 1;

    t2(0, 0) = 3;
    t2(1, 0) = 2;

    t1.mul_matrix(t2);
    ASSERT_NEAR(8, t1(0, 0), E);

    ASSERT_EQ(1, t1.get_rows());
    ASSERT_EQ(1, t1.get_cols());
}

TEST(MulMatrix, TwoRowsFirstTwoColsSecond) {
    S21Matrix t1(2, 1);
    S21Matrix t2(1, 2);
    t1(0, 0) = 3;
    t1(1, 0) = 1;

    t2(0, 0) = 6;
    t2(0, 1) = 2;

    t1.mul_matrix(t2);
    ASSERT_NEAR(18, t1(0, 0), E);
    ASSERT_NEAR(6, t1(0, 1), E);
    ASSERT_NEAR(6, t1(1, 0), E);
    ASSERT_NEAR(2, t1(1, 1), E);

    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(TransposeMatrix, SqrMatrix) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 1;
    t1(0, 1) = 2;
    t1(1, 0) = 3;
    t1(1, 1) = 4;
    t1 = t1.transpose();
    ASSERT_NEAR(1, t1(0, 0), E);
    ASSERT_NEAR(3, t1(0, 1), E);
    ASSERT_NEAR(2, t1(1, 0), E);
    ASSERT_NEAR(4, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(TransposeMatrix, OneRowsThreeCols) {
    S21Matrix t1(1, 3);
    t1(0, 0) = 1;
    t1(0, 1) = 2;
    t1(0, 2) = 3;
    t1 = t1.transpose();
    ASSERT_NEAR(1, t1(0, 0), E);
    ASSERT_NEAR(2, t1(1, 0), E);
    ASSERT_NEAR(3, t1(2, 0), E);
    ASSERT_EQ(3, t1.get_rows());
    ASSERT_EQ(1, t1.get_cols());
}

TEST(TransposeMatrix, TwoRowsThreeCols) {
    S21Matrix t1(2, 3);
    t1(0, 0) = 1;
    t1(0, 1) = 2;
    t1(0, 2) = 3;
    t1(1, 0) = 4;
    t1(1, 1) = 5;
    t1(1, 2) = 6;
    t1 = t1.transpose();
    ASSERT_NEAR(1, t1(0, 0), E);
    ASSERT_NEAR(4, t1(0, 1), E);
    ASSERT_NEAR(2, t1(1, 0), E);
    ASSERT_NEAR(5, t1(1, 1), E);
    ASSERT_NEAR(3, t1(2, 0), E);
    ASSERT_NEAR(6, t1(2, 1), E);
    ASSERT_EQ(3, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(CalcComplementsMatrix, SqrMatrixOne) {
    S21Matrix t1(1, 1);
    t1(0, 0) = 3;
    t1 = t1.calc_complements();
    ASSERT_NEAR(1, t1(0, 0), E);
    ASSERT_EQ(1, t1.get_rows());
    ASSERT_EQ(1, t1.get_cols());
}

TEST(CalcComplementsMatrix, SqrMatrixTwo) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 1;
    t1(0, 1) = 2;
    t1(1, 0) = 3;
    t1(1, 1) = 4;
    t1 = t1.calc_complements();
    ASSERT_NEAR(4, t1(0, 0), E);
    ASSERT_NEAR(-3, t1(0, 1), E);
    ASSERT_NEAR(-2, t1(1, 0), E);
    ASSERT_NEAR(1, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(CalcComplementsMatrix, SqrMatrixThree) {
    S21Matrix t1(3, 3);
    t1(0, 0) = 4;
    t1(0, 1) = 1;
    t1(0, 2) = 2;
    t1(1, 0) = 3;
    t1(1, 1) = 0;
    t1(1, 2) = 1;
    t1(2, 0) = 3;
    t1(2, 1) = 5;
    t1(2, 2) = 4;
    t1 = t1.calc_complements();
    ASSERT_NEAR(-5, t1(0, 0), E);
    ASSERT_NEAR(-9, t1(0, 1), E);
    ASSERT_NEAR(15, t1(0, 2), E);
    ASSERT_NEAR(6, t1(1, 0), E);
    ASSERT_NEAR(10, t1(1, 1), E);
    ASSERT_NEAR(-17, t1(1, 2), E);
    ASSERT_NEAR(1, t1(2, 0), E);
    ASSERT_NEAR(2, t1(2, 1), E);
    ASSERT_NEAR(-3, t1(2, 2), E);
    ASSERT_EQ(3, t1.get_rows());
    ASSERT_EQ(3, t1.get_cols());
}

TEST(DeterminantMatrix, MatrixSqrOne) {
    S21Matrix t1(1, 1);
    t1(0, 0) = 4;
    double res = t1.determinant();
    ASSERT_NEAR(res, 4, E);
}

TEST(DeterminantMatrix, MatrixSqrTwo) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 3;
    t1(0, 1) = 1;
    t1(1, 0) = 7;
    t1(1, 1) = 2;
    double res = t1.determinant();
    ASSERT_NEAR(res, -1, E);
}

TEST(DeterminantMatrix, MatrixSqrThree) {
    S21Matrix t1(3, 3);
    t1(0, 0) = 5;
    t1(0, 1) = 1;
    t1(0, 2) = -2;
    t1(1, 0) = 7;
    t1(1, 1) = -8;
    t1(1, 2) = 2;
    t1(2, 0) = 1;
    t1(2, 1) = -6;
    t1(2, 2) = 2;
    double res = t1.determinant();
    ASSERT_NEAR(res, 36, E);
}

TEST(DeterminantMatrix, MatrixSqrFour) {
    S21Matrix t1(4, 4);
    t1(0, 0) = 5;
    t1(0, 1) = 1;
    t1(0, 2) = -2;
    t1(0, 3) = 12;
    t1(1, 0) = 7;
    t1(1, 1) = -8;
    t1(1, 2) = 2;
    t1(1, 3) = -22;
    t1(2, 0) = 1;
    t1(2, 1) = -6;
    t1(2, 2) = 2;
    t1(2, 3) = 15;
    t1(3, 0) = 24;
    t1(3, 1) = -7;
    t1(3, 2) = -12;
    t1(3, 3) = 5;
    double res = t1.determinant();
    ASSERT_NEAR(res, -15264, E);
}

TEST(InverseMatrix, SqrMatrixOne) {
    S21Matrix t1(1, 1);
    t1(0, 0) = 5;
    t1 = t1.inverse_matrix();
    ASSERT_NEAR(t1(0, 0), 0.2, E);
}

TEST(InverseMatrix, SqrMatrixTwo) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 5;
    t1(0, 1) = 3;
    t1(1, 0) = 1;
    t1(1, 1) = 6;
    t1 = t1.inverse_matrix();
    ASSERT_NEAR(t1(0, 0), 2.0 / 9.0, E);
    ASSERT_NEAR(t1(0, 1), -1.0 / 9.0, E);
    ASSERT_NEAR(t1(1, 0), -1.0 / 27.0, E);
    ASSERT_NEAR(t1(1, 1), 5.0 / 27.0, E);
}

TEST(InverseMatrix, SqrMatrixThree) {
    S21Matrix t1(3, 3);
    t1(0, 0) = -12;
    t1(0, 1) = 7;
    t1(0, 2) = 3;
    t1(1, 0) = 1;
    t1(1, 1) = -6;
    t1(1, 2) = 14;
    t1(2, 0) = 1;
    t1(2, 1) = 6;
    t1(2, 2) = -23;
    t1 = t1.inverse_matrix();
    ASSERT_NEAR(t1(0, 0), -54.0 / 353.0, E);
    ASSERT_NEAR(t1(0, 1), -179.0 / 353.0, E);
    ASSERT_NEAR(t1(0, 2), -116.0 / 353.0, E);
    ASSERT_NEAR(t1(1, 0), -37.0 / 353.0, E);
    ASSERT_NEAR(t1(1, 1), -273.0 / 353.0, E);
    ASSERT_NEAR(t1(1, 2), -171.0 / 353.0, E);
    ASSERT_NEAR(t1(2, 0), -12.0 / 353.0, E);
    ASSERT_NEAR(t1(2, 1), -79.0 / 353.0, E);
    ASSERT_NEAR(t1(2, 2), -65.0 / 353.0, E);
}

TEST(OperatorEqualMatrix, CorrectInput) {
    S21Matrix t1(2, 3);
    S21Matrix t2(2, 3);
    t1(1, 1) = 1.2;
    t2(1, 1) = 1.2;
    ASSERT_EQ(1, t1 == t2);
}

TEST(OperatorEqualMatrix, IncorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 3);
    t1(1, 1) = 1.2;
    t2(1, 1) = 1.2;
    ASSERT_EQ(0, t1 == t2);
}

TEST(OperatorEqualMatrix, DifferentValues) {
    S21Matrix t1(2, 3);
    S21Matrix t2(2, 3);
    t1(1, 1) = 1.4;
    t2(1, 1) = 1.2;
    ASSERT_EQ(0, t1 == t2);
}

TEST(OperatorSumReplaceMatrix, CorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 1.2;
    t2(1, 0) = 2.5;
    t1 += t2;
    ASSERT_NEAR(1.2, t1(0, 0), E);
    ASSERT_NEAR(0.0, t1(0, 1), E);
    ASSERT_NEAR(2.5, t1(1, 0), E);
    ASSERT_NEAR(0.0, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(OperatorSumMatrix, CorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 1.2;
    t2(1, 0) = 2.5;
    S21Matrix t3 = t1 + t2;
    ASSERT_NEAR(1.2, t3(0, 0), E);
    ASSERT_NEAR(0.0, t3(0, 1), E);
    ASSERT_NEAR(2.5, t3(1, 0), E);
    ASSERT_NEAR(0.0, t3(1, 1), E);
    ASSERT_EQ(2, t3.get_rows());
    ASSERT_EQ(2, t3.get_cols());
}

TEST(OperatorSubReplaceMatrix, CorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 1.2;
    t2(1, 0) = 2.5;
    t1 -= t2;
    ASSERT_NEAR(1.2, t1(0, 0), E);
    ASSERT_NEAR(0.0, t1(0, 1), E);
    ASSERT_NEAR(-2.5, t1(1, 0), E);
    ASSERT_NEAR(0.0, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(OperatorSubMatrix, CorrectInput) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 1.2;
    t2(1, 0) = 2.5;
    S21Matrix t3 = t1 - t2;
    ASSERT_NEAR(1.2, t3(0, 0), E);
    ASSERT_NEAR(0.0, t3(0, 1), E);
    ASSERT_NEAR(-2.5, t3(1, 0), E);
    ASSERT_NEAR(0.0, t3(1, 1), E);
    ASSERT_EQ(2, t3.get_rows());
    ASSERT_EQ(2, t3.get_cols());
}

TEST(OperatorMulReplaceMatrixByNumber, SingleTest) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;
    t1 *= 2;
    ASSERT_NEAR(4, t1(0, 0), E);
    ASSERT_NEAR(2, t1(0, 1), E);
    ASSERT_NEAR(8.4, t1(1, 0), E);
    ASSERT_NEAR(-6.4, t1(1, 1), E);
    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(OperatorMulMatrixByNumber, SingleTest) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;
    S21Matrix t3 = t1 * 2;
    ASSERT_NEAR(4, t3(0, 0), E);
    ASSERT_NEAR(2, t3(0, 1), E);
    ASSERT_NEAR(8.4, t3(1, 0), E);
    ASSERT_NEAR(-6.4, t3(1, 1), E);
    ASSERT_EQ(2, t3.get_rows());
    ASSERT_EQ(2, t3.get_cols());
}

TEST(OperatorMulReplaceMatrix, SqrMatrix) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;

    t2(0, 0) = 4;
    t2(0, 1) = 2;
    t2(1, 0) = -1;
    t2(1, 1) = -3;

    t1 *= t2;
    ASSERT_NEAR(7, t1(0, 0), E);
    ASSERT_NEAR(1, t1(0, 1), E);
    ASSERT_NEAR(20, t1(1, 0), E);
    ASSERT_NEAR(18, t1(1, 1), E);

    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(OperatorMulReplaceMatrix, TwoRowsFirstOneColsSecond) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 1);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;

    t2(0, 0) = 3;
    t2(1, 0) = 2;

    t1 *= t2;
    ASSERT_NEAR(8, t1(0, 0), E);
    ASSERT_NEAR(6.2, t1(1, 0), E);

    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(1, t1.get_cols());
}

TEST(OperatorMulReplaceMatrix, OneRowsFirstOneColsSecond) {
    S21Matrix t1(1, 2);
    S21Matrix t2(2, 1);
    t1(0, 0) = 2;
    t1(0, 1) = 1;

    t2(0, 0) = 3;
    t2(1, 0) = 2;

    t1 *= t2;
    ASSERT_NEAR(8, t1(0, 0), E);

    ASSERT_EQ(1, t1.get_rows());
    ASSERT_EQ(1, t1.get_cols());
}

TEST(OperatorMulReplaceMatrix, TwoRowsFirstTwoColsSecond) {
    S21Matrix t1(2, 1);
    S21Matrix t2(1, 2);
    t1(0, 0) = 3;
    t1(1, 0) = 1;

    t2(0, 0) = 6;
    t2(0, 1) = 2;

    t1 *= t2;
    ASSERT_NEAR(18, t1(0, 0), E);
    ASSERT_NEAR(6, t1(0, 1), E);
    ASSERT_NEAR(6, t1(1, 0), E);
    ASSERT_NEAR(2, t1(1, 1), E);

    ASSERT_EQ(2, t1.get_rows());
    ASSERT_EQ(2, t1.get_cols());
}

TEST(OperatorMulMatrix, SqrMatrix) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 2);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;

    t2(0, 0) = 4;
    t2(0, 1) = 2;
    t2(1, 0) = -1;
    t2(1, 1) = -3;

    S21Matrix t3 = t1 * t2;
    ASSERT_NEAR(7, t3(0, 0), E);
    ASSERT_NEAR(1, t3(0, 1), E);
    ASSERT_NEAR(20, t3(1, 0), E);
    ASSERT_NEAR(18, t3(1, 1), E);

    ASSERT_EQ(2, t3.get_rows());
    ASSERT_EQ(2, t3.get_cols());
}

TEST(OperatorMulMatrix, TwoRowsFirstOneColsSecond) {
    S21Matrix t1(2, 2);
    S21Matrix t2(2, 1);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;

    t2(0, 0) = 3;
    t2(1, 0) = 2;

    S21Matrix t3 = t1 * t2;
    ASSERT_NEAR(8, t3(0, 0), E);
    ASSERT_NEAR(6.2, t3(1, 0), E);

    ASSERT_EQ(2, t3.get_rows());
    ASSERT_EQ(1, t3.get_cols());
}

TEST(OperatorMulMatrix, OneRowsFirstOneColsSecond) {
    S21Matrix t1(1, 2);
    S21Matrix t2(2, 1);
    t1(0, 0) = 2;
    t1(0, 1) = 1;

    t2(0, 0) = 3;
    t2(1, 0) = 2;

    S21Matrix t3 = t1 * t2;
    ASSERT_NEAR(8, t3(0, 0), E);

    ASSERT_EQ(1, t3.get_rows());
    ASSERT_EQ(1, t3.get_cols());
}

TEST(OperatorMulMatrix, TwoRowsFirstTwoColsSecond) {
    S21Matrix t1(2, 1);
    S21Matrix t2(1, 2);
    t1(0, 0) = 3;
    t1(1, 0) = 1;

    t2(0, 0) = 6;
    t2(0, 1) = 2;

    S21Matrix t3 = t1 * t2;
    ASSERT_NEAR(18, t3(0, 0), E);
    ASSERT_NEAR(6, t3(0, 1), E);
    ASSERT_NEAR(6, t3(1, 0), E);
    ASSERT_NEAR(2, t3(1, 1), E);

    ASSERT_EQ(2, t3.get_rows());
    ASSERT_EQ(2, t3.get_cols());
}

TEST(OperatorBracket, SingleTest) {
    S21Matrix t1(2, 1);
    t1(0, 0) = 1;
    ASSERT_NEAR(1, t1(0, 0), E);
}

TEST(Mutator, SingleTest) {
    S21Matrix t1(2, 1);
    t1.set_cols(2);
    t1.set_rows(1);
    ASSERT_EQ(2, t1.get_cols());
    ASSERT_EQ(1, t1.get_rows());
    t1.set_cols(1);
    t1.set_rows(2);
}

TEST(OperatorMulNumberByMatrix, SingleTest) {
    S21Matrix t1(2, 2);
    t1(0, 0) = 2;
    t1(0, 1) = 1;
    t1(1, 0) = 4.2;
    t1(1, 1) = -3.2;
    S21Matrix t3 = 2 * t1;
    ASSERT_NEAR(4, t3(0, 0), E);
    ASSERT_NEAR(2, t3(0, 1), E);
    ASSERT_NEAR(8.4, t3(1, 0), E);
    ASSERT_NEAR(-6.4, t3(1, 1), E);
    ASSERT_EQ(2, t3.get_rows());
    ASSERT_EQ(2, t3.get_cols());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
