#include <iostream>
#include <vector>
#include <functional>

#include "thread_pool.h"

//自己实现任务逻辑交给线程池去执行
class MyTask {
public:
    explicit MyTask(const int num) : num_(num) {}
    void process() const {
        std::cout << num_ << std::endl;
    }
    char num_;
};

int main() {
    ThreadPool pool(4, 10);
    std::vector<MyTask> tasks;
    for (int i = 0; i < 40; i++) {
        tasks.emplace_back(i+'A');
    }
    pool.Start();
    for (int i = 0; i < 40; i++) {
        pool.AddTask(std::bind(&MyTask::process,&tasks[i]));
    }
    pool.Stop();
}
