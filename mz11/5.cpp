#include <iostream>
#include <stack>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;


void f(vector<char> &st, string &result)
{
    char op = st.back();
    st.pop_back();
    if (isalpha(op)) {
        result.push_back(op);
        return;
    }

    result.push_back(')');
    f(st, result);
    result.push_back(op);
    f(st, result);
    result.push_back('(');
}

int main()
{
    vector<char> st;
    string result;
    char c;
    while (cin >> c) {
        st.push_back(c);
    }
    f(st, result);
    reverse(result.begin(), result.end());
    cout << result << endl;
}
