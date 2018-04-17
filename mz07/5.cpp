#include <new>
#include <utility>
#include <stdexcept>

namespace Game
{

/* Matrix class */

template <class T>
class Matrix;

template <class T>
void swap(Matrix<T> &a, Matrix<T> &b);

template <class T>
class Matrix
{
    class Row_Lvalue;
    class Row_Rvalue;

public:
    Matrix(int _rows, int _cols);
    Matrix(int _rows, int _cols, const T &t);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other);
    ~Matrix();
    Matrix& operator=(const Matrix &other);
    Matrix& operator=(Matrix &&other);

    Row_Lvalue operator[](int i) &;
    const Row_Lvalue operator[](int i) const &;
    Row_Rvalue operator[](int i) &&;
    const Row_Rvalue operator[](int i) const &&;

    int get_rows() const;
    int get_cols() const;

    friend void swap<>(Matrix<T> &a, Matrix<T> &b);

    static constexpr int ROWS_MAX = 16384;
    static constexpr int COLS_MAX = 16384;
    static constexpr int MEM_MAX = 1073741824;
private:
    int rows;
    int cols;
    T *m;
    int el_alloc; // number of elements for which memory is alloc'd
};

/* Row class */

template <class T>
class Matrix<T>::Row_Lvalue
{
public:
    Row_Lvalue(int _len, T *_m);
    T& operator[](int j);
    const T& operator[](int j) const;
private:
    int len; // length of a row is the number of columns of the matrix
    T *m;
};

template <class T>
class Matrix<T>::Row_Rvalue
{
public:
    Row_Rvalue(int _len, T *_m);
    T&& operator[](int j);
    const T&& operator[](int j) const;
private:
    int len; // length of a row is the number of columns of the matrix
    T *m;
};

/* Matrix members definitions */

template <class T>
Matrix<T>::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
{
    if (!(
            rows > 0 && cols > 0 &&
            rows < ROWS_MAX && cols < COLS_MAX &&
            rows * cols * sizeof(T) < MEM_MAX)) {
        throw std::invalid_argument("Invalid matrix constructor arguments");
    }
    el_alloc = rows * cols;
    m = (T*) ::operator new(el_alloc * sizeof(*m));
    for (size_t i = 0; i < static_cast<size_t>(rows * cols); ++i) {
        new (&m[i]) T();
    }
}

template <class T>
Matrix<T>::Matrix(int _rows, int _cols, const T &t) : rows(_rows), cols(_cols)
{
    if (!(
            rows > 0 && cols > 0 &&
            rows < ROWS_MAX && cols < COLS_MAX &&
            rows * cols * sizeof(T) < MEM_MAX)) {
        throw std::invalid_argument("Invalid matrix constructor arguments");
    }
    el_alloc = rows * cols;
    m = (T*) ::operator new(el_alloc * sizeof(*m));
    for (size_t i = 0; i < static_cast<size_t>(rows * cols); ++i) {
        new (&m[i]) T(t);
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &other) : rows(other.rows), cols(other.cols)
{
    el_alloc = rows * cols;
    m = (T*) ::operator new(el_alloc * sizeof(*m));
    for (size_t i = 0; i < static_cast<size_t>(rows * cols); ++i) {
        new (&m[i]) T(other.m[i]);
    }
}

template <class T>
Matrix<T>::Matrix(Matrix<T> &&other) : rows(other.rows), cols(other.cols),
        m(other.m), el_alloc(other.el_alloc)
{
    other.m = nullptr;
    other.rows = other.cols = other.el_alloc = 0;
}

template <class T>
Matrix<T>::~Matrix()
{
    for (size_t i = 0; i < static_cast<size_t>(rows * cols); ++i) {
        m[i].~T();
    }
    ::operator delete(m);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other)
{
    // if we have enough memory, we will only copy the contents
    if (el_alloc >= other.rows * other.cols) {
        // destroy the current contents first
        for (int i = 0; i < rows * cols; ++i) {
            m[i].~T();
        }
        rows = other.rows;
        cols = other.cols;
        for (int i = 0; i < rows * cols; ++i) {
            new (&m[i]) T(other.m[i]);
        }
    } else {
        // normal copy-and swap
        Matrix<T> copied(other);
        swap(*this, copied);
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> &&other)
{
    Matrix<T> moved(std::move(other));
    swap(*this, moved);
    return *this;
}

template <class T>
typename Matrix<T>::Row_Lvalue Matrix<T>::operator[](int i) &
{
    if (i < 0 || i >= rows) {
        throw std::range_error("Invalid first index");
    }
    return Row_Lvalue(cols, m + i * cols);
}

template <class T>
const typename Matrix<T>::Row_Lvalue Matrix<T>::operator[](int i) const &
{
    if (i < 0 || i >= rows) {
        throw std::range_error("Invalid first index");
    }
    return Row_Lvalue(cols, m + i * cols);
}

template <class T>
typename Matrix<T>::Row_Rvalue Matrix<T>::operator[](int i) &&
{
    if (i < 0 || i >= rows) {
        throw std::range_error("Invalid first index");
    }
    return Row_Rvalue(cols, m + i * cols);
}

template <class T>
const typename Matrix<T>::Row_Rvalue Matrix<T>::operator[](int i) const &&
{
    if (i < 0 || i >= rows) {
        throw std::range_error("Invalid first index");
    }
    return Row_Rvalue(cols, m + i * cols);
}

template <class T>
int Matrix<T>::get_rows() const
{
    return rows;
}

template <class T>
int Matrix<T>::get_cols() const
{
    return cols;
}

template <class T>
void swap(Matrix<T> &a, Matrix<T> &b)
{
    std::swap(a.rows, b.rows);
    std::swap(a.cols, b.cols);
    std::swap(a.m, b.m);
}

/* Row class definitions */

template <class T>
Matrix<T>::Row_Lvalue::Row_Lvalue(int _len, T *_m) : len(_len), m(_m) {}

template <class T>
Matrix<T>::Row_Rvalue::Row_Rvalue(int _len, T*_m) :len(_len), m(_m) {}

template <class T>
T& Matrix<T>::Row_Lvalue::operator[](int j)
{
    if (j < 0 || j >= len) {
        throw std::range_error("Invalid second index");
    }
    return m[j];
}

template <class T>
const T& Matrix<T>::Row_Lvalue::operator[](int j) const
{
    if (j < 0 || j >= len) {
        throw std::range_error("Invalid second index");
    }
    return m[j];
}

template <class T>
T&& Matrix<T>::Row_Rvalue::operator[](int j)
{
    if (j < 0 || j >= len) {
        throw std::range_error("Invalid second index");
    }
    return std::move(m[j]);
}

template <class T>
const T&& Matrix<T>::Row_Rvalue::operator[](int j) const
{
    if (j < 0 || j >= len) {
        throw std::range_error("Invalid second index");
    }
    return std::move(m[j]);
}

}
