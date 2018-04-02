#include <complex>
#include <array>
#include <vector>
#include <cmath>


namespace Equations
{

template <class T>
std::pair<bool, std::vector<std::complex<T>>>
quadratic(std::array<std::complex<T>, 3> v)
{
    std::vector<std::complex<T>> vec;
    if (norm(v[2]) == 0) {
        if (norm(v[1]) == 0) {
            if (norm(v[0]) == 0) {
                return {false, vec};
            } else {
                return {true, vec};
            }
        } else {
            vec.push_back(-v[0] / v[1]);
            return {true, vec};
        }
    } else {
        std::complex<T> D = v[1] * v[1] - (T) 4.0 * v[2] * v[0];
        if (norm(D) == 0) {
            vec.push_back(-v[1] / ((T) 2.0 * v[2]));
            return {true, vec};
        } else {
            std::complex<T> sd = std::sqrt(D);
            vec.push_back((-v[1] + sd) / ((T) 2.0 * v[2]));
            vec.push_back((-v[1] - sd) / ((T) 2.0 * v[2]));
            return {true, vec};
        }
    }
}

}
