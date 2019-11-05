//
// Created by stas on 5.11.19.
//
#include <iostream>
#include <cstdint>

int main(){
    int ro = 0;
    uint32_t N = 0;
    std::cin >> N >> ro;

    uint64_t mass = 0;

    for(uint32_t i = 0; i < N; ++i){
        uint32_t H = 0, W = 0, D = 0;
        std::cin >> W >> H >> D;

        mass += (uint64_t)ro * W * H * D;
    }

    std::cout << mass;

    return 0;
}
