#include <iostream>
#include <stack>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> st;
string result;

void f()
{
    char op = st.back();
    st.pop_back();
    if (isalpha(op)) {
        result.push_back(op);
        return;
    }

    result.push_back(')');
    f();
    result.push_back(op);
    f();
    result.push_back('(');
}

int main()
{
    char c;
    while (cin >> c) {
        st.push_back(c);
    }
    f();
    reverse(result.begin(), result.end());
    cout << result << endl;
}
