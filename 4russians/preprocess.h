#ifndef PREPROCESS_HEADER
#define PREPROCESS_HEADER

#include <cmath>
#include "matrix.h"

void xor_rows(bool *a, bool*b, bool*c, int n);

void fill_RowSums(Matrix &RowSums, Matrix &B,
int i, int k);

int Num(bool *row, int i, int k);

void mult_matrix(Matrix &A, Matrix &B, Matrix &C);

#endif
