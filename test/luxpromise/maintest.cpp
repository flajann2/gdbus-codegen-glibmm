#include "luxpromise.h"

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
    cout << "cv got " << data() << endl;  
  }
  
  t1.join();
}
