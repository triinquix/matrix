#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 1;
  if (A && B && is_matrix_correct(A) && is_matrix_correct(B)) {
    if (A->columns == B->rows) {
      error = s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          double tmp = 0;
          for (int k = 0; k < A->columns; k++)
            tmp += A->matrix[i][k] * B->matrix[k][j];
          result->matrix[i][j] = tmp;
        }
      }
    } else
      error = 2;
  }
  return error;
}