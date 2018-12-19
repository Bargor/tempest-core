#include <atomic/spinlock.h>
#include <benchmark/benchmark.h>
#include <container/queue.h>
#include <future>
#include <memory>
#include <queue>
#include <thread>

BENCHMARK_MAIN();

namespace tst {
namespace core {
	
	struct s512 {
		std::int64_t arr[8];
	}

    constexpr std::size_t size = 1023;

	template <typename T>
    void BM_spsc_queue(benchmark::State& state) {
        static spsc_queue<T, size> queue;
        std::int32_t count = 0;

        for (auto _ : state) {
            if (state.thread_index == 0) {
                while (count < state.range(0)) {
                    auto res = queue.try_push(count);
                    if (res) ++count;
                }
            } else {
                while (count < state.range(0)) {
                    auto res = queue.try_pop();
                    if (res) {
                        ++count;
                    }
                }
            }
        }

        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    }

	template <typename T>
    void BM_spinlock_queue(benchmark::State& state) {
        static std::queue<T> queue;
        static spinlock spin;

        std::int32_t push_count = 0;
        std::int32_t pop_count = 0;

        for (auto _ : state) {
            if (state.thread_index == 0) {
                while (push_count < state.range(0)) {
                    spin.lock();
                    queue.push(push_count);
                    spin.unlock();
                    ++push_count;
                }
            } else {
                while (pop_count < state.range(0)) {
                    if (!queue.empty()) {
                        spin.lock();
                        queue.pop();
                        spin.unlock();
                        ++pop_count;
                    }
                }
            }
        }

        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    } // namespace core

    BENCHMARK_TEMPLATE(BM_spinlock_queue, std::int32_t, s512)->RangeMultiplier(2)->Range(size, 8 << 18)->Threads(2);
    BENCHMARK_TEMPLATE(BM_spsc_queue, std::int32_t, s512)->RangeMultiplier(2)->Range(size, 8 << 18)->Threads(2);

    static void BM_spinlock_queue_push(benchmark::State& state) {
        std::queue<std::int32_t> queue;
        spinlock spin;

        std::int32_t count = 0;

        for (auto _ : state) {
            while (count < state.range(0)) {
                spin.lock();
                queue.push(count);
                spin.unlock();
                ++count;
            }
        }

        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    }

    static void BM_spsc_queue_push(benchmark::State& state) {
        spsc_queue<std::int32_t, 1 << 16> queue;

        std::int32_t count = 0;

        for (auto _ : state) {
            while (count < state.range(0)) {
                auto res = queue.try_push(count);
                if (res) ++count;
            }
        }

        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    }

    BENCHMARK(BM_spinlock_queue_push)->RangeMultiplier(2)->Range(size, 1 << 16);
    BENCHMARK(BM_spsc_queue_push)->RangeMultiplier(2)->Range(size, 1 << 16);
	
	static void BM_spinlock_queue_pop(benchmark::State& state) {
        std::queue<std::int32_t> queue;
        spinlock spin;

        std::int32_t count = 0;
		
		while (count < state.range(0)) {
            queue.push(count);
            ++count;
        }

        for (auto _ : state) {
            while (count > 0) {
                spin.lock();
                queue.pop();
                spin.unlock();
                --count;
            }
        }

        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    }

    static void BM_spsc_queue_pop(benchmark::State& state) {
        spsc_queue<std::int32_t, 1 << 16> queue;

        std::int32_t count = 0;
		
		while (count < state.range(0)) {
            auto res = queue.try_push(count);
            if (res) ++count;
        }

        for (auto _ : state) {
            while (count > 0) {
                auto res = queue.try_pop(count);
                if (res) --count;
            }
        }

        state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    }

    BENCHMARK(BM_spinlock_queue_pop)->RangeMultiplier(2)->Range(size, 1 << 16);
    BENCHMARK(BM_spsc_queue_pop)->RangeMultiplier(2)->Range(size, 1 << 16);
} // namespace core
} // namespace tst
