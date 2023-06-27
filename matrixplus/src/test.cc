#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor, 1) {
  S21Matrix matrix_a;
  ASSERT_EQ(matrix_a.GetRows(), 1);
  ASSERT_EQ(matrix_a.GetCols(), 1);
}
TEST(Constructor, 2) {
  S21Matrix matrix_a(3, 3);
  ASSERT_EQ(matrix_a.GetRows(), 3);
  ASSERT_EQ(matrix_a.GetCols(), 3);
}
TEST(Constructor, 3) {
  S21Matrix matrix_a(35, 35);
  ASSERT_EQ(matrix_a.GetRows(), 35);
  ASSERT_EQ(matrix_a.GetCols(), 35);
}
TEST(Constructor, 4) {
  S21Matrix matrix_a(5, 5);
  ASSERT_EQ(matrix_a.GetRows(), 5);
  ASSERT_EQ(matrix_a.GetCols(), 5);
}
TEST(Constructor, 5) {
  S21Matrix matrix_a(15, 6);
  ASSERT_EQ(matrix_a.GetRows(), 15);
  ASSERT_EQ(matrix_a.GetCols(), 6);
}

TEST(Constructor, 6) {
  S21Matrix matrix_a(5, 5);
  matrix_a.SetRows(11);
  matrix_a.SetCols(15);
  ASSERT_EQ(matrix_a.GetRows(), 11);
  ASSERT_EQ(matrix_a.GetCols(), 15);
}
TEST(Constructor, 7) {
  S21Matrix matrix_a(19, 29);
  matrix_a.SetRows(1);
  matrix_a.SetCols(6);
  ASSERT_EQ(matrix_a.GetRows(), 1);
  ASSERT_EQ(matrix_a.GetCols(), 6);
}

TEST(Constructor, 8) {
  S21Matrix matrix_a(10, 20);
  S21Matrix matrix_b(std::move(matrix_a));
  EXPECT_EQ(matrix_b.GetRows(), 10);
  EXPECT_EQ(matrix_b.GetCols(), 20);
}

TEST(Constructor, 9) {
  S21Matrix matrix_a(33, 24);
  S21Matrix matrix_b(matrix_a);

  EXPECT_EQ(matrix_b.GetRows(), 33);
  EXPECT_EQ(matrix_b.GetCols(), 24);
  EXPECT_EQ(matrix_a == matrix_b, true);
}
TEST(Constructor, 10) {
  S21Matrix matrix_a(33, 24);
  S21Matrix matrix_b(matrix_a);
  EXPECT_EQ(matrix_b.GetRows(), 33);
  EXPECT_EQ(matrix_b.GetCols(), 24);
  EXPECT_EQ(matrix_a == matrix_b, true);
}

TEST(EqMatrix, 1) {
  S21Matrix matrix_a(1, 1);
  S21Matrix matrix_b(1, 1);
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, 2) {
  S21Matrix matrix_a(2, 3);
  S21Matrix matrix_b(2, 3);
  matrix_a.EqMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, 3) {
  S21Matrix matrix_a(12, 12);
  S21Matrix matrix_b(12, 12);
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, 4) {
  S21Matrix matrix_a(39, 39);
  S21Matrix matrix_b(2, 2);
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(EqMatrix, 5) {
  S21Matrix matrix_a(120, 120);
  S21Matrix matrix_b(120, 120);
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, 6) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a(0, 1) = 1.1;
  matrix_b(0, 1) = 1.1;
  matrix_a(0, 2) = 1.00000001;
  matrix_b(0, 2) = 1.00000002;
  EXPECT_TRUE(matrix_b.EqMatrix(matrix_a));
}

TEST(EqMatrix, 7) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  S21Matrix matrix_c(2, 3);
  S21Matrix matrix_d(3, 3);
  matrix_a(0, 0) = 1.1;
  matrix_b(0, 0) = 1.2;
  EXPECT_FALSE(matrix_b.EqMatrix(matrix_a));
  EXPECT_FALSE(matrix_d.EqMatrix(matrix_c));
}

