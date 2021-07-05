#include <atomic>
#include <future>
using namespace std;

template<class F, class... Args>
void setInterval(std::atomic_bool &cancelToken, size_t interval, F &&f, Args &&... args) {
    cancelToken.store(true);
    auto cb = bind(forward<F>(f), forward<Args>(args)...);
    async(launch::async, [=, &cancelToken]()mutable {
        while (cancelToken.load()) {
            cb();
            this_thread::sleep_for(chrono::milliseconds(interval));
        }
    });
}