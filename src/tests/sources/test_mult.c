#include "../headers/test_mult.h"

START_TEST(mult_number_1) {
  matrix_t A;
  double number = 3.14;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 1);
  ck_assert_int_eq(mult_number(&A, number, NULL), INPUT_ERR);
  remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t A;
  matrix_t C;
  double number = INFINITY;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 1);
  ck_assert_int_eq(mult_number(&A, number, &C), CALC_ERR);
  remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t A;
  matrix_t C;
  double number = 3;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 1);
  A.matrix[2][2] = INFINITY;
  ck_assert_int_eq(mult_number(&A, number, &C), CALC_ERR);
  remove_matrix(&A);
  remove_matrix(&C);
}
END_TEST

START_TEST(mult_number_4) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  double number = 3;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &E);
  ck_assert_int_eq(mult_number(&A, number, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(mult_number_5) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  double number = 3;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 1);
  create_matrix(3, 3, &E);
  fill_matrix(&E, 3, 3);
  ck_assert_int_eq(mult_number(&A, number, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(mult_number_6) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  double number = 2;
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 2, A.matrix[2][1] = 3, A.matrix[2][2] = 4;
  create_matrix(3, 3, &E);
  E.matrix[0][0] = 2, E.matrix[0][1] = 4, E.matrix[0][2] = 6;
  E.matrix[1][0] = 0, E.matrix[1][1] = 8, E.matrix[1][2] = 4;
  E.matrix[2][0] = 4, E.matrix[2][1] = 6, E.matrix[2][2] = 8;
  ck_assert_int_eq(mult_number(&A, number, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t A;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 1);
  ck_assert_int_eq(mult_matrix(&A, NULL, NULL), INPUT_ERR);
  remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  fill_matrix(&A, 1, 1);
  B.matrix[2][2] = INFINITY;
  ck_assert_int_eq(mult_matrix(&A, &B, &C), CALC_ERR);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(3, 2, &A);
  create_matrix(3, 2, &B);
  ck_assert_int_eq(mult_matrix(&A, &B, &C), CALC_ERR);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  create_matrix(3, 3, &E);
  ck_assert_int_eq(mult_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(mult_matrix_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 3, &A);
  fill_matrix(&A, 2, 2);
  create_matrix(3, 3, &B);
  fill_matrix(&B, 1, 9);
  create_matrix(3, 3, &E);
  E.matrix[0][0] = 24, E.matrix[0][1] = 30, E.matrix[0][2] = 36;
  E.matrix[1][0] = 24, E.matrix[1][1] = 30, E.matrix[1][2] = 36;
  E.matrix[2][0] = 24, E.matrix[2][1] = 30, E.matrix[2][2] = 36;
  ck_assert_int_eq(mult_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

START_TEST(mult_matrix_6) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 2, &A);
  A.matrix[0][0] = 1, A.matrix[0][1] = 4;
  A.matrix[1][0] = 2, A.matrix[1][1] = 5;
  A.matrix[2][0] = 3, A.matrix[2][1] = 6;
  create_matrix(2, 3, &B);
  B.matrix[0][0] = 1, B.matrix[0][1] = -1, B.matrix[0][2] = 1;
  B.matrix[1][0] = 2, B.matrix[1][1] = 3, B.matrix[1][2] = 4;
  create_matrix(3, 3, &E);
  E.matrix[0][0] = 9, E.matrix[0][1] = 11, E.matrix[0][2] = 17;
  E.matrix[1][0] = 12, E.matrix[1][1] = 13, E.matrix[1][2] = 22;
  E.matrix[2][0] = 15, E.matrix[2][1] = 15, E.matrix[2][2] = 27;
  ck_assert_int_eq(mult_matrix(&A, &B, &C), 0);
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

Suite* suite_mult_matrix() {
  Suite* s = suite_create("mult");
  TCase* tcn = tcase_create("mult-num");
  TCase* tcm = tcase_create("mult-matrix");
  tcase_add_test(tcn, mult_number_1);
  tcase_add_test(tcn, mult_number_2);
  tcase_add_test(tcn, mult_number_3);
  tcase_add_test(tcn, mult_number_4);
  tcase_add_test(tcn, mult_number_5);
  tcase_add_test(tcn, mult_number_6);
  tcase_add_test(tcm, mult_matrix_1);
  tcase_add_test(tcm, mult_matrix_2);
  tcase_add_test(tcm, mult_matrix_3);
  tcase_add_test(tcm, mult_matrix_4);
  tcase_add_test(tcm, mult_matrix_5);
  tcase_add_test(tcm, mult_matrix_6);
  suite_add_tcase(s, tcn);
  suite_add_tcase(s, tcm);
  return s;
}