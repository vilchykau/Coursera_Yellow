//
// Created by stas on 5.11.19.
//

#include <iostream>
#include <vector>

int main() {
    int k;
    long long sum = 0;
    std::cin >> k;
    std::vector<int> temps(k);
    for (auto &item: temps) {
        std::cin >> item;
        sum += item;
    }

    sum /= k;
    std::vector<size_t> h;
    for (size_t i = 0; i < temps.size(); ++i) {
        if(temps[i] > sum){
            h.push_back(i);
        }
    }

    std::cout << h.size() << '\n';
    for (const auto &item: h) {
        std::cout << item << ' ';
    }
}

