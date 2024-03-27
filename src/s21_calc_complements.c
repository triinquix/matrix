#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 1;
  if (A && is_matrix_correct(A)) {
    if (A->rows == A->columns) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (result->rows == 1)
        result->matrix[0][0] = 1;
      else {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            matrix_t submatrix = create_submatrix(A, i, j);
            double det = 0;
            error = s21_determinant(&submatrix, &det);
            result->matrix[i][j] = pow(-1, i + j) * det;
            s21_remove_matrix(&submatrix);
          }
        }
      }
    } else
      error = 2;
  }
  return error;
}