#include "../headers/test_sum.h"

START_TEST(sum_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  ck_assert_int_eq(sum_matrix(&A, &B, NULL), INPUT_ERR);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(4, 4, &A);
  create_matrix(5, 5, &B);
  ck_assert_int_eq(sum_matrix(&A, &B, &C), CALC_ERR);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  fill_matrix(&A, 1, 1);
  fill_matrix(&B, 1, 1);
  B.matrix[3][3] = INFINITY;
  ck_assert_int_eq(sum_matrix(&A, &B, &C), CALC_ERR);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t E;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  create_matrix(5, 5, &E);
  fill_matrix(&A, 1, 1);
  fill_matrix(&B, 1, 1);
  fill_matrix(&E, 2, 2);
  ck_assert_int_eq(sum_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(sum_matrix_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t E;
  create_matrix(5, 5, &A);
  create_matrix(5, 5, &B);
  create_matrix(5, 5, &E);
  ck_assert_int_eq(sum_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(sum_matrix_6) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  create_matrix(3, 3, &E);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 5;
  A.matrix[2][0] = 0, A.matrix[2][1] = 0, A.matrix[2][2] = 6;

  B.matrix[0][0] = 1, B.matrix[0][1] = 0, B.matrix[0][2] = 0;
  B.matrix[1][0] = 2, B.matrix[1][1] = 0, B.matrix[1][2] = 0;
  B.matrix[2][0] = 3, B.matrix[2][1] = 4, B.matrix[2][2] = 1;

  E.matrix[0][0] = 2, E.matrix[0][1] = 2, E.matrix[0][2] = 3;
  E.matrix[1][0] = 2, E.matrix[1][1] = 4, E.matrix[1][2] = 5;
  E.matrix[2][0] = 3, E.matrix[2][1] = 4, E.matrix[2][2] = 7;
  ck_assert_int_eq(sum_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

Suite* suite_sum_matrix() {
  Suite* s = suite_create("sum");
  TCase* tc = tcase_create("sum-core");
  tcase_add_test(tc, sum_matrix_1);
  tcase_add_test(tc, sum_matrix_2);
  tcase_add_test(tc, sum_matrix_3);
  tcase_add_test(tc, sum_matrix_4);
  tcase_add_test(tc, sum_matrix_5);
  tcase_add_test(tc, sum_matrix_6);
  suite_add_tcase(s, tc);
  return s;
}