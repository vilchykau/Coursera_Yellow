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

bool IsPalindrom(const string& s);

void EdgeTest(){
    AssertEqual(IsPalindrom(""), true);
    AssertEqual(IsPalindrom("f"), true);
    AssertEqual(IsPalindrom(" 7 "), true);
    AssertEqual(IsPalindrom(" .7. "), true);
    AssertEqual(IsPalindrom(" "), true);
}

void BasicTest(){
    AssertEqual(IsPalindrom("  55 55  "), true);
    AssertEqual(IsPalindrom("  5asd5  "), false);
    AssertEqual(IsPalindrom("8  5asd5  8"), false);
    AssertEqual(IsPalindrom("8  5asa5  8"), true);
    AssertEqual(IsPalindrom("8  5asa5 8"), false);
    AssertEqual(IsPalindrom("8  5asA5  8"), false);
    AssertEqual(IsPalindrom("8  5asA58"), false);
    AssertEqual(IsPalindrom("8 5asA58"), false);
    AssertEqual(IsPalindrom(" g    "), false);
    AssertEqual(IsPalindrom(" g "), true);
    AssertEqual(IsPalindrom(" g G "), false);
    AssertEqual(IsPalindrom("XabbaY"), false);
}

void BasicTest2(){
    AssertEqual(IsPalindrom("Xabba X"), false);
    AssertEqual(IsPalindrom("777778"), false);
    AssertEqual(IsPalindrom("baobab"), false);
    AssertEqual(IsPalindrom("aa"), true);
}

void BasicTest3(){
    AssertEqual(IsPalindrom("aA"), false);
    AssertEqual(IsPalindrom("aaaaaaaaaaaaaaaaaaaaaaaA"), false);
    AssertEqual(IsPalindrom("BaaaaaaaaaaaaaaaaaaaaaaA"), false);
}


void TestPalindrom() {
    AssertEqual(IsPalindrom(""), true, "empty string");
    AssertEqual(IsPalindrom(" "), true, "whitespace");
    AssertEqual(IsPalindrom("A"), true, "A");
    AssertEqual(IsPalindrom("&"), true, "&");
    AssertEqual(IsPalindrom("1"), true, "1");
    AssertEqual(IsPalindrom("121"), true, "121");
    AssertEqual(IsPalindrom("@@"), true, "@@");
    AssertEqual(IsPalindrom("!@# #@!"), true, "!@# #@!");
    AssertEqual(IsPalindrom("madam"), true, "madam");
    AssertEqual(IsPalindrom("baobab"), false, "baobab");
    AssertEqual(IsPalindrom(" weew "), true, " weew ");
    AssertEqual(IsPalindrom("f f ff f f"), true, "f f ff f f");
    AssertEqual(IsPalindrom("f f f f f"), true, "f f f f f");
    AssertEqual(IsPalindrom("A  L L A"), false, "A  L L A");
    AssertEqual(IsPalindrom("mada m"), false, "mada m");
    AssertEqual(IsPalindrom(" weew   "), false, " weew   ");
    AssertEqual(IsPalindrom("   weew "), false, "   weew ");
    AssertEqual(IsPalindrom("qwertyTrewq"), false, "qwertyTrewq");
    AssertEqual(IsPalindrom("qwertytrewq"), true, "qwertytrewq");
    AssertEqual(IsPalindrom("qwerttrewq"), true, "qwerttrewq");
    AssertEqual(IsPalindrom("qwertytrewQ"), false, "qwertytrewQ");
    AssertEqual(IsPalindrom("Q wer ewQ"), false, "Q wer ewQ");
}

void TestEmptyString() {
    Assert( IsPalindrom(""), "Test empty string is palindrom");
}
void TestOneSymString() {
    Assert( IsPalindrom("a"), "Test one symbol string is palindrom");
}
void TestRegularString() {
    Assert( IsPalindrom("AbcaaacbA"), "Test regular palindrom 1");
    Assert( IsPalindrom("madam"), "Test regular palindrom 2");
    Assert( IsPalindrom("level"), "Test regular palindrom 2");
    Assert( !IsPalindrom("baobab"), "Test regular palindrom 2");
    Assert( IsPalindrom("wasitacaroracatisaw"), "Test regular palindrom 2");
    Assert( !IsPalindrom("wasitacaroracatisaW"), "Test regular palindrom 2");
    Assert( !IsPalindrom("QWERTYUIOPASDFGHJKLZXCVBNMmnbvcxzlkjhgfdsapoiuytrewq"), "Test regular palindrom 2");
    Assert( !IsPalindrom("abcd"), "Test not a palindrom");
    Assert( !IsPalindrom("bbbbbbbadbbbbbbb"), "Test not a palindrom");
}

void TestSpaces() {
    Assert( IsPalindrom("ab cdc ba"), "Test palindrome string with spaces");
    Assert( !IsPalindrom("ab  cdc ba"), "Test palindrome string with spaces");
    Assert( !IsPalindrom("ab   cdc  ba"), "Test palindrome string with spaces");
    Assert( !IsPalindrom("ab   cdc  ba "), "Test palindrome string with spaces");
    Assert( !IsPalindrom("  ab   cdc  ba "), "Test palindrome string with spaces");
    Assert( !IsPalindrom("          aba"), "Test not a palindrome string with spaces 2");
    Assert( !IsPalindrom("          aba  "), "Test not a palindrome string with spaces 2");
    Assert( !IsPalindrom("\taba    "), "Test not a palindrome string with spaces 2");
    Assert( !IsPalindrom("\taba "), "Test not a palindrome string with spaces 2");
    Assert( !IsPalindrom("\taba  "), "Test not a palindrome string with spaces 2");
    Assert( !IsPalindrom("\taba   "), "Test not a palindrome string with spaces 2");
    Assert( !IsPalindrom("\taba     "), "Test not a palindrome string with spaces 2");
}

int main(){
    TestRunner runner;
    runner.RunTest(EdgeTest, "EdgeTest");
    runner.RunTest(BasicTest, "BasicTest");
    runner.RunTest(BasicTest2, "BasicTest2");
    runner.RunTest(BasicTest3, "BasicTest3");
    runner.RunTest(TestPalindrom, "TestPalindrom");
    runner.RunTest(TestEmptyString, "TestEmptyString");
    runner.RunTest(TestOneSymString, "TestOneSymString");
    runner.RunTest(TestRegularString, "TestRegularString");
    runner.RunTest(TestSpaces, "TestSpaces");
    return 0;
}