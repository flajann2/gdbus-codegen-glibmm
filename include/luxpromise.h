#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream> // TODO: for debugging. remove this line.

/** Please see the README.org for the details of the
 * locking / waiting semantics.
 */

namespace lux {
  /**
   * property     -- property-type promise, optional blocking
   * method       -- method-type promise, always block, parameters passed in
   * aggeration
   * event        -- event-type promise, always blocks
   * notification -- master notifier that one of the above has changed or
   * triggered
   */
  enum class ptype { property,
                     method,
                     event,
                     notification };

  using mutex_l = std::mutex;
  using unique_l = std::unique_lock<mutex_l>;
  using condvar = std::condition_variable;
  using notify_ob = bool;
  using namespace std; // TODO: for debugging. Remove

  /**
   */
  template <typename Data, ptype LType = ptype::property> class promise {
    Data data_;
    mutex_l mutex_;
    condvar cv_;
    bool fresh_ = false;
    bool active_ = true;

    void stale_wake_up(unique_l &lk) {
      fresh_ = false;
      lk.unlock();
      cv_.notify_all();
    }

    void fresh_wake_up(unique_l &lk) {
      fresh_ = true;
      lk.unlock();
      cv_.notify_all();
    }

    inline void wait_for_fresh(unique_l &lk, bool wait_for = true) {
      //cout << "wait_for_fresh("  << (int) LType << "): active = " << active_ << " fresh " << fresh_ << " wait_for " << wait_for << endl;
      switch (LType) {
      case ptype::method:
      case ptype::event:
      case ptype::notification:
        wait_for = true; // force the wait regardless
      }
      cv_.wait(lk, [&] { return !active_ || (fresh_ || !wait_for); });
    }

    inline void wait_for_stale(unique_l &lk) {
      //cout << "wait_for_stale(" << (int) LType << "): active = " << active_ << " fresh " << fresh_ << endl;
      cv_.wait(lk, [&] { return !active_
            || (LType == ptype::property) || (LType == ptype::notification)
            || !fresh_; });
    }

  public:
    explicit promise() = default;
    promise(const promise&) = delete;
    explicit promise(Data data) : data_(data) {}

    promise &operator=(Data &&update_data) {
      unique_l lk(mutex_);
      wait_for_stale(lk);
      data_ = std::move(update_data);
      fresh_wake_up(lk);
      return *this;
    }

    promise &operator=(Data &update_data) {
      unique_l lk(mutex_);
      wait_for_stale(lk);
      data_ = update_data;
      fresh_wake_up(lk);
      return *this;
    }

    /// Will block if active not fresh
    /// Returns a copy of the data snapshot, though
    /// it is entirely possible the copy will be elided.
    const Data operator()(bool wait_for = true) {
      unique_l lk(mutex_);
      wait_for_fresh(lk, wait_for);
      auto snapshot_data = data_;
    stale_wake_up(lk);
      return snapshot_data;
    }

    inline void end_updates() { active_ = false; }
    inline bool is_active() { return active_; }

    /// Will wait while staying fresh.
    inline promise<Data, LType> &fresh_wait() {
      unique_l lk(mutex_);
      wait_for_fresh(lk);
      return *this;
    }

    /// Will wait while not staying fresh.
    inline promise<Data, LType> &stale_wait() {
      unique_l lk(mutex_);
      wait_for_stale(lk);
      return *this;
    }
  };
}
