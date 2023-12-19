#ifndef MATRIXHEADER
#define MATRIXHEADER

#include <iostream>
class Matrix{
    public:
	Matrix(int rows, int columns);
        ~Matrix();
//        void read_from(std::istream &istr);
        void write_to(std::ostream &ostr);
        int size();
        int c_size();
        int32_t* operator[](int index);
        int32_t& operator()(int i,  int j);
        void generate();
        bool operator== (const Matrix& other);
    private:
	int32_t* a;
        int n, m;
        static int byte;
};

#endif
