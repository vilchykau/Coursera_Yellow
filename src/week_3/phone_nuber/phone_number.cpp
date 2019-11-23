//
// Created by stas on 23.11.2019.
//

#include "phone_number.h"
#include <sstream>
#include <exception>


/* Принимает строку в формате +XXX-YYY-ZZZZZZ
       Часть от '+' до первого '-' - это код страны.
       Часть между первым и вторым символами '-' - код города
       Всё, что идёт после второго символа '-' - местный номер.
       Код страны, код города и местный номер не должны быть пустыми.
       Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

       Примеры:
       * +7-495-111-22-33
       * +7-495-1112233
       * +323-22-460002
       * +1-2-coursera-cpp
       * 1-2-333 - некорректный номер - не начинается на '+'
       * +7-1233 - некорректный номер - есть только код страны и города
    */

PhoneNumber::PhoneNumber(const string &international_number) {
    std::stringstream ss(international_number);

    bool ok = true;

    ok = (ss.peek() == '+');
    ss.get();
    ok = ok && std::getline(ss, country_code_, '-');
    ok = ok && std::getline(ss, city_code_, '-');
    ok = ok && ss >> local_number_;

    if(!ok){
        throw std::invalid_argument("");
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    std::stringstream ss;
    ss << '+' << country_code_<< '-' << city_code_ << '-' << local_number_;
    return ss.str();
}
