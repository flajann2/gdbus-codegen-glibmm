#include "gmock/gmock.h"
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <luxpromise.h>

constexpr int countdown = 28000;

namespace lux {
  class PromiseTests : public ::testing::Test {
  protected:
    Promise<int, Types::property> data{countdown};
    Promise<int, Types::method> method{countdown};
    Promise<int, Types::event> event{countdown};
    Promise<int, Types::notification> notif{countdown};

    void SetUp() override {}

    virtual void TearDown() {}
  };
}

using namespace lux;

TEST_F(PromiseTests, test_property_mode) {

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
    data.wait_for_update();
  }

  t1.join();
}

TEST_F(PromiseTests, test_method_mode) {

  std::thread t1([&]() {
    for (auto i = countdown; i > 0; --i) {
      std::this_thread::sleep_for(std::chrono::microseconds(1));
      method = i;
    }
    method.end_updates();
  });

  int meth_snapshot;
  int last_meth_snapshot = data() + 1;

  while ((meth_snapshot = method()) > 1) {
    if (method.is_active()) {
      ASSERT_TRUE(meth_snapshot < last_meth_snapshot);
    }
    last_meth_snapshot = meth_snapshot;
  }

  t1.join();
}
