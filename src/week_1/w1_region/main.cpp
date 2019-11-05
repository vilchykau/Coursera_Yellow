//
// Created by stas on 5.11.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>

using namespace std;

bool operator<(const Region& left, const Region& right){
    return tie(left.std_name, left.parent_std_name, left.names, left.population) <
           tie(right.std_name, right.parent_std_name, right.names, right.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
    map<Region, int> regions_map;
    int max_ = 0;
    for(const auto& item : regions){
        ++regions_map[item];
        max_ = max(max_, regions_map[item]);
    }
    return max_;
}
