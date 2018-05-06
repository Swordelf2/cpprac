#include <iostream>
#include <vector>

void process(std::vector<int> &v)
{
    if (v.empty()) {
        return;
    }

    auto it_from = v.begin() + 1;
    auto it_to = v.begin();
    while (it_from < v.end()) {
        *it_to = std::move(*it_from);
        ++it_to;
        if (it_from >= v.end() - 2) {
            break;
        }
        it_from += 2;
    }
    v.resize(it_to - v.begin());

    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}
