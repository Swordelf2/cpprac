#include <iostream>

struct Result
{
    int res = 0;
    Result(int a) : res(a) {};
};

Result A(int m, int n)
{
    try {
        if (m == 0) {
            throw Result(n + 1);
        } else {
            if (n == 0) {
                throw A(m - 1, 1);
            } else {
                throw A(m - 1, A(m, n - 1).res);
            }
        }
    }
    catch (Result result) {
        return result;
    }
}

int main()
{
    int n, m;
    std::cin >> m >> n;
    std::cout <<  A(m, n).res << std::endl;
}
