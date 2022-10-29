#include <assert.h>
#include <benchmark/benchmark.h>

#include <iostream>

// Vector
using int_vector = std::vector<int>;

// Capacity
static void STD_Vector_empty(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1 = {1};
        vec1.empty();
    }
}
BENCHMARK(STD_Vector_empty);

static void STD_Vector_size(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1 = {1};
        vec1.size();
    }
}
BENCHMARK(STD_Vector_size);

static void STD_Vector_max_size(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1 = {1};
        vec1.max_size();
    }
}
BENCHMARK(STD_Vector_max_size);

static void STD_Vector_reserve(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1;
        vec1.reserve(5);
    }
}
BENCHMARK(STD_Vector_reserve);

static void STD_Vector_capacity(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1;
        vec1.capacity();
    }
}
BENCHMARK(STD_Vector_capacity);

// Modifiers
static void STD_Vector_clear(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1 = {1};
        vec1.clear();
    }
}
BENCHMARK(STD_Vector_clear);

static void STD_Vector_insert(benchmark::State& state) {
    int_vector vec;
    for (auto _ : state) {
        vec.insert(vec.end(), 0);
    }
}
BENCHMARK(STD_Vector_insert);

static void STD_Vector_erase(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec = {1};
        vec.erase(vec.begin());
    }
}
BENCHMARK(STD_Vector_erase);

static void STD_Vector_push_back(benchmark::State& state) {
    int_vector vec;
    for (auto _ : state) {
        vec.push_back(1);
    }
}
BENCHMARK(STD_Vector_push_back);

static void STD_Vector_pop_back(benchmark::State& state) {
    int_vector vec;
    for (auto _ : state) {
        vec.pop_back();
    }
}
BENCHMARK(STD_Vector_pop_back);

static void STD_Vector_swap(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1 = {1};
        int_vector vec2 = {2};
        vec1.swap(vec2);
    }
}
BENCHMARK(STD_Vector_swap);

static void STD_Vector_resize(benchmark::State& state) {
    for (auto _ : state) {
        int_vector vec1 = {1};
        vec1.resize(5);
    }
}
BENCHMARK(STD_Vector_resize);
