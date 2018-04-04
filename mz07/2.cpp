#include <iostream>
#include <vector>

void process(std::vector<int> &v)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        it = v.erase(it);
        if (it == v.end()) {
            break;
        }
    }
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}
