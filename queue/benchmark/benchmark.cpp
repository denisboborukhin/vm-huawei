#include <vector>
#include <benchmark/benchmark.h>

#include "queue.hpp"

static const int RANGE_QUEUE_NATIVE = 10000000;
static const int RANGE_QUEUE_HARD = 100000;

template <typename queue_type>
static void BM_queue_native(benchmark::State &state)
{
    for (auto _ : state) {
        queue_type queue;

        for (int count = 0; count != state.range(0); ++count)
            queue.push(count);

        long int sum = queue.front();
        while (queue.size() != 1) {
            sum += queue.front();
            queue.pop();
            sum += queue.front();
        }
    }
}

BENCHMARK(BM_queue_native<my_containers::queue_stacks<int>>)->Arg(RANGE_QUEUE_NATIVE)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_queue_native<my_containers::queue_list<int>>)->Arg(RANGE_QUEUE_NATIVE)->Unit(benchmark::kMillisecond);

template <typename queue_type>
static void BM_queue_hard(benchmark::State &state)
{
    for (auto _ : state) {
        queue_type queue;

        for (int count = 0; count != state.range(0); ++count) {
            queue.push(count);
            queue.pop();
        }
    }
}

BENCHMARK(BM_queue_hard<my_containers::queue_stacks<int>>)->Arg(RANGE_QUEUE_HARD)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_queue_hard<my_containers::queue_list<int>>)->Arg(RANGE_QUEUE_HARD)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