TEST(EqMatrix, 8) {
  S21Matrix matrix_a(0, 3);
  S21Matrix matrix_b(0, 3);

  EXPECT_THROW(matrix_a.EqMatrix(matrix_b), std::invalid_argument);
}

TEST(SumMatrix, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a.SumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(SumMatrix, 2) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::out_of_range);
}

TEST(SumMatrix, 3) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  S21Matrix result(3, 3);
  matrix_a(0, 0) = 200.22;
  matrix_a(0, 1) = 0.006;
  matrix_a(0, 2) = 5.9;
  matrix_a(1, 0) = 5.3;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = -2;
  matrix_a(2, 0) = 7.633333;
  matrix_a(2, 1) = 4;
  matrix_a(2, 2) = -3.0009;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = -38;
  matrix_b(0, 2) = 27;
  matrix_b(1, 0) = -1;
  matrix_b(1, 1) = 41;
  matrix_b(1, 2) = -29;
  matrix_b(2, 0) = 1;
  matrix_b(2, 1) = -34;
  matrix_b(2, 2) = 24;

  result(0, 0) = 201.22;
  result(0, 1) = -37.994;
  result(0, 2) = 32.9;
  result(1, 0) = 4.3;
  result(1, 1) = 44;
  result(1, 2) = -31;
  result(2, 0) = 8.633333;
  result(2, 1) = -30;
  result(2, 2) = 20.9991;
  matrix_a.SumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(SumMatrix, 4) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 0);

  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::out_of_range);
}

TEST(SumMatrix, 5) {
  S21Matrix matrix_a(0, 1);
  S21Matrix matrix_b(0, 1);

  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::invalid_argument);
}

TEST(SubMatrix, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  matrix_a.SubMatrix(matrix_b);

  ASSERT_TRUE(matrix_a == result);
}

TEST(SubMatrix, 2) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::out_of_range);
}

TEST(SubMatrix, 3) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  S21Matrix result(3, 3);
  matrix_a(0, 0) = 200.22;
  matrix_a(0, 1) = 0.006;
  matrix_a(0, 2) = 5.9;
  matrix_a(1, 0) = 5.3;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = -2;
  matrix_a(2, 0) = 7.633333;
  matrix_a(2, 1) = 4;
  matrix_a(2, 2) = -3.0009;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = -38;
  matrix_b(0, 2) = 27;
  matrix_b(1, 0) = -1;
  matrix_b(1, 1) = 41;
  matrix_b(1, 2) = -29;
  matrix_b(2, 0) = 1;
  matrix_b(2, 1) = -34;
  matrix_b(2, 2) = 24;

  result(0, 0) = 199.22;
  result(0, 1) = 38.006;
  result(0, 2) = -21.10;
  result(1, 0) = 6.3;
  result(1, 1) = -38;
  result(1, 2) = 27;
  result(2, 0) = 6.633333;
  result(2, 1) = 38;
  result(2, 2) = -27.0009;
  matrix_a.SubMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(SubMatrix, 4) {
  S21Matrix matrix_a(0, 0);
  S21Matrix matrix_b(0, 0);

  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::invalid_argument);
}

TEST(MulNumber, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  matrix_a.MulNumber(10);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulNumber, 2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = 0;
  result(0, 1) = 0;
  result(1, 0) = 0;
  result(1, 1) = 0;

  matrix_a.MulNumber(0);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulNumber, 3) {
  S21Matrix matrix_a(5, 3);
  S21Matrix result(5, 3);

  matrix_a(0, 0) = -4;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 1;
  matrix_a(1, 0) = 0.3;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 0;
  matrix_a(2, 0) = -0.3;
  matrix_a(2, 1) = 9;
  matrix_a(2, 2) = -5.5;
  matrix_a(3, 0) = 12;
  matrix_a(3, 1) = 2.1;
  matrix_a(3, 2) = 3;
  matrix_a(4, 0) = 0;
  matrix_a(4, 1) = 0;
  matrix_a(4, 2) = 0;

  result(0, 0) = -40;
  result(0, 1) = 20;
  result(0, 2) = 10;
  result(1, 0) = 3;
  result(1, 1) = 30;
  result(1, 2) = 0;
  result(2, 0) = -3;
  result(2, 1) = 90;
  result(2, 2) = -55;
  result(3, 0) = 120;
  result(3, 1) = 21;
  result(3, 2) = 30;
  result(4, 0) = 0;
  result(4, 1) = 0;
  result(4, 2) = 0;

  matrix_a.MulNumber(10);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulNumber, 4) {
  S21Matrix matrix_a(0, 6);
  ASSERT_THROW(matrix_a.MulNumber(4), std::invalid_argument);
}

