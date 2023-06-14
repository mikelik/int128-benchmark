#include <benchmark/benchmark.h>
#include "abseil-cpp/absl/numeric/int128.h"
#include "intx/intx.hpp"

static void abseil_create_uint128(benchmark::State& state) {
  for (auto _ : state)
    absl::uint128 v = 1;
  
}
BENCHMARK(abseil_create_uint128);


static void abseil_add_uint128(benchmark::State& state) {
  absl::uint128 v = 1;
  uint64_t a = 999999;
  for (auto _ : state)
    v += a;
}
BENCHMARK(abseil_add_uint128);

static void abseil_multiply_uint128(benchmark::State& state) {
  absl::uint128 v = 10;
  uint64_t a = 2'400;
  for (auto _ : state)
    v *= a;
}
BENCHMARK(abseil_multiply_uint128);

static void abseil_add_multiply_uint128(benchmark::State& state) {
  absl::uint128 v = 10;
  absl::uint128 x = 10;
  uint64_t a = 2'400;
  for (auto _ : state)
    x += v * a;
}
BENCHMARK(abseil_add_multiply_uint128);

///////////////////////

static void builtin_create_uint128(benchmark::State& state) {
  for (auto _ : state)
    unsigned __int128 v = 1;
  
}
BENCHMARK(builtin_create_uint128);


static void builtin_add_uint128(benchmark::State& state) {
  unsigned __int128 v = 1;
  uint64_t a = 999999;
  for (auto _ : state)
    v += a;
}
BENCHMARK(builtin_add_uint128);

static void builtin_multiply_uint128(benchmark::State& state) {
  unsigned __int128 v = 10;
  uint64_t a = 2'400;
  for (auto _ : state)
    v *= a;
}
BENCHMARK(builtin_multiply_uint128);

static void builtin_add_multiply_uint128(benchmark::State& state) {
  unsigned __int128 v = 10;
  unsigned __int128 x = 10;
  uint64_t a = 2'400;
  for (auto _ : state)
    x += v * a;
}
BENCHMARK(builtin_add_multiply_uint128);


//////

static void intx_create_uint128(benchmark::State& state) {
  for (auto _ : state)
    intx::uint128 v = 1;
  
}
BENCHMARK(intx_create_uint128);


static void intx_add_uint128(benchmark::State& state) {
  intx::uint128 v = 1;
  uint64_t a = 999999;
  for (auto _ : state)
    v += a;
}
BENCHMARK(intx_add_uint128);

static void intx_multiply_uint128(benchmark::State& state) {
  intx::uint128 v = 10;
  uint64_t a = 2'400;
  for (auto _ : state)
    v *= a;
}
BENCHMARK(intx_multiply_uint128);

static void intx_add_multiply_uint128(benchmark::State& state) {
  intx::uint128 v = 10;
  intx::uint128 x = 10;
  uint64_t a = 2'400;
  for (auto _ : state)
    x += v * a;
}
BENCHMARK(intx_add_multiply_uint128);

BENCHMARK_MAIN();