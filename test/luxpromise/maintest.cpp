#include "gmock/gmock.h"
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <luxpromise.h>

constexpr int countdown = 28000;

namespace lux {
class PromiseTests : public ::testing::Test {
protected:
  Promise<int> data{countdown};

  void SetUp() override {}

  virtual void TearDown() {}
};
}

using namespace lux;

TEST_F(PromiseTests, test_basic_functionality) {

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
