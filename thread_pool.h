#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <memory>
#include <vector>
#include <functional>
#include <thread>

#include "task_queue.h"

class ThreadPool {
    using Task = std::function<void()>;
public:
    ThreadPool(size_t thread_num, size_t que_size);
    ~ThreadPool() = default;
    void Start();
    void Stop();
    void AddTask(Task&& task);

private:
    Task GetTask();
    void DoTask();

private:
    size_t thread_num_;
    size_t que_size_; 
    std::vector<std::unique_ptr<std::thread>> threads_;
    TaskQueue task_que_;
    bool is_exit_;
};

#endif
