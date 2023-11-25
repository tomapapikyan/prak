#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include "matrix.h"
#include "test_matrix.h"
#include "preprocess.h"
//#include "generate.h"


int open_f(std::fstream &file, const char str[]){
    file.open(str, std::ios::trunc | std::ios::in | std::ios::out);
    if (!file){
        std::cout<<"Could not open the file: "<<str<<"\n";
        return 0;
    }
    return 1;
}


int main(){
    std::srand(time(NULL));

    int size;
    std::fstream input, output, test_output;

    if (!open_f(input, "../input.txt") || !open_f(output, "../output.txt") ||
        !open_f(test_output, "../test_output.txt"))
        return 0;


    std::cin>>size;
    Matrix A(size, size), B(size, size), C(size, size);

    A.generate();
    B.generate();
/*
    std::cout<<"A:\n";
    A.write_to(std::cout);
    std::cout<<"B:\n";
    B.write_to(std::cout);
*/
// check if operation * is correct
/*    A.write_to(input);
    B.write_to(input);

    (A*B).write_to(output);

    input.close();
    input.open("../input.txt");
    output.close();
    output.open("../output.txt");

    tMatrix tA(size, size), tB(size, size), tC(size, size);
    tA.read_from(input);
    tB.read_from(input);
    tC.read_from(output);
    if (tC == (tA*tB))
        std::cout<<"Correct!\n";
*/

    auto start = std::chrono::high_resolution_clock::now();
    mult_matrix(A, B, C);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
/*
    std::cout<<"\nYou got:\n";
    C.write_to(std::cout);
    std::cout<<"\nCorrect is:\n";
    (A*B).write_to(std::cout);
*/
/*
    if (C == (A*B))
        std::cout<<"Correct\n";
*/
    std::cout<<"time: "<<duration.count()<<" microseconds\n";

/*
    C.write_to(output);

    (A*B).write_to(test_output);

    input.close();
    output.close();
    test_output.close();
*/

    return 0;
}
