#include <benchmark/benchmark.h>

#include <boost/multiprecision/cpp_int.hpp>
#include "abseil-cpp/absl/numeric/int128.h"
#include "intx/intx.hpp"

#include <iostream>

template<typename TYPE>
static void create_type(benchmark::State& state) {
   for (auto _ : state)
      TYPE v = 1;
}

template<typename TYPE>
static void add_type(benchmark::State& state) {
   TYPE     v = 1;
   uint64_t a = 999999;
   for (auto _ : state)
      v += a;
}

template<typename TYPE>
static void multiply_type(benchmark::State& state) {
   TYPE     v = 10;
   uint64_t a = 2'400;
   for (auto _ : state)
      v *= a;
}

template<typename TYPE>
static void add_multiply_type(benchmark::State& state) {
   TYPE     v = 10;
   TYPE     x = 10;
   uint64_t a = 2'400;
   for (auto _ : state)
      x += v * a;
}



#define BENCHMARK_TYPE(TYPE)                           \
   BENCHMARK( create_type<TYPE> );                     \
   BENCHMARK( add_type<TYPE> );                        \
   BENCHMARK( multiply_type<TYPE> );                   \
   BENCHMARK( add_multiply_type<TYPE> );               \
   /* BENCHMARK_TYPE */

#if __llvm__
# define BENCHMARK_BIGINT(FUNC) BENCHMARK( FUNC< _BitInt(128) > )
#else
# define BENCHMARK_BIGINT(FUNC)
#endif

#define BENCHMARK_FUNC(FUNC)                                \
   BENCHMARK( FUNC< boost::multiprecision::uint128_t > );   \
   BENCHMARK( FUNC< intx::uint128 > );                      \
   BENCHMARK( FUNC< absl::uint128 > );                      \
   BENCHMARK( FUNC< unsigned __int128> );                   \
   BENCHMARK_BIGINT( FUNC );                                \
   /* BENCHMARK_FUNC */


BENCHMARK_FUNC(create_type)
BENCHMARK_FUNC(add_type)
BENCHMARK_FUNC(multiply_type)
BENCHMARK_FUNC(add_multiply_type)



BENCHMARK_MAIN();
