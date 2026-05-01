#pragma once
// Generic includes
#include <string>
#include <cstdint>
#include <stdint.h>


inline uint64_t SimpleHashULong(const unsigned long _a, const unsigned long _b) { return _a ^ _b; }
inline int64_t	SimpleHashLong(const long _a, const long _b) { return _a ^ _b; }


inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}


inline std::string to_hex(uint64_t x) {
    const char* digits = "0123456789abcdef";
    std::string out(16, '0');

    for (int i = 15; i >= 0; --i) {
        out[i] = digits[x & 0xF];
        x >>= 4;
    }
    return out;
}


inline std::string to_hex_mix(uint64_t x) {
    return to_hex(splitmix64(x));
}

std::string to_hex_mix2(uint64_t v) {
    uint64_t h1 = splitmix64(v);
    uint64_t h2 = splitmix64(v + 0x9e3779b97f4a7c15ULL); // different input

    return to_hex(h1) + to_hex(h2); // 32 hex chars
}