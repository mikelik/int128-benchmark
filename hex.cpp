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

template <typename WideInt> std::string to_string(WideInt value) {
  std::string hexString;
  const char *hexDigits = "0123456789abcdef";

  while (value > 0) {
    int digit = value & 0xF; // Extract the least significant nibble
    hexString = hexDigits[digit] + hexString;
    value >>= 4; // Shift right by 4 bits
  }

  return hexString;
}

template <typename WideInt> std::string to_string2(WideInt value) {
  if (value == 0)
    return "0";

  std::string hex_string;
  const char *hex_digits = "0123456789abcdef";

  const int num_digits = (sizeof(WideInt) * 2);

  hex_string.resize(num_digits);
  char *hex_chars = &hex_string[0];
  int leading_zeros = 0;

  for (int i = num_digits - 1; i >= 0; --i) {
    int least_significant_digit = value & 0xF;
    if (least_significant_digit != 0)
      leading_zeros = 0;
    else
      leading_zeros++;
    hex_chars[i] = hex_digits[least_significant_digit];
    value >>= 4; // Shift right by 4 bits
  }

  return hex_string.substr(leading_zeros);
}

template <typename WideInt> std::string to_string3(WideInt value) {
  if (value == 0)
    return "0";

  std::string hexString;
  const char *hexDigits = "0123456789abcdef";

  // Calculate the number of digits required
  int numDigits =
      (sizeof(WideInt) * 2); // Each byte is represented by 2 hexadecimal digits

  hexString.resize(numDigits); // Resize the string to the required length
  char *hexChars =
      &hexString[0]; // Obtain a pointer to the string's internal buffer
  int leading_zeros = 0;

  // Convert each nibble to a hexadecimal digit
  for (int i = numDigits - 1; i >= 0; --i) {
    int least_significant_digit =
        value & 0xF; // Extract the least significant nibble
    if (least_significant_digit != 0)
      leading_zeros = 0;
    else
      leading_zeros++;
    hexChars[i] = hexDigits[least_significant_digit];
    value = __builtin_rotateright64(value, 4); // Rotate right by 4 bits
  }

  return hexString.substr(leading_zeros);
}

template <typename I>
std::string to_string4(I w, size_t hex_len = sizeof(I) << 1) {
  // TODO: to be fully functional need to trim leading zeros
  static const char *digits = "0123456789ABCDEF";
  std::string rc(hex_len, '0');
  for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
    rc[i] = digits[(w >> j) & 0x0f];
  return rc;
}

// highest performance in benchmarks
template <typename WideInt> std::string to_string5(WideInt value) {
  if (value == 0)
    return "0";

  constexpr int num_digits = (sizeof(WideInt) * 2);
  constexpr int hex_digits_capacity = num_digits + 1; // +1 for null terminator

  char hex_digits[hex_digits_capacity];
  int digit_index = num_digits;
  int leading_zeros = 0;

  while (value != 0 && digit_index > 0) {
    int least_significant_digit = value & 0xF;
    if (least_significant_digit != 0)
      leading_zeros = 0;
    else
      leading_zeros++;
    hex_digits[--digit_index] = "0123456789abcdef"[least_significant_digit];
    value >>= 4;
  }

  return std::string(hex_digits + digit_index,
                     num_digits - digit_index - leading_zeros);
}

