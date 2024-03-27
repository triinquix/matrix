#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 1;
  if (rows > 0 && columns > 0) {
    double **tmp_matrix = NULL;
    tmp_matrix = (double **)malloc(sizeof(double *) * rows);
    if (tmp_matrix) {
      for (int i = 0; i < rows; i++) {
        tmp_matrix[i] = (double *)malloc(sizeof(double) * columns);
        if (!tmp_matrix[i]) {
          for (int j = 0; j < i; j++) free(tmp_matrix[j]);
          free(tmp_matrix);
        }
      }
      if (tmp_matrix) {
        result->matrix = tmp_matrix;
        result->columns = columns;
        result->rows = rows;
        error = 0;
      }
    }
  }
  return error;
}