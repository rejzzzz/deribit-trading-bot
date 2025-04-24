#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

class ThreadPool
{
public:
    // Constructor: Creates a pool of worker threads
    explicit ThreadPool(size_t num_threads);

    // Submit a task to the thread pool
    template <typename Func, typename... Args>
    auto submit(Func &&func, Args &&...args, bool is_critical = false) -> std::future<decltype(func(args...))>;

    // Destructor: Stops all threads
    ~ThreadPool();

private:
    std::vector<std::thread> workers;        // Worker threads
    std::queue<std::function<void()>> tasks; // Task queue
    std::mutex queue_mutex;                  // Mutex for synchronizing access to the task queue
    std::condition_variable condition;       // Condition variable for signaling threads
    bool stop;                               // Flag to indicate shutdown
};

template <typename Func, typename... Args>
auto ThreadPool::submit(Func &&func, Args &&...args, bool is_critical) -> std::future<decltype(func(args...))>
{
    using return_type = decltype(func(args...));

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

    std::future<return_type> result = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        if (stop)
        {
            throw std::runtime_error("ThreadPool is shutting down");
        }

        // Check if all threads are busy and the task is critical
        if (is_critical && tasks.size() >= workers.size())
        {
            // Create a new thread for the critical task
            std::thread([task]()
                        { (*task)(); })
                .detach();
            return result;
        }

        // Otherwise, add the task to the queue
        tasks.emplace([task]()
                      { (*task)(); });
    }

    condition.notify_one();
    return result;
}

#endif // THREAD_POOL_H