#ifndef MATRIXHEADER
#define MATRIXHEADER

#include <iostream>
class Matrix{
    public:
	Matrix(int rows, int columns);
        ~Matrix();
        void read_from(std::istream &istr);
        void write_to(std::ostream &ostr);
        int size();
        int c_size();
        int64_t* operator[](int index);
//        bool* operator[](int index);
        Matrix operator*(Matrix& other);
        void generate();
        bool operator== (const Matrix& other);
    private:
	int64_t* a;
//        bool* a;
        int n, m;
};

#endif
