#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include "matrix.h"
#include "preprocess.h"
//#include "generate.h"

/*
int open_f(std::fstream &file, const char str[]){
    file.open(str, std::ios::trunc | std::ios::in | std::ios::out);
    if (!file){
        std::cout<<"Could not open the file: "<<str<<"\n";
        return 0;
    }
    return 1;
}
*/

int main(){

    int size;
/*    std::fstream input, output, test_output;

    if (!open_f(input, "../input.txt") || !open_f(output, "../output.txt") ||
        !open_f(test_output, "../test_output.txt"))
        return 0;
*/

    std::cin>>size;
    Matrix A(size, size), B(size, size), C(size, size);

    A.generate();
    B.generate();
/*
    generate_input(size, input);

//    input.seekg(0, std::ios::beg);

    input.close();
    input.open("../input.txt");//?

    A.read_from(input);
    B.read_from(input);
*/
    auto start = std::chrono::high_resolution_clock::now();
    mult_matrix(A, B, C);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

/*
    if (C == (A*B))
        std::cout<<"Correct\n";
*/

/*
    C.write_to(output);

    (A*B).write_to(test_output);

    input.close();
    output.close();
    test_output.close();
*/
    std::cout<<"time: "<<duration.count()<<" microseconds\n";

    return 0;
}
