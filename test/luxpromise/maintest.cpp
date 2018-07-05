#include "gmock/gmock.h"
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <luxpromise.h>

constexpr int countdown = 16384;
constexpr int meltdown = 100000;

namespace lux {
  class PromiseTests : public ::testing::Test {
  protected:
    promise<int, ptype::property> data{countdown};
    promise<int, ptype::method> method{meltdown};
    promise<int, ptype::event> event{meltdown};
    promise<int, ptype::notification> notif{meltdown};

    void SetUp() override {}

    virtual void TearDown() {}
  };
}

using namespace lux;
using namespace std;

template<typename PIT>
void test_property_like(PIT& pit, int countdown) {
  std::thread t1([&]() {
    for (auto i = countdown; i > 0; --i) {
      std::this_thread::sleep_for(std::chrono::microseconds(1));
      pit = i;
    }
    pit.end_updates();
  });

  int snapshot;
  int last_snapshot = pit() + 1;

  while ((snapshot = pit()) > 1) {
    if (pit.is_active()) {
      ASSERT_TRUE(snapshot <= last_snapshot);
    }
    last_snapshot = snapshot;
    pit.fresh_wait();
  }

  t1.join();
}


template<typename PIT>
void test_method_like(PIT& pit, int meltdown) {
  std::thread t1([&]() {
      for (auto i = meltdown; i > 0; --i) {
      pit = i;
    }
    pit.end_updates();
  });

  int snapshot;
  int last_snapshot = pit();

  while ((snapshot = pit()) > 1) {
    if (pit.is_active()) {
      ASSERT_TRUE(last_snapshot - snapshot == 1);
    }
    last_snapshot = snapshot;
  }

  t1.join();
}

TEST_F(PromiseTests, test_property_mode) {
  test_property_like(data, countdown);
}

TEST_F(PromiseTests, test_method_mode) {
  test_method_like(method, meltdown);
}

TEST_F(PromiseTests, test_event_mode) {
  test_method_like(event, meltdown);
}

TEST_F(PromiseTests, test_notification_mode) {
  test_property_like(notif, meltdown);
}
