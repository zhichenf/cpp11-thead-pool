#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

#include "thread_pool.h"

ThreadPool::ThreadPool(const size_t thread_num, const size_t que_size) :
thread_num_(thread_num),
que_size_(que_size),
task_que_(que_size_),
is_exit_(false) {
    threads_.reserve(thread_num_);
}

void ThreadPool::Start() {
    for (size_t i = 0; i < thread_num_; i++) {
        threads_.push_back(std::make_unique<std::thread>(std::bind(&ThreadPool::DoTask,this)));
    }
}

void ThreadPool::Stop() {
    //确保任务队列里的任务可以执行完
    while(!task_que_.IsEmpty()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    is_exit_ = true;
    task_que_.WakeUp();
    for (size_t i = 0; i < thread_num_; i++) {
        threads_[i]->join();
    }
}

void ThreadPool::AddTask(Task&& task) {
    if (task) {
        task_que_.Push(std::move(task));
    }
} 

ThreadPool::Task ThreadPool::GetTask() {
    return task_que_.Pop();
}

void ThreadPool::DoTask() {
    while(!is_exit_) {
        if (Task task = GetTask()) {
            task();
        }
    } 
}
