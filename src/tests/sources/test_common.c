#include "../headers/test_common.h"

void fill_matrix(matrix_t* dest, double low, double high) {
  unsigned long long values = dest->rows * dest->columns;
  if (values > 1) {
    double increment = (high - low) / (values - 1);
    for (unsigned long long pos = 0; pos < values; pos++) {
      dest->matrix[pos / dest->columns][pos % dest->columns] =
          low + increment * pos;
    }
  } else {
    dest->matrix[0][0] = low;
  }
}