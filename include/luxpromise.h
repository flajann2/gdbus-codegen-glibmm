#include <condition_variable>
#include <mutex>
#include <thread>

/**
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

  /**
   */
  template <typename Data, ptype LType = ptype::property> class promise {
    Data data_;
    mutex_l mutex_;
    condvar cv_;
    bool fresh_ = false;
    bool active_ = true;

    void wake_down(unique_l &lk) {
      fresh_ = false;
      lk.unlock();
      cv_.notify_all();
    }

    void wake_up(unique_l &lk) {
      
      fresh_ = true;
      lk.unlock();
      cv_.notify_all();
    }

    inline void raw_wait_up(unique_l &lk, bool wait_for = true) {
      switch (LType) {
      case ptype::method:
      case ptype::event:
      case ptype::notification:
        wait_for = true; // force the wait regardless
      }
      cv_.wait(lk, [&] { return !active_ || (fresh_ || !wait_for); });
    }

    inline void raw_wait_down(unique_l &lk) {
      cv_.wait(lk, [&] { return !active_ || !fresh_; });
    }

  public:
    explicit promise() = default;
    promise(const promise&) = delete;
    explicit promise(Data data) : data_(data) {}

    promise &operator=(Data &&update_data) {
      unique_l lk(mutex_);
      raw_wait_down(lk);
      data_ = std::move(update_data);
      wake_up(lk);
      return *this;
    }

    promise &operator=(Data &update_data) {
      unique_l lk(mutex_);
      raw_wait_down(lk);
      data_ = update_data;
      wake_up(lk);
      return *this;
    }

    /// Will block if active not fresh
    /// Returns a copy of the data snapshot, though
    /// it is entirely possible the copy will be elided.
    const Data operator()(bool wait_for = true) {
      unique_l lk(mutex_);
      raw_wait_up(lk, wait_for);
      auto snapshot_data = data_;
      wake_down(lk);
      return snapshot_data;
    }

    inline void end_updates() { active_ = false; }
    inline bool is_active() { return active_; }

    /// Will wait while staying fresh.
    inline promise<Data, LType> &wait_for_update() {
      unique_l lk(mutex_);
      raw_wait_up(lk);
      return *this;
    }

    /// Will wait while not staying fresh.
    inline promise<Data, LType> &wait_for_downdate() {
      unique_l lk(mutex_);
      raw_wait_down(lk);
      return *this;
    }
  };
}
