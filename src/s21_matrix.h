#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <math.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define eps 1e-7

// Creates a matrix
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Deletes given matrix
void s21_remove_matrix(matrix_t *A);

// Checks if two given matrices are equal
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Checks if given matrix is correct
int is_matrix_correct(matrix_t *A);

// Checks if dimensions of two given matrices are equal
int are_dims_equal(matrix_t *A, matrix_t *B);

// Adds two matrices
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Subtracts second matrix from the first one
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Multiplies given matrix by a given scalar
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Multiplies two given matrices
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Transposes given matrix
int s21_transpose(matrix_t *A, matrix_t *result);

// Calculates a determinant of the given matrix
int s21_determinant(matrix_t *A, double *result);

// Creates a submatrix of the given matrix by deleting a row and a column
matrix_t create_submatrix(matrix_t *A, int row_to_delete, int column_to_delete);

// Calculates matrix of algebraic complements of the given matrix
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Calculates an inverse matrix for the given matrix
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif