#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;
  if (A && B && is_matrix_correct(A) && is_matrix_correct(B) &&
      are_dims_equal(A, B)) {
    int rows = A->rows;
    int columns = A->columns;
    for (int i = 0; i < rows && error; i++)
      for (int j = 0; j < columns && error; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= eps) error = FAILURE;
  } else
    error = FAILURE;
  return error;
}