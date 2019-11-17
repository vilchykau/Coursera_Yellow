//
// Created by stas on 17.11.19.
//


#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};
/*
class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
    }
    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
    }
private:
    // приватные поля
};*/

void DefautTest(){
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    AssertEqual(person.GetFullName(1900), "Incognito");
    AssertEqual(person.GetFullName(1965), "Polina with unknown last name");
    AssertEqual(person.GetFullName(1990), "Polina Sergeeva");

    person.ChangeFirstName(1970, "Appolinaria");
    AssertEqual(person.GetFullName(1969), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

    person.ChangeLastName(1968, "Volkova");
    AssertEqual(person.GetFullName(1969), "Polina Volkova");
    AssertEqual(person.GetFullName(1970), "Appolinaria Volkova");
}

void AnotherTest(){
    Person person;

    person.ChangeLastName(1960, "A");
    person.ChangeFirstName(1962, "V");

    AssertEqual(person.GetFullName(1959), "Incognito");
    AssertEqual(person.GetFullName(1961), "A with unknown first name");
    AssertEqual(person.GetFullName(1963), "V A");
}

int main(){
    {
        TestRunner runner;
        runner.RunTest(DefautTest, "DefautTest");
        runner.RunTest(AnotherTest, "AnotherTest");
    }

    return 0;
}