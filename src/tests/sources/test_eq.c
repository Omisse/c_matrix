#include "../headers/test_eq.h"

START_TEST(eq_matrix_1) {
  matrix_t A;
  matrix_t B;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  fill_matrix(&A, 0, 40);
  fill_matrix(&B, 0, 40);
  ck_assert_int_eq(eq_matrix(&A, &B), 1);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_2) {
  matrix_t A;
  matrix_t B;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  ck_assert_int_eq(eq_matrix(&A, &B), 1);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_3) {
  matrix_t A;
  matrix_t B;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  fill_matrix(&A, 0, 1);
  fill_matrix(&B, 0, 1);
  A.matrix[2][2] = 0.00000001;
  B.matrix[2][2] = 0.00000002;
  ck_assert_int_eq(eq_matrix(&A, &B), 1);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_4) {
  matrix_t A;
  matrix_t B;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  fill_matrix(&A, 0, 1);
  fill_matrix(&A, 0, 1);
  A.matrix[2][2] = 0.0000001;
  B.matrix[2][2] = 0.0000002;
  ck_assert_int_eq(eq_matrix(&A, &B), 0);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_5) {
  matrix_t A;
  matrix_t B;
  create_matrix(5, 5, &A);
  create_matrix(3, 4, &B);
  ck_assert_int_eq(eq_matrix(&A, &B), 0);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_6) {
  matrix_t A;
  matrix_t B = {};
  create_matrix(5, 5, &A);
  ck_assert_int_eq(eq_matrix(&A, &B), 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(eq_matrix_7) {
  matrix_t A;
  matrix_t B;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  fill_matrix(&A, 0, 5);
  fill_matrix(&B, 0, 10);
  ck_assert_int_eq(eq_matrix(&A, &B), 0);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

Suite* suite_eq_matrix() {
  Suite* s = suite_create("equality");
  TCase* tc = tcase_create("eq-core");
  tcase_add_test(tc, eq_matrix_1);
  tcase_add_test(tc, eq_matrix_2);
  tcase_add_test(tc, eq_matrix_3);
  tcase_add_test(tc, eq_matrix_4);
  tcase_add_test(tc, eq_matrix_5);
  tcase_add_test(tc, eq_matrix_6);
  tcase_add_test(tc, eq_matrix_7);
  suite_add_tcase(s, tc);
  return s;
}