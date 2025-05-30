#include <iostream>
#include <iomanip>
#include <stdexcept>


template <typename T>
class Matrix {
    int n, m;  // n - кол-во строк; m - кол-во столбцов
    T** data; //массив массивов, поэтому 2 звезды


   public:
    // Основной (базовый) конструктор
    Matrix(int rows, int cols) {
        std::cout << "Constr" << std::endl;
        n = rows;
        m = cols;
        data = new T* [n];//будут содержаться адреса массивов
        for (int i = 0; i < n; i++) data[i] = new T [m];//массив массивов, поэтому 2 звезды
    }


    // Конструктор копирования для создания новой матрицы на основе предыдущей
    Matrix(const Matrix& other) : Matrix(other.n, other.m) {
        std::cout << "Copy Constr" << std::endl;


        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) data[i][j] = other.data[i][j];
    }


    // Оператор присваивания копированием  для копирования существующей в существующую
    Matrix& operator=(const Matrix& other) {
        for (int i = 0; i < n; i++) delete[] data[i]; //удаляем предыдущие данные, чтобы присвоить новое


        delete[] data;


        n = other.n;
        m = other.m;


        data = new T*[n];
        for (int i = 0; i < n; i++) data[i] = new T[m];


        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) data[i][j] = other.data[i][j];


        return *this;
    }


    // Деструктор Он вызывается автоматически, мы его не вызываем
    ~Matrix() {
        std::cout << "Destr before" << std::endl;
        for (int i = 0; i < n; i++) delete[] data[i];


        delete[] data;
        std::cout << "Destr after" << std::endl;
    }


    friend Matrix operator + (const Matrix& a, const Matrix& b) //дружественная функция не является приватной, но имеет доступ к приватным данным класса
    {
        if (a.n != b.n || a.m != b.m)
            throw std::length_error("Sizes do not match.");


        Matrix c = Matrix(a.n, a.m);


        for (int i = 0; i < c.n; i++)
            for (int j = 0; j < c.m; j++)
                c.data[i][j] = a.data[i][j] + b.data[i][j];


        return c;
    }
   
    friend std::ostream& operator << (std::ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++)
                os << std::setw(5) << a.data[i][j];
            os << std::endl;
        }
        return os;
    }


    T * operator [] (int i)
    {
        return data[i];
    }
    friend std::istream& operator >>(std::istream& in, const Matrix& a) //оператор ввода
    {
        for(int i = 0; i < a.n; i++)
            for(int j = 0; j < a.m; j++)
                in >> a.data[i][j];
        return in;
    }


    Matrix&  operator += (const Matrix& other)
    {
        if(n != other.n || m != other.m)
            throw std::length_error("Sizes do not match.");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
               this->data[i][j] += other.data[i][j];
       return *this;
    }
    friend Matrix operator * (const Matrix& a, const Matrix& b)
    {
        if(a.m != b.n)
            throw std::length_error("Sizes do not match.");
        Matrix result(a.n, b.m);


        for (int i = 0; i < a.n; i++)
            for (int j = 0; j < b.m; j++)
                for(int k = 0; k < a.m; k++)
                    result[i][j] += a.data[i][k] * b.data[k][j];
        return result;
    }
    Matrix&  operator *= (const Matrix& other)
    {
        if(m != other.n)
            throw std::length_error("Sizes do not match.");
       
        *this = *this * other;    
        return *this;
    }
    Matrix& operator ++( )
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                this -> data[i][j]++;
        return *this;
    }
    T det()
    {
        if(n != m) throw std::length_error("Sizes do not match.");
        if(n == 1)
            return data[0][0];
        if(n == 2)
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        if(n == 3)
            return data[0][0] * data[1][1] * data[2][2] - data[0][0] * data[1][2] * data[2][1] - data[0][1] * data[1][0] * data[2][2] + data[0][1] * data[1][2] * data[2][0] + data[0][2] * data[1][0] * data[2][1] - data[0][2] * data[1][1] * data[2][1];
    }

};





int main()
{
    Matrix<int> a(3, 3);
    std::cin >> a;
    Matrix<int> c(3, 3);
    std::cin >> c;


    std::cout << ++a << std::endl;
    std::cout << c << std::endl;
    int y = c.det();
    std::cout << y <<std::endl;
    return 0;
}
