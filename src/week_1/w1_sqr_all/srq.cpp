//
// Created by stas on 8.11.19.
//
#include <vector>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

template <typename T>
T Sqr(T value);

template <typename T>
vector<T> Sqr(const vector<T>& old_vector);

template <typename T_KEY, typename T_VALUE>
map<T_KEY, T_VALUE> Sqr(const map<T_KEY, T_VALUE>& old_map);

template <typename T_FIRST, typename T_SECOND>
pair<T_FIRST, T_SECOND> Sqr(const pair<T_FIRST, T_SECOND>& old_pair);



template <typename T>
T Sqr(T value){
    return value * value;
}

template <typename T>
vector<T> Sqr(const vector<T>& old_vector){
    auto new_vector = old_vector;
    for(auto& item : new_vector){
        item = Sqr(item);
    }
    return new_vector;
}

template <typename T_KEY, typename T_VALUE>
map<T_KEY, T_VALUE> Sqr(const map<T_KEY, T_VALUE>& old_map){
    auto new_map = old_map;
    for(auto& pair : new_map){
        pair.second = Sqr(pair.second);
    }
    return new_map;
}

template <typename T_FIRST, typename T_SECOND>
pair<T_FIRST, T_SECOND> Sqr(const pair<T_FIRST, T_SECOND>& old_pair){
    return make_pair<T_FIRST, T_SECOND>(Sqr(old_pair.first),
                                        Sqr(old_pair.second));
}
