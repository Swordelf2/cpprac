#include <utility> 
#include <algorithm>

template <class T>
class Coord
{
public:
    int row = 0;
    int col = 0;

    typedef T value_type;

    Coord() {};
    Coord(int _row, int _col = 0) : row(_row), col(_col) {};
};

template <class T>
T dist(Coord<T> range, Coord<T> p1, Coord<T> p2)
{
    int m = range.row;
    int n = range.col;
    if (p2.row < p1.row) {
        std::swap(p2.row, p1.row);
    }
    if (p2.col < p1.col) {
        std::swap(p2.col, p1.col);
    }
    T one = std::min(p2.row - p1.row, p1.row - p2.row + m);
    T two = std::min(p2.col - p1.col, p1.col - p2.col + n);

    return std::max(one, two);
}
