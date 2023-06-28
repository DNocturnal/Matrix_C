// gcc -o test s21_matrix_test.c s21_matrix.c -lcheck -lm -lpthread && ./test
// leaks -atExit -- ./test
// valgrind --leak-check=full --show-leak-kinds=all -s ./test

#include "matrix.h"

#include <check.h>

START_TEST(test_s21_create) {
  matrix_t result;
  // 1
  int test = s21_create_matrix(0, 0, &result);
  ck_assert_int_eq(test, ERR_MATRIX);
  // 2
  test = s21_create_matrix(10, 20, &result);
  ck_assert_int_eq(test, OK);
  s21_remove_matrix(&result);
  // 3
  test = s21_create_matrix(1, 2, &result);
  ck_assert_int_eq(test, OK);
  s21_remove_matrix(&result);
  // 4
  test = s21_create_matrix(1, 1, &result);
  ck_assert_int_eq(test, OK);
  s21_remove_matrix(&result);
  // 5
  test = s21_create_matrix(80, 80, &result);
  ck_assert_int_eq(test, OK);
  s21_remove_matrix(&result);
  // 6
  test = s21_create_matrix(-2, 2, &result);
  ck_assert_int_eq(test, ERR_MATRIX);
  // 7
  test = s21_create_matrix(0, 32, &result);
  ck_assert_int_eq(test, ERR_MATRIX);
}
END_TEST