template <typename WideInt> WideInt to_int(const std::string &hexString) {
  if (hexString.empty())
    throw std::invalid_argument("Empty hexadecimal string");

  // Skip "0x" prefix if present
  std::size_t startIdx =
      (hexString.size() > 2 && hexString.substr(0, 2) == "0x") ? 2 : 0;

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

// highest performance in benchmarks
template <typename WideInt> WideInt to_int2(const std::string &hex_string) {
  if (hex_string.empty())
    throw std::invalid_argument(
        "eosio::wideint::from_hex Empty hexadecimal string");

  const std::size_t start_idx =
      (hex_string.size() > 2 && hex_string[0] == '0' &&
       (hex_string[1] == 'x' || hex_string[1] == 'X'))
          ? 2
          : 0;

  WideInt result = 0;

  for (std::size_t i = start_idx; i < hex_string.size(); ++i) {
    const char c = hex_string[i];
    int val = 0;
    if (c <= '9') {
      if (c < '0')
        throw std::invalid_argument(
            "eosio::wideint::from_hex invalid hexadecimal string");
      val = c - '0';
    } else {
      if (c <= 'F') {
        if (c < 'A')
          throw std::invalid_argument(
              "eosio::wideint::from_hex invalid hexadecimal string");
        val = c - 'A' + 10;
      } else {
        if (c < 'a' || c > 'f')
          throw std::invalid_argument(
              "eosio::wideint::from_hex invalid hexadecimal string");

        val = c - 'a' + 10;
      }
    }

    result = (result << 4) | static_cast<WideInt>(val);
  }
  return result;
}

template <typename WideInt> WideInt to_int3(const std::string &hexString) {
  if (hexString.empty())
    throw std::invalid_argument("Empty hexadecimal string");

  std::size_t startIdx =
      (hexString.size() > 2 && hexString.substr(0, 2) == "0x") ? 2 : 0;

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

//below function has a bug - do not use, it was just testing LUT
template <typename WideInt> WideInt to_int4(const std::string &hex_string) {
  constexpr int lookup_table[256] = {
      // Initialize the lookup table with values for each hexadecimal character
      // For example: '0' = 0, '1' = 1, ..., 'A' = 10, 'B' = 11, ..., 'F' = 15
      // Invalid characters will have a value of -1
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4,
      5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, -1,
      -1, -1, -1, -1, -1, -1,
      // Repeat the pattern for lowercase letters
      -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      // Fill the remaining values with -1 for invalid characters
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1};

  const std::size_t start_idx =
      (hex_string.size() > 2 && hex_string.substr(0, 2) == "0x") ? 2 : 0;

  WideInt result = 0;

  for (std::size_t i = start_idx; i < hex_string.size(); ++i) {
    const char c = hex_string[i];
    const int value = lookup_table[static_cast<unsigned char>(c)];

    // if (value == -1)
    // eosio::check(false, "eosio::wideint::from_hex Invalid hexadecimal
    // string");

    result = (result << 4) | value;
  }

  return result;
}

static void to_string(benchmark::State &state) {
  int128_t i = 12345678901234567890ULL;

  for (auto _ : state)
    to_string(i);
}

static void to_string2(benchmark::State &state) {
  int128_t i = 12345678901234567890ULL;

  for (auto _ : state)
    to_string2(i);
}

static void to_string3(benchmark::State &state) {
  int128_t i = 12345678901234567890ULL;

  for (auto _ : state)
    to_string3(i);
}

static void to_string4(benchmark::State &state) {
  int128_t i = 12345678901234567890ULL;

  for (auto _ : state)
    to_string4(i);
}

static void to_string5(benchmark::State &state) {
  int128_t i = 12345678901234567890ULL;

  for (auto _ : state)
    to_string5(i);
}

static void to_int(benchmark::State &state) {
  std::string s = "AB54A98CEB1F0ADF";

  for (auto _ : state)
    to_int<int128_t>(s);
}

static void to_int2(benchmark::State &state) {
  std::string s = "AB54A98CEB1F0ADF";

  for (auto _ : state)
    to_int2<int128_t>(s);
}

static void to_int3(benchmark::State &state) {
  std::string s = "AB54A98CEB1F0ADF";

  for (auto _ : state)
    to_int3<int128_t>(s);
}

static void to_int4(benchmark::State &state) {
  std::string s = "AB54A98CEB1F0ADF";

  for (auto _ : state)
    to_int4<int128_t>(s);
}

BENCHMARK(to_string);
BENCHMARK(to_string2);
BENCHMARK(to_string3);
BENCHMARK(to_string4);
BENCHMARK(to_string5);
BENCHMARK(to_int);
BENCHMARK(to_int2);
BENCHMARK(to_int3);
BENCHMARK(to_int4);

BENCHMARK_MAIN();
