#include "../headers/test_main.h"

int main() {
  SRunner* sr = srunner_create(suite_create_matrix());
  srunner_add_suite(sr, suite_remove_matrix());
  srunner_add_suite(sr, suite_eq_matrix());
  srunner_add_suite(sr, suite_sum_matrix());
  srunner_add_suite(sr, suite_sub_matrix());
  srunner_add_suite(sr, suite_mult_matrix());
  srunner_add_suite(sr, suite_transpose());
  srunner_add_suite(sr, suite_calc_complements());
  srunner_add_suite(sr, suite_determinant());
  srunner_add_suite(sr, suite_inverse_matrix());
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
  return 0;
}