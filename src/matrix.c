#include "s21_matrix.h"

/**
 * @brief Создание матрицы
 *
 * @param rows кол-во строк
 * @param columns кол-во колонок
 * @param result результирующая матрица
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = OK;
  if (rows <= 0 || columns <= 0 || !result) {
    err = ERR_MATRIX;
    if (result) {
      result->rows = 0;
      result->columns = 0;
      result->matrix = NULL;
    }
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      for (int j = 0; j < columns; ++j) {
        result->matrix[i][j] = 0;
      }
    }
    result->rows = rows;
    result->columns = columns;
  }
  return err;
}

/**
 * @brief Очистка матрицы
 *
 * @param A очищаемая матрица.
 */
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL && A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

/**
 * @brief Сравнение двух матриц
 *
 * @param A 1 матрица
 * @param B 2 матрица

 * @return (int) 1 если равны и совпадают, 0 если не равны, не совпали элементы
 и если сравнение не прошло до 7 знака после запятой.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = SUCCESS;
  if ((A->rows == B->rows) && (A->columns == B->columns) &&
      (A->matrix != NULL && B->matrix != NULL)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          err = FAILURE;
          break;
        }
      }
    }
  } else {
    err = FAILURE;
  }
  return err;
}

/**
 * @brief Сумма матриц
 *
 * @param A 1 матрица
 * @param B 2 матрица
 * @param result результирующая матрица А+В
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = OK;
  if (s21_incorrect(A) || s21_incorrect(B)) {
    err = ERR_MATRIX;
  } else if (A->rows == B->rows && A->columns == B->columns) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else {
    err = ERR_CALC;
  }
  return err;
}

/**
 * @brief Разность матриц
 *
 * @param A 1 матрица
 * @param B 2 матрица
 * @param result результирующая матрица А-В
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = OK;
  if (s21_incorrect(A) || s21_incorrect(B)) {
    err = ERR_MATRIX;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    err = ERR_CALC;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return err;
}

/**
 * @brief Умножение матрицы на число
 *
 * @param A 1 матрица
 * @param number число, на которое умножаем все элементы матрицы
 * @param result результирующая матрица А[i][j]*n
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result) {  // A[i][j]*n
  int err = OK;
  if (s21_incorrect(A)) {
    err = ERR_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return err;
}

/**
 * @brief Умножение матрицы A * B
 *
 * @param A 1 матрица
 * @param B 2 матрица
 * @param result результирующая матрица С[m][n]. Только для матриц
 * A[m][k]*B[k][n]
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result) {  // A[m][k]*B[k][n]
  int err = OK;
  if (s21_incorrect(A) || s21_incorrect(B)) {
    err = ERR_MATRIX;
  } else if (A->columns != B->rows) {
    err = ERR_CALC;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] =
              result->matrix[i][j] + (A->matrix[i][k] * B->matrix[k][j]);
        }
      }
    }
  }
  return err;
}

/**
 * @brief Транспонированная матрица A
 *
 * @param A 1 матрица
 * @param result результирующая матрица A^T.
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (s21_incorrect(A)) {
    err = ERR_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return err;
}

/**
 * @brief Определитель матрицы
 *
 * @param A Исходная матрица
 * @param result число, равное сумме произведений элементов строки (столбца) на
 * соответствующие алгебраические дополнения. Высчитываемое по формулам. Только
 * для квадратной матрицы
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_determinant(matrix_t *A, double *result) {
  int err = OK;
  *result = 0.0;
  if (s21_incorrect(A)) {
    err = ERR_MATRIX;
  } else if (A->columns != A->rows) {
    err = ERR_CALC;
  } else {
    *result = s21_det_no_err(A);
  }
  return err;
}

/**
 * @brief Алгебраическое дополнение матрицы
 *
 * @param A Исходная матрица
 * @param result Результирующая матрица, равная значению минора умноженное на
 * -1^(i+j).
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = OK;
  matrix_t Min;
  if (s21_incorrect(A)) {
    err = ERR_MATRIX;
  } else if ((A->columns != A->rows) || A->rows == 1) {
    err = ERR_CALC;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double B = 0.0;
        Min = GetMinor(A, i, j);
        s21_determinant(&Min, &B);
        result->matrix[i][j] = B * pow(-1, i + j);
        s21_remove_matrix(&Min);
      }
    }
  }
  return err;
}

/**
 * @brief Обратная матрица
 *
 * @param A Исходная матрица. Обратной матрицы не существует, если определитель
 * равен 0.
 * @param result Результирующая матрица, находится по формуле 1/|A| * A^T
 * @return (int) 0 если ОК, 1 если некорректная матрица и 2 если нельзя
 * посчитать.
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = OK;
  double res_det = 0.0;
  s21_determinant(A, &res_det);
  if (s21_incorrect(A)) {
    err = ERR_MATRIX;
  } else if (A->rows == 1 || A->columns != A->rows || res_det == 0) {
    err = ERR_CALC;
  } else {
    matrix_t B, T;
    s21_calc_complements(A, &B);
    s21_transpose(&B, &T);
    s21_mult_number(&T, 1 / res_det, result);
    s21_remove_matrix(&B);
    s21_remove_matrix(&T);
  }
  return err;
}

/**
 * @brief Расчет определителя без учета проверок на корректность матрицы
 *
 * @param A Исходная матрица.
 * @param result (double) результат вычисления
 */
double s21_det_no_err(matrix_t *A) {
  double result = 0.0;
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else if (A->rows == 2) {
    result = (A->matrix[0][0] * A->matrix[1][1]) -
             (A->matrix[1][0] * A->matrix[0][1]);
  } else if (A->rows >= 3) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t Min = GetMinor(A, 0, j);
      result = result + pow(-1, j) * A->matrix[0][j] * s21_det_no_err(&Min);
      s21_remove_matrix(&Min);
    }
  }
  return result;
}

/**
 * @brief Проверка на некорректность матрицы
 *
 * @param A Исходная матрица.
 * @param result (int) 0 если матрица корректна и 1 если некорректна(столбцов
 * и строк < 0  или нулевая матрица)
 */
int s21_incorrect(matrix_t *A) {
  int err = OK;
  if (A->matrix == NULL) {
    err = ERR_MATRIX;
  } else if (A->rows <= 0 || A->columns <= 0) {
    err = ERR_MATRIX;
  }
  return err;
}

/**
 * @brief Получение матрицы без i-й строки и j-го столбца - Минор
 *
 * @param A Исходная матрица.
 * @param rows кол-во строк
 * @param columns кол-во колонок
 * @param result результирующая матрица
 */
matrix_t GetMinor(matrix_t *A, int rows, int columns) {
  matrix_t result;
  s21_create_matrix(A->rows - 1, A->columns - 1, &result);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      if (i >= rows && j >= columns) {
        result.matrix[i][j] = A->matrix[i + 1][j + 1];
      } else if (i >= rows && j < columns) {
        result.matrix[i][j] = A->matrix[i + 1][j];
      } else if (j >= columns && i < rows) {
        result.matrix[i][j] = A->matrix[i][j + 1];
      } else {
        result.matrix[i][j] = A->matrix[i][j];
      }
    }
  }
  return result;
}
