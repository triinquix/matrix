#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

matrix_t creat_test(int rows, int columns) {
  matrix_t res_matrix;
  int error = s21_create_matrix(rows, columns, &res_matrix);
  ck_assert_int_eq(error, 0);
  ck_assert_ptr_nonnull(res_matrix.matrix);
  ck_assert_int_eq(rows, res_matrix.rows);
  ck_assert_int_eq(columns, res_matrix.columns);
  return res_matrix;
}

void remove_test(matrix_t* A) {
  s21_remove_matrix(A);
  ck_assert_int_eq(A->columns, 0);
  ck_assert_int_eq(A->rows, 0);
  ck_assert_ptr_null(A->matrix);
}

START_TEST(mat_creat_norm) {
  matrix_t res_mat = creat_test(3, 9);
  remove_test(&res_mat);
}
END_TEST

START_TEST(mat_creat_incorrect) {
  matrix_t a;
  int error = s21_create_matrix(0, 12, &a);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite* mat_creat_suite() {
  Suite* s = suite_create("creation_suite");
  TCase* tc = tcase_create("tc_creat");
  tcase_add_test(tc, mat_creat_norm);
  tcase_add_test(tc, mat_creat_incorrect);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(equality_test_correct) {
  matrix_t a = creat_test(3, 7);
  matrix_t b = creat_test(3, 7);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 7; j++) {
      a.matrix[i][j] = 0.1234567;
      b.matrix[i][j] = 0.1234567;
    }
  }
  int error = s21_eq_matrix(&a, &b);
  ck_assert_int_eq(error, SUCCESS);
  remove_test(&a);
  remove_test(&b);
}
END_TEST

START_TEST(equality_test__wr_m) {
  matrix_t a = creat_test(3, 7);
  matrix_t b = {NULL, -1, -3};
  int error = s21_eq_matrix(&a, &b);
  ck_assert_int_eq(error, FAILURE);
  remove_test(&a);
}
END_TEST

START_TEST(equality_test__incorrect) {
  matrix_t a = creat_test(3, 7);
  matrix_t b = creat_test(3, 7);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 7; j++) {
      a.matrix[i][j] = 0.1234567;
      b.matrix[i][j] = 0.1234567;
    }
  }
  a.matrix[1][1] = 0.1234568;
  int error = s21_eq_matrix(&a, &b);
  ck_assert_int_eq(error, FAILURE);
  remove_test(&a);
  remove_test(&b);
}

Suite* eq_suite() {
  Suite* s = suite_create("eq_suite");
  TCase* tc = tcase_create("tc_eq");
  tcase_add_test(tc, equality_test_correct);
  tcase_add_test(tc, equality_test__incorrect);
  tcase_add_test(tc, equality_test__wr_m);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(add_correct) {
  matrix_t a = creat_test(3, 5);
  matrix_t b = creat_test(3, 5);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      a.matrix[i][j] = 1;
      b.matrix[i][j] = -1;
    }
  }
  matrix_t res_mat;
  int error = s21_sum_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < res_mat.rows; i++)
    for (int j = 0; j < res_mat.columns; j++)
      ck_assert_double_eq_tol(0, res_mat.matrix[i][j], eps);
  remove_test(&a);
  remove_test(&b);
  remove_test(&res_mat);
}
END_TEST

START_TEST(add_wr_dim) {
  matrix_t a = creat_test(4, 5);
  matrix_t b = creat_test(5, 4);
  matrix_t res_mat;
  int error = s21_sum_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 2);
  remove_test(&a);
  remove_test(&b);
}
END_TEST

START_TEST(add_inc_mat) {
  matrix_t a = {NULL, 3, -32};
  matrix_t b = creat_test(3, 13);
  matrix_t res_mat;
  int error = s21_sum_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 1);
  remove_test(&b);
}

