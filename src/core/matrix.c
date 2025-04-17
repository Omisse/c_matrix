#include "../matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int err = (!result) * INPUT_ERR;
  if (!err) {
    if ((rows < 1) || (columns < 1)) {
      err = INPUT_ERR;
      result->matrix = NULL;
    } else {
      result->matrix =
          (double **)malloc((rows * columns + rows) * sizeof(double));
      err = (!result->matrix) * INPUT_ERR;
    }
  }
  if (!err) {
    double *index = (double *)(result->matrix + rows);
    for (int y = 0; y < rows; y++) {
      result->matrix[y] = index + y * columns;
    }
    result->rows = rows;
    result->columns = columns;
    clear_matrix(result);
  }
  return err;
}

void remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    free(A->matrix);
    A->matrix = (void *)0;
    A->rows = 0;
    A->columns = 0;
  }
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int err = (validate(2, A, B));
  if (!err) {
    err = !eq_dimensions(2, A, B);
  }
  if (!err) {
    for (int y = 0; y < A->rows && !err; y++) {
      for (int x = 0; x < A->columns && !err; x++) {
        err = fabs(A->matrix[y][x] - B->matrix[y][x]) >= 1e-7;
      }
    }
  }
  return !err;
}

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = (validate(2, A, B) || !result) * INPUT_ERR;
  matrix_t buffer = {};
  if (!err) {
    err = (!eq_dimensions(2, A, B)) * CALC_ERR;
  }
  if (!err) {
    err = create_matrix(A->rows, A->columns, &buffer) * INPUT_ERR;
  }
  if (!err) {
    int soft_err = 0;
    for (int y = 0; y < buffer.rows; y++) {
      for (int x = 0; x < buffer.columns; x++) {
        buffer.matrix[y][x] = A->matrix[y][x] + B->matrix[y][x];
        soft_err += !isfinite(buffer.matrix[y][x]);
      }
    }
    if (result != A && result != B) {
      result->matrix = NULL;
    }
    copy_matrix(&buffer, result);
    err = (soft_err > 0) * CALC_ERR;
  }
  return err;
}

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = (validate(2, A, B) || !result) * INPUT_ERR;
  matrix_t buffer = {};
  if (!err) {
    err = (!eq_dimensions(2, A, B)) * CALC_ERR;
  }
  if (!err) {
    err = create_matrix(A->rows, A->columns, &buffer) * INPUT_ERR;
  }
  if (!err) {
    int soft_err = 0;
    for (int y = 0; y < buffer.rows; y++) {
      for (int x = 0; x < buffer.columns; x++) {
        buffer.matrix[y][x] = A->matrix[y][x] - B->matrix[y][x];
        soft_err += !isfinite(buffer.matrix[y][x]);
      }
    }
    if (result != A && result != B) {
      result->matrix = NULL;
    }
    copy_matrix(&buffer, result);
    err = (soft_err > 0) * CALC_ERR;
  }
  return err;
}

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = (validate(1, A) || !result) * INPUT_ERR;
  matrix_t buffer = {};
  if (!err) {
    err = !isfinite(number) * CALC_ERR;
  }
  if (!err) {
    err = create_matrix(A->rows, A->columns, &buffer);
  }
  if (!err) {
    int soft_err = 0;
    for (int y = 0; y < A->rows; y++) {
      for (int x = 0; x < A->columns; x++) {
        buffer.matrix[y][x] = A->matrix[y][x] * number;
        soft_err += !isfinite(buffer.matrix[y][x]);
      }
    }
    if (result != A) {
      result->matrix = NULL;
    }
    copy_matrix(&buffer, result);
    err = (soft_err > 0) * CALC_ERR;
  }
  return err;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = (validate(2, A, B) || !result) * INPUT_ERR;
  matrix_t buffer = {};
  if (!err) {
    err = (A->columns != B->rows) * CALC_ERR;
  }
  if (!err) {
    err = create_matrix(A->rows, B->columns, &buffer);
  }
  if (!err) {
    int soft_err = 0;
    for (int y = 0; y < buffer.rows; y++) {
      for (int x = 0; x < buffer.columns; x++) {
        buffer.matrix[y][x] = mult_matrix_partial(y, x, A, B);
        soft_err += !isfinite(buffer.matrix[y][x]);
      }
    }
    if (result != A || result != B) {
      result->matrix = NULL;
    }
    copy_matrix(&buffer, result);
    err = (soft_err > 0) * CALC_ERR;
  }
  return err;
}

int transpose(matrix_t *A, matrix_t *result) {
  int err = (validate(1, A) || !result) * INPUT_ERR;
  matrix_t buffer = {};
  if (!err) {
    err = create_matrix(A->columns, A->rows, &buffer);
  }
  if (!err) {
    for (int y = 0; y < buffer.rows; y++) {
      for (int x = 0; x < buffer.columns; x++) {
        buffer.matrix[y][x] = A->matrix[x][y];
      }
    }
    if (result != A) {
      result->matrix = NULL;
    }
    copy_matrix(&buffer, result);
  }
  return err;
}

int determinant(matrix_t *A, double *result) {
  int err = (validate(1, A) || !result) * INPUT_ERR;
  if (!err) {
    err = (A->rows != A->columns) * CALC_ERR;
  }
  if (!err) {
    if (A->columns == 1) {
      *result = A->matrix[0][0];
    } else if (A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      err = determinant_wrapping(A, result);
    }
  }
  return err;
}

int calc_complements(matrix_t *A, matrix_t *result) {
  int err = (validate(1, A) || !result) * INPUT_ERR;
  matrix_t buffer = {};
  int have_buffer = 0;
  if (!err) {
    err = (A->rows == 1 || A->columns == 1) * CALC_ERR;
  }
  if (!err) {
    err = create_matrix(A->rows, A->columns, &buffer);
    have_buffer = !err;
  }
  if (!err) {
    err = complements_wrapping(A, &buffer);
  }
  if (!err) {
    if (result != A) {
      result->matrix = NULL;
    }
    copy_matrix(&buffer, result);
  } else if (have_buffer) {
    remove_matrix(&buffer);
  }
  return err;
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = (validate(1, A) || !result) * INPUT_ERR;
  double det = 0.0f;
  if (!err) {
    err = determinant(A, &det);
  }
  if (!err) {
    err = ((det == 0) || (A->rows != A->columns)) * CALC_ERR;
  }
  if (!err) {
    if (A->rows == 1) {
      err = inverse_wrapping_simple(A, result, det);
    } else {
      err = inverse_wrapping_complex(A, result, det);
    }
  }
  return err;
}