TEST(MulMatrix, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  matrix_a.MulMatrix(matrix_b);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulMatrix, 2) {
  S21Matrix matrix_a(2, 3);
  S21Matrix matrix_b(3, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;

  matrix_b(0, 0) = 9.5;
  matrix_b(0, 1) = 8.4;
  matrix_b(1, 0) = 7.15;
  matrix_b(1, 1) = 6.02;
  matrix_b(2, 0) = 5.99;
  matrix_b(2, 1) = 0;

  result(0, 0) = 41.77;
  result(0, 1) = 20.44;
  result(1, 0) = 109.69;
  result(1, 1) = 63.7;

  matrix_a.MulMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(MulMatrix, 3) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.MulMatrix(matrix_b), std::out_of_range);
}

TEST(MulMatrix, 4) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 0);
  ASSERT_THROW(matrix_a.MulMatrix(matrix_b), std::invalid_argument);
}

TEST(OperatorParentheses, true) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_EQ(matrix_a(0, 1), 2);
}

TEST(OperatorParentheses, 2) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_NE(matrix_a(0, 1), 10);
}

TEST(OperatorPlus, true) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a + matrix_b) == result);
}
TEST(OperatorMinus, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a - matrix_b) == result);
}

TEST(OperatorMultiplyMatrix, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a * matrix_b) == result);
}

TEST(OperatorMultiplyNumber, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10) == result);
}

TEST(OperatorMultiplyNumber, 2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((10 * matrix_a) == result);
}

TEST(OperatorEqMatrix, 1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a = matrix_b;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorSumMatrix, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a += matrix_b) == result);
}
TEST(OperatorSumMatrix, 2) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW((matrix_a += matrix_b), std::out_of_range);
}

TEST(OperatorSubMatrix, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a -= matrix_b) == result);
}
TEST(OperatorSubMatrix, 2) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a -= matrix_b, std::out_of_range);
}
TEST(OperatorMulNumber, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a *= 10) == result);
}

TEST(OperatorMulNumber, 2) {
  S21Matrix matrix_a(3, 2);
  double num = 2;
  matrix_a(1, 1) = 1.1;
  matrix_a *= num;
  EXPECT_DOUBLE_EQ(matrix_a(1, 1), 2.2);
}

TEST(OperatorMulMatrix, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a *= matrix_b) == result);
}
TEST(OperatorMulMatrix, 2) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a *= matrix_b, std::out_of_range);
}
TEST(Transpose, 1) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;

  result(0, 0) = 7;
  result(0, 1) = 0;
  result(0, 2) = 3.12;
  result(0, 3) = -78;
  result(1, 0) = -98;
  result(1, 1) = 5.4;
  result(1, 2) = 2323;
  result(1, 3) = 476.4;
  result(2, 0) = 0.5;
  result(2, 1) = 32;
  result(2, 2) = 23;
  result(2, 3) = 21;
  S21Matrix res = matrix_a.Transpose();
  ASSERT_TRUE(res == result);
}

TEST(Transpose, 2) {
  S21Matrix matrix_a(0, 3);
  ASSERT_THROW(matrix_a.Transpose(), std::invalid_argument);
}

TEST(Inverse, 1) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::out_of_range);
}
TEST(Inverse, 2) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  ASSERT_TRUE(matrix_a.InverseMatrix().EqMatrix(result));
}

