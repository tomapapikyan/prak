#ifndef PREPROCESS_HEADER
#define PREPROCESS_HEADER

#include "matrix.h"

void xor_rows(int32_t *a, int32_t *b, int32_t *c, int n);

void fill_RowSums(Matrix &RowSums, Matrix &B,
int i, int k);

int Num(int32_t *row, int i, int k);

void mult_matrix(Matrix &A, Matrix &B, Matrix &C);

#endif

