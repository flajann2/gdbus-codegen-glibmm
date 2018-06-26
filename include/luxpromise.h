#include <condition_variable>
#include <mutex>
#include <thread>

/**
 */

namespace lux {
  /**
   * property     -- property-type promise, optional blocking
   * method       -- method-type promise, always block, parameters passed in aggeration
   * event        -- event-type promise, always blocks
   * notification -- master notifier that one of the above has changed or triggered
   */
  enum class Types { property, method, event, notification };

  using mutex_l = std::mutex;
  using unique_l = std::unique_lock<mutex_l>;
  using condvar = std::condition_variable;

  /**
   */
  template <typename Data, Types LType = Types::property> class Promise {

    Data data_;
    mutex_l mutex_;
    condvar cv_;
    bool fresh_ = false;
    bool active_ = true;

    template <typename LOCK> void wake_up(LOCK &lk) {
      fresh_ = true;
      lk.unlock();
      cv_.notify_all();
    }
    
    template <typename LOCK> void wake_down(LOCK &lk) {
      fresh_ = false;
      lk.unlock();
      cv_.notify_all();
    }

    template <typename LOCK>
    inline void raw_wait_up(LOCK &lk, bool wait_for = true) {
      switch (LType) {
      case Types::method:
      case Types::event:
      case Types::notification:
        wait_for = true; // force the wait regardless
      }
      cv_.wait(lk, [&] { return !active_ || (fresh_ || !wait_for); });
    }

    template <typename LOCK>
    inline void raw_wait_down(LOCK &lk) {
      cv_.wait(lk, [&] { return !active_ || !fresh_; });
    }

  public:
    Promise(Data data) : data_(data) {}

    Promise &operator=(Data &&update_data) {
      unique_l lk(mutex_);
      data_ = std::move(update_data);
      wake_up(lk);
      return *this;
    }

    Promise &operator=(Data &update_data) {
      unique_l lk(mutex_);
      data_ = update_data;
      wake_up(lk);
      return *this;
    }

    /// Will block if active not fresh
    template <typename LOCK>
    const Data &operator()(bool wait_for = true) {
      LOCK lk(mutex_);
      raw_wait_up(lk, wait_for);
      auto data = data_;
      wait_down(lk);
      return data;
    }

    inline void end_updates() { active_ = false; }
    inline bool is_active() { return active_; }

    /// Will wait while staying fresh.
    inline Promise<Data, LType> &wait_for_update() {
      unique_l lk(mutex_);
      raw_wait_up(lk);
      return *this;
    }
    
    /// Will wait while not staying fresh.
    inline Promise<Data, LType> &wait_for_downdate() {
      unique_l lk(mutex_);
      raw_wait_down(lk);
      return *this;
    }
  };
}
