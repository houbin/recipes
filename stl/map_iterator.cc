#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;
vector<int> key_set;
map<int, int> test_map;

struct StartThreadState {
  void (*user_function)(void*);
  void* arg;
};

static void* StartThreadWrapper(void* arg) {
  StartThreadState* state = reinterpret_cast<StartThreadState*>(arg);
  state->user_function(state->arg);
  delete state;
  return NULL;
}

void start_thread(void(*function)(void *arg), void *arg) {
  StartThreadState *state = new StartThreadState;
  state->user_function = function;
  state->arg = arg;
  pthread_t t;
  pthread_create(&t, NULL, &StartThreadWrapper,state);
}

void print_map(void *arg) {
  while (true) {
    if (key_set.empty()) {
      cout << "key_set is empty, wait 2s"<< endl;
      sleep(2);
      continue;
    }
    int i = rand() % (key_set.size());
    int key = key_set[i];
    map<int, int>::iterator iter = test_map.find(key);
    if (iter != test_map.end())
    {
      cout << "print_map: key: " << iter->first << ", value: " << iter->second << ", and wait 2s"<< endl;
      sleep(2);
    } else {
      cout << "print_map, can't find " << key << endl;
      sleep(1);
    }
  }

  return;
}

void insert_map(void *arg) {
  while (true) {
    int i = rand() % 10000000;
    cout << "test_map push_back, key " << i << ", value " << i << endl;
    test_map[i] = i;
    key_set.push_back(i);
    usleep(50000);
  }

  return;
}

int main() {
  int ret = 0;

  start_thread(&print_map, NULL);
  start_thread(&insert_map, NULL);


  sleep(100);

  return 0;
}
