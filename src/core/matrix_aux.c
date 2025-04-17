#include "matrix_aux.h"

void clear_matrix(matrix_t* matrix) {
  for (int y = 0; y < matrix->rows; y++) {
    for (int x = 0; x < matrix->columns; x++) {
      matrix->matrix[y][x] = 0.0f;
    }
  }
}

int validate(int amount, ...) {
  int err = 0;
  va_list matrices;
  va_start(matrices, amount);
  for (int i = 0; i < amount && !err; i++) {
    matrix_t* curr = va_arg(matrices, matrix_t*);
    if (!curr || !curr->matrix || curr->rows < 1 || curr->columns < 1) {
      err = INPUT_ERR;
    }
  }
  va_end(matrices);
  return err;
}

int eq_dimensions(int amount, matrix_t* reference, ...) {
  int err = (!reference) * INPUT_ERR;
  if (!err) {
    int ref_rows = reference->rows;
    int ref_cols = reference->columns;
    int is_equal = 1;
    va_list matrices;
    va_start(matrices, reference);
    for (int i = 0; i < amount - 1 && is_equal; i++) {
      matrix_t* curr = va_arg(matrices, matrix_t*);
      if (!curr || curr->rows != ref_rows || curr->columns != ref_cols) {
        is_equal = 0;
      }
    }
    va_end(matrices);
    err = !is_equal;
  }
  return (!err);
}

void copy_matrix(matrix_t* src, matrix_t* dest) {
  int err = validate(1, src) || !dest;
  if (!err) {
    remove_matrix(dest);
    *dest = *src;
  }
}

double mult_matrix_partial(int y, int x, matrix_t* A, matrix_t* B) {
  double out = 0.0f;
  for (int xm = 0; xm < A->columns; xm++) {
    out += A->matrix[y][xm] * B->matrix[xm][x];
  }
  return out;
}

void fill_minor(int banned_y, int banned_x, matrix_t* in, matrix_t* out) {
  int oy = 0;
  for (int y = 0; y < in->rows; y++) {
    int valid_y = y != banned_y;
    int ox = 0;
    for (int x = 0; valid_y && x < in->columns; x++) {
      if (x != banned_x) {
        out->matrix[oy][ox++] = in->matrix[y][x];
      }
    }
    oy += valid_y;
  }
}

int create_minor(int banned_y, int banned_x, matrix_t* in, matrix_t* out) {
  matrix_t buffer = {};
  int err = create_matrix(in->rows - 1, in->columns - 1, &buffer);
  if (!err) {
    fill_minor(banned_y, banned_x, in, &buffer);
    copy_matrix(&buffer, out);
  }
  return err;
}

int determinant_wrapping(matrix_t* A, double* result) {
  int err = 0;
  *result = 0.0f;
  for (int x = 0; x < A->columns && !err; x++) {
    matrix_t minor = {0, 0, 0};
    double mdet = 0.0f;
    err = create_minor(0, x, A, &minor);
    if (!err) {
      err = determinant(&minor, &mdet);
      remove_matrix(&minor);
    }
    if (!err) {
      int minor_sign = x % 2 ? -1 : 1;
      *result += A->matrix[0][x] * mdet * minor_sign;
    }
  }
  return err;
}

int complements_wrapping(matrix_t* A, matrix_t* buffer) {
  int err = 0;
  for (int y = 0; y < A->rows && !err; y++) {
    for (int x = 0; x < A->columns && !err; x++) {
      matrix_t minor = {};
      double det = 0.0f;
      err = create_minor(y, x, A, &minor);
      if (!err) {
        err = determinant(&minor, &det);
        remove_matrix(&minor);
      }
      if (!err) {
        err = !isfinite(det) * CALC_ERR;
      }
      if (!err) {
        int sign = ((x + y) % 2) ? -1 : 1;
        buffer->matrix[y][x] = det * sign;
      }
    }
  }
  return err;
}

int inverse_wrapping_simple(matrix_t* A, matrix_t* result, double det) {
  if (result == A) {
    remove_matrix(result);
  }
  int err = create_matrix(1, 1, result);
  if (!err) {
    result->matrix[0][0] = 1 / det;
  }
  return err;
}

int inverse_wrapping_complex(matrix_t* A, matrix_t* result, double det) {
  matrix_t comps;
  int err = calc_complements(A, &comps);
  if (!err) {
    err = transpose(&comps, &comps);
  }
  if (!err) {
    err = mult_number(&comps, 1 / det, result);
    remove_matrix(&comps);
  }
  return err;
}

/*
void print_matrix(matrix_t matrix) {
  for (int y = 0; y < matrix.rows; y++) {
    for (int x = 0; x < matrix.columns; x++) {
      if (x) {
        printf("\t");
      }
      printf("%0.7g", matrix.matrix[y][x]);
    }
    printf("\n");
  }
}
*/