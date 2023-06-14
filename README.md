# Benchmark of uint128

In this repository you can run benchmark for following uint128 implementations:
- GCC builtin unsigned __int128
- chfast intx::uint128
- abseil absl::uint128
- boost::multiprecision::uint128

# Prerequisites

Google Benchmark should be installed according to https://github.com/google/benchmark#installation
Boost includes installed

# How to run benchmark?

```
git clone https://github.com/mikelik/int128-benchmark.git
cd int128-benchmark
git submodule update --init  --recursive
mkdir build
cd build
cmake ..
make
taskset -c 0 ./int128-benchmark
```

To reduce variation follow steps from https://github.com/google/benchmark/blob/main/docs/reducing_variance.md#reducing-variance-in-benchmarks

# Example output

```
$ taskset -c 0 ./int128-benchmark 
2023-06-14T14:32:24+02:00
Running ./int128-benchmark
Run on (20 X 3431.84 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
Load Average: 1.08, 0.83, 0.68
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
abseil_create_uint128             0.655 ns        0.655 ns   1000000000
abseil_add_uint128                 6.91 ns         6.91 ns    102300654
abseil_multiply_uint128            7.17 ns         7.17 ns     98244952
abseil_add_multiply_uint128        11.7 ns         11.7 ns     60102632
builtin_create_uint128            0.657 ns        0.657 ns   1000000000
builtin_add_uint128                1.75 ns         1.75 ns    400711845
builtin_multiply_uint128           1.97 ns         1.97 ns    355840282
builtin_add_multiply_uint128       1.67 ns         1.67 ns    422742424
intx_create_uint128               0.661 ns        0.661 ns   1000000000
intx_add_uint128                   16.6 ns         16.6 ns     42058001
intx_multiply_uint128              15.1 ns         15.1 ns     46044943
intx_add_multiply_uint128          27.8 ns         27.8 ns     25115148
boost_create_uint128              0.656 ns        0.656 ns   1000000000
boost_add_uint128                  13.4 ns         13.4 ns     52874018
boost_multiply_uint128             13.2 ns         13.2 ns     52872268
boost_add_multiply_uint128         29.5 ns         29.5 ns     23178985
$ taskset -c 0 ./int128-benchmark 
2023-06-14T14:32:42+02:00
Running ./int128-benchmark
Run on (20 X 688.621 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
Load Average: 1.05, 0.84, 0.69
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
abseil_create_uint128             0.656 ns        0.656 ns   1000000000
abseil_add_uint128                 7.05 ns         7.05 ns    101091393
abseil_multiply_uint128            7.37 ns         7.37 ns     94419389
abseil_add_multiply_uint128        11.9 ns         11.9 ns     58683362
builtin_create_uint128            0.656 ns        0.656 ns   1000000000
builtin_add_uint128                1.75 ns         1.75 ns    400529383
builtin_multiply_uint128           1.96 ns         1.96 ns    354129418
builtin_add_multiply_uint128       1.66 ns         1.66 ns    419210581
intx_create_uint128               0.659 ns        0.659 ns   1000000000
intx_add_uint128                   17.0 ns         17.0 ns     41242503
intx_multiply_uint128              15.4 ns         15.4 ns     45459449
intx_add_multiply_uint128          27.9 ns         27.9 ns     25054660
boost_create_uint128              0.655 ns        0.655 ns   1000000000
boost_add_uint128                  13.1 ns         13.1 ns     52835982
boost_multiply_uint128             13.1 ns         13.1 ns     52708928
boost_add_multiply_uint128         29.8 ns         29.8 ns     23038686
```
