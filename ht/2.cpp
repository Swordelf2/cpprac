#include <mutex>
#include <thread>
#include <cstdio>
#include <vector>

using namespace std;

void thread_func(unsigned iter_count,
        unsigned index1, double sum1,
        unsigned index2, double sum2,
        mutex *mutexes,
        double *acc)
{
    if (index1 > index2) {
        swap(index1, index2);
        swap(sum1, sum2);
    }
    for (unsigned i = 0; i < iter_count; ++i) {
        mutexes[index1].lock();
        if (index2 != index1) {
            mutexes[index2].lock();
        }
        acc[index1] += sum1;
        acc[index2] += sum2;
        mutexes[index1].unlock();
        if (index2 != index1) {
            mutexes[index2].unlock();
        }
    }
}

int main()
{
    unsigned acc_count, thr_count;
    scanf("%u %u", &acc_count, &thr_count);

    vector<thread> thr(thr_count);
    vector<double> acc(acc_count);
    vector<mutex> mutexes(acc_count);

    for (unsigned i = 0; i < acc_count; ++i) {
        acc[i] = 0.0;
    }

    for (unsigned i = 0; i < thr_count; ++i) {
        unsigned iter_count, index1, index2;
        double sum1, sum2;
        scanf("%u %u %lf %u %lf", &iter_count, &index1, &sum1, &index2, &sum2);
        thr[i] = thread(thread_func, iter_count,
                index1, sum1, index2, sum2,
                mutexes.data(), acc.data());
    }

    for (unsigned i = 0; i < thr_count; ++i) {
        thr[i].join();
    }

    for (unsigned i = 0; i < acc_count; ++i) {
        printf("%.10g\n", acc[i]);
    }
}

