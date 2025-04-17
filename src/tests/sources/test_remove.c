#include "../headers/test_remove.h"

START_TEST(remove_matrix_1) {
  matrix_t A;
  create_matrix(5, 5, &A);
  remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(remove_matrix_2) {
  remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(remove_matrix_3) {
  matrix_t A = {};
  remove_matrix(&A);
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite* suite_remove_matrix() {
  Suite* s = suite_create("removing");
  TCase* tc = tcase_create("remove-core");
  tcase_add_test(tc, remove_matrix_1);
  tcase_add_test(tc, remove_matrix_2);
  tcase_add_test(tc, remove_matrix_3);
  suite_add_tcase(s, tc);
  return s;
}