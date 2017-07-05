#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

mutex m;
bool ready[5] = {0};
condition_variable cv;

void foo(int x) {
  for (int i = 0; i < 5; ++i) {
    unique_lock<mutex> lk(m);
    while (!ready[x])
      cv.wait(lk);
    cout << x << endl;
    ready[x] = 0;
  }
}

int main() {
  thread t1(foo, 1), t2(foo, 2), t3(foo, 3);
  for (int i = 0; i < 5; ++i) {
    //  cout << i;
    unique_lock<mutex> lk(m);
    for (int i = 1; i <= 3; ++i)
      ready[i] = 1;
    cv.notify_all();
    lk.unlock();
    // cout << 1;
    while (ready[1] || ready[2] || ready[3])
      ;
  }

  t1.join();
  t2.join();
  t3.join();

  return 0;
}