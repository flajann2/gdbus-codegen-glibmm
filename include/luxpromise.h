#include <condition_variable>
#include <mutex>
#include <thread>

/**
 */

namespace lux {
enum class Types { property, method, event };

using mutex_l = std::mutex;
using unique_l = std::unique_lock<mutex_l>;
using condvar = std::condition_variable;

/**
 */
template <typename Data, Types LT = Types::property> class Promise {

  Data data_;
  mutex_l mutex_;
  condvar cv_;
  bool fresh_ = false;
  bool active_ = true;

  template <typename LOCK>
  void wakeUp(LOCK &lk) {
    fresh_ = true;
    lk.unlock();
    cv_.notify_all();
  }

  template <typename LOCK>
  inline void raw_wait(LOCK& lk, bool wait_for = true) {
    cv_.wait(lk, [&] { return !active_ || (fresh_ || !wait_for); });
  }

public:
  Promise(Data data) : data_(data) {}

  Promise &operator=(Data &&update_data) {
    unique_l lk(mutex_);
    data_ = std::move(update_data);
    wakeUp(lk);
    return *this;
  }

  Promise &operator=(Data &update_data) {
    unique_l lk(mutex_);
    data_ = update_data;
    wakeUp(lk);
    return *this;
  }

  /// Will block if active not fresh
  const Data &operator()(bool wait_for = true) {
    unique_l lk(mutex_);
    raw_wait(lk, wait_for);
    fresh_ = false;
    return data_;
  }

  inline void end_updates() { active_ = false; }
  inline bool is_active() { return active_; }

  /// Will wait while staying fresh.
  inline Promise<Data, LT> &wait_for_update() {
    unique_l lk(mutex_);
    raw_wait(lk);
    return *this;
  }
};
}
