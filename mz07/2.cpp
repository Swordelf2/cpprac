#include <iostream>
#include <vector>

void process(std::vector<int> &v)
{
    if (v.empty()) {
        return;
    }

    auto it = v.begin() + 1;
    size_t cnt = 0;
    while (it < v.end()) {
        *(v.begin() + (it - v.begin() - 1) / 2) = std::move(*it);
        ++cnt;
        if (it < v.end() - 2) {
            it += 2;
        } else {
            it = v.end();
        }
    }
    v.resize(cnt);

    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}
