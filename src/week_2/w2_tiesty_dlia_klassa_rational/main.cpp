//
// Created by stas on 16.11.19.
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
class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);

    int Numerator() const;
    int Denominator() const;
};*/

void AssertEqualRat(const Rational& rational, int num, int den){
    AssertEqual(rational.Denominator(), den);
    AssertEqual(rational.Numerator(), num);
}

void DefaultConstructorTest(){
    Rational rational;
    AssertEqual(rational.Numerator(), 0);
    AssertEqual(rational.Denominator(), 1);
}

void CutTest(){
    {
        Rational rational(2, 2);
        AssertEqualRat(rational, 1, 1);
    }
    {
        Rational rational(36, 9);
        AssertEqualRat(rational, 4, 1);
    }
    {
        Rational rational(9, 36);
        AssertEqualRat(rational, 1, 4);
    }
}

void NegativeTest(){
    {
        Rational rational(-2, 2);
        AssertEqualRat(rational, -1, 1);
    }
    {
        Rational rational(36, -9);
        AssertEqualRat(rational, -4, 1);
    }
    {
        Rational rational(-9, -36);
        AssertEqualRat(rational, 1, 4);
    }
}

void ZeroNum(){
    {
        Rational rational(0, 2);
        AssertEqualRat(rational, 0, 1);
    }
    {
        Rational rational(0, -9);
        AssertEqualRat(rational, 0, 1);
    }
    {
        Rational rational(0, -36);
        AssertEqualRat(rational, 0, 1);
    }
}

int main(){
    TestRunner runner;
    runner.RunTest(DefaultConstructorTest, "DefaultConstructorTest");
    runner.RunTest(CutTest, "CutTest");
    runner.RunTest(NegativeTest, "NegativeTest");
    runner.RunTest(ZeroNum, "ZeroNum");

    return 0;
}