Suite* sum_suite() {
  Suite* s = suite_create("suite_sum");
  TCase* tc = tcase_create("tc_sum");
  tcase_add_test(tc, add_correct);
  tcase_add_test(tc, add_inc_mat);
  tcase_add_test(tc, add_wr_dim);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(sub_correct) {
  matrix_t a = creat_test(3, 5);
  matrix_t b = creat_test(3, 5);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      a.matrix[i][j] = 1;
      b.matrix[i][j] = 1;
    }
  }
  matrix_t res_mat;
  int error = s21_sub_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < res_mat.rows; i++)
    for (int j = 0; j < res_mat.columns; j++)
      ck_assert_double_eq_tol(0, res_mat.matrix[i][j], eps);
  remove_test(&a);
  remove_test(&b);
  remove_test(&res_mat);
}
END_TEST

START_TEST(sub_wr_dim) {
  matrix_t a = creat_test(4, 5);
  matrix_t b = creat_test(5, 4);
  matrix_t res_mat;
  int error = s21_sub_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 2);
  remove_test(&a);
  remove_test(&b);
}
END_TEST

START_TEST(sub_inc_mat) {
  matrix_t a = {NULL, 3, -32};
  matrix_t b = creat_test(3, 13);
  matrix_t res_mat;
  int error = s21_sub_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 1);
  remove_test(&b);
}

Suite* sub_suite() {
  Suite* s = suite_create("suite_sub");
  TCase* tc = tcase_create("tc_sum");
  tcase_add_test(tc, sub_correct);
  tcase_add_test(tc, sub_inc_mat);
  tcase_add_test(tc, sub_wr_dim);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(scal_mul_cor) {
  matrix_t mat = creat_test(4, 5);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 5; j++) mat.matrix[i][j] = 1;
  double scalar = 4;
  matrix_t res_mat;
  int error = s21_mult_number(&mat, scalar, &res_mat);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < res_mat.rows; i++)
    for (int j = 0; j < res_mat.columns; j++)
      ck_assert_double_eq_tol(4, res_mat.matrix[i][j], eps);
  remove_test(&mat);
  remove_test(&res_mat);
}
END_TEST

