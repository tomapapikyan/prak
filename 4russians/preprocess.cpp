#include <cmath>
#include "matrix.h"

void xor_rows(bool *a, bool*b, bool*c, int n){
    for (int i = 0; i < n; i++)
        c[i] = (a[i] != b[i]);
}

void fill_RowSums(Matrix &RowSums, Matrix &B, int i, int k){

    for (int l = 1; l < pow(2, k); l++){
        int m = std::floor(log(l) / log(2));
        xor_rows(RowSums[l - pow(2, m)], B[i + m], RowSums[l], B.size());
    }
}

int Num(bool *row, int i, int k){
    int r = 0;
    for (int j = 0; j < k; j++){
        r += row[i + j] * pow(2, j);
    }
    return r;
}


void mult_matrix(Matrix &A, Matrix &B, Matrix &C){

    int n = A.size();
    int k = std::log(n) / std::log(2);
    Matrix RowSums(pow(2, k), n);

    for (int i = 0; i < n/k; i++){
        fill_RowSums(RowSums, B, i*k, k);
        for (int j = 0; j < n; j++)
            xor_rows(C[j], RowSums[Num(A[j], i*k, k)], C[j], n);
    }

    if (n%k){
        fill_RowSums(RowSums, B, k*(n/k), n%k);
        for (int j = 0; j < n; j++)
            xor_rows(C[j], RowSums[Num(A[j], k*(n/k), n%k)], C[j], n);
    }
}

