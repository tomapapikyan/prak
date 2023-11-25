#include <iostream>
#include <chrono>
#include "matrix.h"
#include "preprocess.h"

int main(){
    std::srand(time(NULL));

    int size;

    std::cin>>size;
    Matrix A(size, size), B(size, size), C(size, size);

    A.generate();
    B.generate();

    auto start = std::chrono::high_resolution_clock::now();
    mult_matrix(A, B, C);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"time: "<<duration.count()<<" microseconds\n";

    return 0;
}
