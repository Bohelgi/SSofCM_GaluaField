#pragma once
#ifndef Galua_Field_H
#define Galua_Field_H

#include <vector>
#include <string>

class Galua {
public:
    std::vector<int> vec_x;
    Galua(std::vector<int> pows = {});
    std::string get();
    std::string toBin();
};

Galua toPol(std::string s);
void shift(Galua& a, int b);
void delZeros(Galua& a);
int comparePol(const Galua& a, const Galua& b);
std::pair<Galua, Galua> toOneLength(const Galua& a, const Galua& b);
Galua xorPol(const Galua& a, const Galua& b);
Galua Add(const Galua& a, const Galua& b);
Galua Sub(const Galua& a, const Galua& b);
Galua mod(const Galua& a, const Galua& b);
Galua Mul(const Galua& a, const Galua& b);
Galua Pow(const Galua& a, const std::string& b);
Galua Trace(const Galua& a);
Galua Inverse(const Galua& a);

#endif