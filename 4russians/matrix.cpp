#include <iostream>
#include <stdlib.h>

class Matrix{
    public:
        Matrix(int rows, int columns);
        ~Matrix();
        void read_from(std::istream &istr);
        void write_to(std::ostream &ostr);
        int size();
        int c_size();
        bool* operator[](int index);
        Matrix operator*(Matrix& other);
        void generate();
        bool operator== (const Matrix& other);
    private:
        bool* a;
        int n, m;
};

Matrix::Matrix(int rows, int columns): n(rows), m(columns){
    a = new bool[rows * columns];
    for (int i = 0; i < rows*columns; i++)
            a[i] = 0;
}

Matrix::~Matrix(){
    delete[] a;
}

void Matrix::read_from(std::istream& istr){
    for (int i = 0; i < n*m; i++)
        istr >> a[i];
}
 void Matrix::write_to(std::ostream &ostr){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++)
            ostr << a[i*n + j] << " ";
        ostr << "\n";
    }
}

int Matrix::size(){
    return n;
}

int Matrix::c_size(){
    return m;
}

bool* Matrix::operator[](int index){
    return (a + index);
}

Matrix Matrix::operator*(Matrix& other){
    Matrix C(n, other.m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < other.m; j++)
            for (int k = 0; k < m; k++)
                *C[i*n + j] = (*C[i*n + j] != a[i*n + k]*other.a[k * other.n + j]);
    return C;
}

void Matrix::generate(){
    for (int i = 0; i < n*m; i++)
        a[i] = bool(std::rand()%2);
}

bool Matrix::operator == (const Matrix & other){
    if (n != other.n || m != other.m)
        return false;
    for (int i = 0; i < n*m; i++)
        if (a[i] != other.a[i])
            return false;
    return true;
}
