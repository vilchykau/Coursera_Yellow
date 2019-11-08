//
// Created by stas on 8.11.19.
//

#include <iostream>
#include "ssylka_na_eliemient.cpp"

int main(){
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
}