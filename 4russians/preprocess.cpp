#include <cmath>
#include "matrix.h"

int bt = 64;

void xor_rows(int64_t *c, int64_t *a, int64_t *b, int n){
    for (int i = 0; i < n; i++){
        c[i] = (a[i] ^ b[i]);
    }
}

void fill_RowSums(Matrix &RowSums, Matrix &B, int i, int k){
    int n = B.c_size();
    for (int j = 1; j < 1<<k; j++){
        int l = std::floor(log(j) / log(2));
        xor_rows(RowSums[j], RowSums[j - (1<<l)], B[i+l], n/bt);
    }
}

int Num(int64_t *row, int i, int k){
    int r = 0;
    for (int j = 0; j < k; j++){
        int p = i+j;
        r += (1<<j)*((row[p/bt]&(1<<(bt-1-p%bt)))>>(bt-1-p%bt));
    }
    return r;
}


void mult_matrix(Matrix &A, Matrix &B, Matrix &C){
    int n = A.size();
    int k;
    if (n>1024)
        k = 19 - std::log(n/3) / std::log(2);
    else
        k = std::log(n) / std::log(2);
    Matrix RowSums(1<<k, n);

    for (int i = 0; i < n/k; i++){
        fill_RowSums(RowSums, B, i*k, k);
        for (int j = 0; j < n; j++)
            xor_rows(C[j], RowSums[Num(A[j], i*k, k)], C[j], n/bt);
    }

    if (n%k){
        fill_RowSums(RowSums, B, k*(n/k), n%k);
        for (int j = 0; j < n; j++)
            xor_rows(C[j], RowSums[Num(A[j], k*(n/k), n%k)], C[j], n/bt);
    }

}

