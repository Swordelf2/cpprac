#include <string>
#include <iostream>

using namespace std;

enum State
{
    Q0 = 0x0, Q1, Q2, Q3, Q4, Q5, Q6, Q7,
    Q8, // good exit
    Q9, // bad exit
    Q10, // final exit
};

constexpr unsigned BIT_MASK = 0x7;
constexpr unsigned GOOD_BIT = 0x4;

int main()
{
    string s;
    while (cin >> s) {
        enum State state = Q0;
        
        auto it = s.begin();
        // exits are Q8 and Q9
        while (state != Q10) {
            // state dependency (exit states)
            if (state == Q8) {
                cout << 1 << endl;
                state = Q10;
            } else if (state == Q9) {
                cout << 0 << endl;
                state = Q10;
            } else {
                // input dependency case 1
                if (it == s.end()) {
                    // state dependencies
                    if (state & GOOD_BIT) {
                        state = Q8;
                    } else 
                        state = Q9;
                } else if (*it == '0' || *it == '1') {
                // input dependency case 2
                    // the new state is chosen based on current state
                    unsigned state_bits = state;
                    state_bits = ((state_bits << 1) & BIT_MASK) | (*it - '0');
                    state = (State) state_bits;

                } else {
                    state = Q9;
                }
            }
            ++it;
        }
    }
}
