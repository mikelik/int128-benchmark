# Benchmark of uint128

In this repository you can run benchmark for following uint128 implementations:
- GCC builtin unsigned __int128
- chfast intx::uint128
- abseil absl::uint128

# Prerequisites

Google Benchmark should be installed according to https://github.com/google/benchmark#installation

# How to run benchmark?

```
git clone https://github.com/mikelik/int128-benchmark.git
git submodule update --init  --recursive
mkdir int128-benchmark/build
cd int128-benchmark/build
cmake ..
make
taskset -c 0 ./int128-benchmark
```

To reduce variation follow steps from https://github.com/google/benchmark/blob/main/docs/reducing_variance.md#reducing-variance-in-benchmarks

# Example output

```
mikel@msi:~/repo/int128-benchmark/build$ taskset -c 0 ./int128-benchmark 
2023-06-14T12:32:01+02:00
Running ./int128-benchmark
Run on (20 X 920.971 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
Load Average: 0.74, 0.69, 0.65
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
abseil_create_uint128             0.656 ns        0.656 ns   1000000000
abseil_add_uint128                 7.04 ns         7.04 ns    100385057
abseil_multiply_uint128            7.30 ns         7.30 ns     96445849
abseil_add_multiply_uint128        11.8 ns         11.8 ns     59687066
builtin_create_uint128            0.657 ns        0.657 ns   1000000000
builtin_add_uint128                1.75 ns         1.75 ns    400995245
builtin_multiply_uint128           1.97 ns         1.97 ns    354758577
builtin_add_multiply_uint128       1.67 ns         1.67 ns    418413346
intx_create_uint128               0.656 ns        0.656 ns   1000000000
intx_add_uint128                   17.0 ns         17.0 ns     41162334
intx_multiply_uint128              14.2 ns         14.2 ns     49350020
intx_add_multiply_uint128          28.0 ns         28.0 ns     24998648
mikel@msi:~/repo/int128-benchmark/build$ taskset -c 0 ./int128-benchmark 
2023-06-14T12:32:12+02:00
Running ./int128-benchmark
Run on (20 X 972.583 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
Load Average: 0.93, 0.74, 0.66
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
abseil_create_uint128             0.655 ns        0.655 ns   1000000000
abseil_add_uint128                 7.11 ns         7.11 ns     99958711
abseil_multiply_uint128            7.39 ns         7.39 ns     95289530
abseil_add_multiply_uint128        11.9 ns         11.9 ns     58429688
builtin_create_uint128            0.656 ns        0.656 ns   1000000000
builtin_add_uint128                1.74 ns         1.74 ns    400869463
builtin_multiply_uint128           1.97 ns         1.97 ns    355227532
builtin_add_multiply_uint128       1.67 ns         1.67 ns    416988853
intx_create_uint128               0.655 ns        0.655 ns   1000000000
intx_add_uint128                   17.1 ns         17.1 ns     40955219
intx_multiply_uint128              14.2 ns         14.2 ns     49197544
intx_add_multiply_uint128          28.0 ns         28.0 ns     24825084
```
