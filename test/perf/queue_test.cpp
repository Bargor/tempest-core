#include <benchmark/benchmark.h>
#include <queue>
#include <container/queue.h>
#include <atomic/spinlock.h>
#include <future>
#include <thread>

BENCHMARK_MAIN();

namespace tst {
namespace core {

    constexpr std::size_t size = 1023;

    static void BM_spsc_queue(benchmark::State& state) {

        spsc_queue<std::int32_t, size> queue;

		if (state.thread_index == 0) {
	        std::int32_t count = 0;

            for (auto _ : state) {

                while (count < state.range(0)) {
                    auto res = queue.try_push(count);
                    if (res) ++count;
                }
            }
		} else {
			std::int32_t count = 0;

            for (auto _ : state) {
                while (count < state.range(0)) {
                    auto res = queue.try_pop();
                    if (res) {
                        count++;
                    }
                }
            }
		}
        
        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    }

    static void BM_spinlock_queue(benchmark::State& state) {
        std::queue<std::int32_t> queue;
        spinlock spin;

		if (state.thread_index == 0) {
			std::int32_t count = 0;
			
			for (auto _ : state) {
                while (count < state.range(0)) {
                    spin.lock();
                    queue.push(count);
                    spin.unlock();
                    ++count;
                }
            }
		} else {
			std::int32_t count = 0;

            for (auto _ : state) {
                while (count < state.range(0)) {
                    if (!queue.empty())
                    {
                        spin.lock();
                        queue.pop();
                        spin.unlock();
                        ++count;
                    }
                }
            }
		}

        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    }

    BENCHMARK(BM_spinlock_queue)->RangeMultiplier(2)->Range(size, 8 << 18)->Threads(2);
    BENCHMARK(BM_spsc_queue)->RangeMultiplier(2)->Range(size, 8 << 18)->Threads(2);

}
}

