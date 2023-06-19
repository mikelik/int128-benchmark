#include <benchmark/benchmark.h>
#include <iostream>


#if defined __llvm__
typedef _BitInt(128) int128_t;
typedef unsigned _BitInt(128) uint128_t;
typedef _BitInt(256) int256_t;
typedef unsigned _BitInt(256) uint256_t;
#elif defined __GNUC__
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
#endif


template <typename WideInt>
std::string to_string(WideInt value) {
    std::string hexString;
    const char* hexDigits = "0123456789abcdef";

    while (value > 0) {
        int digit = value & 0xF;  // Extract the least significant nibble
        hexString = hexDigits[digit] + hexString;
        value >>= 4;  // Shift right by 4 bits
    }

    return hexString;
}


template <typename WideInt>
std::string to_string2(WideInt value) {
    std::string hexString;
    const char* hexDigits = "0123456789abcdef";

    // Calculate the number of digits required
    int numDigits = (sizeof(WideInt) * 2); // Each byte is represented by 2 hexadecimal digits

    hexString.resize(numDigits); // Resize the string to the required length
    char* hexChars = &hexString[0]; // Obtain a pointer to the string's internal buffer

    // Convert each nibble to a hexadecimal digit
    for (int i = numDigits - 1; i >= 0; --i) {
        int digit = value & 0xF;  // Extract the least significant nibble
        hexChars[i] = hexDigits[digit];
        value >>= 4;  // Shift right by 4 bits
    }

    return hexString;
}

template <typename WideInt>
std::string to_string3(WideInt value) {
    std::string hexString;
    const char* hexDigits = "0123456789abcdef";

    // Calculate the number of digits required
    int numDigits = (sizeof(WideInt) * 2); // Each byte is represented by 2 hexadecimal digits

    hexString.resize(numDigits); // Resize the string to the required length
    char* hexChars = &hexString[0]; // Obtain a pointer to the string's internal buffer

    // Convert each nibble to a hexadecimal digit
    for (int i = numDigits - 1; i >= 0; --i) {
        int digit = value & 0xF;  // Extract the least significant nibble
        hexChars[i] = hexDigits[digit];
        value = __builtin_rotateright64(value, 4);  // Rotate right by 4 bits
    }

    return hexString;
}

template <typename WideInt>
WideInt to_int(const std::string& hexString) {
    if (hexString.empty())
        throw std::invalid_argument("Empty hexadecimal string");

    // Skip "0x" prefix if present
    std::size_t startIdx = (hexString.size() > 2 && hexString.substr(0, 2) == "0x") ? 2 : 0;

    WideInt result = 0;

    for (std::size_t i = startIdx; i < hexString.size(); ++i) {
        char c = hexString[i];

        if (c >= '0' && c <= '9')
            result = (result << 4) + (c - '0');
        else if (c >= 'a' && c <= 'f')
            result = (result << 4) + (c - 'a' + 10);
        else if (c >= 'A' && c <= 'F')
            result = (result << 4) + (c - 'A' + 10);
        else
            throw std::invalid_argument("Invalid hexadecimal string");
    }

    return result;
}

template <typename WideInt>
WideInt to_int2(const std::string& hexString) {
    if (hexString.empty())
        throw std::invalid_argument("Empty hexadecimal string");

    // Skip "0x" prefix if present
    std::size_t startIdx = (hexString.size() > 2 && hexString.substr(0, 2) == "0x") ? 2 : 0;

    static const std::unordered_map<char, int> hexLookup = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
        {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
        {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11},
        {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15},
        {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13},
        {'E', 14}, {'F', 15}
    };

    WideInt result = 0;

    for (std::size_t i = startIdx; i < hexString.size(); ++i) {
        char c = hexString[i];
        auto it = hexLookup.find(c);

        if (it == hexLookup.end())
            throw std::invalid_argument("Invalid hexadecimal string");

        result = (result << 4) | it->second;
    }

    return result;
}

template <typename WideInt>
WideInt to_int3(const std::string& hexString) {
    if (hexString.empty())
        throw std::invalid_argument("Empty hexadecimal string");

    std::size_t startIdx = (hexString.size() > 2 && hexString.substr(0, 2) == "0x") ? 2 : 0;

    WideInt result = 0;

    for (std::size_t i = startIdx; i < hexString.size(); ++i) {
        char c = hexString[i];

        if (c >= '0' && c <= '9')
            result = (result << 4) | (c - '0');
        else if (c >= 'a' && c <= 'f')
            result = (result << 4) | (c - 'a' + 10);
        else if (c >= 'A' && c <= 'F')
            result = (result << 4) | (c - 'A' + 10);
        else
            throw std::invalid_argument("Invalid hexadecimal string");
    }

    return result;
}

static void to_string(benchmark::State& state) {
   int128_t i = 12345678901234567890ULL;
   
   for (auto _ : state)
      to_string(i);
}

static void to_string2(benchmark::State& state) {
   int128_t i = 12345678901234567890ULL;
   
   for (auto _ : state)
      to_string2(i);
}

static void to_string3(benchmark::State& state) {
   int128_t i = 12345678901234567890ULL;
   
   for (auto _ : state)
      to_string3(i);
}

static void to_int(benchmark::State& state) {
   std::string s = "AB54A98CEB1F0ADF";
   
   for (auto _ : state)
      to_int<int128_t>(s);
}

static void to_int2(benchmark::State& state) {
   std::string s = "AB54A98CEB1F0ADF";
   
   for (auto _ : state)
      to_int2<int128_t>(s);
}

static void to_int3(benchmark::State& state) {
   std::string s = "AB54A98CEB1F0ADF";
   
   for (auto _ : state)
      to_int3<int128_t>(s);
}

BENCHMARK(to_string);
BENCHMARK(to_string2);
BENCHMARK(to_string3);
BENCHMARK(to_int);
BENCHMARK(to_int2);
BENCHMARK(to_int3);

BENCHMARK_MAIN();
