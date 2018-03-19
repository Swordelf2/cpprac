#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

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
        istringstream istrs(s);
        string s1, s2;
        char c;
        istrs >> c;
        switch (c) {
            case 'C':
                istrs >> s1;
                f = Circle::make(s1);
                break;
            case 'S':
                istrs >> s1;
                f = Square::make(s1);
                break;
            case 'R':
                istrs >> s1 >> s2;
                f = Rectangle::make(s1 + " " + s2);
                break;
            default:
                ;
        }
        v.push_back(f);
    }

    stable_sort(v.begin(), v.end(), Cmpr());

    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << (*it)->to_string() << endl;
        delete *it;
    }
}
