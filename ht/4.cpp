#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <future>
#include <iomanip>
#include <utility>

using namespace std;

pair<uint64_t, uint64_t> thr_func(uint32_t id, uint64_t op_cnt)
{
    uint64_t in_circle = 0, overall = 0;
    for (uint64_t i = 0; i < op_cnt; ++i) {
        double x = (double) rand_r(&id) / RAND_MAX;
        double y = (double) rand_r(&id) / RAND_MAX;
        double newx = x - 0.5;
        double newy = y - 0.5;
        if (newx * x + newy * newy <= 0.25) {
            ++in_circle;
        }
        ++overall;
    }
    return {in_circle, overall};
}

int main(int argc, char *argv[])
{
    uint64_t thr_cnt = strtoull(argv[1], NULL, 0);
    uint32_t op_cnt = strtoul(argv[2], NULL, 0);
    
    vector<future<pair<uint64_t, uint64_t>>> fts(thr_cnt);
    for (uint32_t i = 0; i < thr_cnt; ++i) {
        fts[i] = async(launch::async, thr_func, i, op_cnt);
    }

    uint64_t in_circle = 0, overall = 0;
    for (uint32_t i = 0; i < thr_cnt; ++i) {
        auto p = fts[i].get();
        in_circle += p.first;
        overall += p.second;
    }

    cout << setprecision(6) << 4 * static_cast<double>(in_circle) / overall << endl;
}
