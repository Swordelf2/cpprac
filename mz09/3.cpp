#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main()
{
    string s, str;
    while (getline(cin ,str)) {
        s += str;
    }
    int i;
    for (i = s.length() - 1; i >= 0 && isspace(static_cast<unsigned char>(s[i])); --i) {}
    s.resize(i + 1);

    const char *cs = s.c_str();

    vector<const char *> v;
    v.reserve(s.length());
    for (size_t i = 0; i < s.length(); ++i) {
        v.push_back(cs + i);
    }
    sort(v.begin(), v.end(), [](const char *s1, const char *s2) { return strcmp(s1, s2) < 0; });

    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it - cs << endl;
    }
}
