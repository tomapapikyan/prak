#ifndef PREPROCESS_HEADER
#define PREPROCESS_HEADER

#include "matrix.h"

void xor_rows(int64_t *a, int64_t *b, int64_t *c, int n);

void fill_RowSums(Matrix &RowSums, Matrix &B,
int i, int k);

int Num(int64_t *row, int i, int k);

void mult_matrix(Matrix &A, Matrix &B, Matrix &C);

#endif

