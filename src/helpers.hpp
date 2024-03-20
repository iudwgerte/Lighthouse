#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "types.hpp"

class PRNG {
private:
    uint64_t s;
    uint64_t rand64() {
        s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
        return s * 2685821657736338717ull;
    }

public:
    PRNG(uint64_t seed) : s(seed) { assert(seed); }

    template <typename T> T rand() { return T(rand64()); }
};

std::vector<std::string> splitString(const std::string &str,
                                     const char &delim) {
    std::stringstream string_stream(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(string_stream, token, delim))
        tokens.emplace_back(token);
    return tokens;
}

template <typename T, size_t S> class FixedVector {
private:
    std::array<T, S> data{};
    size_t length = 0;

public:
    FixedVector() = default;
    T &operator[](int idx) { return data[idx]; }
    int size() { return length; }
    bool empty() { return length == 0; }
    void push_back(const T &item) { data[length++] = item; }
    void pop_back() { length--; }
    void clear() { length = 0; }
    T back() { return data[length - 1]; }
    void swap(int idx1, int idx2) { return std::swap(data[idx1], data[idx2]); }
    auto begin() { return data.begin(); }
    auto end() { return begin() + length; }
};

inline uint64_t fast_mod(uint64_t a, uint64_t b) {
    return (__uint128_t(a) * __uint128_t(b)) >> 64;
}

#endif
