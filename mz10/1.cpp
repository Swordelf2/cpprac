#include <iostream>

using namespace std;

int main()
{
    size_t k;
    size_t n;
    cin >> k;
    for (n = 0; n <= k; ++n) {
        for (unsigned i = 0; i < (1u << n); ++i) {
            for (unsigned j = 0; j < (1u << (k - n)); ++j) {
                // print first n
                for (unsigned s = 0; s < n; ++s) {
                    if (i & (0x1u << (n - 1 - s))) {
                        cout << '4';
                    } else {
                        cout << '3';
                    }
                }
                // print last (k - n)
                for (unsigned s = 0; s < (k - n); ++s) {
                    if (j & (0x1u << (k - n - 1 - s))) {
                        cout << '2';
                    } else {
                        cout << '1';
                    }
                }
                cout << endl;
            }
        }
    }
}
