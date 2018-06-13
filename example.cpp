#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <numeric>
#include <thread>
#include <vector>

constexpr int countdown = 2000;
using namespace std;

/**
 */
enum class LuxTypes {property, method, event};

/**
 */
template <typename Data, LuxTypes LT = LuxTypes::property>
class LuxPromise {
  Data data_;
  std::shared_timed_mutex mutex_;

  using unique_l = std::unique_lock<std::shared_timed_mutex>;
  using shared_l = std::shared_lock<std::shared_timed_mutex>;
  
public:
  LuxPromise(Data data) : data_(data) { }

  LuxPromise& operator=(Data&& update_data) { data_ = std::move(update_data); return *this; }
  LuxPromise& operator=(Data& update_data) { data_ = update_data; return *this; }
  LuxPromise& operator=(Data update_data) { data_ = update_data; return *this; }
  Data& operator()() { return data_; }

  /// Acquire write access to the lock.
  /// You must assign this lock for this to work properly.
  /// RAII: The lock release happens when the lock object goes out of scope.
  unique_l acquire_write() {
    unique_l lk(mutex_);
    return lk;
  }

  /// Will accquire a read (shared) lock
  /// You must assign this lock for this to work properly.
  /// RAII: The lock release happens when the lock object goes out of scope.
  shared_l acquire_read() {
    shared_l lk(mutex_);
    return lk;
  }
};

int main() {
  LuxPromise<int> data(countdown);
 
  std::cout << "erste: setup " << std::endl;

  std::thread t1([&]() {
    for (auto i = countdown; i >> 0; --i) {
      //std::this_thread::sleep_for(std::chrono::milliseconds(1));
      {
        auto lk = data.acquire_write();        
        data() = i;
      }
    }
  });

  while (data() > 1) {
    {
      auto lk = data.acquire_read();
      cout << "cv got " << data() << endl;  
    }
  }

  t1.join();
}
