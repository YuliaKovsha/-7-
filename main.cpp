#include <iostream>
#include <stdexcept>
using namespace std;

// ------------------- 1. Варіант без специфікації -------------------
int wholePart1(int numerator, int denominator)
{
    if (denominator == 0)
        throw runtime_error("Ділення на нуль");

    return numerator / denominator;
}

// ------------------- 2. Варіант зі специфікацією throw() -------------------
int wholePart2(int numerator, int denominator) throw()
{
    if (denominator == 0)
        return 0; // не можемо кинути виключення — специфікація забороняє

    return numerator / denominator;
}

// ------------------- 3. Варіант зі стандартним виключенням -------------------
int wholePart3(int numerator, int denominator) throw(invalid_argument)
{
    if (denominator == 0)
        throw invalid_argument("Знаменник не може бути нулем");

    return numerator / denominator;
}

// ------------------- 4. Власні виключення -------------------
class EmptyException {}; // порожній

class FractionError {    // з полями
public:
    int num, den;
    FractionError(int n, int d) : num(n), den(d) {}
};

class FractionException : public exception { // спадкоємець exception
    int num, den;
    string msg;
public:
    FractionException(int n, int d) : num(n), den(d) {
        msg = "Неправильний дріб: " + to_string(n) + "/" + to_string(d);
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// функція з власним виключенням
int wholePart4(int numerator, int denominator) throw(EmptyException)
{
    if (denominator == 0)
        throw EmptyException();

    return numerator / denominator;
}

int wholePart5(int numerator, int denominator) throw(FractionError)
{
    if (denominator == 0)
        throw FractionError(numerator, denominator);

    return numerator / denominator;
}

int wholePart6(int numerator, int denominator) throw(FractionException)
{
    if (denominator == 0)
        throw FractionException(numerator, denominator);

    return numerator / denominator;
}

// ------------------- ГОЛОВНА ФУНКЦІЯ -------------------
int main()
{
    int a, b;

    cout << "Введіть чисельник: ";
    cin >> a;
    cout << "Введіть знаменник: ";
    cin >> b;

    cout << "\n--- ТЕСТУВАННЯ ВИКЛЮЧЕНЬ ---\n";

    // 1
    try {
        cout << "wholePart1: " << wholePart1(a, b) << endl;
    }
    catch (runtime_error& e) {
        cout << "Помилка wholePart1: " << e.what() << endl;
    }

    // 2
    try {
        cout << "wholePart2: " << wholePart2(a, b) << endl;
    }
    catch (...) {
        cout << "wholePart2 не повинен кидати виключення\n";
    }

    // 3
    try {
        cout << "wholePart3: " << wholePart3(a, b) << endl;
    }
    catch (invalid_argument& e) {
        cout << "Помилка wholePart3: " << e.what() << endl;
    }

    // 4 — EmptyException
    try {
        cout << "wholePart4: " << wholePart4(a, b) << endl;
    }
    catch (EmptyException&) {
        cout << "Помилка wholePart4: EmptyException\n";
    }

    // 5 — FractionError
    try {
        cout << "wholePart5: " << wholePart5(a, b) << endl;
    }
    catch (FractionError& e) {
        cout << "Помилка wholePart5: num=" << e.num << ", den=" << e.den << endl;
    }

    // 6 — FractionException
    try {
        cout << "wholePart6: " << wholePart6(a, b) << endl;
    }
    catch (FractionException& e) {
        cout << "Помилка wholePart6: " << e.what() << endl;
    }

    return 0;
}
