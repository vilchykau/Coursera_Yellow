//
// Created by stas on 8.11.19.
//

#include <map>
#include <exception>
using namespace std;

template <typename T_KEY, typename T_VALUE>
T_VALUE& GetRefStrict(map<T_KEY, T_VALUE>& m, T_KEY key){
    if(!m.count(key)){
        throw runtime_error("");
    }
    return m[key];
}