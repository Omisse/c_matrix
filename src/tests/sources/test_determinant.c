#include "../headers/test_determinant.h"

START_TEST(determinant_1) {
  matrix_t A = {};
  double det = 0;
  ck_assert_int_eq(determinant(&A, &det), INPUT_ERR);
}
END_TEST

START_TEST(determinant_2) {
  matrix_t A;
  double det = 0;
  create_matrix(3, 2, &A);
  fill_matrix(&A, 1, 1);
  ck_assert_int_eq(determinant(&A, &det), CALC_ERR);
  ck_assert_double_eq(det, 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  matrix_t A;
  double det = 0;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 9);
  ck_assert_int_eq(determinant(&A, &det), 0);
  ck_assert_double_eq(det, 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t A;
  double det = 0;
  create_matrix(2, 2, &A);
  fill_matrix(&A, 1, 4);
  ck_assert_int_eq(determinant(&A, &det), 0);
  ck_assert_double_eq(det, -2);
  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_5) {
  matrix_t A;
  double det = 0;
  create_matrix(1, 1, &A);
  A.matrix[0][0] = 21;
  ck_assert_int_eq(determinant(&A, &det), 0);
  ck_assert_double_eq(det, 21);
  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_6) {
  matrix_t A;
  double det = 0;
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7;
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;
  ck_assert_int_eq(determinant(&A, &det), 0);
  ck_assert_double_eq(det, -1);
  remove_matrix(&A);
}
END_TEST

Suite* suite_determinant() {
  Suite* s = suite_create("determinant");
  TCase* tc = tcase_create("determinant-core");
  tcase_add_test(tc, determinant_1);
  tcase_add_test(tc, determinant_2);
  tcase_add_test(tc, determinant_3);
  tcase_add_test(tc, determinant_4);
  tcase_add_test(tc, determinant_5);
  tcase_add_test(tc, determinant_6);
  suite_add_tcase(s, tc);
  return s;
}