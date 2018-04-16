#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

class Cmpr
{
    public:
    bool operator()(const Figure *f1, const Figure *f2)
    {
        return f1->get_square() < f2->get_square();
    }
};


int main()
{
    vector<Figure *> v;
    string s;
    while (getline(cin, s)) {
        Figure *f;
        size_t i = 0;
        for (; isspace(s[i]); ++i) {}
        char c = s[i];
        s = s.substr(i + 1);
        switch (c) {
        case 'C':
            f = Circle::make(s);
            break;
        case 'S':
            f = Square::make(s);
            break;
        case 'R':
            f = Rectangle::make(s);
            break;
        default:
            ;
        }
        v.push_back(f);
    }

    stable_sort(v.begin(), v.end(), Cmpr());
    
    for (auto f_ptr : v) {
        cout << f_ptr->to_string() << endl;
        delete f_ptr;
    }
}