TEST(Inverse, 3) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 6;
  matrix_a(0, 2) = 5;
  matrix_a(1, 0) = 5;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = -2;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 4;
  matrix_a(2, 2) = -3;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = -38;
  matrix_b(0, 2) = 27;
  matrix_b(1, 0) = -1;
  matrix_b(1, 1) = 41;
  matrix_b(1, 2) = -29;
  matrix_b(2, 0) = 1;
  matrix_b(2, 1) = -34;
  matrix_b(2, 2) = 24;

  S21Matrix matrix_c(matrix_a.InverseMatrix());
  EXPECT_TRUE(matrix_b.EqMatrix(matrix_b));
}

TEST(Inverse, 4) {
  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;

  EXPECT_THROW(matrix_b.InverseMatrix(), std::runtime_error);
}

TEST(Inverse, 5) {
  S21Matrix matrix_b(0, 3);

  EXPECT_THROW(matrix_b.InverseMatrix(), std::invalid_argument);
}

TEST(Determinant, 1) {
  S21Matrix matrix_a(4, 4);
  matrix_a(0, 0) = 9;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 2;
  matrix_a(0, 3) = 4;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 4;
  matrix_a(1, 3) = 4;
  matrix_a(2, 0) = 4;
  matrix_a(2, 1) = 4;
  matrix_a(2, 2) = 9;
  matrix_a(2, 3) = 9;
  matrix_a(3, 0) = 1;
  matrix_a(3, 1) = 1;
  matrix_a(3, 2) = 5;
  matrix_a(3, 3) = 1;
  EXPECT_EQ(matrix_a.Determinant(), -578);
  S21Matrix matrix_b(1, 1);
  matrix_b(0, 0) = 10;
  EXPECT_EQ(matrix_b.Determinant(), 10);
  S21Matrix matrix_c(2, 2);
  matrix_c(0, 0) = 1.1;
  matrix_c(0, 1) = 3.5;
  matrix_c(1, 0) = -2;
  matrix_c(1, 1) = 4;
  EXPECT_DOUBLE_EQ(matrix_c.Determinant(), 11.4);
}

TEST(Determinant, 2) {
  S21Matrix matrix_a(4, 4);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(0, 3) = 4;
  matrix_a(1, 0) = 1;
  matrix_a(1, 1) = 2;
  matrix_a(1, 2) = 5;
  matrix_a(1, 3) = 7;
  matrix_a(2, 0) = 1;
  matrix_a(2, 1) = 0;
  matrix_a(2, 2) = 6;
  matrix_a(2, 3) = 8;
  matrix_a(3, 0) = 1;
  matrix_a(3, 1) = 0;
  matrix_a(3, 2) = 6;
  matrix_a(3, 3) = 6;
  EXPECT_EQ(matrix_a.Determinant(), -8);
}

TEST(Determinant, 3) {
  S21Matrix matrix_a(3, 2);
  EXPECT_THROW(matrix_a.Determinant(), std::out_of_range);
}

TEST(Determinant, 4) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 9;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;
  ASSERT_EQ(matrix_a.Determinant(), 30);
}

TEST(Determinant, 5) {
  S21Matrix matrix_a(0, 0);
  EXPECT_THROW(matrix_a.Determinant(), std::invalid_argument);
}

TEST(CalcComplements, 1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 1;

  result(0, 0) = 0;
  result(0, 1) = 10;
  result(0, 2) = -20;
  result(1, 0) = 4;
  result(1, 1) = -14;
  result(1, 2) = 8;
  result(2, 0) = -8;
  result(2, 1) = -2;
  result(2, 2) = 4;

  S21Matrix matrix_c(matrix_a.CalcComplements());
  EXPECT_TRUE(matrix_c.EqMatrix(result));
}

TEST(CalcComplements, 2) {
  S21Matrix matrix_a(5, 4);
  EXPECT_THROW(matrix_a.CalcComplements(), std::out_of_range);
}

TEST(CalcComplements, 3) {
  S21Matrix matrix_a(0, 0);
  EXPECT_THROW(matrix_a.CalcComplements(), std::invalid_argument);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}