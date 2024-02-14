// #include "ThreadPool.h"

// ThreadPool::ThreadPool(unsigned int numThreads) : m_Stop(false)
// {
//     m_Workers.reserve(numThreads);
//     for (unsigned int i = 0; i < numThreads; ++i)
//     {
//         m_Workers.emplace_back([this]
//                                {
//                 while(true)
//                 {
//                     std::function<void()> task;
//                     {
//                         std::unique_lock lock(m_QueueMutex);

//                         while(!m_Stop && m_Tasks.empty())
//                         {
//                             m_Condition.wait(lock);
//                         }

//                         if (m_Stop && m_Tasks.empty())
//                         {
//                             return;
//                         }

//                         task = std::move(m_Tasks.front());
//                         m_Tasks.pop();
//                     }

//                     task();
//                 } });
//     }
// }

// template <typename F, typename... Args>
// auto ThreadPool::Enqueue(F &&f, Args &&...args) -> std::future<std::invoke_result_t<F, Args...>>
// {
//     using ReturnType = std::invoke_result_t<F, Args...>;

//     auto task = std::make_shared<std::packaged_task<ReturnType()>>(
//         [f = std::forward<F>(f), args = std::make_tuple(std::forward<Args>(args)...)]() mutable
//         {
//             return std::apply(std::move(f), std::move(args));
//         });

//     auto future = task->get_future();

//     {
//         std::unique_lock lock(m_QueueMutex);
//         m_Tasks.emplace([task]()
//                         { std::invoke(*task); });
//     }

//     m_Condition.notify_one();
//     return future;
// }

// ThreadPool::~ThreadPool()
// {
//     {
//         std::unique_lock lock(m_QueueMutex);
//         m_Stop = true;
//     }

//     m_Condition.notify_all();

//     for (auto &worker : m_Workers)
//     {
//         worker.join();
//     }
// }
