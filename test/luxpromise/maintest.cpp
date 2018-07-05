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
void test_propertish(PIT& pit, int countdown) {
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


TEST_F(PromiseTests, test_property_mode) {
  test_propertish(data, countdown);
  std::thread t1([&]() {
    for (auto i = countdown; i > 0; --i) {
      std::this_thread::sleep_for(std::chrono::microseconds(1));
      data = i;
    }
    data.end_updates();
  });

  int data_snapshot;
  int last_data_snapshot = data() + 1;

  while ((data_snapshot = data()) > 1) {
    if (data.is_active()) {
      ASSERT_TRUE(data_snapshot <= last_data_snapshot);
    }
    last_data_snapshot = data_snapshot;
    data.fresh_wait();
  }

  t1.join();
}


template<typename PIT>
void test_non_property(PIT& pit, int meltdown) {
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

TEST_F(PromiseTests, test_method_mode) {
  test_non_property(method, meltdown);
}

TEST_F(PromiseTests, test_event_mode) {
  test_non_property(event, meltdown);
}

TEST_F(PromiseTests, test_notification_mode) {
  test_non_property(notif, meltdown);
}
