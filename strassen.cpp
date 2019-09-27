#include <iostream>
using namespace std;

template <typename T>
class Matrix {
    public:
        int n;
        T** arr = NULL;
    
        Matrix();
        Matrix(int size);
        Matrix operator + (Matrix const &Obj);
        Matrix operator - (Matrix const &Obj);
        Matrix divide(Matrix Obj, int x, int y);
        Matrix conquer(Matrix C11, Matrix C12, Matrix C21, Matrix C22);
        Matrix operator * (Matrix const &Obj);
};

template <class T>
Matrix<T>::Matrix() {}

template <class T>
Matrix<T>::Matrix(int size) {
    n = size;
    arr = new T*[n];
    for (int i = 0;i < n;i++)
        arr[i] = new T[n];
}

template <class T>
Matrix<T> Matrix<T>::operator + (Matrix const &Obj)
{
    Matrix B(n);
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++)
            B.arr[i][j] = arr[i][j] + Obj.arr[i][j];
    return B;
}

template <class T>
Matrix<T> Matrix<T>::operator - (Matrix const &Obj)
{
    Matrix B(n);
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++)
            B.arr[i][j] = arr[i][j] - Obj.arr[i][j];
    return B;
}


template <class T>
Matrix<T> Matrix<T>::divide(Matrix Obj, int x, int y)
{
    int size = Obj.n / 2;
    Matrix R(size);
    for (int i = 0;i < size;i++)
        for (int j = 0;j < size;j++)
            R.arr[i][j] = Obj.arr[i + x][j + y];
    return R;
}

template <class T>
Matrix<T> Matrix<T>::conquer(Matrix C11, Matrix C12, Matrix C21, Matrix C22)
{
    Matrix R(n);
    for (int i = 0;i < n/2;i++)
        for (int j = 0;j < n/2;j++)
            R.arr[i][j] = C11.arr[i][j];
    for (int i = 0;i < n/2;i++)
        for (int j = 0;j < n/2;j++)
            R.arr[i][j + n/2] = C12.arr[i][j];
    for (int i = 0;i < n/2;i++)
        for (int j = 0;j < n/2;j++)
            R.arr[i + n/2][j] = C21.arr[i][j];
    for (int i = 0;i < n/2;i++)
        for (int j = 0;j < n/2;j++)
            R.arr[i + n/2][j + n/2] = C22.arr[i][j];
    return R;
}


template <class T>
Matrix<T> Matrix<T>::operator * (Matrix const &Obj)
{
    if (n == 1) {
        Matrix R(1);
        R.arr[0][0] = arr[0][0] * Obj.arr[0][0];
        return R;
    }
    else {
        Matrix A11 = divide(*this, 0, 0);
        Matrix A12 = divide(*this, 0, n/2);
        Matrix A21 = divide(*this, n/2, 0);
        Matrix A22 = divide(*this, n/2, n/2);

        Matrix B11 = divide(Obj, 0, 0);
        Matrix B12 = divide(Obj, 0, n/2);
        Matrix B21 = divide(Obj, n/2, 0);
        Matrix B22 = divide(Obj, n/2, n/2);

        Matrix P1 = (A11 + A22) * (B11 + B22);
        Matrix P2 = (A21 + A22) * B11;
        Matrix P3 = A11 * (B12 - B22);
        Matrix P4 = A22 * (B21 - B11);
        Matrix P5 = (A11 + A12) * B22;
        Matrix P6 = (A21 - A11) * (B11 + B12);
        Matrix P7 = (A12 - A22) * (B21 + B22);

        Matrix C11 = P1 + P4 - P5 + P7;
        Matrix C12 = P3 + P5;
        Matrix C21 = P2 + P4;
        Matrix C22 = P1 - P2 + P3 + P6;
        return conquer(C11, C12, C21, C22);
    }
}

int main()
{
    int size;
    cout << "Enter the size of Matrix (Power of 2 only): ";
    cin >> size;

    Matrix<int> M1(size);
    cout << "Enter the Matrix 1:\n";
    for (int i = 0;i < size;i++)
        for (int j = 0;j < size;j++)
            cin >> M1.arr[i][j];

    Matrix<int> M2(size);
    cout << "Enter the Matrix 2:\n";
    for (int i = 0;i < size;i++)
        for (int j = 0;j < size;j++)
            cin >> M2.arr[i][j];

    Matrix M3 = M1 * M2;

    cout << "The product of two matrix is:\n";
    for (int i = 0;i < size;i++) {
        for (int j = 0;j < size;j++)
            cout << M3.arr[i][j] << " ";
        cout << "\n";
    }  
}
