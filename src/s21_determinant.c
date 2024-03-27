#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = 1;
  if (A && is_matrix_correct(A)) {
    if (A->rows == A->columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
        error = 0;
      } else {
        double tmp = 0;
        for (int i = 0; i < A->columns; i++) {
          matrix_t submatrix = create_submatrix(A, 0, i);
          double tmp_det = 0;
          s21_determinant(&submatrix, &tmp_det);
          tmp += tmp_det * pow(-1, i) * A->matrix[0][i];
          s21_remove_matrix(&submatrix);
        }
        *result = tmp;
        error = 0;
      }
    } else
      error = 2;
  }
  return error;
}