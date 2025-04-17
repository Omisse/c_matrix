#include "../headers/test_transpose.h"

START_TEST(transpose_1) {
  matrix_t A = {};
  matrix_t C;
  ck_assert_int_eq(transpose(&A, &C), INPUT_ERR);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 2, &A);
  create_matrix(2, 3, &E);
  ck_assert_int_eq(transpose(&A, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  create_matrix(2, 3, &A);
  create_matrix(3, 2, &E);
  ck_assert_int_eq(transpose(&A, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(transpose_4) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  create_matrix(2, 3, &A);
  create_matrix(3, 2, &E);
  fill_matrix(&A, 1, 6);
  ck_assert_int_eq(transpose(&A, &C), 0);
  E.matrix[0][0] = 1, E.matrix[0][1] = 4;
  E.matrix[1][0] = 2, E.matrix[1][1] = 5;
  E.matrix[2][0] = 3, E.matrix[2][1] = 6;
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&E);
  remove_matrix(&C);
}
END_TEST

START_TEST(transpose_5) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 2, &A);
  create_matrix(2, 3, &E);
  A.matrix[0][0] = 1, A.matrix[0][1] = 4;
  A.matrix[1][0] = 2, A.matrix[1][1] = 5;
  A.matrix[2][0] = 3, A.matrix[2][1] = 6;
  ck_assert_int_eq(transpose(&A, &C), 0);
  E.matrix[0][0] = 1, E.matrix[0][1] = 2, E.matrix[0][2] = 3;
  E.matrix[1][0] = 4, E.matrix[1][1] = 5, E.matrix[1][2] = 6;
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&E);
  remove_matrix(&C);
}
END_TEST

START_TEST(transpose_6) {
  matrix_t A;
  matrix_t E;
  create_matrix(1, 2, &A);
  create_matrix(2, 1, &E);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  ck_assert_int_eq(transpose(&A, &A), 0);
  E.matrix[0][0] = 1;
  E.matrix[1][0] = 4;
  ck_assert_int_eq(eq_matrix(&A, &E), 1);
  remove_matrix(&A);
  remove_matrix(&E);
}
END_TEST

Suite* suite_transpose() {
  Suite* s = suite_create("transpose");
  TCase* tc = tcase_create("transpose-core");
  tcase_add_test(tc, transpose_1);
  tcase_add_test(tc, transpose_2);
  tcase_add_test(tc, transpose_3);
  tcase_add_test(tc, transpose_4);
  tcase_add_test(tc, transpose_5);
  tcase_add_test(tc, transpose_6);
  suite_add_tcase(s, tc);
  return s;
}