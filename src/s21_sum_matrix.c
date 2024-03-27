#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 1;
  if (A && B && is_matrix_correct(A) && is_matrix_correct(B)) {
    if (are_dims_equal(A, B)) {
      error = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    } else
      error = 2;
  }
  return error;
}