START_TEST(test_s21_eq) {
  matrix_t test1, test2;
  // 1
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &test2);
  test1.matrix[0][0] = 453.89;
  test1.matrix[0][1] = 33.0;
  test1.matrix[1][0] = 1.11111;
  test1.matrix[1][1] = 3.4585;
  test2.matrix[0][0] = 453.89;
  test2.matrix[0][1] = 33.0;
  test2.matrix[1][0] = 1.11111;
  test2.matrix[1][1] = 3.4585;
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 2
  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  test1.matrix[0][0] = 1;
  int res = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 3
  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  res = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 4
  s21_create_matrix(1, 2, &test1);
  s21_create_matrix(1, 1, &test2);
  res = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 5
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &test2);
  test1.matrix[0][0] = 0.1234567;
  test1.matrix[0][1] = 33.0;
  test1.matrix[1][0] = 1.11111;
  test1.matrix[1][1] = 3.4585;
  test2.matrix[0][0] = 0.1234568;
  test2.matrix[0][1] = 33.0;
  test2.matrix[1][0] = 1.11111;
  test2.matrix[1][1] = 3.4585;
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 6
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &test2);
  test1.matrix[0][0] = 0.12345678;
  test1.matrix[0][1] = 33.0;
  test1.matrix[1][0] = 1.11111;
  test1.matrix[1][1] = 3.4585;
  test2.matrix[0][0] = 0.12345679;
  test2.matrix[0][1] = 33.0;
  test2.matrix[1][0] = 1.11111;
  test2.matrix[1][1] = 3.4585;
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(test_s21_matrix_sum) {
  matrix_t test1, test2, result1, result2;
  // 1
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);
  s21_create_matrix(3, 3, &result2);
  test1.matrix[0][0] = 1;
  test2.matrix[0][0] = 2;
  result2.matrix[0][0] = 3;
  int res_sum = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_sum, OK);
  int res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 2
  test1.rows = -3;
  res_sum = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_sum, ERR_MATRIX);
  // 3
  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  res_sum = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_sum, ERR_CALC);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 4
  s21_create_matrix(1, 4, &test1);
  test1.matrix[0][0] = 55.0;
  test1.matrix[0][1] = 33.0;
  test1.matrix[0][2] = -7.538;
  test1.matrix[0][3] = 3;
  s21_create_matrix(1, 4, &test2);
  test2.matrix[0][0] = 0.2222222;
  test2.matrix[0][1] = -33.0;
  test2.matrix[0][2] = 1.11111;
  test2.matrix[0][3] = -256;
  s21_create_matrix(1, 4, &result2);
  result2.matrix[0][0] = 55.2222222;
  result2.matrix[0][1] = 0;
  result2.matrix[0][2] = -6.42689;
  result2.matrix[0][3] = -253;
  res_sum = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_sum, OK);
  res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 5
  s21_create_matrix(0, 2, &test1);
  s21_create_matrix(2, 3, &test2);
  ck_assert_int_eq(s21_sum_matrix(&test1, &test2, &result1), ERR_MATRIX);
  s21_remove_matrix(&test2);
  // 6
  int rows = 2;
  int columns = 4;
  s21_create_matrix(rows, columns, &test1);
  test1.matrix[0][0] = 1;
  test1.matrix[0][1] = 3;
  test1.matrix[0][2] = -7;
  test1.matrix[0][3] = 3;
  test1.matrix[1][0] = 55;
  test1.matrix[1][1] = 33;
  test1.matrix[1][2] = 0;
  test1.matrix[1][3] = 3;
  s21_create_matrix(rows, columns, &test2);
  test2.matrix[0][0] = 0;
  test2.matrix[0][1] = -3;
  test2.matrix[0][2] = 1;
  test2.matrix[0][3] = -2;
  test2.matrix[1][0] = 2;
  test2.matrix[1][1] = -3;
  test2.matrix[1][2] = 4;
  test2.matrix[1][3] = 2;
  s21_create_matrix(rows, columns, &result2);
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = 0;
  result2.matrix[0][2] = -6;
  result2.matrix[0][3] = 1;
  result2.matrix[1][0] = 57;
  result2.matrix[1][1] = 30;
  result2.matrix[1][2] = 4;
  result2.matrix[1][3] = 5;
  ck_assert_int_eq(s21_sum_matrix(&test1, &test2, &result1), OK);
  ck_assert_int_eq(s21_eq_matrix(&result1, &result2), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(test_s21_matrix_sub) {
  matrix_t test1, test2, result1, result2;
  // 1
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);
  s21_create_matrix(3, 3, &result2);
  test1.matrix[0][0] = 5;
  test2.matrix[0][0] = 2;
  result2.matrix[0][0] = 3;
  int res_sub = s21_sub_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_sub, OK);
  int res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 2
  test1.rows = -1;
  res_sub = s21_sub_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_sub, ERR_MATRIX);
  // 3
  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  res_sub = s21_sub_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_sub, ERR_CALC);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 4
  int rows = 1;
  int columns = 4;
  s21_create_matrix(rows, columns, &test1);
  test1.matrix[0][0] = 55.2222222;
  test1.matrix[0][1] = 33.0;
  test1.matrix[0][2] = -7.538;
  test1.matrix[0][3] = 3;
  s21_create_matrix(rows, columns, &test2);
  test2.matrix[0][0] = 2;
  test2.matrix[0][1] = -33.0;
  test2.matrix[0][2] = 1.11111;
  test2.matrix[0][3] = -256;
  s21_create_matrix(rows, columns, &result2);
  result2.matrix[0][0] = 53.2222222;
  result2.matrix[0][1] = 66;
  result2.matrix[0][2] = -8.64911;
  result2.matrix[0][3] = 259;
  ck_assert_int_eq(s21_sub_matrix(&test1, &test2, &result1), OK);
  ck_assert_int_eq(s21_eq_matrix(&result2, &result1), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
  // 5
  s21_create_matrix(0, 2, &test1);
  s21_create_matrix(2, 3, &test2);
  ck_assert_int_eq(s21_sub_matrix(&test1, &test2, &result1), ERR_MATRIX);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(test_s21_matrix_mult_number) {
  matrix_t test1, result1, result2;
  // 1
  double number = 5.0;
  s21_create_matrix(3, 3, &test1);
  test1.matrix[0][0] = 1;
  s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 5.0;
  int res_mult = s21_mult_number(&test1, number, &result1);
  ck_assert_int_eq(res_mult, OK);
  int res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result2);
  // 2
  test1.rows = 0;
  res_mult = s21_mult_number(&test1, number, &result1);
  ck_assert_int_eq(res_mult, ERR_MATRIX);
  // 3
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &test1);
  s21_create_matrix(rows, columns, &result2);
  ck_assert_int_eq(s21_mult_number(&test1, 200.2345, &result1), OK);
  ck_assert_int_eq(s21_eq_matrix(&result2, &result1), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
  // 4
  rows = 1;
  columns = 4;
  s21_create_matrix(rows, columns, &test1);
  test1.matrix[0][0] = 55.0;
  test1.matrix[0][1] = 33.5;
  test1.matrix[0][2] = -7.538;
  test1.matrix[0][3] = 3;
  s21_create_matrix(rows, columns, &result2);
  result2.matrix[0][0] = 165;
  result2.matrix[0][1] = 100.5;
  result2.matrix[0][2] = -22.614;
  result2.matrix[0][3] = 9;
  ck_assert_int_eq(s21_mult_number(&test1, 3, &result1), OK);
  ck_assert_int_eq(s21_eq_matrix(&result2, &result1), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
  // 5
  s21_create_matrix(0, 2, &test1);
  ck_assert_int_eq(s21_mult_number(&test1, 45, &result1), ERR_MATRIX);
}
END_TEST

START_TEST(test_s21_matrix_mult_matrix) {
  matrix_t test1, test2, result1, result2;
  // 1
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(1, 2, &test2);
  int res_mult = s21_mult_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_mult, ERR_CALC);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  // 2
  s21_create_matrix(2, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  s21_create_matrix(2, 2, &result2);
  test1.matrix[0][0] = 2;
  test1.matrix[1][0] = 4;
  test2.matrix[0][0] = 1;
  test2.matrix[0][1] = 3;
  result2.matrix[0][0] = 2;
  result2.matrix[0][1] = 6;
  result2.matrix[1][0] = 4;
  result2.matrix[1][1] = 12;
  res_mult = s21_mult_matrix(&test1, &test2, &result1);
  int res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_mult, OK);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 3
  test1.rows = -1;
  res_mult = s21_mult_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_mult, ERR_MATRIX);
  // 4
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 4, &test2);
  s21_create_matrix(2, 4, &result2);
  test1.matrix[0][0] = 2.987654;
  test1.matrix[0][1] = -5.3456;
  test1.matrix[1][0] = 6.23;
  test1.matrix[1][1] = -3.9292;
  test2.matrix[0][0] = 4.838;
  test2.matrix[0][1] = 8.0987;
  test2.matrix[0][2] = 8.09;
  test2.matrix[0][3] = -987;
  test2.matrix[1][0] = -8;
  test2.matrix[1][1] = -0.921;
  test2.matrix[1][2] = -0.91;
  test2.matrix[1][3] = 21;
  result2.matrix[0][0] = 57.219070052;
  result2.matrix[0][1] = 29.1194110498;
  result2.matrix[0][2] = 29.03461686;
  result2.matrix[0][3] = -3061.072098;
  result2.matrix[1][0] = 61.57434;
  result2.matrix[1][1] = 54.0736942;
  result2.matrix[1][2] = 53.976272;
  result2.matrix[1][3] = -6231.5232;
  res_mult = s21_mult_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(res_mult, OK);
  res_eq = s21_eq_matrix(&result2, &result1);
  ck_assert_int_eq(res_eq, SUCCESS);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 5
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &test1);
  s21_create_matrix(rows, columns, &test2);
  s21_create_matrix(rows, columns, &result2);
  ck_assert_int_eq(s21_mult_matrix(&test1, &test2, &result1), OK);
  ck_assert_int_eq(s21_eq_matrix(&result2, &result1), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 6
  s21_create_matrix(3, 2, &test1);
  test1.matrix[0][0] = 1;
  test1.matrix[0][1] = 4;
  test1.matrix[1][0] = 2;
  test1.matrix[1][1] = 5;
  test1.matrix[2][0] = 3;
  test1.matrix[2][1] = 6;
  s21_create_matrix(2, 1, &test2);
  test2.matrix[0][0] = 1;
  test2.matrix[1][0] = -1;
  s21_create_matrix(3, 1, &result2);
  result2.matrix[0][0] = -3;
  result2.matrix[1][0] = -3;
  result2.matrix[2][0] = -3;
  ck_assert_int_eq(s21_mult_matrix(&test1, &test2, &result1), OK);
  ck_assert_int_eq(s21_eq_matrix(&result2, &result1), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
  // 7
  s21_create_matrix(3, 3, &test1);
  test1.matrix[0][0] = 1;
  test1.matrix[0][1] = 2;
  test1.matrix[0][2] = 3;
  test1.matrix[1][0] = 4;
  test1.matrix[1][1] = 5;
  test1.matrix[1][2] = 4;
  test1.matrix[2][0] = 3;
  test1.matrix[2][1] = 2;
  test1.matrix[2][2] = 1;
  s21_create_matrix(3, 3, &test2);
  test2.matrix[0][0] = 0.2;
  test2.matrix[0][1] = 0.4;
  test2.matrix[0][2] = 0.1;
  test2.matrix[1][0] = 0.5;
  test2.matrix[1][1] = 0.6;
  test2.matrix[1][2] = 0.1;
  test2.matrix[2][0] = 1.2;
  test2.matrix[2][1] = 4;
  test2.matrix[2][2] = 1;
  s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 4.8;
  result2.matrix[0][1] = 13.6;
  result2.matrix[0][2] = 3.3;
  result2.matrix[1][0] = 8.1;
  result2.matrix[1][1] = 20.6;
  result2.matrix[1][2] = 4.9;
  result2.matrix[2][0] = 2.8;
  result2.matrix[2][1] = 6.4;
  result2.matrix[2][2] = 1.5;
  ck_assert_int_eq(s21_mult_matrix(&test1, &test2, &result1), OK);
  ck_assert_int_eq(s21_eq_matrix(&result2, &result1), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 8
  s21_create_matrix(1, 2, &test1);
  s21_create_matrix(3, 4, &test2);
  ck_assert_int_eq(s21_mult_matrix(&test1, &test2, &result1), ERR_CALC);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  // 9
  s21_create_matrix(3, 2, &test1);
  s21_create_matrix(0, 4, &test2);
  ck_assert_int_eq(s21_mult_matrix(&test1, &test2, &result1), ERR_MATRIX);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t test1 = {0}, result1, result2;
  int res_transp, res_eq;
  // 1
  test1.rows = -1;
  res_transp = s21_transpose(&test1, &result1);
  ck_assert_int_eq(res_transp, ERR_MATRIX);
  // 3
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &result2);
  test1.matrix[0][0] = 1;
  test1.matrix[0][1] = 2;
  test1.matrix[1][0] = 3;
  test1.matrix[1][1] = 4;
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = 3;
  result2.matrix[1][0] = 2;
  result2.matrix[1][1] = 4;
  res_transp = s21_transpose(&test1, &result1);
  res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_transp, 0);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 4
  s21_create_matrix(0, 3, &test1);
  ck_assert_int_eq(s21_transpose(&test1, &result1), ERR_MATRIX);
  // 6
  s21_create_matrix(3, 3, &test1);
  test1.matrix[0][0] = 0;
  test1.matrix[0][1] = 1;
  test1.matrix[0][2] = 2;
  test1.matrix[1][0] = 3;
  test1.matrix[1][1] = 4;
  test1.matrix[1][2] = 5;
  test1.matrix[2][0] = 6;
  test1.matrix[2][1] = 7;
  test1.matrix[2][2] = 8;
  s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 0;
  result2.matrix[0][1] = 3;
  result2.matrix[0][2] = 6;
  result2.matrix[1][0] = 1;
  result2.matrix[1][1] = 4;
  result2.matrix[1][2] = 7;
  result2.matrix[2][0] = 2;
  result2.matrix[2][1] = 5;
  result2.matrix[2][2] = 8;
  res_transp = s21_transpose(&test1, &result1);
  res_eq = s21_eq_matrix(&result2, &result1);
  ck_assert_int_eq(res_transp, OK);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  matrix_t test = {0}, result1, result2;
  int res_compl, res_eq;
  // 1
  test.rows = -1;
  res_compl = s21_calc_complements(&test, &result1);
  ck_assert_int_eq(res_compl, ERR_MATRIX);
  // 2
  s21_create_matrix(1, 1, &test);
  test.matrix[0][0] = 5;
  res_compl = s21_calc_complements(&test, &result1);
  ck_assert_int_eq(res_compl, ERR_CALC);
  s21_remove_matrix(&test);
  // 3
  s21_create_matrix(3, 3, &test);
  s21_create_matrix(3, 3, &result2);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  result2.matrix[0][0] = 0;
  result2.matrix[0][1] = 10;
  result2.matrix[0][2] = -20;
  result2.matrix[1][0] = 4;
  result2.matrix[1][1] = -14;
  result2.matrix[1][2] = 8;
  result2.matrix[2][0] = -8;
  result2.matrix[2][1] = -2;
  result2.matrix[2][2] = 4;
  res_compl = s21_calc_complements(&test, &result1);
  res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_compl, 0);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 4
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 9;
  test.matrix[0][1] = 8;
  test.matrix[0][2] = 7;
  test.matrix[1][0] = 6;
  test.matrix[1][1] = 5;
  test.matrix[1][2] = 4;
  test.matrix[2][0] = 3;
  test.matrix[2][1] = 8;
  test.matrix[2][2] = 9;
  s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 13;
  result2.matrix[0][1] = -42;
  result2.matrix[0][2] = 33;
  result2.matrix[1][0] = -16;
  result2.matrix[1][1] = 60;
  result2.matrix[1][2] = -48;
  result2.matrix[2][0] = -3;
  result2.matrix[2][1] = 6;
  result2.matrix[2][2] = -3;
  res_compl = s21_calc_complements(&test, &result1);
  res_eq = s21_eq_matrix(&result2, &result1);
  ck_assert_int_eq(res_compl, OK);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 5
  s21_create_matrix(3, 4, &test);
  ck_assert_int_eq(s21_calc_complements(&test, &result1), ERR_CALC);
  s21_remove_matrix(&test);
  // 6
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 4;
  test.matrix[0][2] = 5;
  test.matrix[1][0] = 2;
  test.matrix[1][1] = 3;
  test.matrix[1][2] = 6;
  test.matrix[2][0] = 9;
  test.matrix[2][1] = 8;
  test.matrix[2][2] = 7;
  s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = -27;
  result2.matrix[0][1] = 40;
  result2.matrix[0][2] = -11;
  result2.matrix[1][0] = 12;
  result2.matrix[1][1] = -38;
  result2.matrix[1][2] = 28;
  result2.matrix[2][0] = 9;
  result2.matrix[2][1] = 4;
  result2.matrix[2][2] = -5;
  res_compl = s21_calc_complements(&test, &result1);
  res_eq = s21_eq_matrix(&result2, &result1);
  ck_assert_int_eq(res_compl, OK);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(test_s21_determinant) {
  matrix_t test = {0};
  double result;
  int res_determ;
  // 1
  test.rows = -1;
  res_determ = s21_determinant(&test, &result);
  ck_assert_int_eq(res_determ, ERR_MATRIX);
  // 2
  s21_create_matrix(2, 4, &test);
  res_determ = s21_determinant(&test, &result);
  ck_assert_int_eq(res_determ, ERR_CALC);
  s21_remove_matrix(&test);
  // 3
  s21_create_matrix(1, 1, &test);
  res_determ = s21_determinant(&test, &result);
  ck_assert_int_eq(res_determ, OK);
  s21_remove_matrix(&test);

  // 4
  s21_create_matrix(2, 2, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 4;
  test.matrix[1][0] = 2;
  test.matrix[1][1] = 5;
  res_determ = s21_determinant(&test, &result);
  ck_assert_int_eq(res_determ, OK);
  ck_assert_int_eq(result, -3);
  s21_remove_matrix(&test);
  // 5
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 4;
  test.matrix[1][1] = 5;
  test.matrix[1][2] = 6;
  test.matrix[2][0] = 7;
  test.matrix[2][1] = 8;
  test.matrix[2][2] = 9;
  res_determ = s21_determinant(&test, &result);
  ck_assert_int_eq(res_determ, 0);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&test);
  // 6
  s21_create_matrix(4, 4, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[0][3] = 4;
  test.matrix[1][0] = 5;
  test.matrix[1][1] = 6;
  test.matrix[1][2] = 7;
  test.matrix[1][3] = 8;
  test.matrix[2][0] = 9;
  test.matrix[2][1] = 10;
  test.matrix[2][2] = 11;
  test.matrix[2][3] = 12;
  test.matrix[3][0] = 13;
  test.matrix[3][1] = 14;
  test.matrix[3][2] = 15;
  test.matrix[3][3] = 16;
  res_determ = s21_determinant(&test, &result);
  ck_assert_int_eq(res_determ, 0);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&test);
  // 7
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 5;
  test.matrix[0][2] = 7;
  test.matrix[1][0] = 6;
  test.matrix[1][1] = 3;
  test.matrix[1][2] = 4;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = -2;
  test.matrix[2][2] = -3;
  res_determ = s21_determinant(&test, &result);
  ck_assert_int_eq(res_determ, 0);
  ck_assert_int_eq(result, -1);
  s21_remove_matrix(&test);
}
END_TEST