START_TEST(sca_mul_incor) {
  matrix_t mat = {NULL, 1, 2};
  matrix_t res_mat;
  int error = s21_mult_number(&mat, 12, &res_mat);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite* scalar_suite() {
  Suite* s = suite_create("mul_by_scalar_suite");
  TCase* tc = tcase_create("tc_scalar_mul");
  tcase_add_test(tc, sca_mul_incor);
  tcase_add_test(tc, scal_mul_cor);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(matrix_mul_corr) {
  matrix_t a = creat_test(3, 2);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 4;
  a.matrix[1][0] = 2;
  a.matrix[1][1] = 5;
  a.matrix[2][0] = 3;
  a.matrix[2][1] = 6;
  matrix_t b = creat_test(2, 3);
  b.matrix[0][0] = 1;
  b.matrix[0][1] = -1;
  b.matrix[0][2] = 1;
  b.matrix[1][0] = 2;
  b.matrix[1][1] = 3;
  b.matrix[1][2] = 4;
  matrix_t res_mat;
  int error = s21_mult_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(a.rows, res_mat.rows);
  ck_assert_int_eq(b.columns, res_mat.columns);
  ck_assert_ldouble_eq_tol(9, res_mat.matrix[0][0], eps);
  ck_assert_ldouble_eq_tol(11, res_mat.matrix[0][1], eps);
  ck_assert_ldouble_eq_tol(17, res_mat.matrix[0][2], eps);
  ck_assert_ldouble_eq_tol(12, res_mat.matrix[1][0], eps);
  ck_assert_ldouble_eq_tol(13, res_mat.matrix[1][1], eps);
  ck_assert_ldouble_eq_tol(22, res_mat.matrix[1][2], eps);
  ck_assert_ldouble_eq_tol(15, res_mat.matrix[2][0], eps);
  ck_assert_ldouble_eq_tol(15, res_mat.matrix[2][1], eps);
  ck_assert_ldouble_eq_tol(27, res_mat.matrix[2][2], eps);
  remove_test(&a);
  remove_test(&b);
  remove_test(&res_mat);
}
END_TEST

START_TEST(matrix_mul_incor) {
  matrix_t a = {NULL, 1, 2};
  matrix_t b = {NULL, 12, -9};
  matrix_t res_mat;
  int error = s21_mult_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(matrix_mul_wr_dim) {
  matrix_t a = creat_test(1, 7);
  matrix_t b = creat_test(8, 8);
  matrix_t res_mat;
  int error = s21_mult_matrix(&a, &b, &res_mat);
  ck_assert_int_eq(error, 2);
  remove_test(&a);
  remove_test(&b);
}
END_TEST

Suite* matrix_mul_suite() {
  Suite* s = suite_create("Matrix mul suite");
  TCase* tc = tcase_create("tc_mat_mul");
  tcase_add_test(tc, matrix_mul_corr);
  tcase_add_test(tc, matrix_mul_incor);
  tcase_add_test(tc, matrix_mul_wr_dim);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(mat_transpose_correct) {
  matrix_t a = creat_test(3, 7);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;
  matrix_t res_mat;
  int error = s21_transpose(&a, &res_mat);
  ck_assert_int_eq(0, error);
  for (int i = 0; i < res_mat.rows; i++)
    for (int j = 0; j < res_mat.columns; j++)
      ck_assert_double_eq_tol(res_mat.matrix[i][j], a.matrix[j][i], eps);
  remove_test(&a);
  remove_test(&res_mat);
}
END_TEST

START_TEST(mat_transpose_incorrect) {
  matrix_t a = {NULL, -1, 5};
  matrix_t res_mat;
  int error = s21_transpose(&a, &res_mat);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite* transpose_suite() {
  Suite* s = suite_create("trans_suite");
  TCase* tc = tcase_create("tc_transpose");
  tcase_add_test(tc, mat_transpose_correct);
  tcase_add_test(tc, mat_transpose_incorrect);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(det_corr) {
  matrix_t a = creat_test(3, 3);
  int counter = 1;
  for (int i = 0; i < a.rows; i++, counter++)
    for (int j = 0; j < a.columns; j++, counter++) a.matrix[i][j] = counter;
  double det = 1;
  int error = s21_determinant(&a, &det);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(0, det, eps);
  remove_test(&a);
}
END_TEST

START_TEST(det_wr_dim) {
  matrix_t a = creat_test(3, 4);
  double det = 1;
  int error = s21_determinant(&a, &det);
  ck_assert_int_eq(error, 2);
  remove_test(&a);
}
END_TEST

START_TEST(det_incorrect) {
  matrix_t a = {NULL, 12, 2};
  double det = 1;
  int error = s21_determinant(&a, &det);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite* det_suite_create() {
  Suite* s = suite_create("Matrix determinant suite");
  TCase* tc = tcase_create("tc_det");
  tcase_add_test(tc, det_corr);
  tcase_add_test(tc, det_incorrect);
  tcase_add_test(tc, det_wr_dim);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(compl_corr) {
  matrix_t a = creat_test(3, 3);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  matrix_t compl_mat;
  int error = s21_calc_complements(&a, &compl_mat);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(compl_mat.matrix[0][0], 0, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[0][1], 10, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[0][2], -20, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[1][0], 4, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[1][1], -14, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[1][2], 8, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[2][0], -8, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[2][1], -2, eps);
  ck_assert_double_eq_tol(compl_mat.matrix[2][2], 4, eps);
  remove_test(&a);
  remove_test(&compl_mat);
}
END_TEST

START_TEST(compl_corr_2) {
  matrix_t a = creat_test(1, 1);
  a.matrix[0][0] = -0.2323;
  matrix_t res_mat;
  int error = s21_calc_complements(&a, &res_mat);
  ck_assert_int_eq(error, 0);
  remove_test(&a);
  remove_test(&res_mat);
}
END_TEST

START_TEST(compl_incor) {
  matrix_t a = {NULL, 1, 2};
  matrix_t res_mat;
  int error = s21_calc_complements(&a, &res_mat);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(compl_dim) {
  matrix_t a = creat_test(2, 4);
  matrix_t res_mat;
  int error = s21_calc_complements(&a, &res_mat);
  ck_assert_int_eq(error, 2);
  remove_test(&a);
}
END_TEST

Suite* compl_create_suite() {
  Suite* s = suite_create("complements suite");
  TCase* tc = tcase_create("tc_complements");
  tcase_add_test(tc, compl_corr);
  tcase_add_test(tc, compl_corr_2);
  tcase_add_test(tc, compl_dim);
  tcase_add_test(tc, compl_incor);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(inv_correct) {
  matrix_t a = creat_test(3, 3);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[0][2] = 7;
  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  a.matrix[1][2] = 4;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = -2;
  a.matrix[2][2] = -3;
  matrix_t res_mat;
  int error = s21_inverse_matrix(&a, &res_mat);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(res_mat.matrix[0][0], 1, eps);
  ck_assert_double_eq_tol(res_mat.matrix[0][1], -1, eps);
  ck_assert_double_eq_tol(res_mat.matrix[0][2], 1, eps);
  ck_assert_double_eq_tol(res_mat.matrix[1][0], -38, eps);
  ck_assert_double_eq_tol(res_mat.matrix[1][1], 41, eps);
  ck_assert_double_eq_tol(res_mat.matrix[1][2], -34, eps);
  ck_assert_double_eq_tol(res_mat.matrix[2][0], 27, eps);
  ck_assert_double_eq_tol(res_mat.matrix[2][1], -29, eps);
  ck_assert_double_eq_tol(res_mat.matrix[2][2], 24, eps);
  remove_test(&a);
  remove_test(&res_mat);
}
END_TEST

START_TEST(inv_det_zero) {
  matrix_t a = creat_test(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) a.matrix[i][j] = 1;
  matrix_t res_mat;
  int error = s21_inverse_matrix(&a, &res_mat);
  ck_assert_int_eq(error, 2);
  remove_test(&a);
}
END_TEST

START_TEST(inv_incorrect_mat) {
  matrix_t a = {NULL, 12, 2};
  matrix_t res_mat;
  int error = s21_inverse_matrix(&a, &res_mat);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(inv_wr_dim) {
  matrix_t a = creat_test(2, 4);
  matrix_t res_mat;
  int error = s21_inverse_matrix(&a, &res_mat);
  ck_assert_int_eq(error, 2);
  remove_test(&a);
}
END_TEST

Suite* create_inv_suite() {
  Suite* s = suite_create("inv_suite");
  TCase* tc = tcase_create("tc_inv_mat");
  tcase_add_test(tc, inv_correct);
  tcase_add_test(tc, inv_det_zero);
  tcase_add_test(tc, inv_incorrect_mat);
  tcase_add_test(tc, inv_wr_dim);
  suite_add_tcase(s, tc);
  return s;
}

void run_test(Suite* s, const char* test_kind, int* failed) {
  SRunner* sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  printf("\033[95m%s\n\033[92m", test_kind);
  srunner_run_all(sr, CK_MINIMAL);
  (*failed) += srunner_ntests_failed(sr);
  srunner_free(sr);
  printf("\n\033[39m");
}

int main() {
  int number_of_failed = 0;
  // Suites
  Suite* create_suite = mat_creat_suite();
  Suite* equality_suite = eq_suite();
  Suite* addition_suite = sum_suite();
  Suite* subtraction_suite = sub_suite();
  Suite* mul_by_scal_suite = scalar_suite();
  Suite* mul_matrices_suite = matrix_mul_suite();
  Suite* trans_suite = transpose_suite();
  Suite* det_suite = det_suite_create();
  Suite* compl_suite = compl_create_suite();
  Suite* inv_suite = create_inv_suite();
  // Running all tests
  run_test(create_suite, "Matrix creation tests and removal tests",
           &number_of_failed);
  run_test(equality_suite, "Matrix equality tests", &number_of_failed);
  run_test(addition_suite, "Matrix additions tests", &number_of_failed);
  run_test(subtraction_suite, "Matrix subtraction tests", &number_of_failed);
  run_test(mul_by_scal_suite, "Multiplication by scalar tests",
           &number_of_failed);
  run_test(mul_matrices_suite, "Multiplication of two matrices tests",
           &number_of_failed);
  run_test(trans_suite, "Matrix transpose tests", &number_of_failed);
  run_test(det_suite, "Matrix determinant tests", &number_of_failed);
  run_test(compl_suite, "Matrix of algebraic complements tests",
           &number_of_failed);
  run_test(inv_suite, "Inverse of the matrix tests", &number_of_failed);
  return (number_of_failed == 0) ? 0 : 1;
}