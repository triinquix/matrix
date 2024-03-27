#include "s21_matrix.h"

int is_matrix_correct(matrix_t* A) {
  int res = 0;
  if (A->columns > 0 && A->rows > 0 && A->matrix) res = 1;
  return res;
}

int are_dims_equal(matrix_t* A, matrix_t* B) {
  int res = 0;
  if (A->rows == B->rows && A->columns == B->columns) res = 1;
  return res;
}

matrix_t create_submatrix(matrix_t* A, int row_to_delete,
                          int column_to_delete) {
  matrix_t res_mat;
  s21_create_matrix(A->rows - 1, A->columns - 1, &res_mat);
  int row_counter = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != row_to_delete) {
      int column_counter = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != column_to_delete) {
          res_mat.matrix[row_counter][column_counter] = A->matrix[i][j];
          column_counter++;
        }
      }
      row_counter++;
    }
  }
  return res_mat;
}