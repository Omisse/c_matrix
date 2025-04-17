#include "../headers/test_complements.h"

START_TEST(calc_complements_1) {
  matrix_t A;
  create_matrix(3, 3, &A);
  ck_assert_int_eq(calc_complements(&A, NULL), INPUT_ERR);
  remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t A;
  matrix_t C;
  create_matrix(1, 3, &A);
  fill_matrix(&A, 1, 3);
  ck_assert_int_eq(calc_complements(&A, &C), CALC_ERR);
  remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t A;
  matrix_t C;
  matrix_t E;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &E);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 5, A.matrix[2][1] = 2, A.matrix[2][2] = 1;
  ck_assert_int_eq(calc_complements(&A, &C), 0);
  E.matrix[0][0] = 0, E.matrix[0][1] = 10, E.matrix[0][2] = -20;
  E.matrix[1][0] = 4, E.matrix[1][1] = -14, E.matrix[1][2] = 8;
  E.matrix[2][0] = -8, E.matrix[2][1] = -2, E.matrix[2][2] = 4;
  ck_assert_int_eq(eq_matrix(&C, &E), 1);
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&E);
}
END_TEST

Suite* suite_calc_complements() {
  Suite* s = suite_create("complements");
  TCase* tc = tcase_create("complements-core");
  tcase_add_test(tc, calc_complements_1);
  tcase_add_test(tc, calc_complements_2);
  tcase_add_test(tc, calc_complements_3);
  suite_add_tcase(s, tc);
  return s;
}