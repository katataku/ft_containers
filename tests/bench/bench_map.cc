#include <assert.h>
#include <benchmark/benchmark.h>

#include <iostream>

// map
using str_int_map = std::map<std::string, int>;

// capacity
static void STD_map_empty(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {};
        map.empty();
    }
}
BENCHMARK(STD_map_empty);

static void STD_map_size(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {};
        map.size();
    }
}
BENCHMARK(STD_map_size);

static void STD_map_max_size(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {};
        map.max_size();
    }
}
BENCHMARK(STD_map_max_size);

// modifier
static void STD_map_clear(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.clear();
    }
}
BENCHMARK(STD_map_clear);

static void STD_map_insert(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.insert({"two", 2});
    }
}
BENCHMARK(STD_map_insert);

static void STD_map_erase(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.erase(map.begin());
        assert(map.size() == 0);
    }
}
BENCHMARK(STD_map_erase);

static void STD_map_swap(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map1 = {{"one", 1}};
        str_int_map map2 = {{"one", 1}, {"two", 2}};
        assert(map1.size() == 1);
        assert(map2.size() == 2);
        map1.swap(map2);
        assert(map1.size() == 2);
        assert(map2.size() == 1);
    }
}
BENCHMARK(STD_map_swap);

// Lookup
static void STD_map_count(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.count("one");
    }
}
BENCHMARK(STD_map_count);

static void STD_map_find(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.find("one");
    }
}
BENCHMARK(STD_map_find);

static void STD_map_equal_range(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.equal_range("one");
    }
}
BENCHMARK(STD_map_equal_range);

static void STD_map_lower_bound(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.lower_bound("one");
    }
}
BENCHMARK(STD_map_lower_bound);

static void STD_map_upper_bound(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.upper_bound("one");
    }
}
BENCHMARK(STD_map_upper_bound);

// Observers
static void STD_map_key_comp(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.key_comp();
    }
}
BENCHMARK(STD_map_key_comp);

static void STD_map_value_comp(benchmark::State& state) {
    for (auto _ : state) {
        str_int_map map = {{"one", 1}};
        map.value_comp();
    }
}
BENCHMARK(STD_map_value_comp);
