# Benchmark of uint128

In this repository you can run benchmark for following uint128 implementations:
- GCC builtin unsigned __int128
- LLVM builtin _BitInt(128)
- chfast intx::uint128
- abseil absl::uint128
- boost::multiprecision::uint128

# Requirements

1. Google Benchmark should be installed according to https://github.com/google/benchmark#installation
2. Boost includes installed
3. (Optionally) If you want to use LLVM, install at least clang-16


# How to run benchmark?

```
git clone https://github.com/mikelik/int128-benchmark.git
cd int128-benchmark
git submodule update --init  --recursive
mkdir build
cd build
# Optionally if you want to use LLVM - uncomment two below lines
# export CC=/usr/bin/clang
# export CXX=/usr/bin/clang++
cmake ..
make
taskset -c 0 ./int128-benchmark
```

To reduce variation follow steps from https://github.com/google/benchmark/blob/main/docs/reducing_variance.md#reducing-variance-in-benchmarks

# Example output for GCC

```
$ taskset -c 0 ./int128-benchmark 
2023-06-15T09:46:31+02:00
Running ./int128-benchmark
Run on (20 X 4600 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
Load Average: 1.93, 1.47, 0.90
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
------------------------------------------------------------------------------------------------
Benchmark                                                      Time             CPU   Iterations
------------------------------------------------------------------------------------------------
create_type< boost::multiprecision::uint128_t >            0.658 ns        0.658 ns   1000000000
create_type< intx::uint128 >                               0.658 ns        0.658 ns   1000000000
create_type< absl::uint128 >                               0.657 ns        0.657 ns   1000000000
create_type< unsigned __int128>                            0.656 ns        0.656 ns   1000000000
add_type< boost::multiprecision::uint128_t >                13.2 ns         13.2 ns     52938826
add_type< intx::uint128 >                                   16.8 ns         16.8 ns     42118742
add_type< absl::uint128 >                                   7.10 ns         7.10 ns     97035886
add_type< unsigned __int128>                                1.74 ns         1.74 ns    400531400
multiply_type< boost::multiprecision::uint128_t >           13.1 ns         13.1 ns     53095995
multiply_type< intx::uint128 >                              15.2 ns         15.2 ns     45782580
multiply_type< absl::uint128 >                              7.41 ns         7.41 ns     93341554
multiply_type< unsigned __int128>                           1.97 ns         1.97 ns    354164013
add_multiply_type< boost::multiprecision::uint128_t >       29.6 ns         29.6 ns     23458579
add_multiply_type< intx::uint128 >                          28.0 ns         28.0 ns     24805161
add_multiply_type< absl::uint128 >                          11.9 ns         11.9 ns     58560456
add_multiply_type< unsigned __int128>                       1.68 ns         1.68 ns    418555225
```

# Example output for LLVM

```
$ taskset -c 0 ./int128-benchmark 
2023-06-15T09:43:19+02:00
Running ./int128-benchmark
Run on (20 X 4600 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
Load Average: 4.23, 1.44, 0.76
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
------------------------------------------------------------------------------------------------
Benchmark                                                      Time             CPU   Iterations
------------------------------------------------------------------------------------------------
create_type< boost::multiprecision::uint128_t >             4.17 ns         4.17 ns    168308870
create_type< intx::uint128 >                                1.97 ns         1.97 ns    355572831
create_type< absl::uint128 >                                1.53 ns         1.53 ns    456689371
create_type< unsigned __int128>                             1.53 ns         1.53 ns    456332937
create_type< _BitInt(128) >                                 1.53 ns         1.53 ns    456871724
add_type< boost::multiprecision::uint128_t >                11.3 ns         11.3 ns     61984518
add_type< intx::uint128 >                                   20.0 ns         20.0 ns     34847497
add_type< absl::uint128 >                                   7.99 ns         7.99 ns     87621849
add_type< unsigned __int128>                                1.53 ns         1.53 ns    456825360
add_type< _BitInt(128) >                                    1.53 ns         1.53 ns    457364423
multiply_type< boost::multiprecision::uint128_t >           11.5 ns         11.5 ns     60967866
multiply_type< intx::uint128 >                              14.1 ns         14.1 ns     49644945
multiply_type< absl::uint128 >                              8.08 ns         8.08 ns     86424209
multiply_type< unsigned __int128>                           1.54 ns         1.54 ns    456751520
multiply_type< _BitInt(128) >                               1.53 ns         1.53 ns    457306012
add_multiply_type< boost::multiprecision::uint128_t >       27.1 ns         27.1 ns     25883643
add_multiply_type< intx::uint128 >                          33.0 ns         33.0 ns     21215771
add_multiply_type< absl::uint128 >                          12.8 ns         12.8 ns     54193273
add_multiply_type< unsigned __int128>                       1.75 ns         1.75 ns    394886961
add_multiply_type< _BitInt(128) >                           1.97 ns         1.97 ns    355335862

```

# Results

The fastest are compiler builtins: either __int128 from GCC or _BitInt(128) from clang.
Recommended is _BitInt(128) as it will be included in C23 standard.