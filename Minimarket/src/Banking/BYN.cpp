#include <cmath>
#include "BYN.hpp"
/**
 * @file BYN.cpp
 * @brief Реализация класса `BYN`.
 * @details
 * Этот файл содержит реализацию методов класса `BYN`,
 * который моделирует белорусскую валюту.
 * @author
 * Ekatsune
 */
std::istream& operator>>(std::istream& is, BYN& byn) {
    std::string token;
    if (!(is >> token)) {
        return is;
    }
    for (char& c : token) {
        if (c == ',') c = '.';
    }
    try {
        double value = std::stod(token);
        byn.kopecks = static_cast<long long>(std::round(value * 100));
    }
    catch (...) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool BYN::operator<(const BYN& other) const { return kopecks < other.kopecks; }

bool BYN::operator>(const BYN& other) const { return kopecks > other.kopecks; }

bool BYN::operator<=(const BYN& other) const { return kopecks <= other.kopecks; }

bool BYN::operator>=(const BYN& other) const { return kopecks >= other.kopecks; }

bool BYN::operator==(const BYN& other) const { return kopecks == other.kopecks; }

BYN& BYN::operator-=(const BYN& other) { kopecks -= other.kopecks; return *this; }

BYN& BYN::operator+=(const BYN& other) { kopecks += other.kopecks; return *this; }

bool BYN::operator!=(const BYN& other) const { return kopecks != other.kopecks; }

BYN BYN::operator+(const BYN& other) const { return BYN(kopecks + other.kopecks); }

BYN BYN::operator-(const BYN& other) const {return BYN(kopecks - other.kopecks);}

long long BYN::GetKopecks() const { return kopecks % 100; }

long long BYN::GetRubles() const { return kopecks / 100; }

std::ostream& operator<<(std::ostream& os, const BYN& byn)
{
    long long rub = byn.GetRubles();
    long long kop = byn.GetKopecks();

    os << rub << "," << (kop < 10 ? "0" : "") << kop << " BYN";
    return os;
}

BYN BYN::operator*(double value) const {
    long long result = static_cast<long long>(std::round(kopecks * value));
    return BYN(result);
}

BYN BYN::operator/(double value) const {
    long long result = static_cast<long long>(std::round(kopecks / value));
    return BYN(result);
}
