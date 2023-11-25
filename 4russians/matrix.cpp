#include <iostream>
#include <stdlib.h>

int byte = 64;

class Matrix{
    public:
        Matrix(int rows, int columns);
        ~Matrix();
        void read_from(std::istream &istr);
        void write_to(std::ostream &ostr);
        int size();
        int c_size();
        int64_t* operator[](int index);
        int64_t& operator()(int i, int j);
        Matrix operator*(Matrix& other);
        void generate();
        bool operator== (const Matrix& other);
    private:
        int64_t* a;
        int n, m;
};

Matrix::Matrix(int rows, int columns): n(rows), m(columns){
    a = new int64_t[rows * columns/byte];
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

int64_t* Matrix::operator[](int index){
    return (a + index*m/byte);
}

int64_t& Matrix::operator()(int i, int j){
    return a[(i*m + j)/byte];
}

Matrix Matrix::operator*(Matrix& other){
    Matrix C(n, other.m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < other.m; j++){
            int64_t sum = 0;
            for (int k = 0; k < m; k++){
                int p = k%byte;
                int64_t c = (a[(i*m+k)/byte]&(1<<(byte-1-p)))>>(byte-1-p);//a[i, k]
                p = j%byte;
                int8_t d = (other.a[(k*other.m + j)/byte]&(1<<byte-1-p))>>(byte-1-p);//b[k, j]
                sum = sum ^(c&d);
            }
            C(i, j) = C(i, j) | (sum<<(byte-1-j%byte));
        }
    return C;
}


void Matrix::generate(){
    for (int i = 0; i < n*m/byte; i++)
        a[i] = int64_t(std::rand());
}

bool Matrix::operator == (const Matrix & other){
    if (n != other.n || m != other.m)
        return false;
    for (int i = 0; i < n*m/byte; i++)
        if (a[i] != other.a[i])
            return false;
    return true;
}

