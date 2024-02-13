#pragma once

#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <stop_token>
#include <condition_variable>
#include <queue>
#include <functional>
#include <tuple>

class ThreadPool
{
public:
    explicit ThreadPool(std::size_t numThreads);

    template <typename F, typename... Args>
    auto Enqueue(F &&f, Args &&...args) -> std::future<std::invoke_result_t<F, Args...>>;

    ~ThreadPool();

private:
    std::vector<std::thread> m_Workers;
    std::queue<std::function<void()>> m_Tasks;

    std::mutex m_QueueMutex;
    std::condition_variable m_Condition;
    bool m_Stop;
};
