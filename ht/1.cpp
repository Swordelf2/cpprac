#include <mutex>
#include <thread>
#include <cstdio>

using namespace std;

constexpr int THR_CNT = 3;
constexpr int OP_CNT = 1000000;
constexpr int NUM = 100;

double arr[THR_CNT];

mutex m;

void thread_func(int id)
{
    int id_next = (id + 1 < THR_CNT) ? id + 1 : 0;
    for (int i = 0; i < OP_CNT; ++i) {
        lock_guard g(m);
        arr[id] += NUM * (id + 1);
        arr[id_next] -= NUM * (id + 1) + 1;
    }
}

int main()
{
    thread thr[THR_CNT];
    for (thread &t : thr) {
        t = thread(thread_func, &t - thr);
    }
    for (thread &t : thr) {
        t.join();
    }

    for (const double &el : arr) {
        printf("%.10g ", el);
    }
    putchar('\n');
}
