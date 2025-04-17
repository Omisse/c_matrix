#include "../headers/test_inverse.h"

START_TEST(inverse_matrix_1) {
  matrix_t A = {};
  matrix_t C;
  ck_assert_int_eq(inverse_matrix(&A, &C), INPUT_ERR);
}
END_TEST

START_TEST(inverse_matrix_2) {
  matrix_t A;
  matrix_t C;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 9);
  ck_assert_int_eq(inverse_matrix(&A, &C), CALC_ERR);
  remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t A;
  matrix_t C;
  create_matrix(5, 3, &A);
  fill_matrix(&A, 1, 9);
  ck_assert_int_eq(inverse_matrix(&A, &C), CALC_ERR);
  remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  create_matrix(1, 1, &A);
  create_matrix(1, 1, &E);
  A.matrix[0][0] = 21;
  E.matrix[0][0] = 1.0 / 21.0;
  ck_assert_int_eq(inverse_matrix(&A, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(inverse_matrix_5) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &E);
  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7;
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;
  E.matrix[0][0] = 1, E.matrix[0][1] = -1, E.matrix[0][2] = 1;
  E.matrix[1][0] = -38, E.matrix[1][1] = 41, E.matrix[1][2] = -34;
  E.matrix[2][0] = 27, E.matrix[2][1] = -29, E.matrix[2][2] = 24;
  ck_assert_int_eq(inverse_matrix(&A, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

Suite* suite_inverse_matrix() {
  Suite* s = suite_create("inverse");
  TCase* tc = tcase_create("inverse-core");
  tcase_add_test(tc, inverse_matrix_1);
  tcase_add_test(tc, inverse_matrix_2);
  tcase_add_test(tc, inverse_matrix_3);
  tcase_add_test(tc, inverse_matrix_4);
  tcase_add_test(tc, inverse_matrix_5);
  suite_add_tcase(s, tc);
  return s;
}