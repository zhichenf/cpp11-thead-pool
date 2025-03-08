#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class TaskQueue{
    //表示任务的类型
    using ElemType = std::function<void()>;
 
public:
    explicit TaskQueue(int que_size);
    ~TaskQueue() = default;
    void Push(ElemType&& ptask);
    ElemType Pop();
    bool IsFull() const;
    bool IsEmpty() const;
    void WakeUp();

private:
    size_t que_size_;
    std::queue<ElemType> que_;			//用于存放任务，任务应当是一个void()的可调用对象
    std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    bool flag_;  //为了唤醒所有的工作线程，可以让while退出
};

#endif
