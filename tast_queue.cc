#include "task_queue.h"

TaskQueue::TaskQueue(const int que_size) : 
que_size_(que_size),
mutex_(),
not_full_(),
not_empty_(),
flag_(true)
{   
}

void TaskQueue::Push(ElemType&& ptask) {
    std::unique_lock lock(mutex_);
    while(IsFull()) {
        //等待not_full_来唤醒
        not_full_.wait(lock);
    }
    que_.push(std::move(ptask));
    not_empty_.notify_one();
}

TaskQueue::ElemType TaskQueue::Pop() {
    std::unique_lock lock(mutex_);
    while(IsEmpty() && flag_) {
        //等待not_empty_来唤醒
        not_empty_.wait(lock);
    }
    if (flag_) {
        ElemType task = que_.front();
        que_.pop();
        not_full_.notify_one();
        return task;
    } else {
        return nullptr;
    }
}

bool TaskQueue::IsFull() const {
    return que_.size() == que_size_;
}

bool TaskQueue::IsEmpty() const {
    return que_.empty();
}

void TaskQueue::WakeUp() {
    flag_ = false;
    not_empty_.notify_all();
}
