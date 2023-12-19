#include <iostream>
#include <chrono>
#include "matrix.h"
#include "preprocess.h"
#include <fstream>
#include "matmul_fortran.h"

int open_f(std::fstream &file, const char str[]){
    file.open(str, std::ios::trunc | std::ios::in | std::ios::out);
    if (!file){
        std::cout<<"Could not open file "<<str<<"\n";
        return 0;
    }
    return 1;
}

int main(int argc, char **argv){
    std::srand(time(NULL));
    std::string argv1 = argv[1];

    int size;

    std::cin>>size;
    Matrix A(size, size), B(size, size), C(size, size);
    A.generate();
    B.generate();
    auto start = std::chrono::high_resolution_clock::now();
        if (argv1=="c++")
            mult_matrix(A, B, C);
        if (argv1=="fortran")
            matmul_f90(size, size/32, A[0], B[0], C[0]);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"time: "<<duration.count()<<" microseconds\n";

//testing

    if (argc>2){

        std::fstream input, output, test_output;
        if (!open_f(input, "../input.txt") || !open_f(output, "../output.txt")
        || !open_f(test_output, "../test_output.txt"))
            return 0;

        A.write_to(input);
        B.write_to(input);
        C.write_to(output);

        int *a, *b;
        a = new int[size*size];
        b = new int[size*size];
        input.seekg(0);
        for (int i = 0; i < size*size; i++)
            input>>a[i];

        for (int i = 0; i < size*size; i++)
            input>>b[i];
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                int s=0;
                for (int k=0; k<size; k++)
                    s = (s != a[i*size + k]*b[k*size + j]);
                test_output<<s<<" ";
            }
            test_output<<"\n";
        }
        test_output<<"\n";
        if (system("diff ../output.txt ../test_output.txt"))
            std::cout<<"Wrong answer!\n";
        else
            std::cout<<"Correct\n";
    }

        return 0;
}
