#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 1;
  if (A && is_matrix_correct(A)) {
    if (A->rows == A->columns) {
      double det = 0;
      error = s21_determinant(A, &det);
      if (fabs(det) < eps)
        error = 2;
      else {
        matrix_t alg_com;
        error = s21_calc_complements(A, &alg_com);
        matrix_t trans_alg_com;
        error = s21_transpose(&alg_com, &trans_alg_com);
        s21_remove_matrix(&alg_com);
        error = s21_mult_number(&trans_alg_com, 1 / det, result);
        s21_remove_matrix(&trans_alg_com);
      }
    } else
      error = 2;
  }
  return error;
}