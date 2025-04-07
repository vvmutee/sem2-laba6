#include <iostream>
#include <stdexcept>

template<typename T, size_t N, size_t M>
class Matrix {
    static_assert(N <= 3 && M <= 3, "Matrix dimensions must be <= 3");

private:
    T data[N][M]{};

public:
    // Базовый конструктор
    Matrix() = default;

    // Конструктор копирования
    Matrix(const Matrix& other) {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = other.data[i][j];
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    data[i][j] = other.data[i][j];
        }
        return *this;
    }

    // Оператор ввода
    friend std::istream& operator>>(std::istream& in, Matrix& m) {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                in >> m.data[i][j];
        return in;
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j)
                out << m.data[i][j] << ' ';
            out << '\n';
        }
        return out;
    }

    // Оператор +
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Оператор +=
    Matrix& operator+=(const Matrix& other) {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] += other.data[i][j];
        return *this;
    }

    // Оператор *
    Matrix operator*(const Matrix<T, M, N>& other) const {
        static_assert(N == M, "Matrix multiplication requires N == M for square matrices");
        Matrix<T, N, N> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                for (size_t k = 0; k < M; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    // Оператор *=
    Matrix& operator*=(const T& scalar) {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] *= scalar;
        return *this;
    }

    // Оператор ++ (префикс)
    Matrix& operator++() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                ++data[i][j];
        return *this;
    }

    // Доступ к элементу (по ссылке для изменения)
    T& operator()(size_t i, size_t j) {
        if (i >= N || j >= M) throw std::out_of_range("Index out of bounds");
        return data[i][j];
    }

    // Доступ к элементу (только для чтения)
    const T& operator()(size_t i, size_t j) const {
        if (i >= N || j >= M) throw std::out_of_range("Index out of bounds");
        return data[i][j];
    }

    // Метод вычисления определителя (только для квадратных 2x2 и 3x3)
    T determinant() const {
        static_assert(N == M, "Determinant can only be calculated for square matrices");

        if constexpr (N == 1) {
            return data[0][0];
        } else if constexpr (N == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        } else if constexpr (N == 3) {
            return
                data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
                data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
                data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        } else {
            throw std::logic_error("Determinant not implemented for this size");
        }
    }
};
int main() {
    Matrix<int, 2, 2> A, B;
    std::cin >> A >> B;
    Matrix<int, 2, 2> C = A + B;
    std::cout << "C = A + B:\n" << C;
    ++C;
    std::cout << "C после ++:\n" << C;
    std::cout << "Определитель C: " << C.determinant() << "\n";
    C(0, 1) = 99;
    std::cout << "После изменения элемента C(0,1):\n" << C;
}

