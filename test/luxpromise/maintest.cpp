#include <iostream>
#include <luxpromise.h>
#include <gtest/gtest.h>
#include <cstdlib>
#include "gmock/gmock.h"


constexpr int countdown = 1400;

int main() {
  LuxPromise<int> data(countdown);
 
  std::cout << "erste: setup " << std::endl;

  std::thread t1([&]() {
      for (auto i = countdown; i > 0; --i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      data = i;      
      }
      data.end_updates();
    });
  
  while (data() > 1) {
    std::cout << "cv got " << data() << std::endl;  
  }
  
  t1.join();
}
