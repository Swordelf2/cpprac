#include <iostream>

struct Result
{
    int res = 0;
    Result(int a) : res(a) {};
};

void A(int m, int n)
{
    if (m == 0) {
        throw Result(n + 1);
    } else {
        if (n == 0) {
            A(m - 1, 1);
        } else {
            try {
                A(m, n - 1);
            } catch (Result recRes) {
                A(m - 1, recRes.res);
            }
        }
    }
}

int main()
{
    int n, m;
    std::cin >> m >> n;
    try {
        A(m, n);
    } catch (Result result) {
        std::cout <<  result.res << std::endl;
    }
}
