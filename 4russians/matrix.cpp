#include <iostream>
#include <stdlib.h>

class Matrix{
    public:
        Matrix(int rows, int columns);
        ~Matrix();
        void read_from(std::istream &istr);
        void write_to(std::ostream &ostr);
        int size();
        bool* operator[](int index);
        Matrix operator*(Matrix& other);
        void generate();
        bool operator== (const Matrix& other);
    private:
        bool** a;
        int n, m;
};

Matrix::Matrix(int rows, int columns): n(rows), m(columns){
    a = new bool*[rows];
    for (int i = 0; i < rows; i++){
        a[i] = new bool[columns];
        for (int j = 0; j < columns; j ++)
            a[i][j] = 0;
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
}

void Matrix::read_from(std::istream& istr){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            istr >> a[i][j];
}
 void Matrix::write_to(std::ostream &ostr){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++)
            ostr << a[i][j] << " ";
        ostr << "\n";
    }
}

int Matrix::size(){
    return n;
}

bool* Matrix::operator[](int index){
    return a[index];
}

Matrix Matrix::operator*(Matrix& other){
    Matrix C(n, other.m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < other.m; j++)
            for (int k = 0; k < m; k++)
                C[i][j] = (C[i][j] != a[i][k]*other.a[k][j]);
    return C;
}

void Matrix::generate(){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = bool(std::rand()%2);
}

bool Matrix::operator== (const Matrix & other){
    if (n != other.n || m != other.m)
        return false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] != other.a[i][j])
                return false;
    return true;
}
