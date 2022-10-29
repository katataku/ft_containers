#include <assert.h>
#include <benchmark/benchmark.h>

#include <iostream>

// Vector
#include "./bench_vector.cc"

// map
#include "./bench_map.cc"
BENCHMARK_MAIN();