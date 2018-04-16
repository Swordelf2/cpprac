#include <complex>
#include <array>
#include <vector>
#include <cmath>
#include <limits>


namespace Equations
{

template <class T>
std::pair<bool, std::vector<std::complex<T>>>
quadratic(std::array<std::complex<T>, 3> v)
{
    constexpr T EPS = std::numeric_limits<T>::epsilon() * 32;
    std::vector<std::complex<T>> vec;
    if (norm(v[2]) < EPS) {
        if (norm(v[1]) < EPS) {
            if (norm(v[0]) < EPS) {
                return {false, vec};
            } else {
                return {true, vec};
            }
        } else {
            vec.push_back(-v[0] / v[1]);
            return {true, vec};
        }
    } else {
        std::complex<T> D = v[1] * v[1] - (T) 4.0L * v[2] * v[0];
        if (norm(D) < EPS) {
            vec.push_back(-v[1] / ((T) 2.0 * v[2]));
            vec.push_back(vec[0]);
            return {true, vec};
        } else {
            std::complex<T> sd = std::sqrt(D);
            vec.push_back((-v[1] + sd) / ((T) 2.0L * v[2]));
            vec.push_back((-v[1] - sd) / ((T) 2.0L * v[2]));
            return {true, vec};
        }
    }
}

}
