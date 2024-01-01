#include "Galua_Field.h"
#include "config.h"
#include <algorithm>
#include <cmath>
#include <bitset>

Galua::Galua(std::vector<int> pows) {
    if (pows.empty()) {
        vec_x = {};
    }
    else {
        for (int i = 0; i <= *max_element(pows.begin(), pows.end()); ++i) {
            if (find(pows.begin(), pows.end(), i) != pows.end()) {
                vec_x.push_back(1);
            }
            else {
                vec_x.push_back(0);
            }
        }
    }
}

std::string Galua::get() {
    std::string outstr = "";
    for (int i = vec_x.size() - 1; i >= 0; --i) {
        if (vec_x[i] == 1) {
            if (i == 0) {
                outstr += " + 1";
            }
            else {
                outstr += " + x^" + std::to_string(i);
            }
        }
    }
    if (outstr == "") {
        return "0";
    }
    return outstr.substr(3);
}

std::string Galua::toBin() {
    std::string c = "";
    for (int i = vec_x.size() - 1; i >= 0; --i) {
        c += std::to_string(vec_x[i]);
    }
    return c;
}

Galua toPol(std::string s) {
    Galua c;
    for (int i = s.length() - 1; i >= 0; --i) {
        c.vec_x.push_back(s[i] - '0');
    }
    return c;
}

void shift(Galua& a, int b) {
    for (int i = 0; i < b; ++i) {
        a.vec_x.insert(a.vec_x.begin(), 0);
    }
}

void delZeros(Galua& a) {
    while (a.vec_x.back() == 0 && a.vec_x.size() > 1) {
        a.vec_x.pop_back();
    }
}

int comparePol(const Galua& a, const Galua& b) {
    if (a.vec_x.size() > b.vec_x.size()) {
        return 1;
    }
    if (a.vec_x.size() < b.vec_x.size()) {
        return -1;
    }
    for (int i = a.vec_x.size() - 1; i >= 0; --i) {
        if (a.vec_x[i] > b.vec_x[i]) {
            return 1;
        }
        if (a.vec_x[i] < b.vec_x[i]) {
            return -1;
        }
    }
    return 0;
}

std::pair<Galua, Galua> toOneLength(const Galua& a, const Galua& b) {
    Galua a1 = a;
    Galua b1 = b;
    if (a.vec_x.size() > b.vec_x.size()) {
        while (a1.vec_x.size() > b1.vec_x.size()) {
            b1.vec_x.push_back(0);
        }
        return std::make_pair(a1, b1);
    }
    if (a.vec_x.size() < b.vec_x.size()) {
        while (a1.vec_x.size() < b1.vec_x.size()) {
            a1.vec_x.push_back(0);
        }
        return std::make_pair(a1, b1);
    }
    return std::make_pair(a1, b1);
}

Galua xorPol(const Galua& a, const Galua& b) {
    Galua c;
    for (int i = 0; i < a.vec_x.size(); ++i) {
        c.vec_x.push_back(a.vec_x[i] ^ b.vec_x[i]);
    }
    delZeros(c);
    return c;
}

Galua Add(const Galua& a, const Galua& b) {
    auto element = toOneLength(a, b);
    return xorPol(element.first, element.second);
}


Galua Sub(const Galua& a, const Galua& b) {
    Galua a1 = a;
    Galua b1 = b;
    while (a1.vec_x.size() > b1.vec_x.size()) {
        b1.vec_x.insert(b1.vec_x.begin(), 0);
    }
    return xorPol(a1, b1);
}

Galua mod(const Galua& a, const Galua& b) {
    Galua a1 = a;
    while (comparePol(a1, b) >= 0) {
        a1 = Sub(a1, b);
    }
    return a1;
}

Galua Mul(const Galua& a, const Galua& b) {
    Galua c;
    Galua gen(config::generator);
    for (int i = 0; i < b.vec_x.size(); ++i) {
        if (b.vec_x[i] == 0) {
            continue;
        }
        else {
            Galua temp = a;
            shift(temp, i);
            c = Add(c, temp);
        }
    }
    delZeros(c);
    return mod(c, gen);
}

Galua Trace(const Galua& a) {
    std::vector<Galua> d;
    d.push_back(a);
    for (int i = 1; i < config::m; ++i) {
        d.push_back(Mul(d[i - 1], d[i - 1]));
    }
    Galua sum;
    for (const auto& i : d) {
        sum = Add(sum, i);
    }
    delZeros(sum);
    return sum;
}

Galua Pow(const Galua& a, const std::string& b) {
    Galua gen(config::generator);
    Galua c({ 0 });
    for (int i = 0; i < b.length(); ++i) {
        if (b[i] == '1') {
            c = Mul(c, a);
        }
        if (i != b.length() - 1) {
            c = Mul(c, c);
        }
    }
    return mod(c, gen);
}

Galua Inverse(const Galua& a) {
    Galua c;
    for (int i = 0; i < config::m - 1; ++i) {
        c.vec_x.push_back(1);
    }
    c.vec_x.insert(c.vec_x.begin(), 0);
    return Pow(a, c.toBin());
}