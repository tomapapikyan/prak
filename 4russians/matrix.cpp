#include <iostream>
#include <stdlib.h>

int byte = 32;

class Matrix{
    public:
        Matrix(int rows, int columns);
        ~Matrix();
        void read_from(std::istream &istr);
        void write_to(std::ostream &ostr);
        int size();
        int c_size();
        int32_t* operator[](int index);
        int32_t& operator()(int i, int j);
        void generate();
        bool operator== (const Matrix& other);
    private:
        int32_t* a;
        int n, m;
};

Matrix::Matrix(int rows, int columns): n(rows), m(columns){
    a = new int32_t[rows * columns/byte];
    for (int i = 0; i < rows*columns/byte; i++)
            a[i] = 0;
}

Matrix::~Matrix(){
    delete[] a;
}

void Matrix::write_to(std::ostream &ostr){

    for (int i=0; i<n; i++){
        for (int j=0; j<m/byte; j++){
            for (int k = byte-1; k>=0; k--)
                ostr << ((a[i*m/byte+j]&(1<<k))>>k) << " ";
        }
        ostr << "\n";
    }
    ostr<<"\n";
}

int Matrix::size(){
    return n;
}

int Matrix::c_size(){
    return m;
}

int32_t* Matrix::operator[](int index){
    return (a + index*m/byte);
}

int32_t& Matrix::operator()(int i, int j){
    return a[(i*m + j)/byte];
}

void Matrix::generate(){
    for (int i = 0; i < n*m/byte; i++)
        a[i] = int32_t(std::rand());
}

bool Matrix::operator == (const Matrix & other){
    if (n != other.n || m != other.m)
        return false;
    for (int i = 0; i < n*m/byte; i++)
        if (a[i] != other.a[i])
            return false;
    return true;
}

