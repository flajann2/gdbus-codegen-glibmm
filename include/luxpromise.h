#include <mutex>
#include <numeric>
#include <thread>
#include <vector>
#include <condition_variable>

/**
 */
enum class LuxTypes {property, method, event};

using mutex_l   = std::mutex;
using unique_l  = std::unique_lock<mutex_l>;
using condvar = std::condition_variable;

/**
 */
template <typename Data, LuxTypes LT = LuxTypes::property>
class LuxPromise {
  
  Data data_;
  mutex_l mutex_;
  condvar cv_;
  bool fresh_ = false;
  bool active_ = true;

  template<typename LOCK>
  void wakeUp(LOCK& lk) {
    fresh_ = true;
    lk.unlock();
    cv_.notify_all();
  }
  
public:
  LuxPromise(Data data) : data_(data) { }

  LuxPromise& operator=(Data&& update_data) {
    unique_l lk(mutex_);
    data_ = std::move(update_data);
    wakeUp(lk);
    return *this;
  }

  LuxPromise& operator=(Data& update_data) {
    unique_l lk(mutex_);
    data_ = update_data;
    wakeUp(lk);
    return *this;
  }
  
  const Data& operator()(bool wait_for = true) {
    unique_l lk(mutex_);
    cv_.wait(lk, [&]{ return !active_ || (fresh_ || !wait_for); });
    fresh_ = false;
    return data_;
  }

  void end_updates() { active_ = false; }
};
