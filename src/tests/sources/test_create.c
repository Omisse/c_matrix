#include "../headers/test_create.h"

START_TEST(create_matrix_1) {
  matrix_t A;
  ck_assert_int_eq(create_matrix(5, 5, &A), 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_2) {
  ck_assert_int_eq(create_matrix(5, 5, NULL), INPUT_ERR);
}
END_TEST

START_TEST(create_matrix_3) {
  matrix_t A;
  ck_assert_int_eq(create_matrix(5, 0, &A), INPUT_ERR);
}
END_TEST

Suite* suite_create_matrix() {
  Suite* s = suite_create("creation");
  TCase* tc = tcase_create("create-core");
  tcase_add_test(tc, create_matrix_1);
  tcase_add_test(tc, create_matrix_2);
  tcase_add_test(tc, create_matrix_3);
  suite_add_tcase(s, tc);
  return s;
}