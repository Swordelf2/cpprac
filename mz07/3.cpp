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
        constexpr auto c_4 = static_cast<T>(4.0l);
        constexpr auto c_2 = static_cast<T>(2.0l);
        std::complex<T> D = v[1] * v[1] - c_4 * v[2] * v[0];
        std::complex<T> sd = std::sqrt(D);
        vec.push_back((-v[1] + sd) / (c_2 * v[2]));
        vec.push_back((-v[1] - sd) / (c_2 * v[2]));
        return {true, vec};
    }
}

}
