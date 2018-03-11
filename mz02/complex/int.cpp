#include "complex.h"
#include "eval.h"

#include <stdio.h>
#include <cmath>

#include <iostream>

using numbers::complex;
using numbers::eval;

enum Args
{
    ARG_CENTER = 1,
    ARG_RADIUS = 2,
    ARG_N = 3,
    ARG_FUNC = 4
};

enum
{
    OUTPUT_BUF_SIZE = 128
};

inline complex GetPoint(const complex &center, double R, double angle);

int main(int argc, char **argv)
{
    complex center(argv[ARG_CENTER]);
    double R = strtod(argv[ARG_RADIUS], NULL);
    unsigned long N = strtol(argv[ARG_N], NULL, 0);

    char **expr = argv + ARG_FUNC;

    complex I = 0;
    complex prev_p = GetPoint(center, R, 0);
    double prev_angle = 0;
    for (unsigned long i = 1; i <= N; ++i) {
        double angle = 2.0 * M_PI * i / N;
        complex p = GetPoint(center, R, angle);
        complex val = eval(expr, GetPoint(center, R, (angle + prev_angle) * 0.5));
        I = I + val * (p - prev_p);
        prev_p = p;
        prev_angle = angle;
    }

    char buf[OUTPUT_BUF_SIZE];
    I.to_string(buf, sizeof(buf));
    std::cout << buf << std::endl;
}

complex GetPoint(const complex &center, double R, double angle)
{
    double cosine = cos(angle);
    double sine;
    if (angle <= M_PI) {
        sine = sqrt(1 - cosine * cosine);
    } else {
        sine = -sqrt(1 - cosine * cosine);
    }
    return center + complex(R * cosine, R * sine);
}
