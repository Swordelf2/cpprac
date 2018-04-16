#include <utility> 
#include <algorithm>

template <class T>
class Coord
{
public:
    T row = {};
    T col = {};

    typedef T value_type;

    Coord() {};
    Coord(T _row, T _col = 0) : row(_row), col(_col) {};
};

template <class T>
T dist(Coord<T> range, Coord<T> p1, Coord<T> p2)
{
    T m = range.row;
    T n = range.col;

    T row_diff = std::abs(p2.row - p1.row);
    T col_diff = std::abs(p2.col - p1.col);

    T one = std::min(row_diff, m - row_diff);
    T two = std::min(col_diff, n - col_diff);

    return std::max(one, two);
}
