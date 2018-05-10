#include <iostream>
#include <vector>
#include <cstdint>
#include <thread>
#include <cmath>
#include <future>

using namespace std;

bool is_prime(uint64_t num)
{
    if (num < 2) {
        return false;
    }
    uint64_t sqr_root = floor(sqrt(num));
    for (uint64_t i = 2; i <= sqr_root; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void thread_func(uint64_t low, uint64_t high, promise<uint64_t> *prs, uint32_t count)
{
    uint32_t i = 0;
    for (uint64_t num = low; num <= high && i < count; ++num) {
        if (is_prime(num)) {
            prs[i++].set_value(num);
        }
    }
    if (i < count) {
        prs[i].set_exception(make_exception_ptr(high));
    }
}

int main()
{
    uint64_t low, high;
    uint32_t count;
    cin >> low >> high >> count;

    vector<promise<uint64_t>> prs(count);
    vector<future<uint64_t>> fts(count);

    for (uint32_t i = 0; i < count; ++i) {
        fts[i] = prs[i].get_future();
    }

    thread thr(thread_func, low, high, prs.data(), count);

    try {
        for (uint32_t i = 0; i < count; ++i) {
            cout << fts[i].get() << endl;
        }
    } catch (uint64_t e) {
        cout << e << endl;
    }

    thr.join();
}