START_TEST(test_s21_inverse) {
  matrix_t test = {0}, result1, result2;
  int res_inverse, res_eq;
  // 1
  test.rows = -4;
  res_inverse = s21_inverse_matrix(&test, &result1);
  ck_assert_int_eq(res_inverse, ERR_MATRIX);
  // 2
  s21_create_matrix(1, 1, &test);
  test.matrix[0][0] = 0;
  res_inverse = s21_inverse_matrix(&test, &result1);
  ck_assert_int_eq(res_inverse, ERR_CALC);
  s21_remove_matrix(&test);
  // 3
  s21_create_matrix(2, 2, &test);
  s21_create_matrix(2, 2, &result2);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[1][0] = -1;
  test.matrix[1][1] = 2;
  result2.matrix[0][0] = 0.5;
  result2.matrix[0][1] = -0.5;
  result2.matrix[1][0] = 0.25;
  result2.matrix[1][1] = 0.25;
  res_inverse = s21_inverse_matrix(&test, &result1);
  res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_inverse, OK);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  // 4
  s21_create_matrix(3, 3, &test);

  s21_create_matrix(3, 3, &result2);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 5;
  test.matrix[0][2] = 7;
  test.matrix[1][0] = 6;
  test.matrix[1][1] = 3;
  test.matrix[1][2] = 4;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = -2;
  test.matrix[2][2] = -3;
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = -1;
  result2.matrix[0][2] = 1;
  result2.matrix[1][0] = -38;
  result2.matrix[1][1] = 41;
  result2.matrix[1][2] = -34;
  result2.matrix[2][0] = 27;
  result2.matrix[2][1] = -29;
  result2.matrix[2][2] = 24;
  res_inverse = s21_inverse_matrix(&test, &result1);
  res_eq = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(res_inverse, OK);
  ck_assert_int_eq(res_eq, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

int main() {
  Suite *s = suite_create("s21_matrix_tests");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s);
  int number_failed;

  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_s21_create);
  tcase_add_test(tc_core, test_s21_eq);
  // tcase_add_test(tc_core, test_s21_remove);
  tcase_add_test(tc_core, test_s21_matrix_sum);
  tcase_add_test(tc_core, test_s21_matrix_sub);
  tcase_add_test(tc_core, test_s21_matrix_mult_number);
  tcase_add_test(tc_core, test_s21_matrix_mult_matrix);
  tcase_add_test(tc_core, test_s21_transpose);
  tcase_add_test(tc_core, test_s21_calc_complements);
  tcase_add_test(tc_core, test_s21_determinant);
  tcase_add_test(tc_core, test_s21_inverse);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

