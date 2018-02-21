#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int
main()
{
    double sum = 0.0;
    double sumsqr = 0.0;
    double a;
    int n = 0;
    while (cin >> a) {
        sum += a;
        sumsqr += a * a;
        ++n;
    }

    double av = sum / n;
    double avsqr = sumsqr / n;
    cout << setprecision(10) << av << endl << sqrt(avsqr - av*av) << endl;
    return 0;
}
